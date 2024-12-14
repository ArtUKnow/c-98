#include <gtest/gtest.h>
#include "../include/medieval.h"

// Test for adding new NPC
TEST(MedievalTest, AddNPC) {
    // Arrange
    set_t array;
    std::shared_ptr<NPC> orc = std::make_shared<Orc>(100, 100);
    std::shared_ptr<NPC> knight = std::make_shared<Knight>(200, 200);
    std::shared_ptr<NPC> bear = std::make_shared<Bear>(300, 300);

    // Act
    array.insert(orc);
    array.insert(knight);
    array.insert(bear);

    // Assert
    ASSERT_EQ(array.size(), 3);
    ASSERT_TRUE(array.find(orc) != array.end());
    ASSERT_TRUE(array.find(knight) != array.end());
    ASSERT_TRUE(array.find(bear) != array.end());
}

// Test for saving and loading NPC
TEST(MedievalTest, SaveLoadNPC) {
    // Arrange
    set_t array;
    std::shared_ptr<NPC> orc = std::make_shared<Orc>(100, 100);
    std::shared_ptr<NPC> knight = std::make_shared<Knight>(200, 200);
    std::shared_ptr<NPC> bear = std::make_shared<Bear>(300, 300);
    array.insert(orc);
    array.insert(knight);
    array.insert(bear);

    // Act
    save(array, "test_npc.txt");
    set_t loaded_array = load("test_npc.txt");

    // Log the contents of the loaded array
    std::cout << "Loaded array contents:" << std::endl;
    for (const auto& npc : loaded_array) {
        npc->print();
    }

    // Assert
    ASSERT_EQ(loaded_array.size(), 3);
    ASSERT_TRUE(loaded_array.find(orc) != loaded_array.end());
    ASSERT_TRUE(loaded_array.find(knight) != loaded_array.end());
    ASSERT_TRUE(loaded_array.find(bear) != loaded_array.end());
}

// Test for fighting NPC
TEST(MedievalTest, FightNPC) {
    // Arrange
    set_t array;
    std::shared_ptr<NPC> orc = std::make_shared<Orc>(100, 100);
    std::shared_ptr<NPC> knight = std::make_shared<Knight>(200, 200);
    std::shared_ptr<NPC> bear = std::make_shared<Bear>(300, 300);
    array.insert(orc);
    array.insert(knight);
    array.insert(bear);

    // Act
    set_t dead_list = fight(array, 100);

    // Log the contents of the dead list
    std::cout << "Dead list contents:" << std::endl;
    for (const auto& npc : dead_list) {
        npc->print();
    }

    // Assert
    ASSERT_EQ(dead_list.size(), 1); // Expecting that one NPC will be killed
}
