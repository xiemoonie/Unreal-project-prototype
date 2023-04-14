// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"
#include "PlayerShooter.h"
#include "ToonPlayerController.h"



void AToonGameMode::ActorDied(AActor* DeadActor) {

	if (DeadActor == Player) {
		Player->HandleDestruction();
		if (ToonPlayerController) {
			ToonPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (AEnemy* DestroyedEnemy = Cast<AEnemy>(DeadActor)) {
		DestroyedEnemy->HandleDestruction();
		--AmountEnemies;
		UE_LOG(LogTemp, Display, TEXT("Amount Of Enemies %d"), AmountEnemies);
		if (AmountEnemies == 0) {
			//GameOver(true);
		}
	}

}
void AToonGameMode::BeginPlay() {
	Super::BeginPlay();

	HandleGameStart();
	

}

void AToonGameMode::HandleGameStart() {

	AmountEnemies = GetAmountEnemies();
	Player = Cast<APlayerShooter>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonPlayerController = Cast<AToonPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	UE_LOG(LogTemp, Display, TEXT("Game Starts"));

	if (ToonPlayerController) {
		ToonPlayerController->SetPlayerEnabledState(false);
		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimer = FTimerDelegate::CreateUObject(
			ToonPlayerController,
			&AToonPlayerController::SetPlayerEnabledState,
			true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimer, StartDelay, false);
	}
    
}

int32 AToonGameMode::GetAmountEnemies() {
	TArray<AActor*> CurrentEnemies;
	UGameplayStatics::GetAllActorsOfClass(this,AEnemy::StaticClass(), CurrentEnemies);
	return CurrentEnemies.Num();
}