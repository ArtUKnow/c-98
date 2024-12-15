#include <gtest/gtest.h>
#include "../include/medieval.h"

// Test for adding new NPC
TEST(MedievalTest, AddNPC) {
    set_t array;
    std::shared_ptr<NPC> orc = std::make_shared<Orc>(100, 100);
    std::shared_ptr<NPC> knight = std::make_shared<Knight>(200, 200);
    std::shared_ptr<NPC> bear = std::make_shared<Bear>(300, 300);

    array.insert(orc);
    array.insert(knight);
    array.insert(bear);

    ASSERT_EQ(array.size(), 3);
    ASSERT_TRUE(array.find(orc) != array.end());
    ASSERT_TRUE(array.find(knight) != array.end());
    ASSERT_TRUE(array.find(bear) != array.end());
}

// Test for saving and loading NPC
TEST(MedievalTest, SaveLoadNPC) {
    set_t array;
    std::shared_ptr<NPC> orc = std::make_shared<Orc>(100, 100);
    std::shared_ptr<NPC> knight = std::make_shared<Knight>(200, 200);
    std::shared_ptr<NPC> bear = std::make_shared<Bear>(300, 300);
    array.insert(orc);
    array.insert(knight);
    array.insert(bear);

    save(array, "test_npc.txt");
    set_t loaded_array = load("test_npc.txt");

    std::cout << "Loaded array contents:" << std::endl;
    for (const auto& npc : loaded_array) {
        npc->print();
    }

    ASSERT_EQ(loaded_array.size(), 3);
    ASSERT_TRUE(loaded_array.find(orc) != loaded_array.end());
    ASSERT_TRUE(loaded_array.find(knight) != loaded_array.end());
    ASSERT_TRUE(loaded_array.find(bear) != loaded_array.end());
}

TEST(MedievalTest, FightNPC) {
    set_t npcs;
    npcs.insert(std::make_shared<Orc>(0, 0)); // Орк
    npcs.insert(std::make_shared<Knight>(3, 4)); // Рыцарь в радиусе 5
    npcs.insert(std::make_shared<Bear>(10, 10)); // Медведь слишком далеко

    auto dead_list = fight(npcs, 5); // Расстояние для боя = 5

    EXPECT_EQ(dead_list.size(), 1); // Должен быть убит только 1 NPC
}


TEST(MedievalTest, Comparator) {
    set_t array;
    std::shared_ptr<NPC> orc = std::make_shared<Orc>(100, 100);
    std::shared_ptr<NPC> knight = std::make_shared<Knight>(200, 200);
    std::shared_ptr<NPC> bear = std::make_shared<Bear>(300, 300);
    array.insert(orc);
    array.insert(knight);
    array.insert(bear);

    auto it = array.begin();
    ASSERT_EQ((*it)->type, OrcType);
    ++it;
    ASSERT_EQ((*it)->type, KnightType);
    ++it;
    ASSERT_EQ((*it)->type, BearType);
}