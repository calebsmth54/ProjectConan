// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "WaapiPicker/WwiseTreeItem.h"

/**
* Implements the visual style of LogVisualizer.
*/
class AKAUDIO_API FAkAudioStyle
{
public:
	static void Initialize();

	static void Shutdown();

	/** @return The Slate style set for Fortnite Editor */
	static const ISlateStyle& Get();

	static FName GetStyleSetName();

	static const FSlateBrush* GetBrush(EWwiseTreeItemType::Type ItemType);
	static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL);
	static const FSlateFontInfo GetFontStyle(FName PropertyName, const ANSICHAR* Specifier = NULL);

private:

	static TSharedRef< class FSlateStyleSet > Create();

private:

	static TSharedPtr< class FSlateStyleSet > StyleInstance;
};

