#include "road.hpp"

namespace ariel {

    Road::Road(string nameOfOwner, Tile tile1, Tile tile2) {
        // Insert the nearby tiles into the set
        this->nearby_areas.insert(tile1);
        this->nearby_areas.insert(tile2);
        // Set the name of the owner
        this->nameOfOwner = nameOfOwner;
    }

    const std::set<Tile>& Road::getNearbyAreas() const {
        return this->nearby_areas;  // Return the set of nearby areas
    }

    bool Road::operator==(const Road& other) const {
        // Check if the names of the owners are different
        if (this->nameOfOwner != other.nameOfOwner) {
            return false;
        }

        // Compare each tile in the nearby areas sets
        auto it1 = this->nearby_areas.begin();
        auto it2 = other.nearby_areas.begin();
        for (; it1 != this->nearby_areas.end() && it2 != other.nearby_areas.end(); ++it1, ++it2) {
            if (*it1 != *it2) {
                return false;
            }
        }
        return true;
    }

    bool Road::operator<(const Road& other) const {
        // First compare the names of the owners
        if (this->nameOfOwner != other.nameOfOwner) {
            return this->nameOfOwner < other.nameOfOwner;
        }

        // If the names are the same, compare the nearby_areas
        auto it1 = this->nearby_areas.begin();
        auto it2 = other.nearby_areas.begin();
        for (; it1 != this->nearby_areas.end() && it2 != other.nearby_areas.end(); ++it1, ++it2) {
            if (*it1 != *it2) {
                return *it1 < *it2;
            }
        }

        // If all compared tiles are equal, the road with fewer nearby tiles is considered less
        return this->nearby_areas.size() < other.nearby_areas.size();
    }

    // Output operator implementation
    std::ostream& operator<<(std::ostream& os, const Road& road) {
        // Print the owner's name
        os << "Road(name of owner: " << road.nameOfOwner << ", nearby_areas: [";
        // Print each tile in the nearby areas
        for (const auto& tile : road.nearby_areas) {
            os << tile << ", ";
        }
        os << "])";
        return os;
    }

} // namespace ariel