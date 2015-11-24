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

	time -= DeltaSeconds;


	//Hanlde player input, fixxa
	APawn* pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		//this->DefaultPawnClass
	ASW_Project2Pawn* thePawn = Cast<ASW_Project2Pawn>(pawn);

	if (thePawn->bFinish)
	{
	
		UGameplayStatics::OpenLevel(this, TEXT("/Game/TransitionMap"), true);
	//	UGameplayStatics::OpenLevel((this, FName(TEXT("NewMap1"),false ));


	}

}
