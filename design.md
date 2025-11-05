classDiagram
    class Team {
        +string schoolName
        +vector~Player~ roster
        +float nilBudget
        +recruitPlayer(Player)
        +getPlayer(string)
    }

    class Player {
        +string name
        +int overallRating
        +float nilValue
        +NegotiationStrategy* strategy
        +evaluateOffers(vector~NILDeal~)
        +addDeal(NILDeal)
    }

    class Sponsor {
        +string brandName
        +float budget
        +Prestige prestige
        +createOffer(Player) NILDeal
    }

    class NILDeal {
        +Sponsor sponsor
        +float contractValue
        +int durationWeeks
        +DealStatus status
        +accept()
        +expire()
    }

    class NegotiationStrategy {
        <<Interface>>
        +selectBestOffer(vector~NILDeal~) NILDeal
    }

    class GreedyStrategy{
      +selectBestOffer(vector~NILDeal~) NILDeal
    }
    class LoyalStrategy{
      +selectBestOffer(vector~NILDeal~) NILDeal
    }
    class PrestigeStrategy{
      +selectBestOffer(vector~NILDeal~) NILDeal
    }

    Team "1" o-- "0..*" Player : has a roster of
    Player "1" o-- "1" NegotiationStrategy : uses
    Player "1" -- "0..*" NILDeal : signs
    NILDeal "1" -- "1" Sponsor : is offered by
    NegotiationStrategy <|-- GreedyStrategy
    NegotiationStrategy <|-- LoyalStrategy
    NegotiationStrategy <|-- PrestigeStrategy