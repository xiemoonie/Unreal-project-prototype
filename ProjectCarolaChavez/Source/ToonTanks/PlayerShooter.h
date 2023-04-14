// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PlayerShooter.generated.h"


/**
 *
 */
UCLASS()
class TOONTANKS_API APlayerShooter : public ABasePawn
{
	GENERATED_BODY()

public:
	APlayerShooter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();
	APlayerController* GetPlayerShooterController() const { return PlayerShooterController; }

	bool isAlive = true;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Character Component")
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Character Component")
		class UCameraComponent* Camera;


	void Move(float Value);
	void Turn(float Value);

	UPROPERTY(EditAnywhere);
	float Speed = 10;
	UPROPERTY(EditAnywhere);
	float TurnSpeed = 100;

	APlayerController* PlayerShooterController;



};
