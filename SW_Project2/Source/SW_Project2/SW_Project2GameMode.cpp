// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SW_Project2.h"
#include "SW_Project2GameMode.h"
#include "SW_Project2Pawn.h"

ASW_Project2GameMode::ASW_Project2GameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = ASW_Project2Pawn::StaticClass();
}
