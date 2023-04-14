// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AHealingItem::AHealingItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Colider"));


	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));


}

// Called when the game starts or when spawned
void AHealingItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealingItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

