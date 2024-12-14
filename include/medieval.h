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
using set_t = std::set<std::shared_ptr<NPC>>;

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

struct NPC : public std::enable_shared_from_this<NPC>
{
    NpcType type;
    int x{0};
    int y{0};
    std::vector<std::shared_ptr<IFightObserver>> observers;

    NPC(NpcType t, int _x, int _y);
    NPC(NpcType t, std::istream &is);

    void subscribe(std::shared_ptr<IFightObserver> observer);
    void fight_notify(const std::shared_ptr<NPC> defender, bool win);
    virtual bool is_close(const std::shared_ptr<NPC> &other, size_t distance) const;
    virtual bool accept(std::shared_ptr<NPC> other) = 0;
    virtual void print() = 0;
    virtual void save(std::ostream &os);
    friend std::ostream &operator<<(std::ostream &os, NPC &npc);
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

#endif
