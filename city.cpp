#include "city.hpp"

namespace ariel {

    City::City(std::string nameOfOwner, Tile tile1, Tile tile2, Tile tile3) {
        // Insert the tiles into the set of nearby areas
        this->nearby_areas.insert(tile1);
        this->nearby_areas.insert(tile2);
        this->nearby_areas.insert(tile3);
        // Set the name of the owner
        this->nameOfOwner = nameOfOwner;
    }

    const std::set<Tile>& City::getNearbyAreas() const {
        return this->nearby_areas;  // Return the set of nearby areas
    }

    bool City::operator==(const City& other) const {
        // Check if the sizes of the nearby areas sets are different
        if (this->nearby_areas.size() != other.nearby_areas.size()) {
            return false;
        }

        // Compare each tile in the nearby areas sets
        auto it1 = this->nearby_areas.begin();
        auto it2 = other.nearby_areas.begin();
        while (it1 != this->nearby_areas.end() && it2 != other.nearby_areas.end()) {
            if (!(*it1 == *it2)) {
                return false;
            }
            ++it1;
            ++it2;
        }
        return true;
    }

    bool City::operator<(const City& other) const {
        // Check if either owner's name is empty
        if (this->nameOfOwner.empty() || other.nameOfOwner.empty()) {
            return true;
        }
        // Compare the names of the owners
        if (this->nameOfOwner != other.nameOfOwner) {
            return this->nameOfOwner < other.nameOfOwner;
        }
        // Compare the nearby areas
        return this->nearby_areas < other.nearby_areas;
    }

    std::ostream& operator<<(std::ostream& os, const City& city) {
        // Print the owner's name
        os << "City(name of owner: " << city.nameOfOwner << "\n";
        // Print the nearby areas
        os << "nearby_areas: [\n";
        for (const auto& tile : city.nearby_areas) {
            os << "  " << tile << ",\n";
        }
        os << "])\n";
        return os;
    }
}  // namespace ariel