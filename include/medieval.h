#ifndef MEDIEVAL_H
#define MEDIEVAL_H

#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <random>
#include <fstream>
#include <set>
#include <math.h>

struct NPC;
struct Orc;
struct Knight;
struct Bear;

struct NPCComparator {
    bool operator()(const std::shared_ptr<NPC>& lhs, const std::shared_ptr<NPC>& rhs) const {
        if (!lhs || !rhs) {
            return lhs < rhs; // nullptr должен быть "меньше"
        }
        return *lhs < *rhs;
    }
};

using set_t = std::set<std::shared_ptr<NPC>, NPCComparator>;

enum NpcType
{
    Unknown = 0,
    OrcType = 1,
    KnightType = 2,
    BearType = 3
};

struct IFightObserver {
    virtual void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) = 0;
};

struct NPC : public std::enable_shared_from_this<NPC> {
    std::string name;  // Уникальное имя
    NpcType type;
    int x{0};
    int y{0};
    std::vector<std::shared_ptr<IFightObserver>> observers;

    NPC(NpcType t, int _x, int _y, const std::string& _name);
    NPC(NpcType t, std::istream &is);

    void subscribe(std::shared_ptr<IFightObserver> observer);
    void fight_notify(const std::shared_ptr<NPC> defender, bool win);
    virtual bool is_close(const std::shared_ptr<NPC> &other, size_t distance) const;
    virtual bool accept(std::shared_ptr<NPC> other) = 0;
    virtual void print() = 0;
    virtual void save(std::ostream &os);
    friend std::ostream &operator<<(std::ostream &os, NPC &npc);

    bool operator==(const NPC &other) const;
    bool operator<(const NPC &other) const;
};

struct Orc : public NPC
{
    Orc(int x, int y);
    Orc(std::istream &is);

    void print() override;
    void save(std::ostream &os) override;
    bool accept(std::shared_ptr<NPC> other) override;

    friend std::ostream &operator<<(std::ostream &os, Orc &orc);
};

struct Knight : public NPC
{
    Knight(int x, int y);
    Knight(std::istream &is);
    void print() override;
    void save(std::ostream &os) override;
    bool accept(std::shared_ptr<NPC> other) override;
    friend std::ostream &operator<<(std::ostream &os, Knight &knight);
};

struct Bear : public NPC
{
    Bear(int x, int y);
    Bear(std::istream &is);
    void print() override;
    void save(std::ostream &os) override;
    bool accept(std::shared_ptr<NPC> other) override;
    friend std::ostream &operator<<(std::ostream &os, Bear &bear);
};

class TextObserver : public IFightObserver
{
private:
    TextObserver(){};

public:
    static std::shared_ptr<IFightObserver> get()
    {
        static TextObserver instance;
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override
    {
        if (win)
        {
            std::cout << std::endl
                      << "Murder --------" << std::endl;
            attacker->print();
            defender->print();
        }
    }
};

std::shared_ptr<NPC> factory(std::istream &is);
std::shared_ptr<NPC> factory(NpcType type, int x, int y);
void save(const set_t &array, const std::string &filename);
set_t load(const std::string &filename);
set_t fight(const set_t &array, size_t distance);

std::ostream &operator<<(std::ostream &os, const set_t &array);

#endif
