// Team.cpp - Evan Broadus
// Keeps roster records and starting-lineup assignments consistent.
#include "Team.h"
#include <ostream>
#include <stdexcept>

Team::Team(const std::string& teamCity, const std::string& teamName,
    const std::string& coachName, const std::string& coachingRole)
    : city(teamCity), name(teamName), coach(coachName, coachingRole) {
    if (city.find_first_not_of(" \t\r\n") == std::string::npos ||
        name.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument("A team needs a city and name.");
    }
}

std::size_t Team::GetRosterSize() const {
    return roster.GetSize();
}

bool Team::AddPlayer(const Player& player) {
    return roster.AddPlayer(player);
}

bool Team::RemovePlayer(int jerseyNumber) {
    if (!roster.RemovePlayer(jerseyNumber)) {
        return false;
    }
    // Erase any lineup assignment before a removed jersey can be used again.
    for (auto entry = startingLineup.begin(); entry != startingLineup.end();) {
        if (entry->second == jerseyNumber) {
            entry = startingLineup.erase(entry);
        }
        else {
            ++entry;
        }
    }
    return true;
}

const Player* Team::FindPlayer(int jerseyNumber) const {
    return roster.FindPlayer(jerseyNumber);
}

bool Team::UpdatePlayerStats(int jerseyNumber, int points, int rebounds, int assists) {
    return roster.UpdatePlayerStats(jerseyNumber, points, rebounds, assists);
}

bool Team::SetStarter(const std::string& position, int jerseyNumber) {
    const Player* player = FindPlayer(jerseyNumber);
    if (!Player::IsValidPosition(position) || player == nullptr ||
        player->GetPosition() != position) {
        return false;
    }
    // Reassigning a position replaces its former starter automatically.
    startingLineup[position] = jerseyNumber;
    return true;
}

bool Team::ClearStarter(const std::string& position) {
    return startingLineup.erase(position) != 0;
}

bool Team::IsStarter(int jerseyNumber) const {
    for (const auto& entry : startingLineup) {
        if (entry.second == jerseyNumber) {
            return true;
        }
    }
    return false;
}

const Player* Team::GetStarter(const std::string& position) const {
    // Hash-table lookup is average O(1). Finding its player in the list is O(n).
    const auto entry = startingLineup.find(position);
    if (entry == startingLineup.end()) {
        return nullptr;
    }
    return roster.FindPlayer(entry->second);
}

void Team::SortRosterByPoints() {
    roster.SortByPoints();
}

void Team::DisplaySummary(std::ostream& output) const {
    output << "\nTeam: " << city << ' ' << name << '\n';
    // Polymorphism: a TeamMember reference calls the Coach version of Display().
    const TeamMember& member = coach;
    member.Display(output);
    output << "\nPlayers: " << GetRosterSize() << '\n';
}

void Team::DisplayRoster(std::ostream& output) const {
    DisplaySummary(output);
    output << "\nRoster\n";
    roster.Display(output);
    DisplayLineup(output);
    output << "Players not assigned to the starting lineup are on the bench.\n";
}

bool Team::DisplayPlayer(int jerseyNumber, std::ostream& output) const {
    const Player* player = FindPlayer(jerseyNumber);
    if (player == nullptr) {
        return false;
    }
    // Polymorphism: the same base type now calls the Player override.
    const TeamMember& member = *player;
    member.Display(output);
    output << " | " << (IsStarter(jerseyNumber) ? "Starter" : "Bench") << '\n';
    return true;
}

void Team::DisplayLineup(std::ostream& output) const {
    // unordered_map has no display order; use basketball's position order.
    const std::string positions[] = { "PG", "SG", "SF", "PF", "C" };
    output << "\nStarting lineup\n";
    for (const std::string& position : positions) {
        output << position << ": ";
        const Player* player = GetStarter(position);
        if (player == nullptr) {
            output << "Unassigned\n";
        }
        else {
            output << '#' << player->GetJerseyNumber() << " | "
                << player->GetName() << '\n';
        }
    }
}
