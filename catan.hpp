#ifndef CATAN_H
#define CATAN_H

#include <iostream>
#include "knight_card.hpp"
#include "monopoly_card.hpp"
#include "road_building_card.hpp"
#include "year_of_plenty_card.hpp"
#include "player.hpp"
#include "board.hpp"
#include <ctime>

namespace ariel {

class Catan {
private:
    Player& player1;
    Player& player2;
    Player& player3; 
    Player* currentPlayer;
    Board board; 

public:
    Catan(Player &player1, Player &player2, Player &player3);
    Board& getBoard();
    void rollDice(Player& player);
    void endTurn(Player& player);
    void trade(Player &First_Player, Player &Second_Player, std::string resource1, std::string resource2, int num1, int num2);
    void playDevelopmentCard(Player &player, std::string resource);
    void playDevelopmentCard(Player &player, std::vector<std::string> places1, std::vector<int> placesNum1, std::vector<std::string> places2, std::vector<int> placesNum2, Board& board);
    void playDevelopmentCard(Player& player, const std::string& resource1, const std::string& resource2);
    void playDevelopmentCard(Player& player);
    void printWinner();
};

} // namespace ariel

#endif // CATAN_H