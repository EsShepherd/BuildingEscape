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
}

void UOpenDoor::OpenDoor()
{
	FRotator CurRotation = Owner->GetActorRotation();
	FRotator NewRotation = FRotator(0.f, OpenAngle, 0.f);
	Owner->SetActorRotation(NewRotation);
	if (CurRotation != Owner->GetActorRotation()) {
		if (OpenSound != nullptr) OpenSound->Play();
	}
}

void UOpenDoor::CloseDoor()
{
	FRotator CurRotation = Owner->GetActorRotation();
	FRotator NewRotation = FRotator(0.f, CloseAngle, 0.f);
	Owner->SetActorRotation(NewRotation);
	if (CurRotation != Owner->GetActorRotation()) {
		if (CloseSound != nullptr) CloseSound->Play();
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// If ActorThatOpens is in the volume
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	// Check if its time to close the door
	if (IsOpen()) {
		if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > TimeToClose) {
			CloseDoor();
		}
	} 
}

bool UOpenDoor::IsOpen()
{
	if (GetOwner()->GetActorRotation().Yaw != CloseAngle) {
		return true;
	}
	return false;
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;

	// Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto& Actor : OverlappingActors) {
		UE_LOG(LogTemp, Warning, TEXT("%s is in the Trigger Volume"), *Actor->GetName());
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	// iterate through them adding their masses

	return TotalMass;
}
