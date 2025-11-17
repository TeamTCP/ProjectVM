// Fill out your copyright notice in the Description page of Project Settings.


#include "AOE/VMAOEBlastBase.h"

#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"


#include <Kismet/GameplayStatics.h>

AVMAOEBlastBase::AVMAOEBlastBase()
{
    SceneRootComp = CreateDefaultSubobject <USceneComponent>(TEXT("SceneRooCompt"));

    RootComponent = SceneRootComp;

    ConstructorHelpers::FObjectFinder<UParticleSystem> BlastEffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
    BlastEffect = BlastEffectRef.Object;

    ConstructorHelpers::FObjectFinder<USoundBase> BlastSoundRef(TEXT("/Script/Engine.SoundCue'/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue'"));
    BlastSound = BlastSoundRef.Object;
}

void AVMAOEBlastBase::SpawnAOESphere()
{
    Super::SpawnAOESphere();

    // Cascade 시스템 소환
    SpawnBlastEffect();

    // 음악 틀기.
    PlayBlastSound();
}

void AVMAOEBlastBase::OnFinishParticle(UParticleSystemComponent* ParticleSystem)
{
    UE_LOG(LogTemp, Log, TEXT("UParticleSystemComponent finished: %s"), *ParticleSystem->GetName());
    ParticleSystem->Deactivate();
    Destroy();
}

void AVMAOEBlastBase::SpawnBlastEffect()
{
    FVector SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();

    //UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BlastEffect, SpawnLocation, SpawnRotation, true);

    UParticleSystemComponent* PSC = UGameplayStatics::SpawnEmitterAttached(BlastEffect, RootComponent, NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
    if (PSC == nullptr)
    {
        UE_LOG(LogTemp, Log, TEXT("SpawnEmitterAttached가 실패하였습니다."));
        return;
    }
}

void AVMAOEBlastBase::PlayBlastSound()
{
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), BlastSound, GetActorLocation());

    UParticleSystemComponent* PSC = Cast<UParticleSystemComponent>(RootComponent->GetChildComponent(0));
    PSC->OnSystemFinished.AddDynamic(this, &AVMAOEBlastBase::OnFinishParticle);
}
