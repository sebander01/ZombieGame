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

/// <summary>
/// A method to more the player forwards based on a FVector direction variable assigned in blueprint
/// </summary>
void APlayerCharacter::MoveDirection(FVector Direction)
{
	//Direction multiplied by the walk speed
	moveComp->AddImpulse(Direction * walkSpeed);
}

