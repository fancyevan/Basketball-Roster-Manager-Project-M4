// Coach.cpp - Evan Broadus
// Validates the coaching role and displays coach information.
#include "Coach.h"
#include <ostream>
#include <stdexcept>

Coach::Coach(const std::string& coachName, const std::string& coachingRole)
    : TeamMember(coachName), role(coachingRole) {
    if (role.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument("A coach needs a coaching role.");
    }
}

const std::string& Coach::GetRole() const {
    return role;
}

void Coach::Display(std::ostream& output) const {
    output << "Coach: " << GetName() << " | Role: " << role;
}
