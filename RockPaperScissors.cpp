/**************************************************************
 Author: D.S. Malik and Dr. Hayes and Kori Hanes

 Program: Rock, Paper, and Scissors

 Date 27_OCT_2025
 
 This program is a 1-player game of rock, paper, and scissors.
***************************************************************/

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

/**
 * The possible outcomes of a game.
 */
enum GameOutcome { TIE = 0, WIN = 1, LOSS = 2 };

// Namespace Action
namespace Action 
{

	// Enum for the shapes that a player can make in this game.
	// includes INVALID_SHAPE for invalid shapes
	enum Shape { ROCK = 0, PAPER = 1, SCISSORS = 2, INVALID_SHAPE = 3 };

	// Prototype for the function that converts a character to a shape.
	Action::Shape charToShape(char selection);

	// Prototype for the function that checks if a shape is valid.
	bool validShape(char selection);
	
	// Prototype for the function that converts a shape to a string.
	std::string shapeToString(Action::Shape object);
	
	// Prototype for the function that determines the winning shape.
	Action::Shape winningShape(Action::Shape shape1, Action::Shape shape2);
} // namespace Action

// Function Prototypes
// Prototype for the function that displays the rules of the game.
void displayRules();

// Prototype for the function that determines the outcome of the game.
GameOutcome determineGameOutcome(Action::Shape player, Action::Shape computer);

// Prototype for the function that displays the statistics of the game.
void displayStats(int gameCount, int playerWins, int computerWins);

// Main function
int main()
{
	// Declare main block variables
	int gameCount = 0; // Stores the number of games played
	int winCount = 0;  // Stores the number of games won by player
	int lossCount = 0; // Stores the number of games won by computer
	char response;  // Holds the user's response to play the game
	Action::Shape player;   // player's selection
	Action::Shape computer; // computer's selection

	// Seed the random-number generator 
	// using the time function to get the current time
	// and the static_cast function to convert the time to an unsigned int
	srand(static_cast<unsigned int>(time(nullptr)));

	// Display the rules of the game by running the displayRules function
	// which is defined below the main function
	displayRules();

	// Confirm with the user if they want to play the game.
	std::cout << "Enter Y/y to play the game: ";

	// store the user's response to play the game in the response variable
	std::cin >> response;

	// print a new line
	std::cout << std::endl;

	// Play games until the user does not respond with y.
	while (response == 'Y' ||  response == 'y')
	{

		// Get the users choice of shape
		// Make sure that the user's input is valid.
		do
		{
			std::cout << "Enter your choice (r, p, or s): ";
			std::cin >> response;
			std::cout << std::endl;
		}

		// pass the response to the validShape function to check if it is a 
		// valid shape using a while loop to continue asking for input until 
		// the input is valid
		while (!Action::validShape(response));

		// convert the user's response to a shape using the charToShape function
		player = Action::charToShape(response);

		// Computer will pick a shape a random
		computer = static_cast<Action::Shape>(rand() % Action::INVALID_SHAPE);

		gameCount++; // Count the number of games played

		// Check who one the game by passing the player
		// and computer's shapes to the determineGameOutcome function
		switch (determineGameOutcome(player, computer))
		{

			// The return from the determineGameOutcome function 
			// is compared to the WIN, LOSS, and TIE cases
			case WIN:
				winCount++; // increment the win count
				std::cout << "You won the game!" << std::endl;
				break;
			case LOSS:
				lossCount++; // increment the loss count
				std::cout << "You lost the game." << std::endl;
				break;
			default:
				std::cout << "This game is a tie." << std::endl;
		}
		std::cout << std::endl;

		// Once a match has been played,
		// ask the user if they want to play again.
		// starting the loop over while maintaining the win, loss, 
		// and tie counts
		std::cout << "Enter Y/y to play another game: ";
		std::cin >> response;
		std::cout << std::endl;
	} // end while

	// Once the user indicates they are done playing,
	// display the game statistics by running the displayStats function
	// by passing the game count, win count, and loss count variable 
	// to the function
	displayStats(gameCount, winCount, lossCount); // Display game stats

	return 0;
} //end main

// This function displays the rules of the game by using std::cout 
// to print the rules to the console. 
void displayRules()
{

	// Display the instructions for the game.
	std::cout << "Welcome to the game of Rock, Paper, and Scissors.\n";
	std::cout << "  This is a single-player game against to computer. "
		"For each \n";
	std::cout << "  game the player and computer each select one of the "
		"objects,\n";
	std::cout << "  Rock, Paper or Scissors.\n";
	std::cout << "The rules for winning the game are:\n";
	std::cout << "  1. If both players selects the same object, it is a tie.\n";
	std::cout << "  2. Rock breaks Scissors: So player who selects Rock "
		"wins.\n";
	std::cout << "  3. Paper covers Rock: So player who selects Paper wins.\n";
	std::cout << "  4. Scissors cuts Paper: So player who selects Scissors "
		<< "wins.\n\n";
	std::cout << "Enter R or r to select Rock, P or p to select "
		<< "Paper, and S or s to select Scissors." << std::endl;
}

// Function that compares the players shapes to determint he winner
// by passing the player's and computer's shapes to the function
// and returning the outcome of the game
GameOutcome determineGameOutcome(Action::Shape player, Action::Shape computer)
{

	// Declare variables 
	Action::Shape winnerObject; // Stores the winner's shape
	GameOutcome winner; // Stores the outcome of the game

	// Check for a tie by comparing the player's and computer's shapes
	if (player == computer)
	{

		// If the player's and computer's shapes are the same,
		// a tie is declared. 
		winner = TIE;
		std::cout << "Both players selected " << shapeToString(player) << ".\n";
	}
	else // See who won
	{
		winnerObject = winningShape(player, computer);

		//Output each player's choice
		std::cout << "The player selected " << shapeToString(player);
		std::cout << " and the computer selected " << shapeToString(computer)
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
} // end determineGameOutcome

void displayStats(int gameCount, int playerWins, int computerWins)
{
	// Display the game count, wins, and losses.
	std::cout << "The total number of games: " << gameCount << std::endl;
	std::cout << "The number of games won:   " << playerWins << std::endl;
	std::cout << "The number of games lost:  " << computerWins << std::endl;
}

// Action Namespace
namespace Action 
{

	bool validShape(char selection)
	{
		// Return true if the char represents a valid shape.
		return charToShape(selection) != INVALID_SHAPE;
	}
	
	Action::Shape charToShape(char selection)
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
	
	std::string shapeToString(Action::Shape object)
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
	
	Action::Shape winningShape(Action::Shape shape1, Action::Shape shape2)
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
	
		// This will never happen, because of assumptions in the 
		// switch statement.
		return INVALID_SHAPE;
	}

} // namespace Action