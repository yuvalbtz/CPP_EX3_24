#include "road_building_card.hpp"


namespace ariel {

    void RoadBuildingCard::play(Player& player, std::vector<std::string> places1, std::vector<int> placesNum1, std::vector<std::string> places2, std::vector<int> placesNum2, Board& board) {
        player.setBricks(player.getBricks()+2); // Add 2 bricks to the player's resources
        player.setWood(player.getWood()+2); // Add 2 wood to the player's resources
        player.placeRoad(places1, placesNum1, board); // Place the first road
        player.placeRoad(places2, placesNum2, board); // Place the second road
        // Notify that the Road Building card has been played
        std::cout << "Road Building card played by " << player.getName() << ": You can build two roads without cost." << std::endl;
    }

} // namespace ariel