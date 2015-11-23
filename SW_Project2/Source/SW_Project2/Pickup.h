// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class SW_PROJECT2_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();


	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;


	UPROPERTY(VisibleDefaultsOnly, Category = Pickup)
	class USphereComponent* CollisionComp;



	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }


	
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
