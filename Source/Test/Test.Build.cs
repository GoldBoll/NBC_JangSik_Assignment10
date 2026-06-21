using UnrealBuildTool;

public class Test : ModuleRules
{
	public Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// 모듈 루트를 public include 경로로 노출 → 의존 모듈(주 모듈)이 "TestActor.h"로 직접 포함 가능
		PublicIncludePaths.Add(ModuleDirectory);

		// 액터(UObject 파생)를 담으므로 CoreUObject·Engine 필요
		PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine" });
	}
}
