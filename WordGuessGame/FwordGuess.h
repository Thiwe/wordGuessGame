
#pragma once
#include <string>

//to make syntax unreal engine friendly
using FString = std::string;
using int32 = int;

// initialises bulls and cows to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Not_English,
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
};

class FBullCowGame {
public:

	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	//FString GetDifficulty();

	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();

	// counting bulls and cows and increasing try # and assumes valid guess
	FBullCowCount SubmitValidGuess(FString); //when declaring method here we dont have to have variable name, dont need handle to hold on to 


private: //compile-time values. the constructor later has the runtime values
	//see constructor for instantiation
	int32 MyMaxTry; //these are methods
	int32 MyCurrentTry;
	FString MyHiddenWord;
	//FString MyDifficulty;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};