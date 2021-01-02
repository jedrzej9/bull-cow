// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
#include "Math/UnrealMathUtility.h" //RandRange

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words);

    SetupGame();

    //PrintLine(TEXT("The number of possible words is %i."), Words.Num());
    //PrintLine(TEXT("The number of valid words is %i."), GetValidWords(Words).Num());
    //PrintLine(TEXT("%d"), IsIsogram(HiddenWord));
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
    
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    
    Lives = HiddenWord.Len();  //set lives
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue..."));
    PrintLine(TEXT("The HiddenWord is %s."), *HiddenWord); //Debug line
}

void UBullCowCartridge::EndGame()
{
    PrintLine(TEXT("Press enter to restart the game"));
    bGameOver = true;
}

void UBullCowCartridge::ProccessGuess(const FString& Guess)
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

    Lives--; //Remove life

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

    int32 Bulls = 0, Cows = 0;
    GetBullCows(Guess, Bulls, Cows);

    PrintLine(TEXT("You have %i bulls and %i cows"), Bulls, Cows);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 startingPoint = 0; startingPoint < Word.Len(); startingPoint++)
    {
        for (int32 i = startingPoint + 1; i < Word.Len(); i++)
        {
            if (Word[startingPoint] == Word[startingPoint + 1])
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& Words) const
{
    TArray<FString> ValidWords;

    for (FString Word : Words)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}

void UBullCowCartridge::GetBullCows(const FString& Guess, int32 BullCount, int32& CowCount) const
{
    BullCount = 0;
    CowCount = 0;

    for (int32 i = 0; i < Guess.Len(); i++)
    {
        if (Guess[i] == HiddenWord[i])
        {
            BullCount++;
            continue;
        }

        for (int32 j = 0; j < HiddenWord.Len(); j++)
        {
            if (Guess[i] == HiddenWord[j]) 
            {
                CowCount++;
                break;
            }
        }
    }
}
