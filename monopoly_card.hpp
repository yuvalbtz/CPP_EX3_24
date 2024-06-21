#ifndef MONOPOLYCARD_HPP
#define MONOPOLYCARD_HPP

#include <vector>
#include <string>
#include "development_card.hpp"
#include "player.hpp"
using namespace std;
namespace ariel
{

    class Player;

    class MonopolyCard : public DevelopmentCard
    {
    public:
        void play(Player &player, vector<reference_wrapper<ariel::Player>> players, const string &resource);
    };

} // namespace ariel

#endif // MONOPOLYCARD_HPP