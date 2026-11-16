// Team.h - Evan Broadus
// Connects team information, the custom roster, and the lineup hash table.
#ifndef TEAM_H
#define TEAM_H

#include "Coach.h"
#include "RosterList.h"
#include <unordered_map>

class Team {
private:
    std::string city;
    std::string name;
    Coach coach;
    RosterList roster;

    // Map ADT: a position key identifies a starter by unique jersey number.
    std::unordered_map<std::string, int> startingLineup;

public:
    Team(const std::string& teamCity, const std::string& teamName,
        const std::string& coachName, const std::string& coachingRole);

    std::size_t GetRosterSize() const;
    bool AddPlayer(const Player& player);
    bool RemovePlayer(int jerseyNumber);
    const Player* FindPlayer(int jerseyNumber) const;
    bool UpdatePlayerStats(int jerseyNumber, int points, int rebounds, int assists);
    bool SetStarter(const std::string& position, int jerseyNumber);
    bool ClearStarter(const std::string& position);
    bool IsStarter(int jerseyNumber) const;
    const Player* GetStarter(const std::string& position) const;
    void SortRosterByPoints();
    void DisplaySummary(std::ostream& output) const;
    void DisplayRoster(std::ostream& output) const;
    bool DisplayPlayer(int jerseyNumber, std::ostream& output) const;
    void DisplayLineup(std::ostream& output) const;
};

#endif
