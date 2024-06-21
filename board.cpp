#include "board.hpp"
#include <array>

using namespace std;

namespace ariel
{

    Board::Board() : tiles(19)
    { // Initializer list approach
        // initializes the tiles vector with 19 elements. Each element is a default-constructed Tile object.
        tiles[0] = {"Mountains", 9}; // Initialize specific tile with terrain and number
        tiles[1] = {"Pasture Land", 2};
        tiles[2] = {"Forest", 9};
        tiles[3] = {"Agricultural Land", 12};
        tiles[4] = {"Hills", 6};
        tiles[5] = {"Pasture Land", 4};
        tiles[6] = {"Hills", 10};
        tiles[7] = {"Agricultural Land", 9};
        tiles[8] = {"Forest", 11};
        tiles[9] = {"Desert", 0};
        tiles[10] = {"Forest", 3};
        tiles[11] = {"Mountains", 8};
        tiles[12] = {"Forest", 8};
        tiles[13] = {"Mountains", 3};
        tiles[14] = {"Agricultural Land", 4};
        tiles[15] = {"Pasture Land", 5};
        tiles[16] = {"Hills", 5};
        tiles[17] = {"Agricultural Land", 6};
        tiles[18] = {"Pasture Land", 11};

        // Initialize neighbors using indices
        tiles[0].setNearbyAreas({&tiles[1], &tiles[3], &tiles[4]});
        tiles[1].setNearbyAreas({&tiles[0], &tiles[2], &tiles[4], &tiles[5]});
        tiles[2].setNearbyAreas({&tiles[1], &tiles[5], &tiles[6]});
        tiles[3].setNearbyAreas({&tiles[0], &tiles[4], &tiles[7], &tiles[8]});
        tiles[4].setNearbyAreas({&tiles[0], &tiles[1], &tiles[3], &tiles[5], &tiles[8], &tiles[9]});
        tiles[5].setNearbyAreas({&tiles[1], &tiles[2], &tiles[4], &tiles[6], &tiles[9], &tiles[10]});
        tiles[6].setNearbyAreas({&tiles[2], &tiles[5], &tiles[10], &tiles[11]});
        tiles[7].setNearbyAreas({&tiles[3], &tiles[8], &tiles[12]});
        tiles[8].setNearbyAreas({&tiles[3], &tiles[4], &tiles[7], &tiles[9], &tiles[12], &tiles[13]});
        tiles[9].setNearbyAreas({&tiles[4], &tiles[5], &tiles[8], &tiles[10], &tiles[13], &tiles[14]});
        tiles[10].setNearbyAreas({&tiles[5], &tiles[6], &tiles[9], &tiles[11], &tiles[14], &tiles[15]});
        tiles[11].setNearbyAreas({&tiles[6], &tiles[10], &tiles[15]});
        tiles[12].setNearbyAreas({&tiles[7], &tiles[8], &tiles[16]});
        tiles[13].setNearbyAreas({&tiles[8], &tiles[9], &tiles[16], &tiles[17]});
        tiles[14].setNearbyAreas({&tiles[9], &tiles[10], &tiles[17], &tiles[18]});
        tiles[15].setNearbyAreas({&tiles[10], &tiles[11], &tiles[18]});
        tiles[16].setNearbyAreas({&tiles[12], &tiles[13], &tiles[17]});
        tiles[17].setNearbyAreas({&tiles[13], &tiles[14], &tiles[16], &tiles[18]});
        tiles[18].setNearbyAreas({&tiles[14], &tiles[15], &tiles[17]});
    }

    vector<Tile> &Board::getTiles()
    {
        return tiles;
    }

    set<Road> &Board::getRoads()
    {
        return roads;
    }

    set<Settlement> &Board::getSettlements()
    {
        return settlements;
    }

    set<City> &Board::getCities()
    {
        return Cities;
    }

    bool Board::isPossibleRoad(const Road &road) const
    {
        for (const auto &road_on_Board : roads)
        { // Iterate through all roads on the board
            if (road == road_on_Board)
            {                 // Check if the given road matches any existing road
                return false; // Road placement is not possible if it already exists
            }
        }
        return true; // Road placement is possible if no matching road is found
    }

    bool Board::isPossibleSettlement(const Settlement &settlement, const City &city) const
    {
        for (const auto &settlement_on_Board : settlements)
        { // Iterate through all settlements on the board
            if (settlement == settlement_on_Board)
            {                 // Check if the given settlement matches any existing settlement
                return false; // Settlement placement is not possible if it already exists
            }
        }
        for (const auto &city_on_Board : Cities)
        { // Iterate through all cities on the board
            if (city == city_on_Board)
            {                 // Check if the given city matches any existing city
                return false; // Settlement placement is not possible if it matches an existing city
            }
        }
        return true; // Settlement placement is possible if no matching settlement or city is found
    }

    // Assignment operator
    Board &Board::operator=(const Board &other)
    {
        cout << "Board assignment operator called" << endl;
        if (this != &other)
        {                                    // Check for self-assignment
            tiles = other.tiles;             // Copy tiles
            roads = other.roads;             // Copy roads
            settlements = other.settlements; // Copy settlements
        }
        return *this; // Return the updated object
    }
}