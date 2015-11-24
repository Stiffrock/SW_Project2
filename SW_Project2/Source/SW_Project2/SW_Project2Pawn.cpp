// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SW_Project2.h"
#include "SW_Project2Pawn.h"
#include "Engine.h"
#include "Projectile.h"
#include "Block.h"
#include "Engine.h"
#include "SW_Project2GameMode.h"

ASW_Project2Pawn::ASW_Project2Pawn()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Flying/Meshes/UFO.UFO"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create static mesh component
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh0"));
	PlaneMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	RootComponent = PlaneMesh;

	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->AttachTo(RootComponent);
	SpringArm->TargetArmLength = 160.0f; // The camera follows at this distance behind the character	
	SpringArm->SocketOffset = FVector(0.f,0.f,60.f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.f;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(FName(TEXT("TestLight")));
	PointLight->AttachTo(this->GetPlaneMesh(), "Socket_Shoot");

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // Don't rotate camera with controller

	// Set handling parameters
	Acceleration = 500.f;
	TurnSpeed = 50.f;
	MaxSpeed = 4000.f;
	MinSpeed = 500.f;
	CurrentForwardSpeed = 500.f;

	energy = 1.0f;
	health = 1.0f;

	bThrust = false;

	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Projectile_BP.Projectile_BP'"));
	if (ItemBlueprint.Object)
	Projectile_BP = (UClass*)ItemBlueprint.Object->GeneratedClass;
}

void ASW_Project2Pawn::Tick(float DeltaSeconds)
{
	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaSeconds, 0.f, 0.f);

	if (bThrust && energy != 0.0f)
	{
		energy -= 0.5f * DeltaSeconds;
	}
	else
		energy += 0.1f * DeltaSeconds;

	// Move plan forwards (with sweep so we stop when we collide with things)
	AddActorLocalOffset(LocalMove, true);

	// Calculate change in rotation this frame
	FRotator DeltaRotation(0,0,0);
	FRotator CurrentRotation = GetActorRotation();
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaSeconds;

	DeltaRotation.Yaw = CurrentYawSpeed * DeltaSeconds;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaSeconds;

	OffsetY = CurrentPitchSpeed * DeltaSeconds;
	OffsetX = CurrentYawSpeed * DeltaSeconds;


	// Rotate and limit plane
	if (CurrentRotation.Pitch >= 30.0f && DeltaRotation.Pitch > 0.f)
	{
		DeltaRotation.Pitch = 0.f;
	}

	if (CurrentRotation.Pitch <= -30.0f && DeltaRotation.Pitch < 0.f)
	{
		DeltaRotation.Pitch = 0.f;
	}

	if (CurrentRotation.Yaw >= 30.0f && DeltaRotation.Yaw > 0.f)
	{
		DeltaRotation.Yaw = 0.f;
	}

	if (CurrentRotation.Yaw <= -30.0f && DeltaRotation.Yaw < 0.f)
	{
		DeltaRotation.Yaw = 0.f;
	}
	AddActorLocalRotation(DeltaRotation);

	// Call any parent class Tick implementation
	Super::Tick(DeltaSeconds);
}

void ASW_Project2Pawn::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	ABlock* block = Cast<ABlock>(Other);

	if (Other == block)
	{
		if (block->Pickup)
		{
			AGameMode* gModePtr = GetWorld()->GetAuthGameMode();
			ASW_Project2GameMode* GameModePtr = Cast<ASW_Project2GameMode>(gModePtr);
			GameModePtr->time += 10.0f;

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TakeDamage"));
		}
		else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TakeDamage"));		
		health -= 0.2f;
		//TakeDamage
	}

	Other->Destroy();
	// Set velocity to zero upon collision
	CurrentForwardSpeed = 0.f;
}


void ASW_Project2Pawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	// Bind our control axis' to callback functions
	InputComponent->BindAxis("Thrust", this, &ASW_Project2Pawn::ThrustInput);
	InputComponent->BindAxis("MoveUp", this, &ASW_Project2Pawn::MoveUpInput);
	InputComponent->BindAxis("MoveRight", this, &ASW_Project2Pawn::MoveRightInput);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &ASW_Project2Pawn::ShootProjectile);
}

void ASW_Project2Pawn::ThrustInput(float Val)
{
	// Is there no input?
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	if (energy >= 0.0f)
	{
		// If input is not held down, reduce speed
		float CurrentAcc = bHasInput ? (Val * Acceleration) : (-0.5f * Acceleration);
		// Calculate new speed
		float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
		// Clamp between MinSpeed and MaxSpeed
		CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);

		if (bHasInput)		
			bThrust = true;		
		else
			bThrust = false;
	}
	else
	{
		bHasInput = false;
		bThrust = false;
		float CurrentAcc = bHasInput ? (Val * Acceleration) : (-0.5f * Acceleration);
		float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
		CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);
	}

}

void ASW_Project2Pawn::MoveUpInput(float Val)
{
	// Target pitch speed is based in input
	float TargetPitchSpeed = (Val * TurnSpeed * 1.f);
	

	// When steering, we decrease pitch slightly
	TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2f);



	// Smoothly interpolate to target pitch speed
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

}

void ASW_Project2Pawn::MoveRightInput(float Val)
{
	// Target yaw speed is based on input
	float TargetYawSpeed = (Val * TurnSpeed);

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);



	// Is there any left/right input?
	const bool bIsTurning = FMath::Abs(Val) > 0.2f;

	// If turning, yaw value is used to influence roll
	// If not turning, roll to reverse current roll value
	float TargetRollSpeed = bIsTurning ? (CurrentYawSpeed * 0.5f) : (GetActorRotation().Roll * -2.f);

	// Smoothly interpolate roll speed
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ASW_Project2Pawn::ShootProjectile()
{
	
	const FRotator SpawnRotation = SpringArm->GetComponentRotation();
	FRotator CurrentRotation = GetActorRotation();

	FVector SocketPos = PointLight->GetComponentLocation();
	FRotator SocketRotation = PointLight->GetComponentRotation();



	
	//const FVector SpawnLocation = GetActorLocation() + FVector(200.f - Offset.X, 0.f - Offset.Y, 0.f - Offset.Z);
	const FVector SpawnLocation = SocketPos + FVector(200.f, 0, 0);

	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Shoot"));
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;
		AProjectile* Projectile = World->SpawnActor<AProjectile>(Projectile_BP, SpawnLocation, SocketRotation, SpawnParams);
	}
}