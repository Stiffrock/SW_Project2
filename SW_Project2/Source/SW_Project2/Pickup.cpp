// Fill out your copyright notice in the Description page of Project Settings.

#include "SW_Project2.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));

	CollisionComp->InitSphereRadius(50.0f);

	RootComponent = CollisionComp;
	StaticMesh->AttachTo(RootComponent);

}



// Called every frame
void APickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

