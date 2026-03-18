// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ZOMBIEGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomVariables-PlayerMovement")
	float walkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomVariables-Input")
	UInputMappingContext* map_standardGameplay;

	UCharacterMovementComponent* moveComp;

	UFUNCTION(BlueprintCallable, Category = "PlayerMovement")
	//Move in a direction given an FVector of direction and the players move componet.
	void MoveDirection(FVector Direction);

	UFUNCTION(BlueprintCallable, Category = "CameraMovement")

	/// <summary>
	/// A method to handle first and third person camera based on the current mode
	/// </summary>
	/// <param name="cam"></param>
	void CameraControls(UCameraComponent* cam, float maxX, float minX, float maxY, float minY, float speed, bool debug);

private:
	APlayerController* playerCon;
};
