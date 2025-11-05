#pragma once

#include <string>

class Sponsor;

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
