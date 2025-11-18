
#include "VMPortal.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Core/InteractComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Engine/LevelStreaming.h"
AVMPortal::AVMPortal()
{
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->InitCapsuleSize(70.0f, 150.0f);
	RootComponent = Capsule;

	// 나이아가라 컴포넌트 생성 및 Capsule에 붙이기
	PortalNiagaraSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PortalNiagara"));
	PortalNiagaraSystem->SetupAttachment(RootComponent);

	// 나이아가라 시스템 에셋 할당
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> PortalNiagaraRef(TEXT("/Game/PortalSystem/FX/NS_Portal_02.NS_Portal_02"));
	if (PortalNiagaraRef.Succeeded())
	{
		PortalNiagaraSystem->SetAsset(PortalNiagaraRef.Object);
		PortalNiagaraSystem->bAutoActivate = true; // 생성과 동시에 자동 재생
	}

	//상호작용 컴포넌트 추가
	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));
	InteractComponent->SetupAttachment(RootComponent);
}

void AVMPortal::Interact()
{
	UE_LOG(LogTemp, Log, TEXT("Portal 진입"));
	FName TargetLevel = FName("BossMap1");

	UGameplayStatics::OpenLevel(GetWorld(), TargetLevel);
}

void AVMPortal::BeginPlay()
{
	Super::BeginPlay();

}

