// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"



// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Bullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	RootComponent = Bullet;

	ParticlesFlow = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles Flow"));
	ParticlesFlow->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;


}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	Bullet->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	if (LaunchSound) {
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}


}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr) {
		Destroy();
		return;
	}

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if (HitParticles) {
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
			UE_LOG(LogTemp, Warning, TEXT("Hitting Particles Appear"));
		}
		if (HitSound) {
			UGameplayStatics::PlaySoundAtLocation(this, HitSound,GetActorLocation());
			UE_LOG(LogTemp, Warning, TEXT("Hitting Sounds"));
		}
		if (HitCameraClass) {
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraClass);
		}
	}
	Destroy();

	}



