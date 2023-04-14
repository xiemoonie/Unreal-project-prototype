// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RandomMapScript.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ARandomMapScript : public AGameModeBase
{
	GENERATED_BODY()


public:
	void ActorDied(AActor* DeadActor);

	

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class APlayerShooter* Player;
	class AToonPlayerController* ToonPlayerController;

	float StartDelay = 0.1f;
	void HandleGameStart();
	int32 AmountEnemies = 0;


	int32 GetAmountEnemies();
};
