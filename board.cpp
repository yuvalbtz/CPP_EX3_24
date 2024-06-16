#include "board.hpp"
#include <algorithm> 
namespace ariel {

    Board::Board() {
        // Initialize the board with tiles. This is a simple representation.
        // In a full implementation, the board should be more complex and initialized according to the game rules.
        tiles = {
            {"Forest", 5}, {"Hills", 6}, {"Agricultural Land", 3}, {"Desert", 4}, {"Mountains", 4},
            {"Pasture Land", 9}, {"Forest", 5}, {"Hills", 6}, {"Agricultural Land", 3}, {"Desert", 4},
            {"Mountains", 4}, {"Pasture Land", 9}, {"Forest", 5}, {"Hills", 6}, {"Agricultural Land", 3},
            {"Desert", 4}, {"Mountains", 4}, {"Pasture Land", 9}, {"Forest", 5}
        };
    }

    bool Board::placeSettlement(const std::string& playerName, const std::vector<int>& tileIndices) {
        // Check if the placement is valid (e.g., not already occupied)
        for (int index : tileIndices) {
            if (settlements.count(playerName) && 
                std::find(settlements[playerName].begin(), settlements[playerName].end(), index) != settlements[playerName].end()) {
                return false; // Settlement already exists at this location for this player
            }
        }
        // Place the settlement
        settlements[playerName].insert(settlements[playerName].end(), tileIndices.begin(), tileIndices.end());
        return true;
    }

    bool Board::placeRoad(const std::string& playerName, const std::vector<int>& tileIndices) {
        // Check if the placement is valid (e.g., not already occupied)
        for (int index : tileIndices) {
            if (roads.count(playerName) && 
                std::find(roads[playerName].begin(), roads[playerName].end(), index) != roads[playerName].end()) {
                return false; // Road already exists at this location for this player
            }
        }
        // Place the road
        roads[playerName].insert(roads[playerName].end(), tileIndices.begin(), tileIndices.end());
        return true;
    }

    std::vector<std::pair<std::string, int>> Board::getTiles() const {
        return tiles;
    }

    std::unordered_map<std::string, std::vector<int>> Board::getSettlements() const {
        return settlements;
    }

    std::unordered_map<std::string, std::vector<int>> Board::getRoads() const {
        return roads;
    }

}
