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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	bool bMapPause;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	bool bGameFinish;


	void MoveToMenuMap();
	void DisplayRestartMenu();

	/*TSubclassOf<class UUserWidget> HUDWidgetClass;
	UPROPERTY()
	class UUserWidget* CurrentWidget;*/

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

};



