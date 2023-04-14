// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ToonGameMode.h"
#include "RandomMapScript.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealth::DamageTaken);

	auto ahoj = UGameplayStatics::GetGameMode(this);

	
	//UE_LOG(LogTemp, Warning, TEXT("HitComp: %s"), *HitComp->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Health bar to max"));
	ToonGameMode = Cast<AToonGameMode>(UGameplayStatics::GetGameMode(this));
	RandomMap = Cast<ARandomMapScript>(UGameplayStatics::GetGameMode(this));
			
}


// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealth::Healing()
{
	if (CurrentHealth < MaxHealth) {
		CurrentHealth = CurrentHealth + 10.0f;
		UE_LOG(LogTemp, Display, TEXT("Incrementing health"));
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("No able to increment health"));
	}	
}

void UHealth::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0) return;
	CurrentHealth -= Damage;


	if (CurrentHealth <= 0 && ToonGameMode) {
		ToonGameMode->ActorDied(DamagedActor);
		UE_LOG(LogTemp, Display, TEXT("Player dies"));
	}

	if (CurrentHealth <= 0 && RandomMap) {
		RandomMap->ActorDied(DamagedActor);
		UE_LOG(LogTemp, Display, TEXT("Player dies"));
	}

}

