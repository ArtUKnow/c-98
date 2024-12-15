#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <memory>
#include <thread>
#include <random>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <chrono>

static const int MAP_WIDTH = 100;
static const int MAP_HEIGHT = 100;

enum NpcType { 
    Unknown = 0, 
    OrcType = 1, 
    KnightType = 2, 
    BearType = 3 
};

std::string npcTypeToString(NpcType type) {
    switch (type) {
    case OrcType: return "Orc";
    case KnightType: return "Knight";
    case BearType: return "Bear";
    default: return "Unknown";
    }
}

struct NPC {
    NpcType type;
    int x, y;
    bool dead{false};

    NPC(NpcType t, int x_, int y_) : type(t), x(x_), y(y_) {}
};

std::shared_ptr<NPC> createNPC(NpcType type, int x, int y) {
    return std::make_shared<NPC>(type, x, y);
}

static std::set<std::shared_ptr<NPC>> npcs;
static std::vector<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> fightQueue;
static std::shared_mutex npcsMutex;
static std::mutex fightQueueMutex;
static std::condition_variable fightQueueCV;
static std::atomic<bool> gameRunning{true};

int get_move_distance(NpcType type) {
    switch (type) {
    case OrcType: return 20;
    case KnightType: return 30;
    case BearType: return 5;
    default: return 0;
    }
}

void moveNPC(std::shared_ptr<NPC> npc) {
    if (!npc || npc->dead) return;

    int moveDist = get_move_distance(npc->type);
    int dx = (std::rand() % (2 * moveDist + 1)) - moveDist;
    int dy = (std::rand() % (2 * moveDist + 1)) - moveDist;

    npc->x = std::clamp(npc->x + dx, 0, MAP_WIDTH - 1);
    npc->y = std::clamp(npc->y + dy, 0, MAP_HEIGHT - 1);
}

void movementThreadFunc() {
    while (gameRunning) {
        {
            std::unique_lock lock(npcsMutex);
            for (auto& npc : npcs) {
                if (!npc->dead) moveNPC(npc);
            }

            for (auto it1 = npcs.begin(); it1 != npcs.end(); ++it1) {
                auto npc1 = *it1;
                if (npc1->dead) continue;

                for (auto it2 = std::next(it1); it2 != npcs.end(); ++it2) {
                    auto npc2 = *it2;
                    if (npc2->dead) continue;

                    int dx = npc1->x - npc2->x;
                    int dy = npc1->y - npc2->y;
                    if (dx * dx + dy * dy <= 100) {
                        std::lock_guard lock(fightQueueMutex);
                        fightQueue.emplace_back(npc1, npc2);
                        fightQueueCV.notify_one();
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void fightThreadFunc() {
    while (gameRunning) {
        std::unique_lock<std::mutex> lock(fightQueueMutex);
        fightQueueCV.wait(lock, [] { return !fightQueue.empty() || !gameRunning; });

        if (!gameRunning) break;

        auto [attacker, defender] = fightQueue.back();
        fightQueue.pop_back();
        lock.unlock();

        int attackRoll = std::rand() % 6 + 1;
        int defenseRoll = std::rand() % 6 + 1;

        std::unique_lock npcsLock(npcsMutex);
        if (!attacker->dead && !defender->dead) {
            if (attackRoll > defenseRoll) defender->dead = true;
            else attacker->dead = true;
        }
    }
}

void printMapThreadFunc() {
    while (gameRunning) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::shared_lock lock(npcsMutex);
            std::cout << "Map State:\n";
            for (const auto& npc : npcs) {
                if (!npc->dead) {
                    std::cout << npcTypeToString(npc->type)
                              << " (" << npc->x << "," << npc->y << ")\n";
                }
            }
            std::cout << "--------------------------\n";
        }
    }
}

int main() {
    std::srand(std::time(nullptr));
    {
        std::unique_lock lock(npcsMutex);
        for (int i = 0; i < 50; ++i) {
            NpcType type = static_cast<NpcType>(std::rand() % 3 + 1);
            int x = std::rand() % MAP_WIDTH;
            int y = std::rand() % MAP_HEIGHT;
            npcs.insert(createNPC(type, x, y));
        }
    }

    std::thread movementThread(movementThreadFunc);
    std::thread fightThread(fightThreadFunc);
    std::thread printMapThread(printMapThreadFunc);

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(30s);

    gameRunning = false;
    fightQueueCV.notify_all();

    if (movementThread.joinable()) movementThread.join();
    if (fightThread.joinable()) fightThread.join();
    if (printMapThread.joinable()) printMapThread.join();

    std::cout << "\n--- Survivors ---\n";
    {
        std::shared_lock lock(npcsMutex);
        for (const auto& npc : npcs) {
            if (!npc->dead) {
                std::cout << npcTypeToString(npc->type)
                          << " (" << npc->x << "," << npc->y << ")\n";
            }
        }
    }

    return 0;
}
