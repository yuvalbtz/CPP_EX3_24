#include "player.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm> // For std::find

namespace ariel {

    Player::Player(const std::string& name) : name(name), points(2), developmentCards(0) { // Each player starts with 2 points for initial settlements
        // Initialize resources with some starting values for demonstration purposes
        resources["wood"] = 0;
        resources["brick"] = 0;
        resources["wool"] = 0;
        resources["grain"] = 0;
        resources["ore"] = 0;
    }

    void Player::placeSettelemnt(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board) {
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
    }

    void Player::placeRoad(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board) {
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
            throw std::invalid_argument("Trade not possible due to insufficient resources.");
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
            throw std::invalid_argument("Not enough resources to buy a development card.");
        }
        resources["ore"] -= 1;
        resources["wool"] -= 1;
        resources["grain"] -= 1;
        developmentCards += 1;
        std::cout << name << " bought a development card." << std::endl;
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
