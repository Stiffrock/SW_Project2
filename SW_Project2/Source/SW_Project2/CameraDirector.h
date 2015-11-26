// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

UCLASS()
class SW_PROJECT2_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACameraDirector();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnyWhere)
		AActor* CameraOne;

	UPROPERTY(EditAnywhere)
		AActor* CameraTwo;

	UPROPERTY(EditAnywhere)
		AActor* CameraThree;

	//TArray<AActor*> CameraArray;

	float TimeToNextCameraChange;

};
