// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Press TAB to interact with me."));
    SetupGame();
}

TArray<FString> UBullCowCartridge::GetValidWords() const
{
    TArray<FString> ValidWords;
    for (auto Word : Words)
    {
        if (Word.Len() >= 4 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

void UBullCowCartridge::SetupGame()
{
    ClearScreen();
    bIsGameOver = false;
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    PrintLine(TEXT("Hello Player!"));
    PrintLine(TEXT("And guess the %i letters word"), HiddenWord.Len());
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    if (bIsGameOver)
    {
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have won"));
        EndGame();
    }
    else
    {
        Lives--;
        PrintLine(TEXT("Wrong answer!"));
        if (Lives == 0)
        {
            PrintLine(TEXT("No more lives, you have lost..."));
            PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
            EndGame();
            return;
        }
        const bool bIsRightLen = Guess.Len() == HiddenWord.Len();
        const bool bIsIsogram = IsIsogram(Guess);
        if (!bIsRightLen)
        {
            PrintLine(TEXT("Remember the HiddenWord has %i letters!"), HiddenWord.Len());
        }
        if (!bIsIsogram)
        {
            PrintLine(TEXT("%s is not an isogram"), *Guess);
        }
        if(bIsRightLen && bIsIsogram)
        {
            const FBullsAndCowsCount Count = GetBullsAndCows(Guess);
            PrintLine(TEXT("You got %i Bulls and %i Cows"),Count.Bulls, Count.Cows);
        }
        PrintLine(TEXT("%i Lives left"), Lives);
    }
}

FBullsAndCowsCount UBullCowCartridge::GetBullsAndCows(const FString& ValidGuess) const
{
    FBullsAndCowsCount Count;
    //if I am here the Guess and HiddenWord have same Len() and IsIsogram
    for(int32 GuessIndex = 0; GuessIndex < HiddenWord.Len(); GuessIndex++)
    {
        if (ValidGuess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (ValidGuess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}

void UBullCowCartridge::EndGame()
{
    bIsGameOver = true;
    PrintLine(TEXT("Press ENTER to play again!"));
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 Index1 = 0; Index1 < Word.Len() - 1; Index1++)
    {
        for (int32 Index2 = Index1 + 1; Index2 < Word.Len(); Index2++)
        {
            if (Word[Index1] == Word[Index2])
            {
                return false;
            }
        }
    }
    return true;
}