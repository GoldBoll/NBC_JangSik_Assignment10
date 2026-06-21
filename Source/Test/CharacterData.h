#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterData.generated.h"

/**
 * 캐릭터 데이터 저장용 클래스 (도전 과제).
 * UObject를 상속해 UPROPERTY 속성을 갖는 순수 데이터 컨테이너로 쓴다.
 * Test 모듈에 두어, 주 게임 모듈이 이 클래스를 참조하는 "모듈 간 참조"를 한 번 더 보여준다.
 * TEST_API: 다른 모듈(주 모듈)에서 이 클래스를 쓸 수 있도록 내보내는 매크로.
 */
UCLASS(BlueprintType)
class TEST_API UCharacterData : public UObject
{
	GENERATED_BODY()

public:
	// 캐릭터 이름. 초기값은 데이터 클래스 자체에서 지정한다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	FString CharacterName = TEXT("Jangsik");

	// 체력 초기값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	int32 Health = 100;

	// 이동 속도 초기값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	float MoveSpeed = 600.f;
};
