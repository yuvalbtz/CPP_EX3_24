// development_card.cpp
#include "development_card.hpp"

namespace ariel {

    std::string developmentCardTypeToString(DevelopmentCardType type) {
        switch (type) {
            case DevelopmentCardType::Monopoly:
                return "Monopoly";
            case DevelopmentCardType::RoadBuilding:
                return "Road Building";
            case DevelopmentCardType::YearOfPlenty:
                return "Year of Plenty";
            case DevelopmentCardType::Knight:
                return "Knight";
            case DevelopmentCardType::VictoryPoint:
                return "Victory Point";
            default:
                return "Unknown";
        }
    }

}
