#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "player.hpp"
#include "board.hpp"

using namespace ariel;

TEST_CASE("Player Initialization") {
    Player p("Alice");
    REQUIRE(p.getName() == "Alice");
}

TEST_CASE("Place Settlement") {
    Player p("Alice");
    Board board;
    std::vector<std::string> places = {"Forest"};
    std::vector<int> placesNum = {5};
    p.placeSettlement(places, placesNum, board);
    // Add assertions based on your board implementation
}

TEST_CASE("Place Road") {
    Player p("Alice");
    Board board;
    std::vector<std::string> places = {"Forest", "Hills"};
    std::vector<int> placesNum = {5, 6};
    p.placeRoad(places, placesNum, board);
    // Add assertions based on your board implementation
}

TEST_CASE("Trade Resources") {
    Player p1("Alice");
    Player p2("Bob");
    p1.resources["wood"] = 2;
    p2.resources["brick"] = 2;
    p1.trade(p2, "wood", "brick", 1, 1);
    REQUIRE(p1.resources["wood"] == 1);
    REQUIRE(p1.resources["brick"] == 1);
    REQUIRE(p2.resources["wood"] == 1);
    REQUIRE(p2.resources["brick"] == 1);
}

TEST_CASE("Buy Development Card") {
    Player p("Alice");
    p.resources["grain"] = 1;
    p.resources["wool"] = 1;
    p.resources["ore"] = 1;
    p.buyDevelopmentCard();
    REQUIRE(p.developmentCards == 1);
    REQUIRE(p.resources["grain"] == 0);
    REQUIRE(p.resources["wool"] == 0);
    REQUIRE(p.resources["ore"] == 0);
}

TEST_CASE("Insufficient Resources for Development Card") {
    Player p("Alice");
    p.resources["grain"] = 0;
    p.resources["wool"] = 1;
    p.resources["ore"] = 1;
    REQUIRE_THROWS_AS(p.buyDevelopmentCard(), std::invalid_argument);
}
