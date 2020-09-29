// Copyright Duncan Keenan-Smith 2020


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	//FString Log = TEXT("Hello!");
	//FString* PtrLog = &Log;

	//Log.Len();

	//(*PtrLog).Len();
	//PtrLog->Len();

	//UE_LOG(LogTemp, Warning, TEXT("%s"), **PtrLog);
	*/

	FString ObjName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("This component belongs to %s"), *ObjName);

	FString ObjPosition = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is at position %s"), *ObjName, *ObjPosition);
	
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

