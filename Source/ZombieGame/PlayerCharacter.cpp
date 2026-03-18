// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Getting the player controller
	playerCon = GetWorld()->GetFirstPlayerController();

	//If playerCon is valid
	if (playerCon)
	{
		//Get the sub system for enhanced input and assign it the mapping context we are using and set it's priority to 0 so it's at the top
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer())->AddMappingContext(map_standardGameplay, 0);

	}

	//Get the move component and assign it to the moveComp variable to use throughout the project
	moveComp = this->GetCharacterMovement();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

#pragma region PlayerMovement/CameraMovement
/// <summary>
/// A method to more the player forwards based on a FVector direction variable assigned in blueprint
/// </summary>
void APlayerCharacter::MoveDirection(FVector Direction)
{
	//Direction multiplied by the walk speed
	moveComp->AddImpulse(Direction * walkSpeed);
}

/// <summary>
/// A method to handle first and third person camera based on the current mode
/// </summary>
/// <param name="cam"></param>
void APlayerCharacter::CameraControls(UCameraComponent* cam, float maxX, float minX, float maxY, float minY, float speed, bool debug)
{
	//Get mouse position
	float x, y;
	playerCon->GetMousePosition(x, y);

	//Get screen size
	int sizeX, sizeY;
	playerCon->GetViewportSize(sizeX, sizeY);

	//Center to middle
	float centeredX = x - (sizeX / 2.0f);
	float centeredY = y - (sizeY / 2.0f);

	//Verables for the final output
	FVector2D finalOutput;

	//Setting with data from the current output in case neither are adjusted
	finalOutput.X = cam->GetRelativeRotation().Yaw;
	finalOutput.Y = cam->GetRelativeRotation().Pitch;

	//Debug
	if (debug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("Centered X: %f"), centeredX));
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Centered Y: %f"), centeredY));
	}

	//If between the max and min x
	if (centeredX <= maxX && centeredX >= minX)
	{
		//Adjust speed by delta time * speed to handle camera speed
		finalOutput.X = centeredX + (speed * GetWorld()->DeltaTimeSeconds);
	}

	//If between the max and min y
	if (centeredY <= maxY && centeredY >= minY)
	{
		//Adjust speed by delta time * speed to handle camera speed
		finalOutput.Y = centeredY + (speed * GetWorld()->DeltaTimeSeconds);
	}

	//Set the rotation of the camera based on the position of the mouse
	cam->SetRelativeRotation(FRotator(finalOutput.Y, finalOutput.X, cam->GetRelativeRotation().Roll));
}
#pragma endregion

