#ifndef SETTLEMENT_HPP
#define SETTLEMENT_HPP

#include <iostream>
#include <set>
#include <string>
#include "tile.hpp"

using namespace std;

namespace ariel
{

    class Settlement
    {
    private:
        string nameOfOwner;
        set<Tile> nearby_areas;

    public:
        Settlement(string nameOfOwner, Tile tile1, Tile tile2, Tile tile3);
        const set<Tile> &getNearbyAreas() const;
        bool operator==(const Settlement &other) const;
        bool operator<(const Settlement &other) const;
        friend ostream &operator<<(ostream &os, const Settlement &settlement);
    };

} // namespace ariel

#endif // SETTLEMENT_HPP