#ifndef YEAROFPLENTYCARD_HPP
#define YEAROFPLENTYCARD_HPP

#include <string>
#include "development_card.hpp"
#include "player.hpp"
using namespace std;
namespace ariel
{

    class Player;

    class YearOfPlentyCard : public DevelopmentCard
    {
    public:
        void play(Player &player, string resource1, string resource2);
    };

} // namespace ariel

#endif // YEAROFPLENTYCARD_HPP