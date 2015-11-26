// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SW_Project2.h"
#include "SW_Project2GameMode.h"
#include "SW_Project2Pawn.h"
//#include "Blueprint/UserWidget.h"


ASW_Project2GameMode::ASW_Project2GameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = ASW_Project2Pawn::StaticClass();
	time = 30.f;
	health = 1.0f;
	bGameFinish = false;
	bMapPause = false;
}
  
void ASW_Project2GameMode::BeginPlay()
{
	Super::BeginPlay();

	/*if (HUDWidgetClass)
	{
	//	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		if (CurrentWidget)
		{
			//CurrentWidget->AddViewport();
		}
	}*/
}

void ASW_Project2GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (time <= 0.0f || health <= 0.0f)
		DisplayRestartMenu();
	else
		time -= DeltaSeconds;

	if (bGameFinish)
		MoveToMenuMap();
}

void ASW_Project2GameMode::MoveToMenuMap()
{
	UGameplayStatics::OpenLevel(this, TEXT("/Game/TransitionMap"), true);
}

void ASW_Project2GameMode::DisplayRestartMenu()
{
	bMapPause = true;
}