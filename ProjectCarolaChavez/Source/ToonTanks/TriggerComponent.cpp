// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"


UTriggerComponent::UTriggerComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    if (Mover == nullptr)
    {
        return;
    }

    AActor* Actor = GetAcceptableActor();
    if (Actor != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Gates triggered to move"));
        Mover->MoveObject(true);
    }
    else
    {
        Mover->MoveObject(false);
    }
}


void UTriggerComponent::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}


AActor* UTriggerComponent::GetAcceptableActor()
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

 
    for (AActor* Actor : Actors)
    {
        if (Actor->ActorHasTag(ObjetoGrabbable))
        {
            UE_LOG(LogTemp, Warning, TEXT("Object has the right tag to trigger the gates"));
            GrabbedMesh = Cast<AGrabbableActor>(Actor);
            GrabbedMesh->onGrabbie();
            return Actor;
        }
    }

    return nullptr;
}

