#include <gtest/gtest.h>
#include "../include/medieval.h"


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

    ASSERT_EQ(loaded_array.size(), 3);
    ASSERT_TRUE(loaded_array.find(orc) != loaded_array.end());
    ASSERT_TRUE(loaded_array.find(knight) != loaded_array.end());
    ASSERT_TRUE(loaded_array.find(bear) != loaded_array.end());
}

TEST(MedievalTest, FightNPC) {
    set_t array;
    std::shared_ptr<NPC> orc = std::make_shared<Orc>(100, 100);
    std::shared_ptr<NPC> knight = std::make_shared<Knight>(200, 200);
    std::shared_ptr<NPC> bear = std::make_shared<Bear>(300, 300);
    array.insert(orc);
    array.insert(knight);
    array.insert(bear);

    set_t dead_list = fight(array, 100);

    ASSERT_EQ(dead_list.size(), 1);
}