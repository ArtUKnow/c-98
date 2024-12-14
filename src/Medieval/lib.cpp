#include "../../include/medieval.h"

Orc::Orc(int x, int y) : NPC(OrcType, x, y) {}
Orc::Orc(std::istream &is) : NPC(OrcType, is) {}

Knight::Knight(int x, int y) : NPC(KnightType, x, y) {}
Knight::Knight(std::istream &is) : NPC(KnightType, is) {}

Bear::Bear(int x, int y) : NPC(BearType, x, y) {}
Bear::Bear(std::istream &is) : NPC(BearType, is) {}

NPC::NPC(NpcType t, int _x, int _y) : type(t), x(_x), y(_y) {}
NPC::NPC(NpcType t, std::istream &is) : type(t)
{
    is >> x;
    is >> y;
}

void Orc::print()
{
    std::cout << *this;
}

void Orc::save(std::ostream &os)
{
    os << OrcType << std::endl;
    NPC::save(os);
}

bool Orc::accept(std::shared_ptr<NPC> other)
{
    if (other->type == BearType)
    {
        fight_notify(other, true);
        return true;
    }
    else if (other->type == KnightType)
    {
        fight_notify(other, false);
        return false;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, Orc &orc)
{
    os << "Orc: " << *static_cast<NPC *>(&orc) << std::endl;
    return os;
}

void Knight::print()
{
    std::cout << *this;
}

void Knight::save(std::ostream &os)
{
    os << KnightType << std::endl;
    NPC::save(os);
}

bool Knight::accept(std::shared_ptr<NPC> other)
{
    if (other->type == OrcType)
    {
        fight_notify(other, true);
        return true;
    }
    else if (other->type == BearType)
    {
        fight_notify(other, false);
        return false;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, Knight &knight)
{
    os << "Knight: " << *static_cast<NPC *>(&knight) << std::endl;
    return os;
}

void Bear::print()
{
    std::cout << *this;
}

void Bear::save(std::ostream &os)
{
    os << BearType << std::endl;
    NPC::save(os);
}

bool Bear::accept(std::shared_ptr<NPC> other)
{
    if (other->type == KnightType)
    {
        fight_notify(other, true);
        return true;
    }
    else if (other->type == OrcType)
    {
        fight_notify(other, false);
        return false;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, Bear &bear)
{
    os << "Bear: " << *static_cast<NPC *>(&bear) << std::endl;
    return os;
}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer)
{
   observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win)
{
    for (auto &o : observers)
        o->on_fight(shared_from_this(), defender, win);
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance) const
{
    if (std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <= std::pow(distance, 2))
        return true;
    else
        return false;
}

void NPC::save(std::ostream &os)
{
    os << x << std::endl;
    os << y << std::endl;
}

std::ostream &operator<<(std::ostream &os, NPC &npc)
{
    os << "{ x:" << npc.x << ", y:" << npc.y << "} ";
    return os;
}
