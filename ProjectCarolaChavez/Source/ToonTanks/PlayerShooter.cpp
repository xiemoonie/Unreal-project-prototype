// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShooter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"

// Called when the game starts or when spawned

APlayerShooter::APlayerShooter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

void APlayerShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerShooter::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerShooter::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerShooter::Fire);
}

void APlayerShooter::Move(float Value) {
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value;
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector NewLocation = DeltaLocation * Speed * DeltaTime;
	AddActorLocalOffset(NewLocation, true);
}

void APlayerShooter::Turn(float Value) {

	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}



void APlayerShooter::BeginPlay()
{
	Super::BeginPlay();

	PlayerShooterController = Cast<APlayerController>(GetController());


}


// Called every frame
void APlayerShooter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (PlayerShooterController)
	{
		FHitResult HitResult;
		PlayerShooterController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		RotateTurret(HitResult.ImpactPoint);
		/*DrawDebugSphere(
			GetWorld(),
			HitResult.ImpactPoint,
			25.f,
			12,
			FColor::Red,
			false,
			-1.f);*/
	}

	

}

void APlayerShooter::HandleDestruction() {
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	isAlive = false;
	UE_LOG(LogTemp, Warning, TEXT("Player dies"));
}




