#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>
#include <unordered_map>

namespace ariel {

    class Board {
    private:
        // Each tile on the board is represented by a pair of (resource type, number)
        std::vector<std::pair<std::string, int>> tiles;
        std::unordered_map<std::string, std::vector<int>> settlements; // Player name -> list of settlement tile indices
        std::unordered_map<std::string, std::vector<int>> roads;       // Player name -> list of road tile indices

    public:
        Board();
        bool placeSettlement(const std::string& playerName, const std::vector<int>& tileIndices);
        bool placeRoad(const std::string& playerName, const std::vector<int>& tileIndices);
        std::vector<std::pair<std::string, int>> getTiles() const;
        std::unordered_map<std::string, std::vector<int>> getSettlements() const;
        std::unordered_map<std::string, std::vector<int>> getRoads() const;
    };

}

#endif
