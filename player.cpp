// player.cpp
#include "player.hpp"
#include "development_card.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>

namespace ariel {

    Player::Player(const std::string& name) : name(name), points(2), developmentCards(0), knightCount(0), hasLargestArmy(false) {
        resources["wood"] = 0;
        resources["brick"] = 0;
        resources["wool"] = 0;
        resources["grain"] = 0;
        resources["ore"] = 0;
    }
      DevelopmentCardType Player::drawDevelopmentCard() {
        // For demonstration, let's assume we draw a random development card type
        int cardIndex = rand() % 3; // Generating a random number from 0 to 2 (for 3 types of cards)

        // Depending on cardIndex, return a specific DevelopmentCardType
        switch (cardIndex) {
            case 0:
                return DevelopmentCardType::Knight; // Example card type 1
            case 1:
                return DevelopmentCardType::Monopoly; // Example card type 2
            case 2:
                return DevelopmentCardType::VictoryPoint; // Example card type 3
            default:
                throw std::runtime_error("Error: Unexpected card type drawn.");
        }
    }
    void Player::placeSettelemnt(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board) {
        try {
            if (board.placeSettlement(name, placesNum)) {
                std::cout << name << " placed a settlement at places: ";
                for (const auto& place : places) {
                    std::cout << place << " ";
                }
                std::cout << "with numbers: ";
                for (const auto& num : placesNum) {
                    std::cout << num << " ";
                }
                std::cout << std::endl;
                points++;
            } else {
                throw std::invalid_argument("Failed to place settlement. Location may already be occupied.");
            }
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    void Player::placeRoad(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board) {
        try {
            if (board.placeRoad(name, placesNum)) {
                std::cout << name << " placed a road at places: ";
                for (const auto& place : places) {
                    std::cout << place << " ";
                }
                std::cout << "with numbers: ";
                for (const auto& num : placesNum) {
                    std::cout << num << " ";
                }
                std::cout << std::endl;
            } else {
                throw std::invalid_argument("Failed to place road. Location may already be occupied.");
            }
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    void Player::rollDice() {
        int diceRoll = rand() % 6 + 1 + rand() % 6 + 1; // Rolling two dice
        std::cout << name << " rolled a " << diceRoll << std::endl;
    }

    void Player::endTurn() {
        // Implement end turn logic
        std::cout << name << " ends their turn." << std::endl;
    }

    void Player::trade(Player& other, const std::string& give, const std::string& take, int giveAmount, int takeAmount) {
        std::cout << name << " is attempting to trade " << giveAmount << " " << give << " for " << takeAmount << " " << take << " with " << other.getName() << std::endl;
        std::cout << name << "'s resources before trade: ";
        for (const auto& resource : resources) {
            std::cout << resource.first << ": " << resource.second << " ";
        }
        std::cout << std::endl;

        std::cout << other.getName() << "'s resources before trade: ";
        for (const auto& resource : other.resources) {
            std::cout << resource.first << ": " << resource.second << " ";
        }
        std::cout << std::endl;

        if (resources[give] >= giveAmount && other.resources[take] >= takeAmount) {
            resources[give] -= giveAmount;
            resources[take] += takeAmount;
            other.resources[give] += giveAmount;
            other.resources[take] -= takeAmount;
            std::cout << name << " successfully traded " << giveAmount << " " << give << " for " << takeAmount << " " << take << " with " << other.getName() << std::endl;
        } else {
            std::cout << "Trade not possible due to insufficient resources." << std::endl;
        }

        std::cout << name << "'s resources after trade: ";
        for (const auto& resource : resources) {
            std::cout << resource.first << ": " << resource.second << " ";
        }
        std::cout << std::endl;

        std::cout << other.getName() << "'s resources after trade: ";
        for (const auto& resource : other.resources) {
            std::cout << resource.first << ": " << resource.second << " ";
        }
        std::cout << std::endl;
    }

    void Player::buyDevelopmentCard() {
        if (resources["ore"] < 1 || resources["wool"] < 1 || resources["grain"] < 1) {
            std::cout << "Not enough resources to buy a development card." << std::endl;
            return;
        }
        resources["ore"] -= 1;
        resources["wool"] -= 1;
        resources["grain"] -= 1;
        
        DevelopmentCardType card = drawDevelopmentCard();
        developmentCardsOwned.push_back(card);
        std::cout << name << " bought a " << developmentCardTypeToString(card) << " card." << std::endl;
        
        if (card == DevelopmentCardType::VictoryPoint) {
            points++;
        }
    }

    void Player::useDevelopmentCard(DevelopmentCardType cardType, Board& board, std::vector<Player>& players) {
        auto it = std::find(developmentCardsOwned.begin(), developmentCardsOwned.end(), cardType);
        if (it != developmentCardsOwned.end()) {
            developmentCardsOwned.erase(it);
            switch (cardType) {
                case DevelopmentCardType::Monopoly:
                    // Implement Monopoly logic
                    std::cout << name << " used a Monopoly card." << std::endl;
                    break;
                case DevelopmentCardType::RoadBuilding:
                    // Implement Road Building logic
                    std::cout << name << " used a Road Building card." << std::endl;
                    break;
                case DevelopmentCardType::YearOfPlenty:
                    // Implement Year of Plenty logic
                    std::cout << name << " used a Year of Plenty card." << std::endl;
                    break;
                case DevelopmentCardType::Knight:
                    knightCount++;
                    std::cout << name << " used a Knight card." << std::endl;
                    break;
                default:
                    std::cout << "Unknown development card type used." << std::endl;
                    return;
            }
             developmentCards -= 1;
        }
    }
        void Player::printPoints() const {
        std::cout << name << " has " << points << " points." << std::endl;
    }

    std::string Player::getName() const {
        return name;
      }

    int Player::getPoints() const {
        return points;
    }
   
    }