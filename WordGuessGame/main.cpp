/*
this is the console executable that makes use of the bullcow class. 
this acts  as the view in a mvc pattern, and is responsible for all user interaction. for game logic see the fbullcowgame class.
*/
#pragma once

#include <iostream> 
#include <string>
#include "FwordGuess.h"


// using this so that code is unreal engine standard
using FText = std::string;
using int32 = int;

//introduction to the functions i am going to use in my game.
void PrintIntro();
void PlayGame();
FText GetvalidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

// instantiate "create an instance of a new game" which we re-use across plays.
FBullCowGame BCGame; 

// the main file responsible on a high level for what code is included in my game
int main()
{
	std::cout << BCGame.GetCurrentTry();
	do 
	{
		BCGame.Reset();
		PrintIntro();
		PlayGame();
	} 
	while (	AskToPlayAgain() ); //asktoplayagain returns as a boolean so when the whole loop is run while true
	return 0; //ecxits the application
}


// The intro to the game
void PrintIntro() 
{
	std::cout << "Welcome to WordGuess, a fun word game.\n\n"; 
	std::cout << "Art by Donovan Bake\n\n";

		std::cout << "	    __...--~~~~~- ._   _. - ~~~~~--...__\n";
		std::cout << "	    //               `V'               \\ \n";
		std::cout << "	   //                 |                 \\ \n";
		std::cout << "	  //__...--~~~~~~-._  |  _.-~~~~~~--...__\\ \n";
		std::cout << "	 //__.....----~~~~._\ | /_.~~~~----.....__\\\n";
		std::cout << "	====================\\|//====================\n";
		std::cout << "		dwb `---`\n";
		std::cout << "\n";
		std::cout << "\n";
	/*printing the number of guesses by calling the bcgame get hidden word length getter. */
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram word im looking for?\n\n"; 
	
	return;
}


//PLAYS A SINGLE GAME TO COMPLETION
void PlayGame() 
{
	//BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	std::cout << "Your max tries is: " << MaxTries << std::endl;

	// loop asking for guesses while the game is not won, and there is still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{ // important to read code lika the machine does! so its NOT won
		
		FText Guess = GetvalidGuess();
		// submit a valid guess to the game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
		
	}
	PrintGameSummary();
	return;
}



// get a guess input from the player and loop til valid
FText GetvalidGuess()  
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess!: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "please enter an isogram. \n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "please enter word in lower case letters. \n\n";
			break;
		case EGuessStatus::Not_English:
			std::cout << "please enter an english word in lower case letters. \n\n";
			break;
		default:
			//assuming is valid guess
			break;				
		}
	} while (Status != EGuessStatus::OK); //keep looping intull we get no errors
	return Guess;	
}



bool AskToPlayAgain()
{
	std::cout << "Do you wanna play again with the same hidden word (y/n)?: ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	/* when i have won i want to ´have a text saying that i won. when i lost i want a text saying that insted
	what happens when i win. bgameiswon == true. */
	if ( BCGame.IsGameWon() ) {
		std::cout << "Congratulations, you have won the game!\n\n";
	}
	else {
		std::cout << " oh no! you have lost. better luck next time. You're still awesome though!\n\n";
	}
	return;
}
