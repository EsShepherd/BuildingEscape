// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveToDirection.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UMoveToDirection : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveToDirection();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
		bool MoveToLocation;
	UPROPERTY(EditAnywhere)
		FVector Location;
	UPROPERTY(EditAnywhere)
		bool MoveToTarget;
	UPROPERTY(EditAnywhere)
		bool PlayerIsTarget;
	UPROPERTY(EditAnywhere)
		AActor* Target;

	UPROPERTY(EditAnywhere)
		int Speed = 200; //higher -> slower
};
