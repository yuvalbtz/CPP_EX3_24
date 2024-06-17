#ifndef ROADBUILDINGCARD_HPP
#define ROADBUILDINGCARD_HPP

#include <vector>
#include <string>
#include "development_card.hpp"
#include "player.hpp"
#include "board.hpp"

namespace ariel {

class Player;
class Board;

class RoadBuildingCard : public DevelopmentCard {
public:
    void play(Player& player, std::vector<std::string> places1, std::vector<int> placesNum1, std::vector<std::string> places2, std::vector<int> placesNum2, Board& board);
};

} // namespace ariel

#endif // ROADBUILDINGCARD_HPP