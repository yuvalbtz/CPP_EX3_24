// development_card.hpp
#pragma once

#include <string>

namespace ariel {

    enum class DevelopmentCardType {
        Monopoly,
        RoadBuilding,
        YearOfPlenty,
        Knight,
        VictoryPoint
    };

    std::string developmentCardTypeToString(DevelopmentCardType type);

}
