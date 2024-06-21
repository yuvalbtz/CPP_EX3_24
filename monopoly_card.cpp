#include "monopoly_card.hpp"
using namespace std;
namespace ariel
{

    void MonopolyCard::play(Player &player, vector<reference_wrapper<ariel::Player>> players, const string &resource)
    {
        // Iterate over all players to take the specified resource
        for (auto &other_player_ref : players)
        {
            Player &other_player = other_player_ref.get(); // Dereference the reference wrapper
            if (&other_player != &player)
            {
                // Transfer all of the specified resource from other players to the current player
                player.takeAllResources(other_player, resource);
            }
        }
        // Notify that the Monopoly card has been played
        cout << "Monopoly card played by " << player.getName() << ": All " << resource << " taken from other players." << endl;
    }

} // namespace ariel