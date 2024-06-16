#include "catan.hpp"
#include <iostream>

namespace ariel {

    Catan::Catan(Player& p1, Player& p2, Player& p3) : player1(p1), player2(p2), player3(p3), currentPlayer(&p1), gameBoard() {}

    void Catan::ChooseStartingPlayer() {
        std::cout << "Starting player: " << currentPlayer->getName() << std::endl;
        // Add logic to choose starting player (currently assumed to be player1)
    }

    Board Catan::getBoard() const {
        return gameBoard;
    }

    void Catan::printWinner() const {
        std::cout << "None" << std::endl; // Placeholder logic to print the winner based on points
    }

}
