// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/UnrealMathUtility.h"
#include "WordsList.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullsAndCowsCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	// Your declarations go below!
	private:
	void SetupGame();
	void EndGame();
	TArray<FString> GetValidWords() const;
	void ProcessGuess(const FString& Guess);
	bool IsIsogram(const FString& Word) const;
	FBullsAndCowsCount GetBullsAndCows(const FString& ValidGuess) const;

	const TArray<FString> Isograms = GetValidWords();
	FString HiddenWord;
	int32 Lives;
	bool bIsGameOver = true;
};
