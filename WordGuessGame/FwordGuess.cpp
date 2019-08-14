// THIS FILE IS MAIN CLASS DEFINITION
#pragma once


#include "FwordGuess.h"
#include <map>
#include <random>

#define TMap std::map // To make more unreal engine friendly. used this cause it is more suited. could have used using. using needs to get invovled with parameters
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // DEFINE CONSTRUCTOR TO DO WHAT I LIKE. default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


int32 FBullCowGame::GetMaxTries() const 
{ 
	/* max tries should be following length of the hidden word as we dont want to much tries
	when guessing*/

	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16} };
	
	return WordLengthToMaxTries[MyHiddenWord.length()];
	return MyMaxTry; 
}

// these down here are all methods. reset above is a method called on by the constructor
void FBullCowGame::Reset()
{	

	const FString HIDDEN_WORD[] = { "planet", "world", "orange", "horse", "computer" };
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distribution{0, 4}; // define the range
	int randomNumber = distribution(eng);
	MyHiddenWord = HIDDEN_WORD[randomNumber];
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


//TODO fix all the errors!
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const // guess up here is an handle for incoming parameter
{
	if (!IsIsogram(Guess)) //if the guess is not an isogram
	{
		return EGuessStatus::Not_Isogram;
	}

	else if (!IsLowercase(Guess) )//if the guess is not all lowercase
	{
		return EGuessStatus::Not_Lowercase; 
	} 
	
	else if ( Guess.length() != GetHiddenWordLength() )//if the guess length is wrong	. call methods if you have method
	{
		return EGuessStatus::Wrong_Length;
	}

	else // otherwise
	{
		return EGuessStatus::OK;
	}
}


// recieves a valid guess, incraments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	//setup a return variable
	FBullCowCount BullCowCount; //the first is a type, the other is a variable
	//loop through all the letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess
	for (int32 HWChar = 0; HWChar < WordLength; HWChar++) { // not including hiddenwordlength because we're gonna look in strings which start count in 0! 
		// compare the letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[HWChar]) {
				if (HWChar == GChar) 
				{			
					// For a guess to be a bull, letters need to be in exact same spot. 
					// if a letter is in the end of a word we need somehow to make the code that counts bulls to continue even thogh it has found cows in between.			
					BullCowCount.Bulls++;		
				}								 
				else 
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (WordLength == BullCowCount.Bulls) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram (FString Word) const
{
	/*want to go through each letter in the alphabet and for each match i want to imcrezse that letters number. 
	when any number goes to two, i want to go to error message*/
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; //setup out map 
	for (auto Letter : Word) // for all letters of the word- colon here is IN just remember that
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) //if letter is in LetterSeen, it is not an isogram so break this function
		{ return false;
		} else { LetterSeen[Letter] = true; }

	}

	return true; //for example in casaes where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	/* I want a function that checks if my inpit is all lowercase letters. i will want a map for this too as the 
	letters in the word are the same as above. want to look for every letter in this function and see "are they lowercase". if NOT lowercase 
	then ask to put all in lowercase. Otherwise continue as usuall*/
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word)
	{
		if ( !islower(Letter) )
		{
			return false;
		}
		return true;
	}
}


