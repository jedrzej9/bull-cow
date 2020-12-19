// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT("The HiddenWord is %s."), *HiddenWord); //Debug line
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len()); //Remove hard coded number
    PrintLine(TEXT("Type in your guess and press enter to continue..."));

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You have won!!! :-o"));
    }
    else 
    {
        if (HiddenWord.Len() != Input.Len())
        {
            PrintLine(TEXT("The hidden word is %i characters long!"), HiddenWord.Len());
        }
        PrintLine(TEXT("You have lost :-("));
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("cakeses");

    //set lives
    Lives = 4;
}
