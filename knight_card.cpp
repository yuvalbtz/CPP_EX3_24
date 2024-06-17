#include "knight_card.hpp"

namespace ariel {

    Tile* KnightCard::knight = new Tile("NoTerrain", 0); // Default initialization

    Tile* KnightCard::getKnight() {
        return knight;
    }

    void KnightCard::setKnight(const std::string& terrain, int number) {
        if (knight == nullptr) {
            // Initialize knight if it is null
            knight = new Tile(terrain, number);
        } else {
            // Update the existing knight object
            knight->setTerrain(terrain);
            knight->setNumber(number);
        }
    }

    void KnightCard::play(Player& player) {
        // Prompt the player to enter the resource and number for the knight's tile
        string terrain;
        int num;
        std::cout << "Enter a resource and a number of a tile you want to put the knight on (e.g., Agricultural Land 4): ";
        std::cin >> terrain >> num;

        // Create a new Tile for the knight
        Tile knight(terrain, num);
        // Update the static knight pointer
        this->knight = &knight;

        // Notify the player that the knight card has been played
        std::cout << "Knight card played by " << player.getName() << ": Move the robber to tile with " << terrain << " and number " << num << std::endl;
    }

}  // namespace ariel
