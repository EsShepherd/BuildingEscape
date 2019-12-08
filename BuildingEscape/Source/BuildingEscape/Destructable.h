// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/AudioComponent.h"
#include "Destructable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDestructable : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDestructable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void Destruct();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(EditAnywhere)
	int8 Health = 100;

	UPROPERTY(EditAnywhere)
	AActor* CollidingActor;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* OneShotTrigger;

	UPROPERTY(EditAnywhere)
	UAudioComponent* TargetAudioComponent;
	
};
