// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomMap.h"
#include "Engine/StaticMesh.h"

// Sets default values
ARandomMap::ARandomMap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARandomMap::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			UsedActors[i][j] = nullptr;
		}
	}


	HealingRoomPlacement();

	WallPlacement();

	EnemyPlacement();




}

// Called every frame
void ARandomMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ARandomMap::FindEmptyPosition(int x) {

	for (int j = 0; j <8; j++) {
		if (UsedActors[x][j] == nullptr) {
			return j;
		}

	}
	return -1;
}



bool ARandomMap::FindEmptyWallsPosition(int x, int j) {

	if (UsedActors[x][j] == nullptr) {
		int NullCounter = 0;
		for (int i = 0; i < 8; i++) {
			if (UsedActors[x][i] == nullptr) {
				NullCounter++;
			}
		}

		if (NullCounter >= 2) {
			return true;
		}
		else {
			return false;
		}


	}
	else {
		return false;
	}

}

void ARandomMap::WallPlacement() {
	int WallPositions[] = { 1,2,4,5,8,9 };


	for (int i = 0; i < AmountWalls; i++) {
		int RandValue = FMath::RandRange(0, (sizeof(WallPositions) / sizeof(int)) - 1);
		AxisX = WallPositions[RandValue];
		AxisY = FMath::RandRange(0, 7);

		if (FindEmptyWallsPosition(AxisX, AxisY)) {


			WallTile = GetWorld()->SpawnActor<AActor>(Wall, FVector(AxisX * 400, AxisY * 400, 220.0f), FRotator(0, 0, 0));

			int HorizontalWallChance = FMath::RandRange(0, 1);
			if (HorizontalWallChance == 0 && RandValue % 2 == 0) {
				HoriSomeWall = GetWorld()->SpawnActor<AActor>(HorisontalWall, FVector(AxisX * 400 - 200.0f, AxisY * 400, 220.0f), FRotator(0, 90, 0));
			}



			UsedActors[AxisX][AxisY] = WallTile;
			UE_LOG(LogTemp, Error, TEXT("Wall Created %d %d"), AxisX, AxisY);
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Wall Not Created %d %d"), AxisX, AxisY);
		}

	}

}


void ARandomMap::EnemyPlacement() {

	int EmptyRoomPosition[] = { 0,1,2,3,4,5,6,7};
	for (int i = 0; i < AmountEnemy; i++) {

		int RandValue = FMath::RandRange(0, (sizeof(EmptyRoomPosition) / sizeof(int)) - 1);
		AxisX = EmptyRoomPosition[RandValue];
		AxisY = FMath::RandRange(0, 7);

		AActor* SomeEnemy = nullptr;
		int jPos = FindEmptyPosition(AxisX);
		if (jPos != -1) {
			SomeEnemy = GetWorld()->SpawnActor<AActor>(Enemy, FVector(AxisX*400.0f, jPos*400.0f, 30.0f), FRotator(0, 0, 0));
			UsedActors[AxisX][jPos] = SomeEnemy;
		}

	}
}



void ARandomMap::HealingRoomPlacement() {
	int EmptyRoomPosition[] = { 0,3,6,7 };
	for (int i = 0; i < AmountHealingRooms; i++) {

		int RandValue = FMath::RandRange(0, (sizeof(EmptyRoomPosition) / sizeof(int)) - 1);
		AxisX = EmptyRoomPosition[RandValue];
		AxisY = FMath::RandRange(1, 7);
		AActor* SomeHealingRoom = nullptr;

		FRotator rotation(0, 0, 0);

		int jPos = FindEmptyPosition(AxisX);
		if (jPos != -1) {
			GrabbableItem = GetWorld()->SpawnActor<AActor>(Grabbable, FVector(AxisX * 400.0f - 200.0f, jPos * 400.0f, 250.0f), FRotator(0, 0, 0));
			UsedActors[AxisX][jPos] = SomeHealingRoom;
		}

		if (FindEmptyRoomPosition(AxisX, AxisY)) {
			if (AxisY >= 4) {
				rotation = FRotator(0, 180, 0);
			}

			SomeHealingRoom = GetWorld()->SpawnActor<AActor>(HealingRoom, FVector(AxisX * 400.0f - 200.0f, AxisY * 400.0f, 250.0f), rotation);
			UsedActors[AxisX][AxisY] = SomeHealingRoom;
			UE_LOG(LogTemp, Error, TEXT("HEALING ROOM %d %d"), AxisX, AxisY);
		}
		else {

			UE_LOG(LogTemp, Error, TEXT("Not Created %d %d"), AxisX, AxisY);
		}

	}
}

bool ARandomMap::FindEmptyRoomPosition(int x, int y) {

	if (UsedActors[x][y] == nullptr) {
		switch (y) {
		case 0: return UsedActors[x][y + 1] == nullptr; break;
		case 9: return UsedActors[x][y - 1] == nullptr; break;
		default:
			return UsedActors[x][y + 1] == nullptr && UsedActors[x][y - 1] == nullptr;
		}

	}

	return false;
}