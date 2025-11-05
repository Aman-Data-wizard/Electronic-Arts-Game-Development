#NILDeal.h
#pragma once

#include <string>

// We must forward-declare Sponsor because NILDeal has a Sponsor member.
class Sponsor;

// Enum class for the status of a deal.
enum class DealStatus {
    Offered,
    Accepted,
    Declined,
    Expired
};

class NILDeal {
public:
    // --- Public Interface ---

    // Constructor to create a new deal.
    NILDeal(const Sponsor& sponsor, float value, int durationWeeks);

    // Methods to change the state of the deal.
    void accept();
    void expire();

    // Getter functions to provide read-only access to deal properties.
    float getValue() const;
    DealStatus getStatus() const;

private:
    // --- Private Data Members ---
    const Sponsor& m_sponsor; // Using a reference because a deal MUST have a sponsor.
    float m_contractValue;
    int m_durationWeeks;
    DealStatus m_status;
};


#Team Class Definition.h

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

#Player class Definition.h

#pragma once

#include <string>
#include <vector>
#include "NILDeal.h"
#include "Negotiation Strategy Interface.h" // A player has a strategy.

// Enums for player-specific attributes.
enum class Position { QB, WR, RB, C, OG, OT, DT, DE, LB, CB, S, K, P };
enum class Morale { Ecstatic, Happy, Neutral, Unhappy, Frustrated };


class Player {
public:
    // --- Public Interface ---
    Player(const std::string& name, Position position, int overallRating);

    // The core logic of the player's decision making. It uses its strategy.
    void evaluateOffers(const std::vector<NILDeal>& offers);

    // Adds a signed deal to the player's portfolio.
    void addDeal(const NILDeal& newDeal);

    // Sets the decision-making strategy for this player.
    // This allows us to change player personalities at runtime.
    void setStrategy(NegotiationStrategy* strategy);

private:
    // --- Private Data Members ---
    std::string m_name;
    Position m_position;
    int m_overallRating;
    float m_nilValue;
    Morale m_morale;
    std::vector<NILDeal> m_activeDeals;

    // A pointer to a strategy object. This is the core of the Strategy Pattern.
    NegotiationStrategy* m_strategy;
};

#Negotiation Strategy Interface.h

#pragma once

#include <vector>
#include "NILDeal.h" // We need the full definition of NILDeal to use it in a vector.

// --- The Strategy Interface ---
// This class defines a contract that all concrete strategies must follow.
class NegotiationStrategy {
public:
    // Virtual destructor is crucial for a base class with virtual functions.
    virtual ~NegotiationStrategy() = default;

    // The pure virtual function (= 0) makes this class abstract (an interface).
    // It takes a vector of offers and returns the one it deems "best".
    virtual const NILDeal& selectBestOffer(const std::vector<NILDeal>& offers) = 0;
};


// --- Concrete Strategy Implementations ---

// Chooses the deal with the highest monetary value.
class GreedyStrategy : public NegotiationStrategy {
public:
    const NILDeal& selectBestOffer(const std::vector<NILDeal>& offers) override;
};

// Chooses a deal based on loyalty to their current team (not implemented here).
class LoyalStrategy : public NegotiationStrategy {
public:
    const NILDeal& selectBestOffer(const std::vector<NILDeal>& offers) override;
};

// Chooses a deal based on the prestige of the sponsor.
class PrestigeStrategy : public NegotiationStrategy {
public:
    const NILDeal& selectBestOffer(const std::vector<NILDeal>& offers) override;
};
