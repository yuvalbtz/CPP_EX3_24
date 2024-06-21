#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <string>
#include <set>
using namespace std;
namespace ariel
{

    class Tile
    {
    private:
        string terrain;
        int number;
        set<Tile *> nearby_areas;

    public:
        Tile();
        Tile(const string &terrain, int number);
        Tile(const Tile &other);
        string getTerrain() const;
        int getNumber() const;
        void setTerrain(const string &terrain);
        void setNumber(int number);
        const set<Tile *> &getNearbyAreas() const;
        void setNearbyAreas(const initializer_list<Tile *> &nearbyTiles);
        Tile &operator=(const Tile &other);
        bool operator==(const Tile &other) const;
        bool operator!=(const Tile &other) const;
        bool operator<(const Tile &other) const;
        friend ostream &operator<<(ostream &os, const Tile &tile);
    };

} // namespace ariel

#endif // TILE_HPP