#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include "tile.hpp"
#include "settlement.hpp"
#include "city.hpp"
#include "road.hpp"

using namespace std;

namespace ariel {

    class Board {
    private:
        vector<Tile> tiles;   
        set<Road> roads;       
        set<Settlement> settlements; 
        set<City> Cities;    

    public:
        Board();
        vector<Tile>& getTiles();
        set<Road>& getRoads();
        set<Settlement>& getSettlements();
        set<City>& getCities();
        Board& operator=(const Board& other);
        bool isPossibleRoad(const Road& road) const;
        bool isPossibleSettlement(const Settlement& settlement, const City& city) const;
    };
} // namespace ariel

#endif // BOARD_HPP