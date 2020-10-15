// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectAlphaGameInstance.h"
#include "Crossair.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
//#include "Windows/MinWindows.h"

//#include <AK/SoundEngine/Common/AkMemoryMgr.h> 
//#include <AK/SoundEngine/Common/AkModule.h>                 
//#include <AK/Tools/Common/AkPlatformFuncs.h>                    
//#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
//#include <AK/SoundEngine/Common/AkSoundEngine.h> 


 UProjectAlphaGameInstance::UProjectAlphaGameInstance(const FObjectInitializer & ObjectInitializer)
{
    static ConstructorHelpers::FClassFinder<UUserWidget> CrossairBp (TEXT("/Game/UI/WBP_Crossair"));
    CrossairClass = CrossairBp.Class;
}

void UProjectAlphaGameInstance::Init()
{
    Super::Init();
   // InitSoundEngine();
}


void UProjectAlphaGameInstance::AddReticle()
{
    auto Crossair = CreateWidget<UCrossair>(this, CrossairClass);
    Crossair->AddToViewport();
}


//bool UProjectAlphaGameInstance::InitSoundEngine() 
//{
//    AkMemSettings memSettings;
//    AK::MemoryMgr::GetDefaultSettings(memSettings);
//
//    if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Could not create the memory manager."));
//        return false;
//    }
//
// 
//    // Create and initialize an instance of the default streaming manager. Note
//    // that you can override the default streaming manager with your own. 
//
//    AkStreamMgrSettings stmSettings;
//    AK::StreamMgr::GetDefaultSettings(stmSettings);
//
//    // Customize the Stream Manager settings here.
//    if (!AK::StreamMgr::Create(stmSettings))
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Could not create the Stream manager."));
//        return false;
//    }
//
//    if (AK::SoundEngine::Init(NULL, NULL) != AK_Success)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Could not initialize the Sound Engine."));
//
//        return false;
//
//    }
//
//    return true;
//
//
//}


