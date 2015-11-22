// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "SW_Project2GameMode.generated.h"


UCLASS(minimalapi)
class ASW_Project2GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASW_Project2GameMode();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float time;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

};



