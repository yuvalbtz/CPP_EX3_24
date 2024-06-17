#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <string>
#include <set>

namespace ariel {

class Tile {
private:
    std::string terrain;
    int number;
    std::set<Tile*> nearby_areas;

public:
    Tile();
    Tile(const std::string& terrain, int number);
    Tile(const Tile& other);
    std::string getTerrain() const;
    int getNumber() const;
    void setTerrain(const std::string& terrain);
    void setNumber(int number);
    const std::set<Tile*>& getNearbyAreas() const;
    void setNearbyAreas(const std::initializer_list<Tile*>& nearbyTiles);
    Tile& operator=(const Tile& other);
    bool operator==(const Tile& other) const;
    bool operator!=(const Tile& other) const;
    bool operator<(const Tile& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Tile& tile);
};

} // namespace ariel

#endif // TILE_HPP