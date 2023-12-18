
#include "SingleKeyOfOnscreenKeyboard.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/Image.h"

void USingleKeyOfOnscreenKeyboard::NativePreConstruct()
{
	Super::NativePreConstruct();

	bIsFocusable = true;

	if (IsValid(KeyTexture))
	{
		KeyImage->SetBrushFromTexture(KeyTexture, false);
		KeyImage->SetVisibility(ESlateVisibility::Visible);
		KeyText->SetText(FText());
		CharToShift->SetText(FText());
	}
	else
	{
		KeyImage->SetVisibility(ESlateVisibility::Hidden);
		KeyText->SetText(KeySymbol);
		CharToShift->SetText(KeyUpperSymbol);
	}
}

void USingleKeyOfOnscreenKeyboard::NativeOnInitialized()
{
	KeyButton->WidgetStyle.Disabled = KeyButton->WidgetStyle.Normal;

	Super::NativeOnInitialized();
}

void USingleKeyOfOnscreenKeyboard::PressedShift(bool pressed)
{
	ShiftPressed = pressed;
	if (KeyFunction == EKeyType::EKT_Char && !(IsValid(KeyTexture)))
	{
		if (!ShiftPressed)
		{
			KeyText->SetText(KeySymbol);
			CharToShift->SetText(KeyUpperSymbol);
		}
		else
		{
			KeyText->SetText(KeyUpperSymbol);
			CharToShift->SetText(KeySymbol);
		}
	}

}

FText USingleKeyOfOnscreenKeyboard::GetSymbol()
{
	if (ShiftPressed)
	{
		return KeyUpperSymbol;
	}
	else
	{
		return KeySymbol;
	}
}


void USingleKeyOfOnscreenKeyboard::SetColor(FColor color)
{
	KeyButton->SetBackgroundColor(color);
}
