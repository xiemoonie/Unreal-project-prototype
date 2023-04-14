// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterHealth")
	float CurrentHealth = 0.0f;

	UFUNCTION(BlueprintCallable, meta = (BindWidget))
		void Healing();


	UFUNCTION(BlueprintCallable, meta = (BindWidget))
	float GetCurrentHealth(){
	return CurrentHealth/100.0f;
	}
	


private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.0f;
	
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);

	

    class AToonGameMode* ToonGameMode; //declare class not to include header file

	class ARandomMapScript* RandomMap;
		
};
