// Copyright Duncan Keenan-Smith 2020


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

// Checking for Physics Handle Component
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("There is no Physics Handle Component on actor %s!"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber pressed!"));
	
	// Get player's viewpoint
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewLocation, OUT PlayerViewRotation);
	
	FVector LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * Reach;

	FHitResult Hit = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();

	// If we hit something then attach PhysicsHandle
	if (Hit.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation
			(
				ComponentToGrab,
				NAME_None,
				LineTraceEnd
			);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber released!"));
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player's viewpoint
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewLocation, OUT PlayerViewRotation);
	
	FVector LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * Reach;

	// If PhysicsHandle attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// Move Object we are holding
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// Get player's viewpoint
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewLocation, OUT PlayerViewRotation);
	
	FVector LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * Reach;

	// Ray-cast out to a certain distance (reach)
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	
	// Log out to test
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s actor is hit!"), *ActorHit->GetName());
	}

	return Hit;
}

