/**************************************************************
 Author: D.S. Malik and Dr. Hayes

 Program: Rock, Paper, and Scissors
 This program is a 1-player game of rock, paper, and scissors.
***************************************************************/

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

/**
 * The possible outcomes of a game.
 */
enum GameOutcome { TIE, WIN, LOSS };

/**
 * The shapes that a player can make in this game.
 */
enum Shape { ROCK, PAPER, SCISSORS, INVALID_SHAPE };


void displayRules();


Shape charToShape(char selection);


bool validShape(char selection);


string shapeToString(Shape object);


Shape winningShape(Shape shape1, Shape shape2);


GameOutcome determineGameOutcome(Shape player, Shape computer);


void displayStats(int gameCount, int playerWins, int computerWins);

int main()
{
	int gameCount = 0; // Stores the number of games played
	int winCount = 0;  // Stores the number of games won by player
	int lossCount = 0; // Stores the number of games won by computer
	char response;  // Holds the user's response to play the game
	Shape player;   // player's selection
	Shape computer; // computer's selection

	// Seed the random-number generator
	srand(static_cast<unsigned int>(time(nullptr)));

	// Display the rules
	displayRules();

	// As they user if they want to play.
	cout << "Enter Y/y to play the game: ";
	cin >> response;
	cout << endl;

	// Play games until the user does not respond with y.
	while (response == 'Y' ||  response == 'y')
	{
		// Get the users choice of shape
		// Make sure that the user's input is valid.
		do
		{
			cout << "Enter your choice (r, p, or s): ";
			cin >> response;
			cout << endl;
		}
		while (!validShape(response));

		player = charToShape(response);

		// Computer will pick a shape a random
		computer = static_cast<Shape>(rand() % INVALID_SHAPE);

		gameCount++; // Count the number of games played

		// Check who one the game
		switch (determineGameOutcome(player, computer))
		{
			case WIN:
				winCount++;
				cout << "You won the game!" << endl;
				break;
			case LOSS:
				lossCount++;
				cout << "You lost the game." << endl;
				break;
			default:
				cout << "This game is a tie." << endl;
		}
		cout << endl;

		// As the user if they want to play again.
		cout << "Enter Y/y to play another game: ";
		cin >> response;
		cout << endl;
	} // end while

	displayStats(gameCount, winCount, lossCount); // Display game stats

	return 0;
} //end main

void displayRules()
{
	// Display the instructions for the game.
	cout << "Welcome to the game of Rock, Paper, and Scissors.\n";
	cout << "  This is a single-player game against to computer. For each \n";
	cout << "  game the player and computer each select one of the objects,\n";
	cout << "  Rock, Paper or Scissors.\n";
	cout << "The rules for winning the game are:\n";
	cout << "  1. If both players selects the same object, it is a tie.\n";
	cout << "  2. Rock breaks Scissors: So player who selects Rock wins.\n";
	cout << "  3. Paper covers Rock: So player who selects Paper wins.\n";
	cout << "  4. Scissors cuts Paper: So player who selects Scissors "
		<< "wins.\n\n";
	cout << "Enter R or r to select Rock, P or p to select "
		<< "Paper, and S or s to select Scissors." << endl;
}

bool validShape(char selection)
{
	// Return true if the char represents a valid shape.
	return charToShape(selection) != INVALID_SHAPE;
}

Shape charToShape(char selection)
{
	// Return the shape based on the starting letter.
	switch (selection)
	{
		case 'R':
		case 'r':
			return ROCK;
		case 'P':
		case 'p':
			return PAPER;
		case 'S':
		case 's':
			return SCISSORS;
	}

	return INVALID_SHAPE;
}

string shapeToString(Shape object)
{
	// Return the name of the shape.
	switch (object)
	{
	case ROCK:
		return "Rock";
	case PAPER:
		return "Paper";
	case SCISSORS:
		return "Scissors";
	default:
		return "Unknown Type";
	}
}

Shape winningShape(Shape shape1, Shape shape2)
{
	// Compare the player's shape with the computer's shape
	switch (shape1)
	{
		case ROCK:
			if (shape2 == PAPER) // Paper beats Rock
				return PAPER;
			return ROCK; // Must be a tie or shape1 won with Rock

		case SCISSORS:
			if (shape2 == ROCK) // Rock beats Scissors
				return ROCK;
			return SCISSORS;

		default: // Paper
			if (shape2 == SCISSORS) // Scissors beats Paper
				return SCISSORS;
			return PAPER;
	}

	// This will never happen, because of assumptions in the switch statement.
	return INVALID_SHAPE;
}

GameOutcome determineGameOutcome(Shape player, Shape computer)
{
	Shape winnerObject;
	GameOutcome winner;

	// Check for a tie
	if (player == computer)
	{
		winner = TIE;
		cout << "Both players selected " << shapeToString(player) << ".\n";
	}
	else // See who won
	{
		winnerObject = winningShape(player, computer);

		//Output each player's choice
		cout << "The player selected " << shapeToString(player);
		cout << " and the computer selected " << shapeToString(computer)
			<< ".\n";

		//Decide the winner
		if (player == winnerObject)
		{
			winner = WIN;
		}
		else if (computer == winnerObject)
		{
			winner = LOSS;
		}
	}

	return winner;
}

void displayStats(int gameCount, int playerWins, int computerWins)
{
	// Display the game count, wins, and losses.
	cout << "The total number of games: " << gameCount << endl;
	cout << "The number of games won:   " << playerWins << endl;
	cout << "The number of games lost:  " << computerWins << endl;
}
