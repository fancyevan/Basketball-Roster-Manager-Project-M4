// RosterList.h - Evan Broadus
// Custom singly linked list that owns the team's player records.
#ifndef ROSTER_LIST_H
#define ROSTER_LIST_H

#include "Player.h"
#include <cstddef>

// Data structure built from scratch (List ADT): each private node holds a
// player and a link to the next node. The public methods manage the roster.
class RosterList {
private:
    struct Node {
        Player player;
        Node* next;
        explicit Node(const Player& newPlayer) : player(newPlayer), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t size;

    static Node* MergeSort(Node* first);
    static Node* Merge(Node* left, Node* right);

public:
    RosterList();
    ~RosterList();

    // Each list owns its nodes. Prevent accidental copies of the node pointers.
    RosterList(const RosterList&) = delete;
    RosterList& operator=(const RosterList&) = delete;

    std::size_t GetSize() const;
    const Player* FindPlayer(int jerseyNumber) const;
    bool AddPlayer(const Player& player);
    bool RemovePlayer(int jerseyNumber);
    bool UpdatePlayerStats(int jerseyNumber, int points, int rebounds, int assists);
    void Display(std::ostream& output) const;
    void SortByPoints();
    void Clear();
};

#endif
