// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API  UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void MoveObject(bool ShouldMove);


private:
UPROPERTY(EditAnywhere)
bool ShouldReturn = false;

UPROPERTY(EditAnywhere)
FVector MoveOffSet = FVector(0.0f,0.0f,500.0f);

UPROPERTY(EditAnywhere)
float Time = 2;

UPROPERTY(EditAnywhere)
bool ShouldMove;

UPROPERTY(EditAnywhere)
FVector OriginalLocation;
		
};
