#ifndef CATAN_HPP
#define CATAN_HPP

#include "player.hpp"
#include "board.hpp"

namespace ariel {

    class Catan {
    public:
        Catan(Player& p1, Player& p2, Player& p3);

        void ChooseStartingPlayer();
        Board getBoard() const;
        void printWinner() const;

    private:
        Player& player1;
        Player& player2;
        Player& player3;
        Player* currentPlayer;
        Board gameBoard;
    };

}

#endif // CATAN_HPP
