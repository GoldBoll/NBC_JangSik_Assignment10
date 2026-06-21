using UnrealBuildTool;
using System.Collections.Generic;

public class ModuleAndPluginEditorTarget : TargetRules
{
	public ModuleAndPluginEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;

		// 에디터 타깃도 동일하게 두 모듈을 빌드 대상에 등록
		ExtraModuleNames.AddRange(new[] { "ModuleAndPlugin", "Test" });
	}
}
