#include "year_of_plenty_card.hpp"
using namespace std;
namespace ariel
{

    void YearOfPlentyCard::play(Player &player, string resource1, string resource2)
    {
        player.getCards(resource1, 1); // Grant 1 unit of the first resource to the player
        player.getCards(resource2, 1); // Grant 1 unit of the second resource to the player
        // Notify that the Year of Plenty card has been played
        cout << "Year of Plenty card played by " << player.getName() << ": You received " << resource1 << " and " << resource2 << " from the bank." << endl;
    }

} // namespace ariel