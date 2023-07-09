// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UParticleSystemComponent;
class UFloatingPawnMovement;

UCLASS()
class MYPROJECT_API ABird : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveYaw(float Value);

	void MovePitch(float Value);

	float TurnFilter(float Value);

	void Death();

	UFUNCTION()
	void HandleComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector HitImpulse, const FHitResult& HitResult);

private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BirdMesh;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* DeathFVX;

	UPROPERTY(EditAnywhere)
	USoundBase* DeathSound;

	UPROPERTY(VisibleAnywhere)
	bool IsAlive = true;

	UPROPERTY(EditAnywhere)
	float FlySpeed = 4000.f;


	UPROPERTY(EditAnywhere)
	float MaxTurnSpeed = 0.5f;
};
