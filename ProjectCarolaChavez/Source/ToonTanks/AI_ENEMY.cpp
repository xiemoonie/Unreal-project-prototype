// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_ENEMY.h"

#include "Kismet/GameplayStatics.h"
#include "PlayerShooter.h"
#include "Tasks/AITask_MoveTo.h"
#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"



void AAI_ENEMY::BeginPlay()
{
	Super::BeginPlay();
	bool movement = true;
	//originalLoc = GetPawn()->GetActorLocation();
	//GetWorldTimerManager().SetTimer(TimerHandle, this, &AAI_ENEMY::ChangeDirection, 5.0f, true);
}


void AAI_ENEMY::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	

	auto distance = FVector::Dist(PlayerPawn->GetActorLocation(), GetPawn()->GetActorLocation());
	if (PlayerPawn != nullptr && distance < 1000.0f) {
		SetFocus(PlayerPawn);
		auto res = MoveToActor(PlayerPawn, 300);
		UE_LOG(LogTemp, Error, TEXT("Player found by enemy"));
	
	}
	else {
		switchCounter += DeltaSeconds;

		if (switchCounter > FMath::RandRange(0.5f, 1.5f)) {
			switchCounter = 0;
		    ChangeDirection();
			UE_LOG(LogTemp, Error, TEXT("Enemy moves randomly"));
		}

	}

}

void AAI_ENEMY::ChangeDirection() {	
	originalLoc = GetPawn()->GetActorLocation();
	auto loc = FVector(originalLoc.X + 2000.0f - FMath::RandRange(1000.0f, 3000.0f), originalLoc.Y + 500.0f - FMath::RandRange(250.0f, 750.0f), originalLoc.Z);
	DrawDebugLine(GetWorld(), originalLoc, loc, FColor::Red, false, 2.0f);
	MoveToLocation(loc, -1.0f, false, true, true);
}

