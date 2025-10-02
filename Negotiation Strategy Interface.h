#pragma once

#include <vector>
#include "NILDeal.h"


class NegotiationStrategy {
public:
    
    virtual ~NegotiationStrategy() = default;

    // The pure virtual function (= 0) makes this class abstract (an interface).
    // It takes a vector of offers and returns the one it deems "best".
    virtual const NILDeal& selectBestOffer(const std::vector<NILDeal>& offers) = 0;
};


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
