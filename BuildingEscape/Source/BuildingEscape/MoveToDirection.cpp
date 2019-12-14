// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToDirection.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UMoveToDirection::UMoveToDirection()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveToDirection::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMoveToDirection::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector CurLocation = GetOwner()->GetActorLocation();
	if (MoveToLocation) {
		
		FVector Vector = Location - CurLocation;				//ABv = Bv - Av
		FVector Step = Vector / Speed;							//Step to take in this tick
		GetOwner()->SetActorLocation(CurLocation + Step);
	}
	else if (MoveToTarget) {
		if (PlayerIsTarget) {
			Target = GetWorld()->GetFirstPlayerController()->GetPawn(); //YEEEEEES
		}
		FVector Vector = Target->GetActorLocation() - CurLocation;
		FVector Step = Vector / Speed;
		GetOwner()->SetActorLocation(CurLocation + Step);
	}
	// ...
}

