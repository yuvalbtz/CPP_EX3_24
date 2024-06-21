#include "road_building_card.hpp"

using namespace std;
namespace ariel
{

    void RoadBuildingCard::play(Player &player, vector<string> places1, vector<int> placesNum1, vector<string> places2, vector<int> placesNum2, Board &board)
    {
        player.setBricks(player.getBricks() + 2);     // Add 2 bricks to the player's resources
        player.setWood(player.getWood() + 2);         // Add 2 wood to the player's resources
        player.placeRoad(places1, placesNum1, board); // Place the first road
        player.placeRoad(places2, placesNum2, board); // Place the second road
        // Notify that the Road Building card has been played
        cout << "Road Building card played by " << player.getName() << ": You can build two roads without cost." << endl;
    }

} // namespace ariel