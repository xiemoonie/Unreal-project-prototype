// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	void HandleDestruction();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 someVisibleVariable = 2;
	UPROPERTY(EditAnywhere)
		int32 someEditableVariable = 3;
	UPROPERTY(VisibleInstanceOnly)
		int32 someVisibleInstanceVariable = 4;
	UPROPERTY(VisibleDefaultsOnly , BlueprintReadOnly)
		int32 someDefaultVariable = 5;
	UPROPERTY(VisibleDefaultsOnly)
		int32 someDefaultOnlyInt = 6;
	
protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Component", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Component", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABullet> BulletClass;
	UPROPERTY(EditAnywhere)
	UParticleSystem* ParticlesDeath;

	UPROPERTY(EditAnywhere)
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> DeathCameraClass;

};
