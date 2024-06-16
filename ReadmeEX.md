
## Project Structure

- `catan.hpp` and `catan.cpp`: Manage the overall game flow.
- `player.hpp` and `player.cpp`: Manage player actions and resources.
- `board.hpp` and `board.cpp`: Manage the game board and tiles.

## Game Rules

- Each player starts with 2 settlements and 2 roads.
- Players roll dice to collect resources and take turns to build, trade, and buy development cards.
- The first player to reach 10 points wins the game.

## Main Functions

- `Catan::ChooseStartingPlayer()`: Determines the starting player.
- `Player::placeSettlement()`: Places a settlement for a player.
- `Player::placeRoad()`: Places a road for a player.
- `Player::rollDice()`: Rolls the dice and distributes resources.
- `Player::endTurn()`: Ends the player's turn.
- `Player::trade()`: Trades resources between players.
- `Player::buyDevelopmentCard()`: Buys a development card.
- `Catan::printWinner()`: Prints the winner if any player has 10 or more points.
