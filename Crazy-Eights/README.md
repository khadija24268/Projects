# Crazy Eights Interactive Demo

Welcome to the Crazy Eights interactive demo! This JavaScript project showcases a simplified version of the classic card game, allowing two turns to be played – one for the player and one for the computer.

## Game Overview

- **Deck Configuration:**
  - The game uses a standard 52-card deck of French-suited playing cards.
  - A configuration file can set the initial cards in the draw pile, player's hand, and computer's hand.
  - Without a configuration, the game generates a deck, shuffles it, and deals five cards to each player.

- **Starter Card:**
  - A single card is drawn from the draw pile, serving as the starter.
  - The starter card determines the suit or rank that should be played next.

- **Gameplay:**
  - Players take turns discarding a single card from their hand that matches the suit or rank of the starter.
  - A card with a rank of 8 can be played at any time, allowing the player to set the suit.
  - If a card cannot be played, cards are drawn until a playable card is obtained.
  - The first to discard all cards in their hand wins!

## Demo Structure

The demo consists of two turns:
1. **Player's Turn:**
   - The player interacts with the game, choosing a card to play or drawing cards until a playable card is obtained.

2. **Computer's Turn:**
   - A simplified logic for the computer's turn is implemented.
   - The computer selects a card to play or draws until a playable card is obtained.

## Functions Used

The demo utilizes the following key functions for managing the card game:

- **`generateDeck`:** Creates a standard 52-card deck of French-suited playing cards.

- **`shuffle`:** Shuffles the deck to introduce randomness to the card order.

- **`deal`:** Distributes cards to the player and computer hands based on the game rules.

- **`drawUntilPlayable`:** Draws cards from the draw pile until a playable card is obtained.

- **`matchesAnyProperty`:** Checks if an object contains any of the keys and values of another object.

- **`handToString`:** Produces a string representation of an array of card objects for display.

These functions contribute to the interactive and dynamic gameplay experience in the Crazy Eights demo.
