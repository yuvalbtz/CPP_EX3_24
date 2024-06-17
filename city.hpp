#ifndef CITY_HPP
#define CITY_HPP

#include <iostream>
#include <set>
#include "tile.hpp"

using namespace std;

namespace ariel {

    class City {
    private:
        string nameOfOwner; 
        set<Tile> nearby_areas;

    public:

        City(string nameOfOwner, Tile tile1, Tile tile2, Tile tile3);
        const std::set<Tile>& getNearbyAreas() const;
        bool operator==(const City& other) const;
        bool operator<(const City& other) const;
        friend std::ostream& operator<<(std::ostream& os, const City& city);
    };

}

#endif