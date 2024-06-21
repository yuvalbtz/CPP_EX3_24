#include "player.hpp"
#include "development_card.hpp"
#include "knight_card.hpp"
#include "victory_point_card.hpp"
#include "monopoly_card.hpp"
#include "road_building_card.hpp"
#include "year_of_plenty_card.hpp"

using namespace std;

namespace ariel
{

    Player::Player(string name)
    {
        this->name = name;
        this->wood = 0;
        this->bricks = 0;
        this->wheat = 0;
        this->ore = 0;
        this->wool = 0;
    }

    string Player::getName() const
    {
        return name;
    }

    void Player::setName(const string &name)
    {
        this->name = name;
    }

    vector<unique_ptr<DevelopmentCard>> &Player::getDevelopmentCards()
    {
        return developmentCards;
    }

    const set<Settlement> &Player::getSettlements() const
    {
        return mySettlements;
    }

    const set<Road> &Player::getRoads() const
    {
        return myRoads;
    }

    const set<City> &Player::getCities() const
    {
        return myCities;
    }

    int Player::getWood() const
    {
        return wood;
    }

    void Player::setWood(int amount)
    {
        wood = amount;
    }

    int Player::getBricks() const
    {
        return bricks;
    }

    void Player::setBricks(int amount)
    {
        bricks = amount;
    }

    int Player::getWheat() const
    {
        return wheat;
    }

    void Player::setWheat(int amount)
    {
        wheat = amount;
    }

    int Player::getOre() const
    {
        return ore;
    }

    void Player::setOre(int amount)
    {
        ore = amount;
    }

    int Player::getWool() const
    {
        return wool;
    }

    void Player::setWool(int amount)
    {
        wool = amount;
    }

    bool Player::isPossibleRoad(Road myRoad)
    {
        for (const auto &PossibleRoad : this->possibleRoads)
        {
            if (myRoad == PossibleRoad)
            {
                return true;
            }
        }
        return false;
    }

    bool Player::isPossibleSettlement(Settlement mySettlement)
    {
        for (const auto &PossibleSettlement : this->possibleSettlements)
        {
            if (mySettlement == PossibleSettlement)
            {
                return true;
            }
        }
        return false;
    }

    void Player::getCards(string resource, int amount)
    {
        // Add or remove the specified amount of a resource from the player's inventory
        if (resource == "Mountains" || resource == "ore")
        {
            this->ore += amount;
            if (amount > 0)
            {
                cout << this->name << " earned " << amount << " ore" << endl;
            }
            else if (amount < 0)
            {
                cout << this->name << " lost " << amount << " ore" << endl;
            }
        }
        else if (resource == "Forest" || resource == "wood")
        {
            this->wood += amount;
            if (amount > 0)
            {
                cout << this->name << " earned " << amount << " wood" << endl;
            }
            else if (amount < 0)
            {
                cout << this->name << " lost " << amount << " wood" << endl;
            }
        }
        else if (resource == "Agricultural Land" || resource == "wheat")
        {
            this->wheat += amount;
            if (amount > 0)
            {
                cout << this->name << " earned " << amount << " wheat" << endl;
            }
            else if (amount < 0)
            {
                cout << this->name << " lost " << amount << " wheat" << endl;
            }
        }
        else if (resource == "Pasture Land" || resource == "wool")
        {
            this->wool += amount;
            if (amount > 0)
            {
                cout << this->name << " earned " << amount << " wool" << endl;
            }
            else if (amount < 0)
            {
                cout << this->name << " lost " << amount << " wool" << endl;
            }
        }
        else if (resource == "Hills" || resource == "brick")
        {
            this->bricks += amount;
            if (amount > 0)
            {
                cout << this->name << " earned " << amount << " brick" << endl;
            }
            else if (amount < 0)
            {
                cout << this->name << " lost " << amount << " bricks" << endl;
            }
        }
    }

    bool Player::resource_exist(string resource, int num)
    {
        // Check if the player has enough of the specified resource
        if (resource == "Mountains" || resource == "ore")
        {
            if (this->ore - num < 0)
                return false;
        }
        else if (resource == "Forest" || resource == "wood")
        {
            if (this->wood - num < 0)
                return false;
        }
        else if (resource == "Agricultural Land" || resource == "wheat")
        {
            if (this->wheat - num < 0)
                return false;
        }
        else if (resource == "Pasture Land" || resource == "wool")
        {
            if (this->wool - num < 0)
                return false;
        }
        else if (resource == "Hills" || resource == "brick")
        {
            if (this->bricks - num < 0)
                return false;
        }
        return true;
    }

    void Player::placeSettelemnt(vector<string> places, vector<int> placesNum, Board &board)
    {
        // Place a settlement on the board
        if (places.size() != 3 || placesNum.size() != 3)
        {
            throw invalid_argument("invalid number of places or placesNum provided");
        }
        if ((this->bricks < 1 || this->wood < 1 || this->wheat < 1 || this->wool < 1) && board.getSettlements().size() > 6)
        {
            throw runtime_error("placing Settlement: Insufficient resources");
        }

        Tile tile1(places[0], placesNum[0]);
        Tile tile2(places[1], placesNum[1]);
        Tile tile3(places[2], placesNum[2]);

        Settlement settlement(this->name, tile1, tile2, tile3);
        City city(this->name, tile1, tile2, tile3);
        if (board.isPossibleSettlement(settlement, city))
        {
            board.getSettlements().insert(settlement);

            // Earn resources when placing the first settlements
            if (board.getSettlements().size() <= 6)
            {
                this->getCards(tile1.getTerrain(), 1);
                this->getCards(tile2.getTerrain(), 1);
                this->getCards(tile3.getTerrain(), 1);
            }
            else
            {
                this->bricks--;
                this->wood--;
                this->wheat--;
                this->wool--;
            }

            Road road1(this->name, tile1, tile2);
            Road road2(this->name, tile1, tile3);
            Road road3(this->name, tile2, tile3);

            this->possibleRoads.insert(road1);
            this->possibleRoads.insert(road2);
            this->possibleRoads.insert(road3);
        }
        else
        {
            throw runtime_error("cant place settlement here");
        }
        this->mySettlements.insert(settlement);
        cout << this->name << " placed the Settlement successfully" << endl;
    }

    void Player::placeRoad(vector<string> places, vector<int> placesNum, Board &board)
    {
        // Place a road on the board
        if (places.size() != 2 || placesNum.size() != 2)
        {
            throw invalid_argument("invalid number of places or placesNum provided");
        }

        if ((this->bricks < 1 || this->wood < 1) && board.getSettlements().size() > 6)
        {
            throw runtime_error("placing Road: Insufficient resources");
            return;
        }

        Tile tile1(places[0], placesNum[0]);
        Tile tile2(places[1], placesNum[1]);
        Road road(this->name, tile1, tile2);
        if ((isPossibleRoad(road) || board.getSettlements().size() < 6) && board.isPossibleRoad(road))
        {
            this->possibleRoads.erase(road); // Remove from possible roads if exist
            board.getRoads().insert(road);
            if (board.getRoads().size() > 6)
            {
                this->bricks--;
                this->wood--;
            }

            // Find the common neighbors(should be 2) between tile1 and tile2
            for (auto &neighbor : tile1.getNearbyAreas())
            {
                if (tile2.getNearbyAreas().find(neighbor) != tile2.getNearbyAreas().end())
                {
                    Road road1(this->name, tile1, *neighbor); // Dereference the pointer to get the Tile object
                    Road road2(this->name, tile2, *neighbor); // Dereference the pointer to get the Tile object
                    // Insert the roads into the board's road set
                    this->possibleRoads.insert(road1);
                    this->possibleRoads.insert(road2);
                }
            }
        }
        else
        {
            throw runtime_error("cant place road here");
        }
        this->myRoads.insert(road);
        cout << this->name << " placed the Road successfully" << endl;
    }

    void Player::placeCity(vector<string> places, vector<int> placesNum, Board &board)
    {
        // Place a city on the board
        if (places.size() != 3 || placesNum.size() != 3)
        {
            throw invalid_argument("invalid number of places or placesNum provided");
        }
        if (this->ore < 3 || this->wheat < 2)
        {
            throw runtime_error("placing City: Insufficient resources");
            return;
        }
        Tile tile1(places[0], placesNum[0]);
        Tile tile2(places[1], placesNum[1]);
        Tile tile3(places[2], placesNum[2]);
        Settlement settlement(this->name, tile1, tile2, tile3);
        City city(this->name, tile1, tile2, tile3);
        if (this->mySettlements.find(settlement) != this->mySettlements.end())
        {
            board.getSettlements().erase(settlement);
            board.getCities().insert(city);
        }
        else
        {
            throw runtime_error("cant place city here");
        }
        this->bricks--;
        this->wood--;
        this->wheat--;
        this->wool--;
        this->myCities.insert(city);
        cout << this->name << " placed the City successfully" << endl;
    }

    // Function to distribute resources based on the rolled number
    void Player::distributeResources(int num)
    {

        for (const auto &settlement : this->mySettlements)
        {
            for (const auto &tile : settlement.getNearbyAreas())
            {
                if (tile.getNumber() == num && tile != *(KnightCard::getKnight()))
                {
                    this->getCards(tile.getTerrain(), 1);
                }
            }
        }

        for (const auto &city : this->myCities)
        {
            for (const auto &tile : city.getNearbyAreas())
            {
                if (tile.getNumber() == num && tile != *(KnightCard::getKnight()))
                {
                    this->getCards(tile.getTerrain(), 1);
                }
            }
        }
    }

    void Player::showCards() const
    {
        // Show the player's cards
        cout << "Cards of " << this->getName() << ": " << "wood" << ": " << wood << ", " << "wool" << ": " << wool << ", " << "bricks" << ": " << bricks << ", " << "ore" << ": " << ore << ", " << "wheat" << ": " << wheat << ", " << endl;
    }

    void Player::discardCards()
    {
        int totalCards = this->bricks + this->ore + this->wheat + this->wood + this->wool;

        // If total cards are greater than 7, discard half
        if (totalCards > 7)
        {
            cout << this->getName() << " has " << totalCards << " cards and needs to discard " << totalCards / 2 << " cards." << endl;

            int cardsToDiscard = totalCards / 2;
            while (cardsToDiscard > 0)
            {
                string resource;
                int amount;
                showCards();
                cout << cardsToDiscard << " cards needs to be discard" << endl;
                cout << "Enter the resource to discard and the amount (e.g., wood 2): ";
                cin >> resource >> amount;

                if (amount <= cardsToDiscard)
                {
                    if (resource_exist(resource, amount))
                    {
                        getCards(resource, -amount);
                        cardsToDiscard -= amount;
                    }
                    else
                    {
                        cout << "You do not have enough " << resource << " to discard. Try again." << endl;
                    }
                }
                else
                {
                    cout << "too much cards to discard. Try again." << endl;
                }
            }

            cout << "Discard completed." << endl;
        }
    }

    void Player::takeAllResources(Player &other, string resource)
    {
        // Take all of the specified resource from another player
        int count = 0;
        while (other.resource_exist(resource, 1))
        {
            other.getCards(resource, -1);
            this->getCards(resource, 1);
            count++;
        }
        cout << this->name << " took " << count << " " << resource << " from " << other.name << endl;
    }

    void Player::buyDevelopmentCard()
    {
        // Buy a development card
        if (this->ore < 1 || this->wheat < 1 || this->wool < 1)
        {
            throw runtime_error("buying Development card: Insufficient resources");
            return;
        }

        this->ore--;
        this->wheat--;
        this->wool--;

        random_device rd;
        mt19937 gen(rd());
        //  distribution of 3 progress cards, 3 knight cards, and 4 victory point cards.
        uniform_int_distribution<> distr(0, 9); // Total 10 cards

        unique_ptr<DevelopmentCard> newCard;
        int cardType = distr(gen);
        string type;

        if (cardType < 3)
        {
            uniform_int_distribution<> progressDistr(0, 2);
            int progressType = progressDistr(gen);

            if (progressType == 0)
            {
                newCard = make_unique<MonopolyCard>();
                type = "Monopoly Card";
            }
            else if (progressType == 1)
            {
                newCard = make_unique<RoadBuildingCard>();
                type = "Road Building Card";
            }
            else
            {
                newCard = make_unique<YearOfPlentyCard>();
                type = "Year of Plenty Card";
            }
        }
        else if (cardType < 6)
        {
            newCard = make_unique<KnightCard>();
            type = "Knight Card";
        }
        else
        {
            newCard = make_unique<VictoryPointCard>();
            type = "Victory Point Card";
        }

        developmentCards.push_back(move(newCard));
        cout << "Development card bought successfully: " << type << endl;
    }

    int Player::myPoints()
    {
        // Calculate player's points
        int pointsFromBuildings = this->mySettlements.size() + this->myCities.size() * 2;
        int pointsFromVictoryCards = count_if(developmentCards.begin(), developmentCards.end(), [](const unique_ptr<DevelopmentCard> &card)
                                              { return dynamic_cast<VictoryPointCard *>(card.get()) != nullptr; });
        int pointsFromKnightCards = count_if(developmentCards.begin(), developmentCards.end(), [](const unique_ptr<DevelopmentCard> &card)
                                             { return dynamic_cast<KnightCard *>(card.get()) != nullptr; });
        // if the number of the knight cards are 3 then the player get 2 points.
        if (pointsFromKnightCards == 3)
            pointsFromKnightCards = 2;
        return pointsFromBuildings + pointsFromVictoryCards + pointsFromKnightCards;
    }

    void Player::printPoints()
    {
        // Print player's points
        cout << this->getName() << " has " << this->myPoints() << " points" << endl;
    }

    bool Player::operator==(const Player &player) const
    {
        // Compare players by name
        return this->getName() == player.getName();
    }

    void Player::printAllInfo()
    {
        // Print the player's name
        cout << "Player Name: " << name << endl;

        // Print the player's resources
        cout << "Resources:" << endl;
        cout << "  Wood: " << wood << endl;
        cout << "  Bricks: " << bricks << endl;
        cout << "  Wheat: " << wheat << endl;
        cout << "  Ore: " << ore << endl;
        cout << "  Wool: " << wool << endl;

        // Print the player's settlements
        cout << "Settlements:" << endl;
        for (const auto &settlement : mySettlements)
        {
            cout << "  " << settlement << endl;
        }

        // Print the player's roads
        cout << "Roads:" << endl;
        for (const auto &road : myRoads)
        {
            cout << "  " << road << endl;
        }

        // Print the player's cities
        cout << "Cities:" << endl;
        for (const auto &city : myCities)
        {
            cout << "  " << city << endl;
        }

        // Print the player's development cards
        cout << "Development Cards:" << endl;
        for (const auto &card : developmentCards)
        {
            if (dynamic_cast<MonopolyCard *>(card.get()))
            {
                cout << "  Monopoly Card" << endl;
            }
            else if (dynamic_cast<KnightCard *>(card.get()))
            {
                cout << "  Knight Card" << endl;
            }
            else if (dynamic_cast<RoadBuildingCard *>(card.get()))
            {
                cout << "  Road Building Card" << endl;
            }
            else if (dynamic_cast<YearOfPlentyCard *>(card.get()))
            {
                cout << "  Year of Plenty Card" << endl;
            }
            else if (dynamic_cast<VictoryPointCard *>(card.get()))
            {
                cout << "  Victory Point Card" << endl;
            }
        }

        // Print the player's points
        printPoints();
    }
}