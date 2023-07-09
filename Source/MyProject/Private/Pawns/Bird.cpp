// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ABird::ABird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetCapsuleHalfHeight(15.f);
	Capsule->SetCapsuleRadius(15.f);
	Capsule->SetNotifyRigidBodyCollision(true);
	Capsule->SetCollisionProfileName(TEXT("BlockAll"));
	Capsule->OnComponentHit.AddDynamic(this, &ABird::HandleComponentHit);
	SetRootComponent(Capsule);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 150.f;
	SpringArm->SocketOffset = FVector(0.f, 0.f, 30.f);
	SpringArm->SetWorldRotation(FRotator(-5.f, 0.f, 0.f));
	SpringArm->SetWorldLocation(FVector(-50.f, 0.f, 0.f));

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	ViewCamera->SetupAttachment(SpringArm);

	DeathFVX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DeathFVX"));
	DeathFVX->SetupAttachment(RootComponent);
	DeathFVX->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TEST"));
}

void ABird::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.f)) {
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, Value);
	}
}

void ABird::MoveYaw(float Value)
{
	AddControllerYawInput(TurnFilter(Value));
}

void ABird::MovePitch(float Value)
{
	AddControllerPitchInput(TurnFilter(Value));
}

float ABird::TurnFilter(float Value)
{
	return Value * MaxTurnSpeed;
}

void ABird::Death()
{
	Capsule->SetCollisionProfileName(TEXT("NoCollision"));
	IsAlive = false;
	BirdMesh->DestroyComponent();
	DeathFVX->Activate();
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, DeathFVX->GetComponentLocation());
}

void ABird::HandleComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector HitImpulse, const FHitResult& HitResult)
{
	Death();
}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsAlive) {
		MoveForward(DeltaTime * FlySpeed);
	}
}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABird::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveYaw"), this, &ABird::MoveYaw);
	PlayerInputComponent->BindAxis(TEXT("MovePitch"), this, &ABird::MovePitch);
}

