#include "../../include/medieval.h"
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <chrono>
#include <atomic>
#include <cstdlib>
#include <ctime>

constexpr int MAP_WIDTH = 100;
constexpr int MAP_HEIGHT = 100;
constexpr int SIMULATION_DURATION = 30; // seconds
constexpr size_t NUM_NPCS = 50;

std::mutex cout_mutex;
std::shared_mutex npc_mutex;
std::atomic<bool> running{true};

/*
Таблица убиваемости:

Кто нагоняет: Орк
Расстояние хода: 20
Расстояние при котором он может убить: 10

Кто нагоняет: Рыцарь
Расстояние хода: 30
Расстояние при котором он может убить: 10

Кто нагоняет: Медведь
Расстояние хода: 5
Расстояние при котором он может убить: 10
*/

void print_map(const set_t &npcs) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Map state:\n";
    for (const auto &npc : npcs) {
        std::cout << "NPC (Type: " << npc->type << ", x: " << npc->x << ", y: " << npc->y << ")\n";
    }
}

void move_npcs(set_t &npcs, std::vector<std::function<void()>> &fight_tasks) {
    while (running) {
        {
            std::unique_lock<std::shared_mutex> lock(npc_mutex);
            for (const auto &npc : npcs) {
                if (!npc) continue;

                int move_distance = 0;
                switch (npc->type) {
                case OrcType: move_distance = 20; break;
                case KnightType: move_distance = 30; break;
                case BearType: move_distance = 5; break;
                default: continue;
                }

                npc->x = std::clamp(npc->x + (std::rand() % (2 * move_distance + 1)) - move_distance, 0, MAP_WIDTH);
                npc->y = std::clamp(npc->y + (std::rand() % (2 * move_distance + 1)) - move_distance, 0, MAP_HEIGHT);

                for (const auto &other : npcs) {
                    if (npc == other || !other) continue;

                    int kill_distance = (npc->type == OrcType || npc->type == KnightType || npc->type == BearType) ? 10 : 0;

                    if (npc->is_close(other, kill_distance)) {
                        fight_tasks.emplace_back([npc, other] {
                            int attacker_roll = std::rand() % 6 + 1;
                            int defender_roll = std::rand() % 6 + 1;
                            if (attacker_roll > defender_roll) {
                                std::lock_guard<std::mutex> lock(cout_mutex);
                                std::cout << "NPC (Type: " << npc->type << ") killed NPC (Type: " << other->type << ")\n";
                            }
                        });
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void process_fights(std::vector<std::function<void()>> &fight_tasks) {
    while (running) {
        {
            std::unique_lock<std::shared_mutex> lock(npc_mutex);
            for (auto &task : fight_tasks) {
                task();
            }
            fight_tasks.clear();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    set_t npcs;
    for (size_t i = 0; i < NUM_NPCS; ++i) {
        npcs.insert(factory(NpcType(std::rand() % 3 + 1), std::rand() % MAP_WIDTH, std::rand() % MAP_HEIGHT));
    }

    std::vector<std::function<void()>> fight_tasks;

    std::thread movement_thread(move_npcs, std::ref(npcs), std::ref(fight_tasks));
    std::thread fight_thread(process_fights, std::ref(fight_tasks));

    auto start_time = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start_time < std::chrono::seconds(SIMULATION_DURATION)) {
        print_map(npcs);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    running = false;
    movement_thread.join();
    fight_thread.join();

    std::cout << "Simulation ended. Survivors:\n";
    print_map(npcs);

    return 0;
}
