/*
Noah Tah
03/07/2025
Programming II
Evan Vaverka
Northwestern Oklahoma State University

Assignment Description:
	- Dealer and player both get a hand. Player will go first.
	- Use a random number generator to give the player two numbers ranging from 2 to 11
	- Give player option to stay or add another number to try and get closer to 21.
	- If they go over 21, they bust and lose.
	- After the player loses or stays, the deaer goes. The dealer has to add new numbers
	to their original hand until they reach 17 or higher. If they go over 21, they lose.
	- Once the player and dealer have a number that isn't above 21 and neither have lost,
	the program will compare the two numbers, with the higher number being the winner.
	- A tie between numbers results in the dealer winning.
	- If the player or the dealer manages to get 5 cards in hand and still be less than or
	equal to 21, its an automatic win for that person. 
	- That means that the player or dealer cannot have more than 5 cards.
	- The program should continuously loop by asking the player "Deal another hand?"
	until they say no.
*/
#include <iostream>
#include <string>
#include <cstdlib>

// This is how we want our card to look
// Eventually, i'd like to add suits and faces to the card potentially, but would need to make a struct for a deck of cards as well
struct Card {
	int value;
};

// A player can have a maximum of 5 cards in their hand, per the specifications, and handSize will keep track
// we will also keep a running total of the player's hand
// We initialize the player with a handSize of 0 and a total of 0
// Perhaps could also deal the first 2 cards in the constructor
class Player {
	public:
	Card hand[5];
	int handSize;
	int total;
	Player() {
		handSize = 0;
		total = 0;
	};
};

// Essentially the same as the player, but will make a seperate class
class Dealer {
	public:
	Card hand[5];
	int handSize;
	int total;
	Dealer() {
		handSize = 0;
		total = 0;
	};
};

// rand() generates a number between 0 and 32767
// by using mod 10, we can get a number between 0 and 9, then we add 2 to get a number between 2 and 11
// we then add it to the player's hand and increment the size of the hand and the running total
void dealPlayer(Player &player) {
	Card card;
	card.value = rand() % 10 + 2;
	player.hand[player.handSize] = card;
	player.total += card.value;
	player.handSize++;
};

// Same as the player, but for the dealer
void dealDealer(Dealer &dealer) {
	Card card;
	card.value = rand() % 10 + 2;
	dealer.hand[dealer.handSize] = card;
	dealer.total += card.value;
	dealer.handSize++;
};

// Display the player's hand with a for loop
void displayPlayerHand(Player &player) {
	std::cout << "Player's hand: ";
	for (int i = 0; i < player.handSize; i++) {
		std::cout << player.hand[i].value << " ";
	};
	std::cout << "\n";
};

// Display the dealer's hand with a for loop
void displayDealerHand(Dealer &dealer) {
	std::cout << "Dealer's hand: ";
	for (int i = 0; i < dealer.handSize; i++) {
		std::cout << dealer.hand[i].value << " ";
	};
	std::cout << "\n";
};

void displayPlayerTotal(Player &player) {
	std::cout << "Player's total: " << player.total << "\n";
};

void displayDealerTotal(Dealer &dealer) {
	std::cout << "Dealer's total: " << dealer.total << "\n";
};

void displayWinner(Player &player, Dealer &dealer) {
	if (player.total > 21) {
		std::cout << "Player busts! Dealer wins!\n";
	} else if (dealer.total > 21) {
		std::cout << "Dealer busts! Player wins!\n";
	} else if (player.total > dealer.total) {
		std::cout << "Player wins!\n";
	} else if (player.total < dealer.total) {
		std::cout << "Dealer wins!\n";
	} else {
		std::cout << "It's a tie! Dealer wins!\n";
	};
};

void blackjackGameLoop() {
	Player player;
	Dealer dealer;
	char choice;

	dealPlayer(player);
	dealPlayer(player);
	displayPlayerHand(player);
	displayPlayerTotal(player);

	while (true) {
		std::cout << "Do you want to hit or stay? (h/s): ";
		std::cin >> choice;

		if (choice == 'h') {
			dealPlayer(player);
			displayPlayerHand(player);
			displayPlayerTotal(player);

			if (player.total > 21) {
				break;
			};
		} else if (choice == 's') {
			break;
		};
	};

	if (player.total <= 21) {
		while (dealer.total < 17) {
			dealDealer(dealer);
		};
	};

	displayDealerHand(dealer);
	displayDealerTotal(dealer);
	displayWinner(player, dealer);
};

void playAgain() {
	char choice;
	std::cout << "Do you want to play again? (y/n): ";
	std::cin >> choice;

	if (choice == 'y') {
		blackjackGameLoop();
		playAgain();
	} else if (choice == 'n') {
		std::cout << "Thanks for playing!\n";
	} else {
		std::cout << "Invalid choice. Please enter y or n.\n";
		playAgain();
	};
};

void startGame() {
	std::cout << "Welcome to Blackjack!\n";
	blackjackGameLoop();
	playAgain();
};


int main() {
	srand(time(0));
	startGame();

	return 0;
};