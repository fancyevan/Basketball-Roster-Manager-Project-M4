// main.cpp - Evan Broadus
// Console menu and input validation for the basketball roster manager.
#include "Team.h"
#include <cctype>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

namespace {
    bool ReadText(const std::string& prompt, std::string& value) {
        while (true) {
            std::cout << prompt;
            if (!std::getline(std::cin, value)) {
                return false;
            }
            const std::size_t first = value.find_first_not_of(" \t\r\n");
            if (first != std::string::npos) {
                const std::size_t last = value.find_last_not_of(" \t\r\n");
                value = value.substr(first, last - first + 1);
                return true;
            }
            std::cout << "Please enter a value instead of leaving it blank.\n";
        }
    }

    bool ReadInt(const std::string& prompt, int minimum, int maximum, int& value) {
        std::string line;
        while (true) {
            std::cout << prompt;
            if (!std::getline(std::cin, line)) {
                return false;
            }
            // Parse a whole line so letters, decimals, and overflow are rejected.
            std::istringstream input(line);
            int candidate = 0;
            if (input >> candidate) {
                input >> std::ws;
                if (input.eof() && candidate >= minimum && candidate <= maximum) {
                    value = candidate;
                    return true;
                }
            }
            std::cout << "Enter a whole number from " << minimum
                << " to " << maximum << ".\n";
        }
    }

    bool ReadPosition(std::string& position) {
        while (ReadText("Position (PG, SG, SF, PF, C): ", position)) {
            for (char& letter : position) {
                letter = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
            }
            if (Player::IsValidPosition(position)) {
                return true;
            }
            std::cout << "Please choose PG, SG, SF, PF, or C.\n";
        }
        return false;
    }

    bool ReadStats(int& points, int& rebounds, int& assists) {
        const int maximum = std::numeric_limits<int>::max();
        return ReadInt("Points: ", 0, maximum, points) &&
            ReadInt("Rebounds: ", 0, maximum, rebounds) &&
            ReadInt("Assists: ", 0, maximum, assists);
    }

    bool AddPlayer(Team& team) {
        int jersey = 0;
        if (!ReadInt("Jersey number (0-99): ", 0, 99, jersey)) {
            return false;
        }
        if (team.FindPlayer(jersey) != nullptr) {
            std::cout << "That jersey number is already on the roster.\n";
            return true;
        }
        std::string name;
        std::string position;
        int points = 0;
        int rebounds = 0;
        int assists = 0;
        if (!ReadText("Player name: ", name) || !ReadPosition(position) ||
            !ReadStats(points, rebounds, assists)) {
            return false;
        }
        const Player player(name, position, jersey, points, rebounds, assists);
        if (team.AddPlayer(player)) {
            std::cout << "Player added.\n";
        }
        else {
            std::cout << "That jersey number is already on the roster.\n";
        }
        return true;
    }

    bool SearchPlayer(const Team& team) {
        int jersey = 0;
        if (!ReadInt("Jersey number to find: ", 0, 99, jersey)) {
            return false;
        }
        if (!team.DisplayPlayer(jersey, std::cout)) {
            std::cout << "No player has that jersey number.\n";
        }
        return true;
    }

    bool UpdatePlayer(Team& team) {
        int jersey = 0;
        if (!ReadInt("Jersey number to update: ", 0, 99, jersey)) {
            return false;
        }
        if (!team.DisplayPlayer(jersey, std::cout)) {
            std::cout << "No player has that jersey number.\n";
            return true;
        }
        std::cout << "Enter the replacement totals for this player.\n";
        int points = 0;
        int rebounds = 0;
        int assists = 0;
        if (!ReadStats(points, rebounds, assists)) {
            return false;
        }
        if (team.UpdatePlayerStats(jersey, points, rebounds, assists)) {
            std::cout << "Statistics updated. Sort again if you want points order.\n";
        }
        return true;
    }

    bool RemovePlayer(Team& team) {
        int jersey = 0;
        if (!ReadInt("Jersey number to remove: ", 0, 99, jersey)) {
            return false;
        }
        if (team.RemovePlayer(jersey)) {
            std::cout << "Player removed. Any starting assignment was cleared.\n";
        }
        else {
            std::cout << "No player has that jersey number.\n";
        }
        return true;
    }

    bool AssignStarter(Team& team) {
        int jersey = 0;
        if (!ReadInt("Jersey number to start: ", 0, 99, jersey)) {
            return false;
        }
        const Player* player = team.FindPlayer(jersey);
        if (player == nullptr) {
            std::cout << "No player has that jersey number.\n";
            return true;
        }
        // A player starts at the position stored in the player's record.
        if (team.SetStarter(player->GetPosition(), jersey)) {
            std::cout << player->GetName() << " is now the starting "
                << player->GetPosition() << ". The previous starter moves to the bench.\n";
        }
        return true;
    }

    bool ClearStarter(Team& team) {
        std::string position;
        if (!ReadPosition(position)) {
            return false;
        }
        if (team.ClearStarter(position)) {
            std::cout << "Starting assignment cleared. The player stays on the roster.\n";
        }
        else {
            std::cout << "That position has no starter assigned.\n";
        }
        return true;
    }

    void DisplayMenu() {
        std::cout << "\nBasketball Roster Menu\n"
            << "1. Add a player\n"
            << "2. Display team and roster\n"
            << "3. Search for a player\n"
            << "4. Update player statistics\n"
            << "5. Remove a player\n"
            << "6. Assign a starter\n"
            << "7. Clear a starting position\n"
            << "8. Display the starting lineup\n"
            << "9. Sort roster by points\n"
            << "0. Exit\n";
    }
}

int main() {
    std::cout << "Basketball Franchise and Roster Manager\n"
        << "Data is kept for this run only.\n\nCreate your team.\n";
    std::string city;
    std::string teamName;
    std::string coachName;
    std::string coachingRole;
    if (!ReadText("Team city: ", city) || !ReadText("Team name: ", teamName) ||
        !ReadText("Coach name: ", coachName) ||
        !ReadText("Coaching role (for example, Head Coach): ", coachingRole)) {
        std::cout << "\nInput ended. Program closed.\n";
        return 0;
    }

    Team team(city, teamName, coachName, coachingRole);
    team.DisplaySummary(std::cout);
    while (true) {
        DisplayMenu();
        int choice = 0;
        if (!ReadInt("Choose an option: ", 0, 9, choice)) {
            break;
        }
        bool inputAvailable = true;
        switch (choice) {
        case 1:
            inputAvailable = AddPlayer(team);
            break;
        case 2:
            team.DisplayRoster(std::cout);
            break;
        case 3:
            inputAvailable = SearchPlayer(team);
            break;
        case 4:
            inputAvailable = UpdatePlayer(team);
            break;
        case 5:
            inputAvailable = RemovePlayer(team);
            break;
        case 6:
            inputAvailable = AssignStarter(team);
            break;
        case 7:
            inputAvailable = ClearStarter(team);
            break;
        case 8:
            team.DisplayLineup(std::cout);
            break;
        case 9:
            team.SortRosterByPoints();
            std::cout << "Roster sorted by points, highest first.\n";
            team.DisplayRoster(std::cout);
            break;
        case 0:
            std::cout << "Goodbye.\n";
            return 0;
        }
        if (!inputAvailable) {
            break;
        }
    }
    std::cout << "\nInput ended. Program closed.\n";
    return 0;
}
