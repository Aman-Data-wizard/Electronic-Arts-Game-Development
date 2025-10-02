#pragma once

#include <string>
#include <vector>
#include "Player Class Definition.h" // A Team is composed of Players.
class Team {
public:
    // --- Public Interface ---
    Team(const std::string& schoolName, float initialBudget);

    // Adds a new player to the team's roster.
    void recruitPlayer(const Player& newPlayer);

    // Finds a player on the roster by name.
    Player* getPlayer(const std::string& name);

    // Returns a constant reference to the roster for safe, read-only access.
    const std::vector<Player>& getRoster() const;

private:
    // --- Private Data Members ---
    std::string m_schoolName;
    std::vector<Player> m_roster;
    float m_nilBudget;
};
