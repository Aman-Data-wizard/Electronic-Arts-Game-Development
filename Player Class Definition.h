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
