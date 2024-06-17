#include "settlement.hpp"

namespace ariel {

    Settlement::Settlement(std::string nameOfOwner, Tile tile1, Tile tile2, Tile tile3) {
        // Insert the nearby tiles into the set
        this->nearby_areas.insert(tile1);
        this->nearby_areas.insert(tile2);
        this->nearby_areas.insert(tile3);
        // Set the name of the owner
        this->nameOfOwner = nameOfOwner;
    }

    const std::set<Tile>& Settlement::getNearbyAreas() const {
        return this->nearby_areas;  // Return the set of nearby areas
    }

    bool Settlement::operator==(const Settlement& other) const {
        // Check if the sizes of the nearby areas are different
        if (this->nearby_areas.size() != other.nearby_areas.size()) {
            return false;
        }

        // Compare each tile in the nearby areas
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

    bool Settlement::operator<(const Settlement& other) const {
        // Compare the names of the owners
        if (this->nameOfOwner != other.nameOfOwner) {
            return this->nameOfOwner < other.nameOfOwner;
        }
        // Compare the sets of nearby areas
        return this->nearby_areas < other.nearby_areas;
    }

    std::ostream& operator<<(std::ostream& os, const Settlement& settlement) {
        os << "Settlement(name of owner: " << settlement.nameOfOwner << "\n";
        os << "nearby_areas: [\n";
        // Print each tile in the nearby areas
        for (const auto& tile : settlement.nearby_areas) {
            os << "  " << tile << ",\n";
        }
        os << "])\n";
        return os;
    }
}