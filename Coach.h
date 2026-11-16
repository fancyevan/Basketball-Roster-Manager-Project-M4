// Coach.h - Evan Broadus
// Coach information, derived from TeamMember.
#ifndef COACH_H
#define COACH_H

#include "TeamMember.h"

// Inheritance: Coach extends TeamMember with a coaching role.
class Coach : public TeamMember {
private:
    std::string role;

public:
    Coach(const std::string& coachName, const std::string& coachingRole);
    const std::string& GetRole() const;
    void Display(std::ostream& output) const override;
};

#endif
