# ModuleAndPlugin — 언리얼 모듈과 플러그인 (10번 과제)

언리얼의 빌드 계층(**솔루션 → 프로젝트/플러그인 → 모듈 → 소스코드**)을 직접 만들어 이해하는 과제.
주 게임 모듈에 **새 모듈(`Test`)**을 추가해 연결하고, **독립 플러그인(`Temporary`)**을 손으로 구축한다.
Unreal Engine 5.5 · C++.

## ✅ 검증 상태 (2026-06-21)

빌드 → PIE 실행 → 플러그인 등록까지 에디터에서 직접 확인 완료.

| 항목 | 확인 방법 | 결과 |
|---|---|---|
| 빌드 통과 | Development Editor 풀 빌드 | ✅ LNK/모듈 에러 없음 |
| Test 모듈 동작 | PIE Output Log | ✅ `[Test Module] ATestActor::BeginPlay 호출됨` |
| 모듈 간 참조(스폰) | PIE Output Log | ✅ `[ModuleAndPlugin] GameMode::BeginPlay -> TestActor 스폰 요청` |
| 도전 — 데이터 클래스 | PIE Output Log | ✅ `[ModuleAndPlugin] CharacterData: Jangsik / HP 100 / Speed 600` |
| Temporary 플러그인 등록 | 플러그인 브라우저 | ✅ Enabled, Version 1.0, by JangSik (콘텐츠 브라우저 노출 확인) |

## 평가 기준 충족 매핑

| 평가 항목 | 구분 | 충족 근거 |
|---|---|---|
| 완성도 | 필수 | Test 모듈 추가·연결 + Temporary 플러그인 추가·연결 (위 검증 표) |
| 완성도 | 도전 | `Test` 모듈에 `UCharacterData` 클래스 추가 |
| 이해도 | 필수 | 모든 소스에 의도 중심 주석 작성 |
| 이해도 | 도전 | 주 모듈이 Test 모듈의 `ATestActor`·`UCharacterData` 참조 |
| 우수성 | 필수 | 본 README(플러그인·모듈 제작 과정) |
| 우수성 | 도전 | 모듈 등록 4곳 함정·`IMPLEMENT_MODULE` 이름 일치 함정을 TIL/README에 기록 |

## 구성 요약

| 구성요소 | 종류 | 핵심 매크로 | 역할 |
|---|---|---|---|
| `ModuleAndPlugin` | 주 게임 모듈 | `IMPLEMENT_PRIMARY_GAME_MODULE` | 프로젝트의 주 모듈. GameMode가 Test 모듈 액터를 스폰 |
| `Test` | 일반 모듈 | `IMPLEMENT_MODULE(FDefaultModuleImpl, ...)` | `ATestActor` + `UCharacterData` 제공. 주 모듈이 참조 |
| `Temporary` | 플러그인 모듈 | `IMPLEMENT_MODULE(FTemporaryModule, ...)` | `IModuleInterface` 구현(StartupModule/ShutdownModule) |

## 디렉터리 구조

```
ModuleAndPlugin/
├─ ModuleAndPlugin.uproject        # Modules: ModuleAndPlugin(Default) + Test(PreDefault), Plugins: Temporary
├─ Config/DefaultEngine.ini        # GlobalDefaultGameMode = ModuleAndPluginGameMode
├─ Source/
│  ├─ ModuleAndPlugin.Target.cs        # ExtraModuleNames: ModuleAndPlugin, Test
│  ├─ ModuleAndPluginEditor.Target.cs  # 〃 (Editor)
│  ├─ ModuleAndPlugin/             # 주 게임 모듈
│  │  ├─ ModuleAndPlugin.Build.cs  #   PublicDependency 에 "Test" 추가
│  │  ├─ ModuleAndPlugin.{h,cpp}   #   IMPLEMENT_PRIMARY_GAME_MODULE
│  │  └─ ModuleAndPluginGameMode.* #   BeginPlay 에서 ATestActor 스폰 (모듈 간 참조)
│  └─ Test/                        # 새 일반 모듈
│     ├─ Test.Build.cs             #   Core/CoreUObject/Engine + 모듈 루트 include 노출
│     ├─ Test.{h,cpp}              #   IMPLEMENT_MODULE(FDefaultModuleImpl, Test)
│     ├─ TestActor.{h,cpp}         #   AActor, BeginPlay 로그+화면 메시지
│     └─ CharacterData.{h,cpp}     #   UObject 파생 데이터 클래스 (도전 과제)
└─ Plugins/Temporary/              # 수동 구축 플러그인
   ├─ Temporary.uplugin            #   메타데이터 + Modules(JSON)
   └─ Source/Temporary/
      ├─ Temporary.Build.cs
      ├─ Public/Temporary.h        #   FTemporaryModule : IModuleInterface
      └─ Private/Temporary.cpp     #   StartupModule / ShutdownModule
```

## 모듈을 추가할 때 등록해야 하는 4곳 (핵심 함정)

새 모듈(`Test`)이 빌드·로드되려면 아래 4곳에 빠짐없이 등록해야 한다. 한 곳만 빠져도 `LNK2019`/모듈 못 찾음 에러가 난다.

1. `Source/Test/Test.Build.cs` — 모듈 자체 정의
2. `Source/ModuleAndPlugin.Target.cs` — `ExtraModuleNames`
3. `Source/ModuleAndPluginEditor.Target.cs` — `ExtraModuleNames`
4. `ModuleAndPlugin.uproject` — `Modules` 리스트 (`Test`는 `LoadingPhase: PreDefault`)

> **`PreDefault` 이유**: 주 모듈(`Default`)이 로드되기 전에 `Test`가 먼저 로드돼야, 주 모듈 GameMode가 `ATestActor`를 안전하게 참조·스폰할 수 있다.

## 플러그인 제작 과정 (Temporary)

1. `Plugins/Temporary/` 폴더 생성, 하위에 `Source/`, `Content/` 구성
2. `Temporary.uplugin` 작성 — `Modules` 배열에 런타임 모듈 1개 선언
3. `Source/Temporary/`에 `Build.cs` + `Public/Temporary.h`(`IModuleInterface`) + `Private/Temporary.cpp`
4. `Temporary.cpp`에서 `StartupModule`/`ShutdownModule` 구현 + `IMPLEMENT_MODULE(FTemporaryModule, Temporary)`
5. `.uproject`의 `Plugins`에 `{ "Name": "Temporary", "Enabled": true }` 등록
6. **Generate Visual Studio project files → 빌드** 후, 에디터 콘텐츠 브라우저에서
   보기 옵션 → "플러그인 콘텐츠 표시"로 플러그인 폴더 확인

> `IMPLEMENT_MODULE`의 2번째 인자(모듈명)는 `.uplugin`의 모듈명·`Build.cs` 클래스명과 **정확히 일치**해야 `StartupModule` 로그가 뜬다.

## 도전 과제 — UCharacterData (모듈 간 클래스 참조)

`Test` 모듈에 `UObject`를 상속한 데이터 클래스 `UCharacterData`를 만들고, 캐릭터 데이터처럼 사용한다.

- `Source/Test/CharacterData.{h,cpp}` — `UCharacterData : public UObject`, `UPROPERTY`로 `CharacterName`/`Health`/`MoveSpeed` 초기값 지정 (`TEST_API`로 내보내 다른 모듈에서 참조 가능)
- `ModuleAndPluginGameMode::BeginPlay` — `NewObject<UCharacterData>(this)`로 생성 후 속성값을 화면(`AddOnScreenDebugMessage`)과 로그로 출력

> 데이터 클래스를 `Test` 모듈에 두어, 주 게임 모듈이 이를 참조함으로써 `TestActor`에 이어 **모듈 간 참조를 한 번 더** 보여준다(이해도 도전 항목 충족). `NewObject`의 Outer를 GameMode로 지정해 GC가 수명을 관리하게 한다.

## 빌드 / 실행

1. `ModuleAndPlugin.uproject` 우클릭 → **Generate Visual Studio project files**
2. Development Editor 빌드
3. 에디터 실행 → 아무 레벨에서나 **Play**
4. 확인 포인트
   - 화면: `Test 모듈 정상 동작!` (초록색), `Name: Jangsik  HP: 100  Speed: 600` (하늘색, 도전 과제)
   - Output Log: `[Temporary Plugin] StartupModule ...`, `[Test Module] ATestActor::BeginPlay 호출됨`, `[ModuleAndPlugin] GameMode::BeginPlay -> TestActor 스폰 요청`, `[ModuleAndPlugin] CharacterData: Jangsik / HP 100 / Speed 600`

## 동작 흐름

```
엔진 시작 → Temporary 플러그인 모듈 로드(StartupModule 로그)
레벨 Play → ModuleAndPluginGameMode::BeginPlay
              ├─ World->SpawnActor<ATestActor>()      ← 주 모듈 → Test 모듈 참조
              │    └─ ATestActor::BeginPlay (로그 + 화면 메시지)
              └─ NewObject<UCharacterData>()          ← 주 모듈 → Test 모듈 데이터 클래스 참조 (도전)
                   └─ 속성값(이름/HP/속도) 화면·로그 출력
```
