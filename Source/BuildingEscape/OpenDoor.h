// Copyright Duncan Keenan-Smith 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void FindAudioComponent();
	void FindPressurePlate() const;

	// Tracks whether sound has been played
	bool HasOpenSoundPlayed = false;
	bool HasCloseSoundPlayed = true;

private:
	float CurrentYaw;
	float OriginalYaw;

	UPROPERTY(EditAnywhere)
	float TotalMassToOpenDoor = 60.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenAngle = 90.f;

	float DoorLastOpened = 0.f;
	
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.f;
	
	UPROPERTY(EditAnywhere)
	float CloseDoorSpeed = 90.f;
	
	UPROPERTY(EditAnywhere)
	float OpenDoorSpeed = 15.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
};
