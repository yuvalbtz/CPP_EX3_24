#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "player.hpp"
#include "board.hpp"
#include "development_card.hpp"
#include "monopoly_card.hpp"
#include "knight_card.hpp"
#include "victory_point_card.hpp"
#include "road_building_card.hpp"

using namespace ariel;

TEST_CASE("Player Constructor and Getters")
{
    Player p("Alice");
    REQUIRE(p.getName() == "Alice");
    REQUIRE(p.getWood() == 0);
    REQUIRE(p.getBricks() == 0);
    REQUIRE(p.getWheat() == 0);
    REQUIRE(p.getOre() == 0);
    REQUIRE(p.getWool() == 0);
}

TEST_CASE("Resource Management")
{
    Player p("Bob");
    p.getCards("wood", 5);
    REQUIRE(p.getWood() == 5);
    p.getCards("wood", -2);
    REQUIRE(p.getWood() == 3);
    REQUIRE(p.resource_exist("wood", 2) == true);
    REQUIRE(p.resource_exist("wood", 4) == false);
}

TEST_CASE("Place Settlement")
{
    Player p("Carol");
    Board board;
    // Setup initial board state if needed
    vector<string> places = {"Forest", "Hills", "Mountains"};
    vector<int> placesNum = {5, 3, 8};
    REQUIRE_NOTHROW(p.placeSettelemnt(places, placesNum, board));
    REQUIRE(p.getSettlements().size() == 1);
}

TEST_CASE("Place Road")
{
    Player p("Dave");
    Board board;
    // Setup initial board state if needed
    vector<string> places = {"Forest", "Hills"};
    vector<int> placesNum = {5, 3};
    REQUIRE_NOTHROW(p.placeRoad(places, placesNum, board));
    REQUIRE(p.getRoads().size() == 1);
}

TEST_CASE("Buy Development Card")
{
    Player p("Eve");
    p.getCards("ore", 1);
    p.getCards("wheat", 1);
    p.getCards("wool", 1);
    REQUIRE_NOTHROW(p.buyDevelopmentCard());
    REQUIRE(p.getDevelopmentCards().size() == 1);
}

TEST_CASE("City Constructor and Getters")
{
    Tile t1("Forest", 5);
    Tile t2("Hills", 3);
    Tile t3("Mountains", 8);

    City c("Alice", t1, t2, t3);

    REQUIRE(c.getNearbyAreas().size() == 3);
    REQUIRE(c.getNearbyAreas().count(t1) == 1);
    REQUIRE(c.getNearbyAreas().count(t2) == 1);
    REQUIRE(c.getNearbyAreas().count(t3) == 1);
}

TEST_CASE("City Equality Operator")
{
    Tile t1("Forest", 5);
    Tile t2("Hills", 3);
    Tile t3("Mountains", 8);

    City c1("Alice", t1, t2, t3);
    City c2("Alice", t1, t2, t3);
    City c3("Bob", t1, t2, t3);

    REQUIRE(c1 == c2);
}

TEST_CASE("City Less Than Operator")
{
    Tile t1("Forest", 5);
    Tile t2("Hills", 3);
    Tile t3("Mountains", 8);
    Tile t4("Desert", 2);

    City c1("Alice", t1, t2, t3);
    City c2("Bob", t1, t2, t3);
    City c3("Alice", t1, t2, t4);

    REQUIRE(c1 < c2);
    REQUIRE(!(c2 < c1));
}

TEST_CASE("City Stream Operator")
{
    Tile t1("Forest", 5);
    Tile t2("Hills", 3);
    Tile t3("Mountains", 8);

    City c("Alice", t1, t2, t3);

    std::ostringstream oss;
    oss << c;
    std::string output = oss.str();

    REQUIRE(output.find("Alice") != std::string::npos);
    REQUIRE(output.find("Forest") != std::string::npos);
    REQUIRE(output.find("Hills") != std::string::npos);
    REQUIRE(output.find("Mountains") != std::string::npos);
}

TEST_CASE("KnightCard Initialization and Get/Set Knight")
{
    KnightCard::setKnight("Forest", 5);
    Tile *knight = KnightCard::getKnight();

    REQUIRE(knight->getTerrain() == "Forest");
    REQUIRE(knight->getNumber() == 5);

    KnightCard::setKnight("Hills", 3);
    knight = KnightCard::getKnight();

    REQUIRE(knight->getTerrain() == "Hills");
    REQUIRE(knight->getNumber() == 3);
}

TEST_CASE("MonopolyCard play method")
{
    // Create players
    Player player1("Alice");
    Player player2("Bob");
    Player player3("Charlie");

    // Give some resources to each player
    player1.setWood(2);
    player2.setWood(5);
    player3.setWood(3);

    // Create a vector of players
    vector<reference_wrapper<Player>> players = {player1, player2, player3};

    // Play the Monopoly card
    MonopolyCard monopolyCard;
    monopolyCard.play(player1, players, "wood");

    // Check if the resources have been transferred correctly
    REQUIRE(player1.getWood() == 10);
    REQUIRE(player2.getWood() == 0);
    REQUIRE(player3.getWood() == 0);
}

TEST_CASE("MonopolyCard play method with different resources")
{
    // Create players
    Player player1("Alice");
    Player player2("Bob");
    Player player3("Charlie");

    // Give some resources to each player
    player1.setBricks(2);
    player2.setBricks(5);
    player3.setBricks(3);

    // Create a vector of players
    vector<reference_wrapper<Player>> players = {player1, player2, player3};

    // Play the Monopoly card
    MonopolyCard monopolyCard;
    monopolyCard.play(player1, players, "brick");

    // Check if the resources have been transferred correctly
    REQUIRE(player1.getBricks() == 10);
    REQUIRE(player2.getBricks() == 0);
    REQUIRE(player3.getBricks() == 0);
}

TEST_CASE("MonopolyCard play method when player has no resources")
{
    // Create players
    Player player1("Alice");
    Player player2("Bob");
    Player player3("Charlie");

    // Create a vector of players
    vector<reference_wrapper<Player>> players = {player1, player2, player3};

    // Play the Monopoly card
    MonopolyCard monopolyCard;
    monopolyCard.play(player1, players, "ore");

    // Check if the resources remain unchanged
    REQUIRE(player1.getOre() == 0);
    REQUIRE(player2.getOre() == 0);
    REQUIRE(player3.getOre() == 0);
}

TEST_CASE("Player resource management")
{
    Player player("Alice");

    SECTION("Initial resources are zero")
    {
        REQUIRE(player.getWood() == 0);
        REQUIRE(player.getBricks() == 0);
        REQUIRE(player.getWheat() == 0);
        REQUIRE(player.getOre() == 0);
        REQUIRE(player.getWool() == 0);
    }

    SECTION("Adding and checking resources")
    {
        player.getCards("wood", 3);
        player.getCards("brick", 2);
        player.getCards("wheat", 5);
        player.getCards("ore", 1);
        player.getCards("wool", 4);

        REQUIRE(player.getWood() == 3);
        REQUIRE(player.getBricks() == 2);
        REQUIRE(player.getWheat() == 5);
        REQUIRE(player.getOre() == 1);
        REQUIRE(player.getWool() == 4);
    }

    SECTION("Removing resources")
    {
        player.getCards("wood", 3);
        player.getCards("brick", 2);
        player.getCards("wood", -1);
        player.getCards("brick", -2);

        REQUIRE(player.getWood() == 2);
        REQUIRE(player.getBricks() == 0);
    }

    SECTION("Checking resource existence")
    {
        player.getCards("wood", 3);
        player.getCards("brick", 2);

        REQUIRE(player.resource_exist("wood", 2));
        REQUIRE(!player.resource_exist("wood", 4));
        REQUIRE(player.resource_exist("brick", 2));
        REQUIRE(!player.resource_exist("brick", 3));
    }
}

TEST_CASE("Player building and development")
{
    Player player("Alice");
    Board board;

    SECTION("Placing a settlement")
    {
        player.getCards("wood", 1);
        player.getCards("brick", 1);
        player.getCards("wheat", 1);
        player.getCards("wool", 1);

        vector<string> places = {"Pasture Land", "Hills", "Forest"};
        vector<int> placesNum = {5, 8, 3};
        player.placeSettelemnt(places, placesNum, board);

        REQUIRE(player.getSettlements().size() == 1);
        REQUIRE(board.getSettlements().size() == 1);
    }

    SECTION("Placing a road")
    {
        player.getCards("wood", 1);
        player.getCards("brick", 1);

        vector<string> places = {"Forest", "Hills"};
        vector<int> placesNum = {4, 6};
        player.placeRoad(places, placesNum, board);

        REQUIRE(player.getRoads().size() == 1);
        REQUIRE(board.getRoads().size() == 1);
    }

    SECTION("Placing a city")
    {
        Player player("Amit");

        player.getCards("ore", 5);
        player.getCards("wheat", 5);

        std::vector<std::string> places = {"Forest", "Mountains", "Hills"};
        std::vector<int> placesNum = {3, 8, 10};
        player.placeSettelemnt(places, placesNum, board);
        player.placeCity(places, placesNum, board);

        REQUIRE(player.getCities().size() == 1);
        REQUIRE(board.getCities().size() == 1);
    }
}

TEST_CASE("Player buying development cards")
{
    Player player("Alice");

    SECTION("Buying a development card")
    {
        player.getCards("ore", 1);
        player.getCards("wheat", 1);
        player.getCards("wool", 1);

        player.buyDevelopmentCard();

        REQUIRE(player.getDevelopmentCards().size() == 1);
    }

    SECTION("Insufficient resources to buy development card")
    {
        player.getCards("ore", 1);
        player.getCards("wool", 1);

        REQUIRE_THROWS_AS(player.buyDevelopmentCard(), runtime_error);
    }
}

TEST_CASE("Player calculating points")
{
    Player player("Alice");
    Board board;

    SECTION("Points from settlements and cities")
    {
        player.getCards("wood", 1);
        player.getCards("brick", 1);
        player.getCards("wheat", 1);
        player.getCards("wool", 1);

        vector<string> places = {"Forest", "Hills", "Pasture Land"};
        vector<int> placesNum = {4, 6, 8};
        player.placeSettelemnt(places, placesNum, board);

        player.getCards("ore", 3);
        player.getCards("wheat", 2);
        player.placeCity(places, placesNum, board);

        REQUIRE(player.myPoints() == 3); // 1 settlement + 2 city points
    }

    SECTION("Points from development cards")
    {
        Player daniPlayer("Dani");
        daniPlayer.getCards("ore", 1);
        daniPlayer.getCards("wheat", 1);
        daniPlayer.getCards("wool", 1);
        daniPlayer.buyDevelopmentCard();

        REQUIRE(daniPlayer.myPoints() == 1);
    }
}

TEST_CASE("Player resource distribution and discard")
{
    Player player("Alice");

    SECTION("Distribute resources based on rolled number")
    {
        Tile tile1("Forest", 11);
        Tile tile2("Hills", 6);
        Tile tile3("Pasture Land", 8);
        Board board;

        Settlement settlement("Alice", tile1, tile2, tile3);
        player.placeSettelemnt({"Forest", "Hills", "Pasture Land"}, {11, 6, 8}, board);

        // player.distributeResources(11);
        REQUIRE(player.getWood() == 1);

        // player.distributeResources(6);
        REQUIRE(player.getBricks() == 1);

        // player.distributeResources(8);
        REQUIRE(player.getWool() == 1);
    }

    SECTION("Discard half of the cards if more than 7")
    {
        player.getCards("wood", 8);

        player.discardCards();
        REQUIRE(player.getWood() == 4);
    }
}

TEST_CASE("Player interaction")
{
    Player alice("Alice");
    Player bob("Bob");

    SECTION("Taking all resources from another player")
    {
        bob.getCards("wood", 5);
        alice.takeAllResources(bob, "wood");

        REQUIRE(alice.getWood() == 5);
        REQUIRE(bob.getWood() == 0);
    }
}

TEST_CASE("RoadBuildingCard::play - Valid Play")
{
    // Create a board object
    Board board;

    // Create a player
    Player player("Player1");

    // Set initial resources for verification purposes
    player.setBricks(0);
    player.setWood(0);

    // RoadBuildingCard
    RoadBuildingCard roadBuildingCard;

    // Define the places and placesNum for two roads
    std::vector<std::string> places1 = {"Forest", "Hills"};
    std::vector<int> placesNum1 = {1, 2};
    std::vector<std::string> places2 = {"Forest", "Mountains"};
    std::vector<int> placesNum2 = {1, 3};

    // Play the RoadBuildingCard
    roadBuildingCard.play(player, places1, placesNum1, places2, placesNum2, board);

    // Check that the player received the correct amount of resources
    REQUIRE(player.getBricks() == 2);
    REQUIRE(player.getWood() == 2);

    // Check that the roads were placed correctly
    Tile tile1("Forest", 1);
    Tile tile2("Hills", 2);
    Tile tile3("Mountains", 3);
    Road road1("Player1", tile1, tile2);
    Road road2("Player1", tile1, tile3);

    REQUIRE(player.getRoads().find(road1) != player.getRoads().end());
    REQUIRE(player.getRoads().find(road2) != player.getRoads().end());
    REQUIRE(board.getRoads().find(road1) != board.getRoads().end());
    REQUIRE(board.getRoads().find(road2) != board.getRoads().end());
}

TEST_CASE("Road Constructors and Getters")
{
    SECTION("Default Constructor and Getters")
    {
        // Create tiles
        Tile tile1("Forest", 1);
        Tile tile2("Hills", 2);

        // Create a road
        Road road("Player1", tile1, tile2);

        // Check nearby areas
        const auto &nearbyAreas = road.getNearbyAreas();
        REQUIRE(nearbyAreas.size() == 2);
        REQUIRE(nearbyAreas.count(tile1) == 1);
        REQUIRE(nearbyAreas.count(tile2) == 1);
    }
}

TEST_CASE("Road Comparison Operators")
{
    Tile tile1("Forest", 1);
    Tile tile2("Hills", 2);
    Tile tile3("Mountains", 3);

    Road road1("Player1", tile1, tile2);
    Road road2("Player1", tile1, tile2);
    Road road3("Player2", tile1, tile3);

    SECTION("Equality Operator")
    {
        REQUIRE(road1 == road2);       // Same owner and nearby areas
        REQUIRE_FALSE(road1 == road3); // Different owner
    }

    SECTION("Less Than Operator")
    {
        REQUIRE_FALSE(road1 < road2); // Roads are equal
        REQUIRE(road1 < road3);       // Different owner, road1 < road3 lexically
        REQUIRE_FALSE(road3 < road1); // Different owner, road1 > road3 lexically
    }
}

TEST_CASE("Settlement Constructors and Getters")
{
    SECTION("Default Constructor and Getters")
    {
        // Create tiles
        Tile tile1("Forest", 1);
        Tile tile2("Hills", 2);
        Tile tile3("Pasture", 3);

        // Create a settlement
        Settlement settlement("Player1", tile1, tile2, tile3);

        // Check nearby areas
        const auto &nearbyAreas = settlement.getNearbyAreas();
        REQUIRE(nearbyAreas.size() == 3);
        REQUIRE(nearbyAreas.count(tile1) == 1);
        REQUIRE(nearbyAreas.count(tile2) == 1);
        REQUIRE(nearbyAreas.count(tile3) == 1);
    }
}

TEST_CASE("Tile Constructors and Getters")
{
    SECTION("Default Constructor and Getters")
    {
        Tile tile;
        REQUIRE(tile.getTerrain() == "");
        REQUIRE(tile.getNumber() == 0);
    }

    SECTION("Parameterized Constructor and Getters")
    {
        Tile tile("Forest", 1);
        REQUIRE(tile.getTerrain() == "Forest");
        REQUIRE(tile.getNumber() == 1);
    }
}

TEST_CASE("Tile Setters")
{
    Tile tile;

    SECTION("Set Terrain")
    {
        tile.setTerrain("Hills");
        REQUIRE(tile.getTerrain() == "Hills");
    }

    SECTION("Set Number")
    {
        tile.setNumber(2);
        REQUIRE(tile.getNumber() == 2);
    }
}

TEST_CASE("Tile Comparison Operators")
{
    Tile tile1("Forest", 1);
    Tile tile2("Hills", 2);
    Tile tile3("Forest", 1);

    SECTION("Equality Operator")
    {
        REQUIRE(tile1 == tile3);        // Same terrain and number
        REQUIRE_FALSE(tile1 == tile2);  // Different terrain
        REQUIRE_FALSE(tile1 == Tile()); // Comparing with default-constructed Tile
    }

    SECTION("Inequality Operator")
    {
        REQUIRE(tile1 != tile2);       // Different terrain
        REQUIRE_FALSE(tile1 != tile3); // Same terrain and number
    }

    SECTION("Less Than Operator")
    {
        REQUIRE(tile1 < tile2);       // Lexicographical comparison of terrain
        REQUIRE_FALSE(tile2 < tile1); // Lexicographical comparison of terrain
        REQUIRE_FALSE(tile1 < tile3); // Same terrain and number
    }
}

TEST_CASE("Tile Assignment Operator")
{
    Tile tile1("Forest", 1);
    Tile tile2;

    tile2 = tile1;

    REQUIRE(tile2.getTerrain() == "Forest");
    REQUIRE(tile2.getNumber() == 1);
}

TEST_CASE("Check Board Tiles number")
{
    Board board;
    REQUIRE(board.getTiles().size() == 19);
}
