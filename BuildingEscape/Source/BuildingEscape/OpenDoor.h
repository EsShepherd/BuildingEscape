// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Sound/AmbientSound.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;
	UFUNCTION(BlueprintPure, Category="OpenDoor")
		float GetOpenAngle();
	UFUNCTION(BlueprintPure, Category="OpenDoor")
		float GetSwingTime();

	/** The sound to be played */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
		class USoundBase* OpenSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
		class USoundBase* CloseSound;
		
private:
	UPROPERTY(EditAnywhere)
		float OpenAngle = 75.f;
	UPROPERTY(EditAnywhere, Category="Advanced")
		float SwingTime = 1.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY(EditAnywhere, Category="Advanced")
		float TriggerMass;

	UPROPERTY(EditAnywhere, Category="Timing")
		float Delay = 0.f;
	UPROPERTY(EditAnywhere, Category="Timing")
		float TimeToClose = 0.f;

	AActor* Owner = GetOwner();
	float LastDoorOpenTime = 0.f;
	float LastDoorCloseTime = 0.f;

	// Returns total mass in kg
	float GetTotalMassOfActorsOnPlate();

	bool DoorIsClosed = true;
};
