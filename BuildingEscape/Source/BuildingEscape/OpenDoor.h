// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Sound/AmbientSound.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool IsOpen();

		
private:
	UPROPERTY(EditAnywhere)
		float OpenAngle = 75.f;
	UPROPERTY(EditAnywhere)
		float CloseAngle = 0.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens; //Pawn inherits from actor
	UPROPERTY(EditAnywhere)
		bool PlayerIsATO;
	
	UPROPERTY(EditAnywhere)
		AAmbientSound* OpenSound;
	UPROPERTY(EditAnywhere)
		AAmbientSound* CloseSound;

	UPROPERTY(EditAnywhere)
		float Delay = 0.f;
	UPROPERTY(EditAnywhere)
		float TimeToClose = 0.f;


	AActor* Owner = GetOwner();
	float LastDoorOpenTime = 0.f;
	float LastDoorCloseTime = 0.f;
};
