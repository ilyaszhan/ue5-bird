// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "MyProject/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
		
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComonent"));
	RootComponent = ItemMesh;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

float AItem::TransformedSin(float Value)
{
	return FMath::Sin(Value);
}

float AItem::TransformedCosin(float Value)
{
	return FMath::Cos(Value);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float MovementRate = 50.f;
	float RotationRate = 45.f;

	AddActorWorldOffset(FVector(DeltaTime * MovementRate * -1, 0.f, 0.f));
	AddActorWorldRotation(FRotator(DeltaTime * RotationRate, DeltaTime * RotationRate, DeltaTime * RotationRate));

	RunningTime += DeltaTime;

	//float DeltaZ = FMath::Sin(RunningTime * TimeConstant) * Amplitude;

	//AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));
		
	FVector Location = GetActorLocation();
	FVector Forward = GetActorForwardVector();
	FVector EndLineLocation = Location + Forward * 100.f;

	DRAW_VECTOR_SingleFrame(Location, EndLineLocation);
}

