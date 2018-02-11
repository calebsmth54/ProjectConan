
#include "AkAudioDevice.h"
#include "WaapiPicker/WwiseTreeItem.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "AkAudioStyle.h"
#include "Engine/Texture2D.h"

#define IMAGE_BRUSH( RelativePath, TextureName, ... ) FSlateImageBrush( LoadObject<UTexture2D>(nullptr, *(FString("/Wwise/") / FString(RelativePath) / FString(TextureName) + FString(".") + FString(TextureName))), __VA_ARGS__ )
#define ENGINE_IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(Style.RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#define ENGINE_BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style.RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define ENGINE_TTF_CORE_FONT( RelativePath, ... ) FSlateFontInfo( Style.RootToCoreContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )

TSharedPtr< FSlateStyleSet > FAkAudioStyle::StyleInstance = nullptr;

void FAkAudioStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FAkAudioStyle::Shutdown()
{
    if (StyleInstance.IsValid())
    {
        FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
        ensure(StyleInstance.IsUnique());
        StyleInstance.Reset();
    }
}

FName FAkAudioStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("AudiokineticToolsStyle"));
	return StyleSetName;
}

TSharedRef< FSlateStyleSet > FAkAudioStyle::Create()
{
	const FVector2D Icon15x15(15.0f, 15.0f);
	const FVector2D Icon12x12(12.0f, 12.0f);

	TSharedRef<FSlateStyleSet> StyleRef = MakeShareable(new FSlateStyleSet(FAkAudioStyle::GetStyleSetName()));

	StyleRef->SetContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));

	StyleRef->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));

	FSlateStyleSet& Style = StyleRef.Get();
	{
		Style.Set("AudiokineticTools.ActorMixerIcon", new IMAGE_BRUSH("WwiseTree/Icons", "actor_mixer_nor", Icon15x15));
		Style.Set("AudiokineticTools.SoundIcon", new IMAGE_BRUSH("WwiseTree/Icons", "sound_fx_nor", Icon15x15));
		Style.Set("AudiokineticTools.SwitchContainerIcon", new IMAGE_BRUSH("WwiseTree/Icons", "container_switch_nor", Icon15x15));
		Style.Set("AudiokineticTools.RandomSequenceContainerIcon", new IMAGE_BRUSH("WwiseTree/Icons", "container_random_sequence_nor", Icon15x15));
		Style.Set("AudiokineticTools.BlendContainerIcon", new IMAGE_BRUSH("WwiseTree/Icons", "layer_container_nor", Icon15x15));
		Style.Set("AudiokineticTools.MotionBusIcon", new IMAGE_BRUSH("WwiseTree/Icons", "motion_bus_nor", Icon15x15));
		Style.Set("AudiokineticTools.AkPickerTabIcon", new IMAGE_BRUSH("WwiseTree/Icons", "wwise_logo_32", Icon15x15));
		Style.Set("AudiokineticTools.EventIcon", new IMAGE_BRUSH("WwiseTree/Icons", "event_nor", Icon15x15));
		Style.Set("AudiokineticTools.AcousticTextureIcon", new IMAGE_BRUSH("WwiseTree/Icons", "acoutex_nor", Icon15x15));
		Style.Set("AudiokineticTools.AuxBusIcon", new IMAGE_BRUSH("WwiseTree/Icons", "auxbus_nor", Icon15x15));
		Style.Set("AudiokineticTools.BusIcon", new IMAGE_BRUSH("WwiseTree/Icons", "bus_nor", Icon15x15));
		Style.Set("AudiokineticTools.FolderIcon", new IMAGE_BRUSH("WwiseTree/Icons", "folder_nor", Icon15x15));
		Style.Set("AudiokineticTools.PhysicalFolderIcon", new IMAGE_BRUSH("WwiseTree/Icons", "physical_folder_nor", Icon15x15));
		Style.Set("AudiokineticTools.WorkUnitIcon", new IMAGE_BRUSH("WwiseTree/Icons", "workunit_nor", Icon15x15));
		Style.Set("AudiokineticTools.ProjectIcon", new IMAGE_BRUSH("WwiseTree/Icons", "wproj", Icon15x15));
		Style.Set("AudiokineticTools.RTPCIcon", new IMAGE_BRUSH("WwiseTree/Icons", "gameparameter_nor", Icon15x15));


		Style.Set("AudiokineticTools.GroupBorder", new ENGINE_BOX_BRUSH("Common/GroupBorder", FMargin(4.0f / 16.0f)));
		Style.Set("AudiokineticTools.AssetDragDropTooltipBackground", new ENGINE_BOX_BRUSH("Old/Menu_Background", FMargin(8.0f / 64.0f)));
		// Sources View
		Style.Set("AudiokineticTools.SourceTitleFont", ENGINE_TTF_CORE_FONT("Fonts/Roboto-Regular", 12));

		Style.Set("AudiokineticTools.SourceTreeItemFont", ENGINE_TTF_CORE_FONT("Fonts/Roboto-Regular", 10));
		Style.Set("AudiokineticTools.SourceTreeRootItemFont", ENGINE_TTF_CORE_FONT("Fonts/Roboto-Regular", 12));

		// Buttons that only provide a hover hint.
		FButtonStyle HoverHintOnly = FButtonStyle()
			.SetNormal(FSlateNoResource())
			.SetHovered(ENGINE_BOX_BRUSH("Common/Button_Hovered", FMargin(4 / 16.0f), FLinearColor(1, 1, 1, 0.15f)))
			.SetPressed(ENGINE_BOX_BRUSH("Common/Button_Pressed", FMargin(4 / 16.0f), FLinearColor(1, 1, 1, 0.25f)))
			.SetNormalPadding(FMargin(0, 0, 0, 1))
			.SetPressedPadding(FMargin(0, 1, 0, 0));
		Style.Set("AudiokineticTools.HoverHintOnly", HoverHintOnly);

		Style.Set("AudiokineticTools.Button_EllipsisIcon", new ENGINE_IMAGE_BRUSH("Icons/ellipsis_12x", Icon12x12));
	}

	return StyleRef;
}

#undef IMAGE_BRUSH

const ISlateStyle& FAkAudioStyle::Get()
{
	return *StyleInstance;
}

const FSlateBrush* FAkAudioStyle::GetBrush(EWwiseTreeItemType::Type ItemType)
{
	if (StyleInstance.IsValid())
	{
		switch (ItemType)
		{
		case EWwiseTreeItemType::Event:
			return StyleInstance->GetBrush("AudiokineticTools.EventIcon");
		case EWwiseTreeItemType::AcousticTexture:
			return StyleInstance->GetBrush("AudiokineticTools.AcousticTextureIcon");
		case EWwiseTreeItemType::AuxBus:
			return StyleInstance->GetBrush("AudiokineticTools.AuxBusIcon");
		case EWwiseTreeItemType::Bus:
			return StyleInstance->GetBrush("AudiokineticTools.BusIcon");
		case EWwiseTreeItemType::Folder:
			return StyleInstance->GetBrush("AudiokineticTools.FolderIcon");
		case EWwiseTreeItemType::Project:
			return StyleInstance->GetBrush("AudiokineticTools.ProjectIcon");
		case EWwiseTreeItemType::PhysicalFolder:
			return StyleInstance->GetBrush("AudiokineticTools.PhysicalFolderIcon");
		case EWwiseTreeItemType::StandaloneWorkUnit:
		case EWwiseTreeItemType::NestedWorkUnit:
			return StyleInstance->GetBrush("AudiokineticTools.WorkUnitIcon");
		case EWwiseTreeItemType::ActorMixer:
			return StyleInstance->GetBrush("AudiokineticTools.ActorMixerIcon");
		case EWwiseTreeItemType::Sound:
			return StyleInstance->GetBrush("AudiokineticTools.SoundIcon");
		case EWwiseTreeItemType::SwitchContainer:
			return StyleInstance->GetBrush("AudiokineticTools.SwitchContainerIcon");
		case EWwiseTreeItemType::RandomSequenceContainer:
			return StyleInstance->GetBrush("AudiokineticTools.RandomSequenceContainerIcon");
		case EWwiseTreeItemType::BlendContainer:
			return StyleInstance->GetBrush("AudiokineticTools.BlendContainerIcon");
		case EWwiseTreeItemType::MotionBus:
			return StyleInstance->GetBrush("AudiokineticTools.MotionBusIcon");
		default:
			return nullptr;
		}
	}
	return nullptr;
}

const FSlateBrush* FAkAudioStyle::GetBrush(FName PropertyName, const ANSICHAR* Specifier)
{
	if (StyleInstance.IsValid())
	{
		return StyleInstance->GetBrush(PropertyName, Specifier);
	}
	return nullptr;
}

const FSlateFontInfo FAkAudioStyle::GetFontStyle(FName PropertyName, const ANSICHAR* Specifier)
{
	if (StyleInstance.IsValid())
	{
		return StyleInstance->GetFontStyle(PropertyName, Specifier);
	}
	return FSlateFontInfo();
}