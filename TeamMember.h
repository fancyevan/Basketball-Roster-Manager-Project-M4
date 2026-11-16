// TeamMember.h - Evan Broadus
// Abstract base class for people on the basketball team.
#ifndef TEAM_MEMBER_H
#define TEAM_MEMBER_H

#include <iosfwd>
#include <string>

class TeamMember {
private:
    std::string name;

public:
    explicit TeamMember(const std::string& memberName);
    virtual ~TeamMember();
    const std::string& GetName() const;

    // Abstract class: this pure virtual function makes TeamMember abstract.
    // Player and Coach each provide their own display behavior.
    virtual void Display(std::ostream& output) const = 0;
};

#endif
