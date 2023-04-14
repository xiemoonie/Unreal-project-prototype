// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tasks/AITask_MoveTo.h"
#include "AI_ENEMY.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AAI_ENEMY : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	class AItask* AUAITask_MoveTo;
	UAITask_MoveTo* Task;


	UPROPERTY();
	bool Movement = true;
	//FTimerHandle TimerHandle;

	float switchCounter = 0.0f;

	void ChangeDirection();

	FVector originalLoc;


};
