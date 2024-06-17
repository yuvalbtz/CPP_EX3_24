#ifndef SETTLEMENT_HPP
#define SETTLEMENT_HPP

#include <iostream>
#include <set>
#include <string>
#include "tile.hpp"

using namespace std;

namespace ariel {

class Settlement {
private:
    std::string nameOfOwner;
    std::set<Tile> nearby_areas;

public:
    Settlement(std::string nameOfOwner, Tile tile1, Tile tile2, Tile tile3);
    const std::set<Tile>& getNearbyAreas() const;
    bool operator==(const Settlement& other) const;
    bool operator<(const Settlement& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Settlement& settlement);
};

} // namespace ariel

#endif // SETTLEMENT_HPP