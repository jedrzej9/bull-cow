// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT("The HiddenWord is %s."), *HiddenWord); //Debug line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        //restarting the game
        ClearScreen();
        SetupGame();
    }
    else
    {
        //keep playing
        ProccessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    //Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows!"));
    
    HiddenWord = TEXT("cake");
    
    Lives = HiddenWord.Len();  //set lives
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    PrintLine(TEXT("Press enter to restart the game"));
    bGameOver = true;
}

void UBullCowCartridge::ProccessGuess(FString Guess)
{
    if (Guess == HiddenWord && Lives > 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have won!!! :-o"));
        EndGame();
        return;
    }

    if ((HiddenWord.Len() != Guess.Len()) && Lives > 0)
    {
        PrintLine(TEXT("The hidden word is %i characters long!"), HiddenWord.Len());
        PrintLine(TEXT("You have %i lives"), Lives);
        return;
    }

    Lives--;

    if ((HiddenWord.Len() == Guess.Len()) && Lives > 0)
    {
        PrintLine(TEXT("Wrong guess!"));
        PrintLine(TEXT("You have %i lives"), Lives);
        return;
    }
    else
    {
        ClearScreen();
        PrintLine(TEXT("You have lost :-("));
        PrintLine(TEXT("The hidden word was %s."), *HiddenWord);
        EndGame();
    }
}