#ifndef MONOPOLYCARD_HPP
#define MONOPOLYCARD_HPP

#include <vector>
#include <string>
#include "development_card.hpp"
#include "player.hpp"

namespace ariel {

class Player;

class MonopolyCard : public DevelopmentCard {
public:
    void play(Player& player, std::vector<std::reference_wrapper<ariel::Player>> players, const std::string& resource);
};

} // namespace ariel

#endif // MONOPOLYCARD_HPP