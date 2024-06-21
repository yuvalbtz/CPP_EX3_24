#ifndef ROADBUILDINGCARD_HPP
#define ROADBUILDINGCARD_HPP

#include <vector>
#include <string>
#include "development_card.hpp"
#include "player.hpp"
#include "board.hpp"
using namespace std;
namespace ariel
{

    class Player;
    class Board;

    class RoadBuildingCard : public DevelopmentCard
    {
    public:
        void play(Player &player, vector<string> places1, vector<int> placesNum1, vector<string> places2, vector<int> placesNum2, Board &board);
    };

} // namespace ariel

#endif // ROADBUILDINGCARD_HPP