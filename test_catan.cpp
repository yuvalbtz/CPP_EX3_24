#include "catch.hpp"
#include "catan.hpp"
#include "player.hpp"

using namespace ariel;

TEST_CASE("Catan Initialization") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charlie");
    Catan game(p1, p2, p3);
    // REQUIRE(game.getBoard().getTile() == Board().getTile()); // Assuming Board has a valid equality operator
}

TEST_CASE("Choose Starting Player") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charlie");
    Catan game(p1, p2, p3);
    game.ChooseStartingPlayer();
    // Based on your implementation, assert the correct starting player
}


