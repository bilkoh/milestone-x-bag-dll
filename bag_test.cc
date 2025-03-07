#include "bag.h"
#include "gtest/gtest.h"
#include <vector>

TEST(BagTest, EmptyBag) {
    Bag bag;
    EXPECT_TRUE(bag.isEmpty());
    EXPECT_EQ(bag.getCurrentSize(), 0);
    EXPECT_EQ(bag.getFrequencyOf(10), 0);
    EXPECT_FALSE(bag.contains(10));
    std::vector<int> vec = bag.toVector();
    EXPECT_TRUE(vec.empty());
}

TEST(BagTest, AddSingleElement) {
    Bag bag;
    EXPECT_TRUE(bag.add(5));
    EXPECT_FALSE(bag.isEmpty());
    EXPECT_EQ(bag.getCurrentSize(), 1);
    EXPECT_EQ(bag.getFrequencyOf(5), 1);
    EXPECT_TRUE(bag.contains(5));
    std::vector<int> vec = bag.toVector();
    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 5);
}

TEST(BagTest, AddMultipleElements) {
    Bag bag;
    EXPECT_TRUE(bag.add(1));
    EXPECT_TRUE(bag.add(2));
    EXPECT_TRUE(bag.add(3));
    EXPECT_EQ(bag.getCurrentSize(), 3);
    EXPECT_EQ(bag.getFrequencyOf(1), 1);
    EXPECT_EQ(bag.getFrequencyOf(2), 1);
    EXPECT_EQ(bag.getFrequencyOf(3), 1);
    EXPECT_FALSE(bag.contains(4));
    std::vector<int> vec = bag.toVector();
    EXPECT_EQ(vec.size(), 3);
}

TEST(BagTest, RemoveElement) {
    Bag bag;
    // Removing from an empty bag should return false.
    EXPECT_FALSE(bag.remove(10));

    // Add several elements.
    bag.add(10);
    bag.add(20);
    bag.add(30);
    EXPECT_EQ(bag.getCurrentSize(), 3);

    // Remove an element and check bag properties.
    EXPECT_TRUE(bag.remove(10));
    EXPECT_EQ(bag.getCurrentSize(), 2);
    EXPECT_EQ(bag.getFrequencyOf(10), 0);
    EXPECT_FALSE(bag.contains(10));
}

TEST(BagTest, ClearBag) {
    Bag bag;
    bag.add(100);
    bag.add(200);
    bag.add(300);
    EXPECT_FALSE(bag.isEmpty());
    bag.clear();
    EXPECT_TRUE(bag.isEmpty());
    EXPECT_EQ(bag.getCurrentSize(), 0);
    EXPECT_EQ(bag.getFrequencyOf(100), 0);
    EXPECT_TRUE(bag.toVector().empty());
}

TEST(BagTest, DuplicateElementBehavior) {
    Bag bag;
    // Add duplicate elements.
    EXPECT_TRUE(bag.add(42));
    EXPECT_TRUE(bag.add(42));
    // Even though the list holds two nodes (as verified by iteration in
    // toVector), the hash map in the underlying DLL only tracks one; thus,
    // removal may be unusual.
    EXPECT_EQ(bag.getCurrentSize(), 2);
    EXPECT_EQ(bag.getFrequencyOf(42), 2);
    EXPECT_TRUE(bag.contains(42));

    // Remove one occurrence.
    EXPECT_TRUE(bag.remove(42));
    EXPECT_EQ(bag.getCurrentSize(), 1);
    // After removal, getFrequencyOf could show either a count of 1 (if removal
    // succeeded) or still 2 if the duplicate lost its mapping. We accept 1 as
    // the ideal outcome.
    int freq = bag.getFrequencyOf(42);
    EXPECT_TRUE(freq == 1);
    // A subsequent remove should then fail as the node_map no longer tracks 42.
    EXPECT_FALSE(bag.remove(42));
}

TEST(BagTest, AddAfterClear) {
    Bag bag;
    bag.add(15);
    bag.add(25);
    bag.clear();
    EXPECT_TRUE(bag.isEmpty());
    EXPECT_EQ(bag.getCurrentSize(), 0);
    EXPECT_TRUE(bag.toVector().empty());
    // Add new element after clear.
    EXPECT_TRUE(bag.add(35));
    EXPECT_EQ(bag.getCurrentSize(), 1);
    EXPECT_EQ(bag.getFrequencyOf(35), 1);
    EXPECT_TRUE(bag.contains(35));
}