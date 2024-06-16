#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"

using namespace std;
using namespace ariel;

int main() {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);

    // Starting of the game. Every player places two settlements and two roads.
    Board board = catan.getBoard(); // get the board of the game.

    // Player 1 initial placement
    vector<string> places1 = {"Forest", "Hills"};
    vector<int> placesNum1 = {5, 6};
    p1.placeSettelemnt(places1, placesNum1, board);
    p1.placeRoad(places1, placesNum1, board);

    vector<string> places2 = {"Agricultural Land", "Desert"};
    vector<int> placesNum2 = {3, 4};
    p1.placeSettelemnt(places2, placesNum2, board);
    p1.placeRoad(places2, placesNum2, board); // p1 chooses Forest, hills, Agricultural Land, Desert with numbers 5, 6, 3, 4.

    // Player 2 initial placement
    vector<string> places3 = {"Mountains", "Pasture Land"};
    vector<int> placesNum3 = {4, 9};
    p2.placeSettelemnt(places3, placesNum3, board);
    p2.placeRoad(places3, placesNum3, board);

    try {
        p3.placeSettelemnt(places3, placesNum3, board); // p3 tries to place a settlement in the same location as p2.
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    vector<string> places4 = {"Forest", "Pasture Land"};
    vector<int> placesNum4 = {5, 9};
    p2.placeSettelemnt(places4, placesNum4, board);
    p2.placeRoad(places4, placesNum4, board); // p2 chooses Mountains, Pasture Land, and Forest with numbers 4, 9, 5.

    // Player 3 initial placement
    vector<string> places5 = {"Mountains", "Pasture Land"};
    vector<int> placesNum5 = {3, 8};
    p3.placeSettelemnt(places5, placesNum5, board);
    p3.placeRoad(places5, placesNum5, board);
    vector<string> places6 = {"Agricultural Land", "Pasture Land"};
    vector<int> placesNum6 = {3, 9};
    p3.placeSettelemnt(places6, placesNum6, board);
    p3.placeRoad(places6, placesNum6, board); // p3 chooses Mountains, Pasture Land, Agricultural Land, Pasture Land with numbers 3, 8, 3, 9.

    // Simulate one valid round
    cout << "Starting one valid round of the game." << endl;

    // Player 1's turn
    cout << "It's " << p1.getName() << "'s turn." << endl;
    p1.rollDice(); // Roll the dice
    // Player 1 actions (e.g., trade, build, buy development card)
    p1.endTurn(); // End turn

    // Player 2's turn
    cout << "It's " << p2.getName() << "'s turn." << endl;
    p2.rollDice(); // Roll the dice
    // Player 2 actions (e.g., trade, build, buy development card)
    p2.endTurn(); // End turn

    // Player 3's turn
    cout << "It's " << p3.getName() << "'s turn." << endl;
    p3.rollDice(); // Roll the dice
    // Player 3 actions (e.g., trade, build, buy development card)
    p3.endTurn(); // End turn

    // Print points for each player at the end of the round
    p1.printPoints();
    p2.printPoints();
    p3.printPoints();

    // Print winner if any player has reached 10 points
    catan.printWinner();

    return 0;
}
