// Player.h - Evan Broadus
// Player details and statistics, derived from TeamMember.
#ifndef PLAYER_H
#define PLAYER_H

#include "TeamMember.h"

// Inheritance: Player extends TeamMember with a position and statistics.
class Player : public TeamMember {
private:
    std::string position;
    int jerseyNumber;
    int points;
    int rebounds;
    int assists;

public:
    Player(const std::string& playerName, const std::string& playerPosition,
        int jersey, int playerPoints, int playerRebounds, int playerAssists);

    static bool IsValidPosition(const std::string& playerPosition);
    const std::string& GetPosition() const;
    int GetJerseyNumber() const;
    int GetPoints() const;
    int GetRebounds() const;
    int GetAssists() const;
    void UpdateStats(int newPoints, int newRebounds, int newAssists);
    void Display(std::ostream& output) const override;
};

#endif
