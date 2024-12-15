#include "../../include/medieval.h"

NPC::NPC(NpcType t, int _x, int _y) : type(t), x(_x), y(_y) {}
NPC::NPC(NpcType t, std::istream &is) : type(t)
{
    is >> x;
    is >> y;
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
    return std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <= std::pow(distance, 2);
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

bool NPC::operator==(const NPC &other) const
{
    return type == other.type && x == other.x && y == other.y;
}

bool NPC::operator<(const NPC &other) const {
    if (type != other.type) return type < other.type;
    if (x != other.x) return x < other.x;
    return y < other.y;
}

Orc::Orc(int x, int y) : NPC(OrcType, x, y) {}
Orc::Orc(std::istream &is) : NPC(OrcType, is) {}

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

Knight::Knight(int x, int y) : NPC(KnightType, x, y) {}
Knight::Knight(std::istream &is) : NPC(KnightType, is) {}

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

Bear::Bear(int x, int y) : NPC(BearType, x, y) {}
Bear::Bear(std::istream &is) : NPC(BearType, is) {}

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

std::shared_ptr<NPC> factory(std::istream &is)
{
    std::shared_ptr<NPC> result;
    int type{0};
    if (is >> type)
    {
        switch (type)
        {
        case OrcType:
            result = std::make_shared<Orc>(is);
            break;
        case KnightType:
            result = std::make_shared<Knight>(is);
            break;
        case BearType:
            result = std::make_shared<Bear>(is);
            break;
        }
    }
    else
        std::cerr << "unexpected NPC type:" << type << std::endl;

    if (result)
        result->subscribe(TextObserver::get());

    return result;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y)
{
    std::shared_ptr<NPC> result;
    switch (type)
    {
    case OrcType:
        result = std::make_shared<Orc>(x, y);
        break;
    case KnightType:
        result = std::make_shared<Knight>(x, y);
        break;
    case BearType:
        result = std::make_shared<Bear>(x, y);
        break;
    default:
        break;
    }
    if (result)
        result->subscribe(TextObserver::get());

    return result;
}

void save(const set_t &array, const std::string &filename)
{
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto &n : array)
        n->save(fs);
    fs.flush();
    fs.close();
}

set_t load(const std::string &filename)
{
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open())
    {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i)
            result.insert(factory(is));
        is.close();
    }
    else
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    return result;
}

std::ostream &operator<<(std::ostream &os, const set_t &array)
{
    for (auto &n : array)
        n->print();
    return os;
}

set_t fight(const set_t &array, size_t distance)
{
    set_t dead_list;

    for (const auto &attacker : array) {
        for (const auto &defender : array) {
            if (attacker != defender && attacker->is_close(defender, distance)) {
                bool attacker_wins = attacker->accept(defender);
                if (attacker_wins) {
                    dead_list.insert(defender);
                } 
                else {
                    dead_list.insert(attacker);
                }
            }
        }
    }

    return dead_list;
}