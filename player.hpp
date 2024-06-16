#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "board.hpp"

namespace ariel {

    class Player {
    private:
        std::string name;
        int points;
        std::unordered_map<std::string, int> resources;
        int developmentCards;

    public:
        Player(const std::string& name);
        
        void placeSettelemnt(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board);
        void placeRoad(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board);
        void rollDice();
        void endTurn();
        void trade(Player& other, const std::string& give, const std::string& take, int giveAmount, int takeAmount);
        void buyDevelopmentCard();
        void printPoints() const;
        std::string getName() const;
        int getPoints() const;
    };

}

#endif
