// Player.cpp - Evan Broadus
// Validates player information and displays a player's statistics.
#include "Player.h"
#include <ostream>
#include <stdexcept>

Player::Player(const std::string& playerName, const std::string& playerPosition,
    int jersey, int playerPoints, int playerRebounds, int playerAssists)
    : TeamMember(playerName), position(playerPosition), jerseyNumber(jersey),
      points(0), rebounds(0), assists(0) {
    if (!IsValidPosition(position)) {
        throw std::invalid_argument("Position must be PG, SG, SF, PF, or C.");
    }
    if (jersey < 0 || jersey > 99) {
        throw std::invalid_argument("Jersey numbers must be between 0 and 99.");
    }
    UpdateStats(playerPoints, playerRebounds, playerAssists);
}

bool Player::IsValidPosition(const std::string& playerPosition) {
    return playerPosition == "PG" || playerPosition == "SG" ||
        playerPosition == "SF" || playerPosition == "PF" || playerPosition == "C";
}

const std::string& Player::GetPosition() const {
    return position;
}

int Player::GetJerseyNumber() const {
    return jerseyNumber;
}

int Player::GetPoints() const {
    return points;
}

int Player::GetRebounds() const {
    return rebounds;
}

int Player::GetAssists() const {
    return assists;
}

void Player::UpdateStats(int newPoints, int newRebounds, int newAssists) {
    if (newPoints < 0 || newRebounds < 0 || newAssists < 0) {
        throw std::invalid_argument("Statistics cannot be negative.");
    }
    points = newPoints;
    rebounds = newRebounds;
    assists = newAssists;
}

void Player::Display(std::ostream& output) const {
    output << '#' << jerseyNumber << " | " << GetName()
        << " | " << position << " | Points: " << points
        << " | Rebounds: " << rebounds << " | Assists: " << assists;
}
