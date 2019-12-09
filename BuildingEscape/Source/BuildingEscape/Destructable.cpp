// Fill out your copyright notice in the Description page of Project Settings.


#include "Destructable.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Audio.h"

// Sets default values for this component's properties
UDestructable::UDestructable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDestructable::BeginPlay()
{
	Super::BeginPlay();
	CollidingActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	// ...
	
}


// Called every frame
void UDestructable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CanBeOneShotted) {
		if (OneShotTrigger->IsOverlappingActor(CollidingActor)) {
			Destruct();
		}
	}
	if (GetOwner()->IsOverlappingActor(CollidingActor)) {
		Health -= 1;
		if (Health == 0) Destruct();
		FString ObjectName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Health of %s at %d"), *ObjectName, Health);
	}

	// ...
}

void UDestructable::Destruct()
{
	//*optional* shattering effect
	//vanish
	if (DestructSound != nullptr) DestructSound->Play();
	GetOwner()->Destroy();
}

	