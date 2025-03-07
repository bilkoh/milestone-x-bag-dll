#include "bag.h"
#include "dll_node.h"
#include <vector>

Bag::Bag() : bagSize(0) {}

Bag::~Bag() { dll.clear(); }

int Bag::getCurrentSize() { return bagSize; }

bool Bag::isEmpty() { return dll.isEmpty(); }

bool Bag::add(int newEntry) {
    DllNode *newNode = dll.insertAtTail(newEntry);

    if (newNode != nullptr && newNode->key == newEntry) {
        ++bagSize;
        return true;
    }

    return false;
}

bool Bag::remove(int anEntry) {
    if (dll.remove(anEntry)) {
        --bagSize;
        return true;
    }

    return false;
}

void Bag::clear() {
    dll.clear();
    bagSize = 0;
}

int Bag::getFrequencyOf(int anEntry) {
    if (dll.isEmpty())
        return 0;

    DllNode *curr = dll.head;
    int cnt = 0;

    while (curr != nullptr) {
        if (curr->key == anEntry)
            ++cnt;

        curr = curr->next;
    }

    return cnt;
}

bool Bag::contains(int anEntry) { return dll.findNode(anEntry) != nullptr; }

std::vector<int> Bag::toVector() {
    std::vector<int> v;
    v.reserve(bagSize);

    DllNode *curr = dll.head;

    while (curr != nullptr) {
        v.push_back(curr->key);

        curr = curr->next;
    }

    return v;
}