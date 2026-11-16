// RosterList.cpp - Evan Broadus
// Linked-list operations, linear search, and recursive merge sort.
#include "RosterList.h"
#include <ostream>

RosterList::RosterList() : head(nullptr), tail(nullptr), size(0) {}

RosterList::~RosterList() {
    Clear();
}

std::size_t RosterList::GetSize() const {
    return size;
}

const Player* RosterList::FindPlayer(int jerseyNumber) const {
    // Linear search follows next pointers. Worst-case time is O(n).
    const Node* current = head;
    while (current != nullptr) {
        if (current->player.GetJerseyNumber() == jerseyNumber) {
            return &current->player;
        }
        current = current->next;
    }
    return nullptr;
}

bool RosterList::AddPlayer(const Player& player) {
    if (FindPlayer(player.GetJerseyNumber()) != nullptr) {
        return false;
    }

    Node* newNode = new Node(player);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        tail->next = newNode;
    }
    tail = newNode;
    ++size;
    // Linking at the tail is O(1); the earlier duplicate check is O(n).
    return true;
}

bool RosterList::RemovePlayer(int jerseyNumber) {
    Node* current = head;
    Node* previous = nullptr;
    while (current != nullptr) {
        if (current->player.GetJerseyNumber() == jerseyNumber) {
            if (previous == nullptr) {
                head = current->next;
            }
            else {
                previous->next = current->next;
            }
            if (current == tail) {
                tail = previous;
            }
            delete current;
            --size;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

bool RosterList::UpdatePlayerStats(int jerseyNumber, int points,
    int rebounds, int assists) {
    Node* current = head;
    while (current != nullptr) {
        if (current->player.GetJerseyNumber() == jerseyNumber) {
            current->player.UpdateStats(points, rebounds, assists);
            return true;
        }
        current = current->next;
    }
    return false;
}

void RosterList::Display(std::ostream& output) const {
    if (head == nullptr) {
        output << "The roster is empty.\n";
        return;
    }
    const Node* current = head;
    while (current != nullptr) {
        // Polymorphism: call Player's display through the abstract base type.
        const TeamMember& member = current->player;
        member.Display(output);
        output << '\n';
        current = current->next;
    }
}

void RosterList::SortByPoints() {
    head = MergeSort(head);

    // Sorting changes the links, so find the new tail before another append.
    tail = head;
    while (tail != nullptr && tail->next != nullptr) {
        tail = tail->next;
    }
}

// Custom sorting algorithm: merge sort puts higher point totals first.
// Ties go to the lower jersey number. The sort rearranges the list's links.
RosterList::Node* RosterList::MergeSort(Node* first) {
    // Recursion base case: an empty list or one player is already sorted.
    if (first == nullptr || first->next == nullptr) {
        return first;
    }

    Node* slow = first;
    Node* fast = first->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* secondHalf = slow->next;
    slow->next = nullptr;

    // Divide, recursively sort both halves, then combine their node links.
    Node* left = MergeSort(first);
    Node* right = MergeSort(secondHalf);
    return Merge(left, right);
}

RosterList::Node* RosterList::Merge(Node* left, Node* right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }

    Node* mergedHead = nullptr;
    Node* mergedTail = nullptr;
    while (left != nullptr && right != nullptr) {
        Node* selected = nullptr;
        const int leftPoints = left->player.GetPoints();
        const int rightPoints = right->player.GetPoints();
        const bool takeLeft = leftPoints > rightPoints ||
            (leftPoints == rightPoints && left->player.GetJerseyNumber() <=
                right->player.GetJerseyNumber());

        if (takeLeft) {
            selected = left;
            left = left->next;
        }
        else {
            selected = right;
            right = right->next;
        }
        if (mergedHead == nullptr) {
            mergedHead = selected;
        }
        else {
            mergedTail->next = selected;
        }
        mergedTail = selected;
    }
    // The merge uses a loop, so recursive stack depth stays O(log n).
    mergedTail->next = (left != nullptr) ? left : right;
    return mergedHead;
}

void RosterList::Clear() {
    while (head != nullptr) {
        Node* oldHead = head;
        head = head->next;
        delete oldHead;
    }
    tail = nullptr;
    size = 0;
}
