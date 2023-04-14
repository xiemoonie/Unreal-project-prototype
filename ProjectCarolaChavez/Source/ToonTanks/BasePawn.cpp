// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Colider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);


}


void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(LookAtRotation);
}

void ABasePawn::Fire() {
	

	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();


	auto Projectile = GetWorld()->SpawnActor<ABullet>(BulletClass, Location, Rotation);
	Projectile->SetOwner(this);
	UE_LOG(LogTemp, Error, TEXT("Shooting"));

}

void ABasePawn::HandleDestruction() {
	
		if (ParticlesDeath) {
			UGameplayStatics::SpawnEmitterAtLocation(this, ParticlesDeath, GetActorLocation(), GetActorRotation());
			UE_LOG(LogTemp, Warning, TEXT("Death particles shown"));

		}
		if (DeathSound) {
			UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
			UE_LOG(LogTemp, Warning, TEXT("Death Sound Plays"));
		}
		if (DeathCameraClass) {
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraClass);
			UE_LOG(LogTemp, Warning, TEXT("Shaking Camera"));
		}

}



