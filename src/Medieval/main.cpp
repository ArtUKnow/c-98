#include "../../include/medieval.h"
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <random>

constexpr size_t MAP_WIDTH = 100;
constexpr size_t MAP_HEIGHT = 100;
constexpr size_t NPC_COUNT = 50;
constexpr size_t GAME_DURATION_SECONDS = 30;

std::mutex mtx;
std::condition_variable cv;
bool stop_game = false;
set_t array;

void move_npc(std::shared_ptr<NPC> npc, size_t move_distance) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_x(0, MAP_WIDTH - 1);
    std::uniform_int_distribution<> dis_y(0, MAP_HEIGHT - 1);

    int new_x = std::clamp(npc->x + (dis_x(gen) - MAP_WIDTH / 2), 0, static_cast<int>(MAP_WIDTH - 1));
    int new_y = std::clamp(npc->y + (dis_y(gen) - MAP_HEIGHT / 2), 0, static_cast<int>(MAP_HEIGHT - 1));

    npc->x = new_x;
    npc->y = new_y;
}

void npc_movement_thread() {
    while (!stop_game) {
        std::unique_lock<std::mutex> lock(mtx);
        for (auto& npc : array) {
            size_t move_distance = 0;
            switch (npc->type) {
                case OrcType:
                    move_distance = 20;
                    break;
                case KnightType:
                    move_distance = 30;
                    break;
                case BearType:
                    move_distance = 5;
                    break;
                default:
                    break;
            }
            move_npc(npc, move_distance);
        }
        cv.wait_for(lock, std::chrono::seconds(1));
    }
}

void combat_thread() {
    while (!stop_game) {
        std::unique_lock<std::mutex> lock(mtx);
        set_t dead_list = fight(array, 10);
        for (auto& d : dead_list) {
            array.erase(d);
        }
        cv.wait_for(lock, std::chrono::seconds(1));
    }
}

void print_map_thread() {
    while (!stop_game) {
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "Map:" << std::endl;
        std::cout << array;
        cv.wait_for(lock, std::chrono::seconds(1));
    }
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "Generating NPCs..." << std::endl;
    for (size_t i = 0; i < NPC_COUNT; ++i) {
        array.insert(factory(NpcType(std::rand() % 3 + 1),
                             std::rand() % MAP_WIDTH,
                             std::rand() % MAP_HEIGHT));
    }

    std::thread movement_thread(npc_movement_thread);
    std::thread combat_thread(combat_thread);
    std::thread print_thread(print_map_thread);

    std::this_thread::sleep_for(std::chrono::seconds(GAME_DURATION_SECONDS));
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop_game = true;
    }
    cv.notify_all();

    movement_thread.join();
    combat_thread.join();
    print_thread.join();

    std::cout << "Survivors:" << std::endl;
    std::cout << array;

    return 0;
}
