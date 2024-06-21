#include "tile.hpp"
using namespace std;
namespace ariel
{

    Tile::Tile() : terrain(""), number(0) {}

    Tile::Tile(const string &terrain, int number) : terrain(terrain), number(number) {}

    Tile::Tile(const Tile &other) : terrain(other.terrain), number(other.number)
    {
        // Copy nearby_areas from the other tile
        for (auto tile : other.nearby_areas)
        {
            nearby_areas.insert(tile);
        }
    }

    string Tile::getTerrain() const
    {
        return terrain;
    }

    int Tile::getNumber() const
    {
        return number;
    }

    void Tile::setTerrain(const string &terrain)
    {
        this->terrain = terrain;
    }

    void Tile::setNumber(int number)
    {
        this->number = number;
    }

    const set<Tile *> &Tile::getNearbyAreas() const
    {
        return this->nearby_areas; // Return the set of nearby areas
    }

    void Tile::setNearbyAreas(const initializer_list<Tile *> &nearbyTiles)
    {
        nearby_areas.clear();
        for (Tile *tile : nearbyTiles)
        {
            nearby_areas.insert(tile);
        }
    }

    Tile &Tile::operator=(const Tile &other)
    {
        if (this != &other)
        {
            terrain = other.terrain;
            number = other.number;
            nearby_areas.clear();
            // Copy nearby_areas from the other tile
            for (auto tile : other.nearby_areas)
            {
                nearby_areas.insert(tile);
            }
        }
        return *this;
    }

    bool Tile::operator==(const Tile &other) const
    {
        if (this->terrain.empty() || other.terrain.empty())
        {
            return false;
        }
        return this->terrain == other.terrain && this->number == other.number;
    }

    bool Tile::operator!=(const Tile &other) const
    {
        return !(*this == other);
    }

    bool Tile::operator<(const Tile &other) const
    {
        if (terrain == other.terrain)
        {
            return number < other.number;
        }
        return terrain < other.terrain;
    }

    ostream &operator<<(ostream &os, const Tile &tile)
    {
        os << "Tile(terrain: " << tile.terrain << ", number: " << tile.number << ".";
        return os;
    }
}