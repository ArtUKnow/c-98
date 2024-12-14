
NPC::NPC(NpcType t, int _x, int _y) : type(t), x(_x), y(_y), id(id_counter++) {}
NPC::NPC(NpcType t, std::istream &is) : type(t), id(id_counter++)
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
    if (std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <= std::pow(distance, 2))
        return true;
    else
        return false;
}

void NPC::save(std::ostream &os)
{
    os << id << " " << x << " " << y << std::endl;
}

std::ostream &operator<<(std::ostream &os, NPC &npc)
{
    os << "{ id: " << npc.id << ", x: " << npc.x << ", y: " << npc.y << " } ";
    return os;
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
        return true; // Орк побеждает медведя
    }
    else if (other->type == KnightType)
    {
        fight_notify(other, false);
        return true; // Орк проигрывает рыцарю
    }
    return false; // Нейтральные взаимодействия
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
        return true; // Рыцарь побеждает орка
    }
    else if (other->type == BearType)
    {
        fight_notify(other, false);
        return true; // Рыцарь проигрывает медведю
    }
    return false; // Нейтральные взаимодействия
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
        return true; // Медведь побеждает рыцаря
    }
    else if (other->type == OrcType)
    {
        fight_notify(other, false);
        return true; // Медведь проигрывает орку
    }
    return false; // Нейтральные взаимодействия
}

std::ostream &operator<<(std::ostream &os, Bear &bear)
{
    os << "Bear: " << *static_cast<NPC *>(&bear) << std::endl;
    return os;
}

std::shared_ptr<NPC> factory(std::istream &is)
{
    int type, id, x, y;
    if (is >> id >> type >> x >> y)
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
            std::cerr << "Unknown NPC type: " << type << std::endl;
            return nullptr;
        }
        result->id = id; // Восстанавливаем ID
        result->subscribe(TextObserver::get());
        return result;
    }
    return nullptr;
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

    for (const auto &attacker : array)
    {
        for (const auto &defender : array)
        {
            if (attacker != defender && attacker->is_close(defender, distance))
            {
                if (!defender->accept(attacker)) // Если защитник проиграл
                    dead_list.insert(defender);
            }
        }
    }

    for (const auto &dead : dead_list)
    {
        std::cout << "NPC убит: ";
        dead->print();
    }

    return dead_list;
}