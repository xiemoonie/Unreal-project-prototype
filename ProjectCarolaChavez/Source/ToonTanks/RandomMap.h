// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomMap.generated.h"

UCLASS()
class TOONTANKS_API ARandomMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//UStaticMeshComponent* Walls;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> Wall;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> HorisontalWall;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> Player;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> Enemy;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> HealingRoom;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> Grabbable;

	UPROPERTY(EditAnywhere)
	bool DisplayRandomMap = false;

	AActor *WallTile;
	AActor *SomeWall;
	AActor *HoriSomeWall;
	AActor* GrabbableItem;

	int32 AxisX = 0;
	int32 AxisY = 0;
	int RandVal = 1;
	float NewAxisY = 0.0f;
	float NewAxisYPair = 0.0f;


	UFUNCTION()
	void WallPlacement();
	UFUNCTION()
	int FindEmptyPosition(int x);

	UFUNCTION()
	bool FindEmptyWallsPosition(int x, int j);


	UFUNCTION()
	bool FindEmptyRoomPosition(int x, int j);

	UFUNCTION()
	void EnemyPlacement();

	UFUNCTION()
	void HealingRoomPlacement();

	UPROPERTY(EditAnywhere)
	int AmountEnemy = 3;
	UPROPERTY(EditAnywhere)
	int AmountHealingRooms = 3;
	UPROPERTY(EditAnywhere)
	int AmountWalls = 50;


	

	int pos[10];
	AActor* UsedActors[20][20];
	int rot = 90;
	
	bool WallExists = false;


};
