#include "doubly_linked_list.h"
#include <cstddef>
#include <vector>

class Bag {
  private:
    DoublyLinkedList dll;
    int bagSize;

  public:
    Bag();
    ~Bag();
    int getCurrentSize();
    bool isEmpty();
    bool add(int newEntry);
    bool remove(int anEntry);
    void clear();
    int getFrequencyOf(int anEntry);
    bool contains(int anEntry);
    std::vector<int> toVector();
};