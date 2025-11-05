#pragma once

#include <string>
#include <vector>

// Forward-declarations for all classes in the system.
// This helps resolve dependencies and allows us to order the classes logically.
class Sponsor;
class NILDeal;
class NegotiationStrategy;
class Player;
class Team;

// --- ENUMERATIONS ---

// Used by the Sponsor class
enum class Prestige {
    Local,
    Regional,
    National,
    Global
};

// Used by the NILDeal class
enum class DealStatus {
    Offered,
    Accepted,
    Declined,
    Expired
};

// Used by the Player class
enum class Position { QB, WR, RB, C, OG, OT, DT, DE, LB, CB, S, K, P };
enum class Morale { Ecstatic, Happy, Neutral, Unhappy, Frustrated };


// --- SPONSOR CLASS DEFINITION ---

class Sponsor {
public:
    Sponsor(const std::string& brandName, float budget, Prestige prestige);
    NILDeal createOffer(const Player& targetPlayer);
    void updateBudget(float amount);
    std::string getBrandName() const;
private:
    std::string m_brandName;
    float m_budget;
    Prestige m_prestige;
};


// --- NILDEAL CLASS DEFINITION ---

class NILDeal {
public:
    NILDeal(const Sponsor& sponsor, float value, int durationWeeks);
    void accept();
    void expire();
    float getValue() const;
    DealStatus getStatus() const;
private:
    const Sponsor& m_sponsor;
    float m_contractValue;
    int m_durationWeeks;
    DealStatus m_status;
};


// --- NEGOTIATION STRATEGY INTERFACE & CLASSES ---

class NegotiationStrategy {
public:
    virtual ~NegotiationStrategy() = default;
    virtual const NILDeal& selectBestOffer(const std::vector<NILDeal>& offers) = 0;
};

class GreedyStrategy : public NegotiationStrategy {
public:
    const NILDeal& selectBestOffer(const std::vector<NILDeal>& offers) override;
};

class LoyalStrategy : public NegotiationStrategy {
public:
    const NILDeal& selectBestOffer(const std::vector<NILDeal>& offers) override;
};

class PrestigeStrategy : public NegotiationStrategy {
public:
    const NILDeal& selectBestOffer(const std::vector<NILDeal>& offers) override;
};


// --- PLAYER CLASS DEFINITION ---

class Player {
public:
    Player(const std::string& name, Position position, int overallRating);
    void evaluateOffers(const std::vector<NILDeal>& offers);
    void addDeal(const NILDeal& newDeal);
    void setStrategy(NegotiationStrategy* strategy);
private:
    std::string m_name;
    Position m_position;
    int m_overallRating;
    float m_nilValue;
    Morale m_morale;
    std::vector<NILDeal> m_activeDeals;
    NegotiationStrategy* m_strategy;
};


// --- TEAM CLASS DEFINITION ---

class Team {
public:
    Team(const std::string& schoolName, float initialBudget);
    void recruitPlayer(const Player& newPlayer);
    Player* getPlayer(const std::string& name);
    const std::vector<Player>& getRoster() const;
private:
    std::string m_schoolName;
    std::vector<Player> m_roster;
    float m_nilBudget;
};
