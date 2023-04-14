// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Enemy.generated.h"



/**
 *
 */
UCLASS()
class TOONTANKS_API AEnemy : public ABasePawn
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();
	class APlayerShooter* Player;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Activated = false;
	
	virtual void BeginPlay() override;

private:


	UPROPERTY(EditAnywhere)
	float FireRange = 750.f;

	
	FTimerHandle FireRateTimerHandle;
	float FireRate = FMath::RandRange(0.7f, 1.2f);
	void CheckFireCondition();
	bool FireRangePlayer();


};
