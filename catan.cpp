#include "catan.hpp"

using namespace std;

namespace ariel
{

    Catan::Catan(Player &p1, Player &p2, Player &p3) : player1(p1), player2(p2), player3(p3), currentPlayer(&player1), board()
    {
        srand(time(nullptr)); // Seed the random number generator once
        cout << "Catan game initialized with players: " << player1.getName() << ", " << player2.getName() << ", " << player3.getName() << endl;
        cout << "Starting player is " << (*currentPlayer).getName() << "\n"
             << endl;
    }

    Board &Catan::getBoard()
    {
        return board;
    }

    void Catan::rollDice(Player &player)
    {
        if (*currentPlayer == player)
        {
            // Generate two random numbers between 1 and 6
            int dice1 = rand() % 6 + 1;
            int dice2 = rand() % 6 + 1;
            int sum = dice1 + dice2;
            cout << player.getName() << " rolled the dices and got " << sum << endl;
            if (sum == 7)
            {
                // Each player discards half of their cards if they have more than 7
                player1.discardCards();
                player2.discardCards();
                player3.discardCards();
                string terrain;
                int num;
                cout << "Enter a resource and a number of a tile you want to put the knight on (e.g., Agricultural Land 4 ): ";
                cin >> terrain >> num;
                KnightCard::setKnight(terrain, num);
            }
            else
            {
                // Distribute resources based on the dice roll
                player1.distributeResources(sum);
                player2.distributeResources(sum);
                player3.distributeResources(sum);
            }
        }
        else
        {
            throw runtime_error("its not " + player.getName() + "'s turn, its now " + (*currentPlayer).getName() + "'s turn");
        }
    }

    void Catan::endTurn(Player &player)
    {
        if (currentPlayer == &player)
        {
            cout << player.getName() << "'s turn has ended." << endl;

            // Check if the current player has reached 10 points
            if (player.myPoints() >= 10)
            {
                printWinner();
                exit(0); // Terminate the program
            }

            // Cycle to the next player
            if (currentPlayer == &player1)
            {
                currentPlayer = &player2;
            }
            else if (currentPlayer == &player2)
            {
                currentPlayer = &player3;
            }
            else
            {
                currentPlayer = &player1;
            }
            cout << "It's now " << currentPlayer->getName() << "'s turn.\n"
                 << endl;
        }
        else
        {
            cout << "It's not your turn to end, it's now " << currentPlayer->getName() << "'s turn\n"
                 << endl;
        }
    }

    void Catan::trade(Player &First_Player, Player &Second_Player, string resource1, string resource2, int num1, int num2)
    {
        if ((*this->currentPlayer) == First_Player)
        {
            if (First_Player.resource_exist(resource1, num1))
            {
                if (Second_Player.resource_exist(resource2, num2))
                {
                    // Execute the trade between players
                    First_Player.getCards(resource1, num1 * (-1));  // Remove this resource
                    First_Player.getCards(resource2, num2);         // Add the received resource
                    Second_Player.getCards(resource2, num2 * (-1)); // Remove this resource
                    Second_Player.getCards(resource1, num1);        // Add the received resource
                    cout << First_Player.getName() << " and " << Second_Player.getName() << " traded. "
                         << First_Player.getName() << " gave " << num1 << " " << resource1
                         << " and received " << num2 << " " << resource2 << "." << endl;
                }
                else
                {
                    cout << Second_Player.getName() + " lacks resources" << endl;
                }
            }
            else
            {
                cout << First_Player.getName() + " lacks resources" << endl;
            }
        }
        else
        {
            cout << "its not " + First_Player.getName() + "'s turn, its now " + (*currentPlayer).getName() + "'s turn" << endl;
        }
    }

    void Catan::playDevelopmentCard(Player &player, string resource)
    {
        if ((*this->currentPlayer) == player)
        {
            // Uses find_if to iterate through the developmentCards vector
            auto it = find_if(player.getDevelopmentCards().begin(), player.getDevelopmentCards().end(), [](const unique_ptr<DevelopmentCard> &card)
                              { return dynamic_cast<MonopolyCard *>(card.get()) != nullptr; });

            if (it != player.getDevelopmentCards().end())
            {
                MonopolyCard *monopolyCard = dynamic_cast<MonopolyCard *>(it->get());
                if (monopolyCard)
                {
                    // Play the MonopolyCard
                    vector<reference_wrapper<ariel::Player>> players = {player1, player2, player3};
                    monopolyCard->play(player, players, resource);
                    player.getDevelopmentCards().erase(it); // Remove the card from the vector
                    cout << "Monopoly card played successfully." << endl;
                    this->endTurn(player);
                }
            }
            else
            {
                cout << "You do not have a Monopoly card." << endl;
            }
        }
        else
        {
            cout << "its not " + player.getName() + "'s turn, its now " + (*currentPlayer).getName() + "'s turn" << endl;
        }
    }

    void Catan::playDevelopmentCard(Player &player, vector<string> places1, vector<int> placesNum1, vector<string> places2, vector<int> placesNum2, Board &board)
    {
        // Check if the current player is the one calling the method
        if (*this->currentPlayer == player)
        {
            // Use find_if to iterate through the developmentCards vector
            auto it = find_if(player.getDevelopmentCards().begin(), player.getDevelopmentCards().end(), [](const unique_ptr<DevelopmentCard> &card)
                              { return dynamic_cast<RoadBuildingCard *>(card.get()) != nullptr; });

            if (it != player.getDevelopmentCards().end())
            {
                RoadBuildingCard *roadBuildingCard = dynamic_cast<RoadBuildingCard *>(it->get());
                if (roadBuildingCard)
                {
                    // Play the RoadBuildingCard
                    roadBuildingCard->play(player, places1, placesNum1, places2, placesNum2, board);
                    player.getDevelopmentCards().erase(it); // Remove the card from the vector
                    cout << "Road Building card played successfully." << endl;
                    this->endTurn(player);
                }
            }
            else
            {
                cout << "You do not have a Road Building card." << endl;
            }
        }
        else
        {
            cout << "It's not " + player.getName() + "'s turn, it's now " + this->currentPlayer->getName() + "'s turn" << endl;
        }
    }

    void Catan::playDevelopmentCard(Player &player, const string &resource1, const string &resource2)
    {
        // Check if the current player is the one calling the method
        if (*this->currentPlayer == player)
        {
            // Use find_if to iterate through the developmentCards vector
            auto it = find_if(player.getDevelopmentCards().begin(), player.getDevelopmentCards().end(), [](const unique_ptr<DevelopmentCard> &card)
                              { return dynamic_cast<YearOfPlentyCard *>(card.get()) != nullptr; });

            if (it != player.getDevelopmentCards().end())
            {
                YearOfPlentyCard *yearOfPlentyCard = dynamic_cast<YearOfPlentyCard *>(it->get());
                if (yearOfPlentyCard)
                {
                    // Play the YearOfPlentyCard
                    yearOfPlentyCard->play(player, resource1, resource2);
                    player.getDevelopmentCards().erase(it); // Remove the card from the vector
                    cout << "Year of Plenty card played successfully." << endl;
                    this->endTurn(player);
                }
            }
            else
            {
                cout << "You do not have a Year of Plenty card." << endl;
            }
        }
        else
        {
            cout << "It's not " + player.getName() + "'s turn, it's now " + this->currentPlayer->getName() + "'s turn" << endl;
        }
    }

    void Catan::playDevelopmentCard(Player &player)
    {
        // Check if the current player is the one calling the method
        if (*this->currentPlayer == player)
        {
            // Use find_if to iterate through the developmentCards vector
            auto it = find_if(player.getDevelopmentCards().begin(), player.getDevelopmentCards().end(), [](const unique_ptr<DevelopmentCard> &card)
                              { return dynamic_cast<KnightCard *>(card.get()) != nullptr; });

            if (it != player.getDevelopmentCards().end())
            {
                KnightCard *knightCard = dynamic_cast<KnightCard *>(it->get());
                if (knightCard)
                {
                    // Play the KnightCard
                    knightCard->play(player);
                    player.getDevelopmentCards().erase(it); // Remove the card from the vector
                    cout << "Knight card played successfully." << endl;
                    this->endTurn(player);
                }
            }
            else
            {
                cout << "You do not have a Knight card." << endl;
            }
        }
        else
        {
            cout << "It's not " + player.getName() + "'s turn, it's now " + this->currentPlayer->getName() + "'s turn" << endl;
        }
        this->endTurn(player);
    }

    void Catan::printWinner()
    {
        int p1Points = player1.myPoints();
        int p2Points = player2.myPoints();
        int p3Points = player3.myPoints();

        // Check if no player has reached 10 points
        if (p1Points < 10 && p2Points < 10 && p3Points < 10)
        {
            cout << "There is no winner, No one has reached 10 points\n";
            return;
        }

        if (p1Points > p2Points && p1Points > p3Points)
        {
            cout << "The winner is Player 1: " << player1.getName() << " with " << p1Points << " points!\n";
        }
        else if (p2Points > p1Points && p2Points > p3Points)
        {
            cout << "The winner is Player 2: " << player2.getName() << " with " << p2Points << " points!\n";
        }
        else if (p3Points > p1Points && p3Points > p2Points)
        {
            cout << "The winner is Player 3: " << player3.getName() << " with " << p3Points << " points!\n";
        }
        else
        {
            cout << "There is a tie!\n";
            if (p1Points == p2Points && p1Points > p3Points)
            {
                cout << "Players 1 and 2 (" << player1.getName() << " and " << player2.getName() << ") tie with " << p1Points << " points!\n";
            }
            else if (p1Points == p3Points && p1Points > p2Points)
            {
                cout << "Players 1 and 3 (" << player1.getName() << " and " << player3.getName() << ") tie with " << p1Points << " points!\n";
            }
            else if (p2Points == p3Points && p2Points > p1Points)
            {
                cout << "Players 2 and 3 (" << player2.getName() << " and " << player3.getName() << ") tie with " << p2Points << " points!\n";
            }
            else
            {
                cout << "All players tie with " << p1Points << " points!\n";
            }
        }
    }
}