// player.hpp
#pragma once

#include <string>
#include <vector>
#include <map>
#include "board.hpp"
#include "development_card.hpp"

namespace ariel {

    class Player {
    private:
        std::string name;
        int points;
        int developmentCards;
        std::map<std::string, int> resources;
        std::vector<DevelopmentCardType> developmentCardsOwned;
        int knightCount;
        bool hasLargestArmy;
        
        // Helper function to randomly draw a development card
        DevelopmentCardType drawDevelopmentCard();

    public:
        Player(const std::string& name);

        void placeSettelemnt(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board);
        void placeRoad(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board);
        void rollDice();
        void endTurn();
        void trade(Player& other, const std::string& give, const std::string& take, int giveAmount, int takeAmount);
        void buyDevelopmentCard();
        void useDevelopmentCard(DevelopmentCardType cardType, Board& board, std::vector<Player>& players);

        void printPoints() const;
        std::string getName() const;
        int getPoints() const;
    };

}
