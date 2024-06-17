#ifndef ROAD_HPP
#define ROAD_HPP

#include <iostream>
#include <set>
#include <string>
#include "tile.hpp"

using namespace std;

namespace ariel {

    class Road {
    private:
        string nameOfOwner;
        set<Tile> nearby_areas;

    public:
        Road(string nameOfOwner, Tile tile1, Tile tile2);
        const std::set<Tile>& getNearbyAreas() const;
        bool operator==(const Road& other) const;
        bool operator<(const Road& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Road& road);
    };

}

#endif // ROAD_HPP