// Fill out your copyright notice in the Description page of Project Settings.

#include "SW_Project2.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine.h"
#include "Block.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionComp->InitSphereRadius(50.0f);

	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	RootComponent = CollisionComp;
	StaticMesh->AttachTo(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0;

}

void AProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	ABlock* block = Cast<ABlock>(OtherActor);

	if (OtherActor == block)
	{
		if (block->Pickup || block->Finish)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pickup/Finish block hit detected"));
		}
		else
		{
			OtherActor->Destroy();
		}		
	}
	this->Destroy();

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

