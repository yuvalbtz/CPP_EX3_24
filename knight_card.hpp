#ifndef KNIGHTCARD_HPP
#define KNIGHTCARD_HPP

#include "development_card.hpp"
#include "tile.hpp"
#include "player.hpp"
#include <string>
using namespace std;
namespace ariel
{

    class KnightCard : public DevelopmentCard
    {
    public:
        void play(Player &player);
        static void setKnight(const string &name, int number);
        static Tile *getKnight();

    private:
        static Tile *knight; //  Static pointer to the knight tile
    };

} // namespace ariel

#endif // KNIGHTCARD_HPP