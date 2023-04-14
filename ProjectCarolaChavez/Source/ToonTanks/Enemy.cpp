// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "PlayerShooter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"


void AEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (FireRangePlayer())
	{
		RotateTurret(Player->GetActorLocation());

	}

}
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerShooter>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemy::CheckFireCondition, FireRate, true);


}

void AEnemy::CheckFireCondition()
{

	
	if (Player == nullptr || !Activated) {
		return;
	}
	if (Player->isAlive && FireRangePlayer())
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy shoots at the player"));
		Fire();

	}
	

}


bool AEnemy::FireRangePlayer() {
	if (Player) {

		float Distance = FVector::Dist(GetActorLocation(), Player->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;

}

void AEnemy::HandleDestruction() {
	Super::HandleDestruction();
	Destroy();
	UE_LOG(LogTemp, Warning, TEXT("Enemy is being destroyed"));
}