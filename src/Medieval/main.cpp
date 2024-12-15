#include "../../include/medieval.h"

static const int MAP_WIDTH  = 100;
static const int MAP_HEIGHT = 100;

static std::mt19937 rng(std::random_device{}());
static std::set<std::shared_ptr<NPC>> npcs;

static const std::unordered_map<NpcType, std::string> npcTypeToStringMap = {
    {OrcType, "Orc"},
    {KnightType, "Knight"},
    {BearType, "Bear"},
    {Unknown, "Unknown"}
};
std::string npcTypeToString(NpcType type) {
    auto it = npcTypeToStringMap.find(type);
    if (it != npcTypeToStringMap.end()) {
        return it->second;
    }
    return "Unknown";
}

struct NPCWithLife : public NPC
{
    bool dead{false};
    using NPC::NPC;
    bool accept(std::shared_ptr<NPC> other) override {
        return true;
    }
    void print() override {
        std::cout << "NPCWithLife: Type=" << npcTypeToString(type) << " Pos=(" << x << "," << y << ")" << std::endl;
    }
};

std::shared_ptr<NPCWithLife> factory_with_life(NpcType type, int x, int y)
{
    std::shared_ptr<NPCWithLife> result;
    switch (type)
    {
    case OrcType:
        result = std::make_shared<NPCWithLife>(OrcType, x, y);
        break;
    case KnightType:
        result = std::make_shared<NPCWithLife>(KnightType, x, y);
        break;
    case BearType:
        result = std::make_shared<NPCWithLife>(BearType, x, y);
        break;
    default:
        result = std::make_shared<NPCWithLife>(Unknown, x, y);
        break;
    }
    if (result)
        result->subscribe(TextObserver::get());
    return result;
}
static std::shared_mutex npcsMutex;
static std::mutex fightQueueMutex;
static std::condition_variable fightQueueCV;
static std::vector<std::pair<std::shared_ptr<NPCWithLife>, std::shared_ptr<NPCWithLife>>> fightQueue;
static std::atomic<bool> gameRunning{true};
int get_move_distance(NpcType type) {
    switch (type) {
    case OrcType:    return 20;
    case KnightType: return 30;
    case BearType:   return 5;
    default:         return 0;
    }
}
int get_kill_distance(NpcType) {
    return 10;
}
void move_npc(std::shared_ptr<NPCWithLife> npc)
{
    if (!npc || npc->dead) return;
    int moveDist = get_move_distance(npc->type);
    if (moveDist == 0) return;
    int dx = (std::rand() % (2 * moveDist + 1)) - moveDist;
    int dy = (std::rand() % (2 * moveDist + 1)) - moveDist;
    int newX = npc->x + dx;
    int newY = npc->y + dy;
    
    if (newX < 0) newX = 0;
    if (newX >= MAP_WIDTH)  newX = MAP_WIDTH - 1;
    if (newY < 0) newY = 0;
    if (newY >= MAP_HEIGHT) newY = MAP_HEIGHT - 1;

    npc->x = newX;
    npc->y = newY;
}

void movementThreadFunc()
{
    using namespace std::chrono_literals;
    while (gameRunning.load()) {
        {
            std::unique_lock lock(npcsMutex);
            for (auto &npc_ptr : npcs) {
                auto npc = std::static_pointer_cast<NPCWithLife>(npc_ptr);
                if (npc && !npc->dead) {
                    move_npc(npc);
                }
            }
            std::vector<std::shared_ptr<NPCWithLife>> aliveNpcs;
            aliveNpcs.reserve(npcs.size());
            for (auto &npc_ptr : npcs) {
                auto npc = std::static_pointer_cast<NPCWithLife>(npc_ptr);
                if (npc && !npc->dead) {
                    aliveNpcs.push_back(npc);
                }
            }
            for (size_t i = 0; i < aliveNpcs.size(); ++i) {
                for (size_t j = i + 1; j < aliveNpcs.size(); ++j) {
                    auto &a = aliveNpcs[i];
                    auto &b = aliveNpcs[j];
                    if (!a->dead && !b->dead) {
                        double dist2 = (a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y);
                        double killDist = 10.0;
                        if (dist2 <= killDist * killDist) {
                            fightQueueMutex.lock();
                            fightQueue.push_back({a, b});
                            fightQueueMutex.unlock();
                            fightQueueCV.notify_one();
                        }
                    }
                }
            }
        }
        std::this_thread::sleep_for(200ms);
    }
}
void fightThreadFunc()
{
    while (gameRunning.load()) {
        std::unique_lock<std::mutex> lk(fightQueueMutex);
        fightQueueCV.wait(lk, [] { return !fightQueue.empty() || !gameRunning.load(); });
        if (!gameRunning.load()) {
            break;
        }
        auto task = fightQueue.back();
        fightQueue.pop_back();
        lk.unlock();

        auto attacker = task.first;
        auto defender = task.second;

        if (!attacker || !defender)
            continue;
        {
            std::shared_lock lock(npcsMutex);
            if (attacker->dead || defender->dead)
                continue;
        }
        int attack_roll = std::rand() % 6 + 1;
        int defense_roll = std::rand() % 6 + 1;
        std::unique_lock lock(npcsMutex);
        if (!attacker->dead && !defender->dead) {
            if (attack_roll > defense_roll) {
                defender->dead = true;
                attacker->fight_notify(defender, true);
            } else if (defense_roll > attack_roll) {
                attacker->dead = true;
                defender->fight_notify(attacker, true);
            }
        }
    }
}

int main()
{
    std::srand(unsigned(std::time(nullptr)));
    {
        std::unique_lock lock(npcsMutex);
        for (size_t i = 0; i < 50; ++i)
        {
            NpcType t = static_cast<NpcType>(std::rand() % 3 + 1);
            int x = std::rand() % MAP_WIDTH;
            int y = std::rand() % MAP_HEIGHT;
            auto npc = factory_with_life(t, x, y);
            npcs.insert(npc);
        }
    }
    std::thread movementThread(movementThreadFunc);
    std::thread fightThread(fightThreadFunc);

    using namespace std::chrono_literals;
    auto start_time = std::chrono::steady_clock::now();
    auto duration = 30s;

    while (true) {
        auto now = std::chrono::steady_clock::now();
        if (now - start_time >= duration) {
            gameRunning.store(false);

            fightQueueCV.notify_one();
            break;
        }
        {
            std::shared_lock lock(npcsMutex);
            std::lock_guard<std::mutex> coutLockGuard(fightQueueMutex);
            std::cout << "=== MAP STATE ===\n";
            for (auto &npc_ptr : npcs) {
                auto npc = std::static_pointer_cast<NPCWithLife>(npc_ptr);
                if (!npc->dead) {
                    std::cout << "Type=" << npcTypeToString(npc->type)
                              << " Pos=(" << npc->x << "," << npc->y << ")\n";
                }
            }
            std::cout << "=================\n\n";
        }

        std::this_thread::sleep_for(1s);
    }

    if (movementThread.joinable()) movementThread.join();
    if (fightThread.joinable()) fightThread.join();
    {
        std::shared_lock lock(npcsMutex);
        std::cout << "\n--- Survivors ---\n";
        for (auto &npc_ptr : npcs) {
            auto npc = std::static_pointer_cast<NPCWithLife>(npc_ptr);
            if (!npc->dead) {
                std::cout << "Type=" << npcTypeToString(npc->type)
                          << " Pos=(" << npc->x << "," << npc->y << ")\n";
            }
        }
        std::cout << "-----------------\n";
    }
    return 0;
}
