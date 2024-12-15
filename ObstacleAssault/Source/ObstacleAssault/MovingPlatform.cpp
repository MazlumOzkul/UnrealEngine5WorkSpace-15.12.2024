// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	 StartLocation = GetActorLocation();

	 FName Name = GetFName();

	 UE_LOG(LogTemp, Warning, TEXT("Platform Name: %s"), *Name.ToString()); // Debugging: İsim kontrolü

		// Platform isimlerine göre farklı hızlar atıyoruz
   

    if (Name == FName("BP_MovingPlatform_C_1"))  // BP_MovingPlatform1 platformu için
    {
        PlatformVelocity = FVector(0, 0, 200);  // Y ekseninde 900 hızla hareket etsin
		 MoveDistance = 500;
    }
    else if (Name == FName("BP_MovingPlatform_C_3"))  // BP_MovingPlatform2 platformu için
    {
        PlatformVelocity = FVector(0, 0, -200);  // X ekseninde 500 hızla hareket etsin
		MoveDistance = 500;
    }
    else if(Name == FName("BP_PushingCube_C_1")) 
    {
        PlatformVelocity = FVector(0, 1000, 0);
		MoveDistance = 1500;
    }

	 else if(Name == FName("BP_PushingCube_C_2")) 
    {
        PlatformVelocity = FVector(0, -1200, 0);
		MoveDistance = 2000;
    }
	 else if(Name == FName("BP_PushingCube_C_3")) 
    {
        PlatformVelocity = FVector(0,1500, 0);
		MoveDistance = 3000;
    }

     else if(Name == FName("BP_PushingCube_C_6")) 
    {
        PlatformVelocity = FVector(1500,0, 0);
		MoveDistance = 3000;
    }   
    else if(Name == FName("BP_PushingCube_C_7")) 
    {
        PlatformVelocity = FVector(-1500,0, 0);
		MoveDistance = 3000;
    }   
    else if(Name == FName("BP_RotatingPlatform_C_1")) 
    {
        RotationVelocity = FRotator(0,200, 0);
		
    }
	else if(Name == FName("BP_RotatingPlatform_C_2")) 
    {
        RotationVelocity = FRotator(0,200, 0);
    }
    else if(Name == FName("BP_RotatingPlatform_C_3")) 
    {
        RotationVelocity = FRotator(0,200, 0);
    }
    else if(Name == FName("BP_RotatingPlatform_C_4")) 
    {
        RotationVelocity = FRotator(0,150, 0);
    }
	else if(Name == FName("BP_RotatingPlatform_C_5")) 
    {
        RotationVelocity = FRotator(0,150, 0);
    }
	else if(Name == FName("BP_RotatingPlatform_C_6")) 
    {
        RotationVelocity = FRotator(0,150, 0);
    }
    else if(Name == FName("BP_Sweeper_C_1")) 
    {
        RotationVelocity = FRotator(0,150, 0);
    }
	else if(Name == FName("BP_Sweeper_C_2")) 
    {
        RotationVelocity = FRotator(0,150, 0);
    }
	else if(Name == FName("BP_Sweeper_C_3")) 
    {
        RotationVelocity = FRotator(0,150, 0);
    }
	else if(Name == FName("BP_Sweeper_C_4")) 
    {
        RotationVelocity = FRotator(0,150, 0);
    }
	else if(Name == FName("BP_Sweeper_C_5")) 
    {
        RotationVelocity = FRotator(0,150, 0);
    }
    StartLocation = GetActorLocation();  // Başlangıç konumunu kaydet
}
	


// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

}	
   void AMovingPlatform::MovePlatform(float DeltaTime){

   
	// Move platform forwards
	   //get current location
	FVector CurrentLocation = GetActorLocation();   
	   //Add vector to that location
	CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
	   //set the location
	SetActorLocation(CurrentLocation);   
	//send platform back if gone too far
	   // Check how far we've moved
	   float DistanceMoved= FVector::Dist(StartLocation, CurrentLocation);
	   //reverse direction of motion if gone too far
	  

	  

       if(ShouldPlatformReturn()){

		
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection*MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;

	   }
	   else{
		
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	   
	 }  
    
   }
  void AMovingPlatform::RotatePlatform(float DeltaTime){

	
	AddActorLocalRotation(RotationVelocity * DeltaTime);
  }
    
  bool AMovingPlatform::ShouldPlatformReturn() const
  {
	
	return GetDistanceMoved() > MoveDistance;
  }
   
  float AMovingPlatform::GetDistanceMoved() const
  {
	return FVector::Dist(StartLocation, GetActorLocation());
  }
