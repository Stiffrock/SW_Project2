// Fill out your copyright notice in the Description page of Project Settings.

#include "SW_Project2.h"
#include "Block.h"
#include "Engine.h"


// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	CollisionComp->InitSphereRadius(100.0f);
	RootComponent = CollisionComp;

	StaticMesh->AttachTo(RootComponent);
}


// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlock::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

