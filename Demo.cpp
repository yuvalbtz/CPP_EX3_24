#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"

using namespace std;
using namespace ariel;

int main()
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    Catan catan(p1, p2, p3);

    Board& board = catan.getBoard();

    vector<string> places = {"Forest", "Mountains", "Hills"};
    vector<int> placesNum = {3, 8, 10};
    p1.placeSettelemnt(places, placesNum, board);

    places = {"Forest", "Mountains"};
    placesNum = {3, 8};
    p1.placeRoad(places, placesNum, board);

    places = {"Agricultural Land", "Hills", "Mountains"};
    placesNum = {12, 6, 10};
    p1.placeSettelemnt(places, placesNum, board);

    places = {"Agricultural Land", "Hills"};
    placesNum = {12, 6};
    p1.placeRoad(places, placesNum, board);
    cout << "\n" << endl;

    places = {"Mountains", "Pasture Land", "Sea"};
    placesNum = {8, 5, 0};
    p2.placeSettelemnt(places, placesNum, board);

    try
    {
        p3.placeSettelemnt(places, placesNum, board); // p3 tries to place a settlement in the same location as p2.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    places = {"Mountains", "Pasture Land"};
    placesNum = {8, 5};
    p2.placeRoad(places, placesNum, board);

    places = {"Forest", "Pasture Land", "Hills"};
    placesNum = {9, 4, 10};
    p2.placeSettelemnt(places, placesNum, board);

    places = {"Forest", "Pasture Land"};
    placesNum = {9, 4};
    p2.placeRoad(places, placesNum, board);

    cout << "\n" << endl;

    places = {"Mountains", "Pasture Land", "Sea"};
    placesNum = {10, 2, 0};
    p3.placeSettelemnt(places, placesNum, board);

    places = {"Mountains", "Pasture Land"};
    placesNum = {10, 2};
    p3.placeRoad(places, placesNum, board);

    places = {"Agricultural Land", "Pasture Land", "Pasture Land"};
    placesNum = {4, 5, 11};
    p3.placeSettelemnt(places, placesNum, board);

    places = {"Agricultural Land", "Pasture Land"};
    placesNum = {4, 5};
    p3.placeRoad(places, placesNum, board);

    cout << "\n" << endl;

    catan.rollDice(p1);                                    // Simulating dice roll for player 1
    p1.placeRoad({"Forest", "Hills"}, {3, 10}, board); // Placing a road for player 1
    catan.endTurn(p1);                                     // Ending turn for player 1

    catan.rollDice(p2); // Simulating dice roll for player 2
    catan.endTurn(p2);  // Ending turn for player 2

    catan.rollDice(p3); // Simulating dice roll for player 3
    catan.endTurn(p3);  // Ending turn for player 3

    try{
        catan.rollDice(p2); // p2 tries to roll the dice again, but it's not his turn.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    catan.rollDice(p1);
    catan.trade(p1, p2, "wood", "brick", 1, 1); // p1 trades 1 wood for 1 brick with p2.
    catan.endTurn(p1);                        // p1 ends his turn.

    catan.rollDice(p2);
    catan.trade(p2, p1, "wheat", "brick", 1, 1); // p1 trades 1 wood for 1 brick with p2.
    try
    {
        p2.buyDevelopmentCard(); // p2 tries to buy a development card(he might not have enough resources)
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    vector<string> places1 = {"Pasture Land", "Hills"};
    vector<int> placesNum1 = {4, 10};
    vector<string> places2 = {"Mountains", "Sea"};
    vector<int> placesNum2 = {8, 0};

    //player2 bought one DevelopmentCard, we dont know which he got so we  will try to play them all.
    catan.playDevelopmentCard(p2, places1, placesNum1, places2, placesNum2, board); // play the RoadBuildingCard. the turn ends right after
    catan.playDevelopmentCard(p2, "wool"); // play the MonopolCard. the turn ends right after
    catan.playDevelopmentCard(p2, "wood", "ore"); // play the YearOfPlentyCard. the turn ends right after
    catan.playDevelopmentCard(p2); // play the KnightCard. the turn ends right after

    places = {"Agricultural Land", "Pasture Land", "Pasture Land"};
    placesNum = {4, 5, 11};
    try
    {
        p3.placeCity(places, placesNum, board); // p2 tries to place a city(he might not have enough resources)
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    catan.endTurn(p3);

    p1.printPoints();
    p2.printPoints();
    p3.printPoints();

    catan.printWinner();

    return 0;
}