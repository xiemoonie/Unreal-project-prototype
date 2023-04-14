// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"


// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetOwner()->GetActorLocation();

	// ...

}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove) {
		UE_LOG(LogTemp, Display, TEXT("Gates moves back and forth"));
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = OriginalLocation + MoveOffSet;
		float speed = FVector::Distance(OriginalLocation, TargetLocation) / Time;
		
		float distT = FVector::Distance(CurrentLocation, TargetLocation);
		float distO = FVector::Distance(CurrentLocation, OriginalLocation);

		if (ShouldReturn) {
			if (distO < 10.0f) ShouldReturn = false;

			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, OriginalLocation, DeltaTime, speed);
			GetOwner()->SetActorLocation(NewLocation);
		}
		else {
			if (distT < 10.0f) ShouldReturn = true;

			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, speed);
			GetOwner()->SetActorLocation(NewLocation);
		}		
	}

	/*
	FVector TargetLocation = OriginalLocation; //default value is original location
if(ShouldMove){
	TargetLocation = OriginalLocation + MoveOffSet;

}

FVector CurrentLocation = GetOwner()->GetActorLocation();

float speed = MoveOffSet.Length() / Time;
FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, speed);

GetOwner()->SetActorLocation(NewLocation);

*/

}

void UMover::MoveObject(bool NewShouldMove) {
	ShouldMove = NewShouldMove;
}
