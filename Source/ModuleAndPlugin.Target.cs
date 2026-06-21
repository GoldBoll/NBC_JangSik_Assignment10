using UnrealBuildTool;
using System.Collections.Generic;

public class ModuleAndPluginTarget : TargetRules
{
	public ModuleAndPluginTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;

		// 게임 타깃이 빌드할 모듈: 주 모듈 + 새로 추가한 Test 모듈
		ExtraModuleNames.AddRange(new[] { "ModuleAndPlugin", "Test" });
	}
}
