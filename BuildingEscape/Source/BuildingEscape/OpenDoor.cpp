// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	if (!PressurePlate) {
		UE_LOG(LogTemp, Warning, TEXT("%s missing pressure plate!"), *Owner->GetName());
	}
}

void UOpenDoor::OpenDoor()
{
	OnOpen.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	OnClose.Broadcast();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// If ActorThatOpens is in the volume
	if (DoorIsClosed) { //prevent spamming when in trigger volume
		if (GetTotalMassOfActorsOnPlate() > TriggerMass) {
			OpenDoor();
			DoorIsClosed = false;
			LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		}
	}
	// Check if its time to close the door
	if (!DoorIsClosed) {
		if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > TimeToClose) {
			CloseDoor();
			DoorIsClosed = true;
		}
	}
}


float UOpenDoor::GetOpenAngle()
{
	return OpenAngle;
}

float UOpenDoor::GetSwingTime()
{
	return SwingTime;
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;

	// Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	if (PressurePlate != nullptr) PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	else {
		UE_LOG(LogTemp, Warning, TEXT("PressurePlate is nullptr"));
		return 0;
	}
	for (const auto& Actor : OverlappingActors) {
		UE_LOG(LogTemp, Warning, TEXT("%s is in the Trigger Volume"), *Actor->GetName());
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	// iterate through them adding their masses

	return TotalMass;
}
