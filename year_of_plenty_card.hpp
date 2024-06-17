#ifndef YEAROFPLENTYCARD_HPP
#define YEAROFPLENTYCARD_HPP

#include <string>
#include "development_card.hpp"
#include "player.hpp"

namespace ariel {

class Player;

class YearOfPlentyCard : public DevelopmentCard {
public:
    void play(Player& player, std::string resource1, std::string resource2);
};

} // namespace ariel

#endif // YEAROFPLENTYCARD_HPP