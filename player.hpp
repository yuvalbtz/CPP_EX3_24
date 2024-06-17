#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <memory>
#include <string>
#include <algorithm>
#include "board.hpp"
#include "tile.hpp"
#include "settlement.hpp"
#include "city.hpp"
#include "road.hpp"

using namespace std;

namespace ariel {

    // forward declaration
    class DevelopmentCard;
    class MonopolyCard;
    class KnightCard;
    class RoadBuildingCard;
    class YearOfPlentyCard;

    class Player {
    private:

        std::vector<std::unique_ptr<DevelopmentCard>> developmentCards;
        string name;
        set<Settlement> possibleSettlements;
        set<Road> possibleRoads;
        set<Settlement> mySettlements;
        set<Road> myRoads;
        set<City> myCities;

        int wood; 
        int bricks; 
        int wheat; 
        int ore; 
        int wool; 

        bool isPossibleRoad(Road myRoad);
        bool isPossibleSettlement(Settlement mySettelemnt);
        void showCards() const;

    public:

      
        Player(string name);
        string getName() const;
        void setName(const string& name);
        std::vector<std::unique_ptr<DevelopmentCard>>& getDevelopmentCards();
        const set<Settlement>& getSettlements() const;
        const set<Road>& getRoads() const;
        const set<City>& getCities() const;
        int getWood() const;
        void setWood(int amount);
        int getBricks() const;
        void setBricks(int amount);
        int getWheat() const;
        void setWheat(int amount);
        int getOre() const;
        void setOre(int amount);
        int getWool() const;
         void setWool(int amount);
        void placeSettelemnt(vector<string> places, vector<int> placesNum, Board &board);
        void placeRoad(vector<string> places, vector<int> placesNum, Board &board);
        void placeCity(vector<string> places, vector<int> placesNum, Board &board);
        void getCards(string resource, int amount);
        bool resource_exist(string resource, int num);
        void discardCards();
        void distributeResources(int num);
        void takeAllResources(Player &other, string resource);
        void buyDevelopmentCard();
        int myPoints();
        void printPoints();
        void printAllInfo();
        bool operator==(const Player &player) const;
    };
}

#endif // PLAYER_H