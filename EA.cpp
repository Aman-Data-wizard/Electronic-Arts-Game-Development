#pragma once

#include <string>

// Forward-declare classes that Sponsor interacts with to avoid circular dependencies.
// We don't need the full definition of Player or NILDeal here, just to know they exist.
class Player;
class NILDeal;

// Define an enumeration for the Sponsor's prestige level.
// This is more robust than using simple strings or integers.
enum class Prestige {
    Local,
    Regional,
    National,
    Global
};

class Sponsor {
public:
    // Constructor to initialize a new Sponsor object with its essential properties.
    Sponsor(const std::string& brandName, float budget, Prestige prestige);

    // --- BEHAVIORS / METHODS ---

    // Creates a new NILDeal object targeted at a specific player.
    // Note: This declaration implies a NILDeal class will be fully defined elsewhere.
    NILDeal createOffer(const Player& targetPlayer);

    // Decreases the sponsor's budget when a deal is signed.
    void updateBudget(float amount);

    // --- STATE / ATTRIBUTES ---

    std::string brandName;
    float budget;
    Prestige prestige;

private:
    // Helper methods or private data could be added here in the future.
};
