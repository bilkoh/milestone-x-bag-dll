#include "bag.h"
#include <iostream>

int main(int, char **) {
    std::cout << "Hello, from bag!\n";

    Bag bag;

    // Add some elements (with duplicates)
    bag.add(10);
    bag.add(20);
    bag.add(10);
    bag.add(30);
    bag.add(20);

    // Display the bag contents
    std::cout << "Bag contents: ";
    std::vector<int> contents = bag.toVector();
    for (int item : contents)
        std::cout << item << " ";
    std::cout << "\n";

    // Check frequency of an element
    std::cout << "Frequency of 10: " << bag.getFrequencyOf(10) << "\n";

    // Remove one occurrence of 20 and display a message
    if (bag.remove(20))
        std::cout << "Removed one occurrence of 20.\n";
    else
        std::cout << "20 not found in bag.\n";

    // Display the bag contents after removal
    std::cout << "Bag contents after removal: ";
    contents = bag.toVector();
    for (int item : contents)
        std::cout << item << " ";
    std::cout << "\n";

    // Clear the bag and show its size
    bag.clear();
    std::cout << "Bag cleared. Current size: " << bag.getCurrentSize() << "\n";

    return 0;
}
