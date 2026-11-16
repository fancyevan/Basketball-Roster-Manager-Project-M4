// TeamMember.cpp - Evan Broadus
// Stores and validates the name shared by players and coaches.
#include "TeamMember.h"
#include <stdexcept>

TeamMember::TeamMember(const std::string& memberName) : name(memberName) {
    if (name.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument("A team member needs a name.");
    }
}

TeamMember::~TeamMember() = default;

const std::string& TeamMember::GetName() const {
    return name;
}
