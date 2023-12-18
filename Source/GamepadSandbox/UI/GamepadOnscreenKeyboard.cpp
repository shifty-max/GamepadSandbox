#include "GamepadOnscreenKeyboard.h"
#include "SingleKeyOfOnscreenKeyboard.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/Button.h"
#include "Components/EditableText.h"

void UGamepadOnscreenKeyboard::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GetKeys();

	USingleKeyOfOnscreenKeyboard* firstKey = Cast<USingleKeyOfOnscreenKeyboard>(KeyGridSlots[0]->Content);
	if (IsValid(firstKey))
	{
		firstKey->SetColor(ActiveColor);
	}
}

void UGamepadOnscreenKeyboard::GetKeys()
{
	TArray<UPanelSlot*> allGridSlots = KeysGrid->GetSlots();
	for (UPanelSlot* slot : allGridSlots)
	{
		UGridSlot* keySlot = Cast<UGridSlot>(slot);
		if (IsValid(keySlot))
		{
			USingleKeyOfOnscreenKeyboard* key = Cast<USingleKeyOfOnscreenKeyboard>(keySlot->Content);
			if (IsValid(key))
			{
				key->SetColor(InactiveColor);
			}

			int32 keySpan = keySlot->ColumnSpan;
			while (keySpan > 1)
			{
				KeyGridSlots.Add(keySlot);
				--keySpan;
			}

			KeyGridSlots.Add(keySlot);

			const int32 gridColumn = keySlot->Column;
			if (gridColumn > GridWidth)
			{
				GridWidth = gridColumn;
			}
			const int32 gridRow = keySlot->Row;
			if (gridRow > GridHeight)
			{
				GridHeight = gridRow;
			}
		}
	}

	++GridWidth;
	++GridHeight;

	const int32 gridWidth = GridWidth;
	KeyGridSlots.Sort([gridWidth](const UGridSlot& slot1, const UGridSlot& slot2) { return (slot1.Row * gridWidth + slot1.Column) < (slot2.Row * gridWidth + slot2.Column); });
}


void UGamepadOnscreenKeyboard::LeftKey()
{
	USingleKeyOfOnscreenKeyboard* previousKey = Cast<USingleKeyOfOnscreenKeyboard>(KeyGridSlots[CurrentKeyButtonIndex]->Content);
	if (IsValid(previousKey))
	{
		if ((!ShiftPressed && previousKey->GetKeyFunction() == EKeyType::EKT_Shift) || (previousKey->GetKeyFunction() != EKeyType::EKT_Shift))
		{
			previousKey->SetColor(InactiveColor);
		}
	}

	while (previousKey == KeyGridSlots[CurrentKeyButtonIndex]->Content)
	{
		--CurrentKeyButtonIndex;

		if (CurrentKeyButtonIndex < 0)
		{
			CurrentKeyButtonIndex = KeyGridSlots.Num() - 1;
		}
	}

	USingleKeyOfOnscreenKeyboard* nextKey = Cast<USingleKeyOfOnscreenKeyboard>(KeyGridSlots[CurrentKeyButtonIndex]->Content);

	if (IsValid(nextKey))
	{
		nextKey->SetColor(ActiveColor);
	}
	PlayButtonSound();
}

void UGamepadOnscreenKeyboard::RightKey()
{
	USingleKeyOfOnscreenKeyboard* previousKey = Cast<USingleKeyOfOnscreenKeyboard>(KeyGridSlots[CurrentKeyButtonIndex]->Content);
	if (IsValid(previousKey))
	{
		if ((!ShiftPressed && previousKey->GetKeyFunction() == EKeyType::EKT_Shift) || (previousKey->GetKeyFunction() != EKeyType::EKT_Shift))
		{
			previousKey->SetColor(InactiveColor);
		}
	}

	while (previousKey == KeyGridSlots[CurrentKeyButtonIndex]->Content)
	{
		++CurrentKeyButtonIndex;

		if (CurrentKeyButtonIndex > KeyGridSlots.Num() - 1)
		{
			CurrentKeyButtonIndex = 0;
		}
	}

	USingleKeyOfOnscreenKeyboard* nextKey = Cast<USingleKeyOfOnscreenKeyboard>(KeyGridSlots[CurrentKeyButtonIndex]->Content);
	if (IsValid(nextKey))
	{
		nextKey->SetColor(ActiveColor);
	}
	PlayButtonSound();
}

void UGamepadOnscreenKeyboard::UpKey()
{
	USingleKeyOfOnscreenKeyboard* previousKey = Cast<USingleKeyOfOnscreenKeyboard>(KeyGridSlots[CurrentKeyButtonIndex]->Content);
	if (IsValid(previousKey))
	{
		if ((!ShiftPressed && previousKey->GetKeyFunction() == EKeyType::EKT_Shift) || (previousKey->GetKeyFunction() != EKeyType::EKT_Shift))
		{
			previousKey->SetColor(InactiveColor);
		}
	};

	if (CurrentKeyButtonIndex - GridWidth < 0)
	{
		CurrentKeyButtonIndex = CurrentKeyButtonIndex + GridWidth * (GridHeight - 1);
		if (CurrentKeyButtonIndex > (KeyGridSlots.Num() - 1))
		{
			CurrentKeyButtonIndex = 0;
		}
	}
	else
	{
		CurrentKeyButtonIndex = CurrentKeyButtonIndex - GridWidth;
	}

	USingleKeyOfOnscreenKeyboard* nextKey = Cast<USingleKeyOfOnscreenKeyboard>(KeyGridSlots[CurrentKeyButtonIndex]->Content);
	if (IsValid(nextKey))
	{
		nextKey->SetColor(ActiveColor);
	}
	PlayButtonSound();
}

void UGamepadOnscreenKeyboard::DownKey()
{
	USingleKeyOfOnscreenKeyboard* previousKey = Cast<USingleKeyOfOnscreenKeyboard>(KeyGridSlots[CurrentKeyButtonIndex]->Content);
	if (IsValid(previousKey))
	{
		if ((!ShiftPressed && previousKey->GetKeyFunction() == EKeyType::EKT_Shift) || (previousKey->GetKeyFunction() != EKeyType::EKT_Shift))
		{
			previousKey->SetColor(InactiveColor);
		}
	}

	if (CurrentKeyButtonIndex + GridWidth > (KeyGridSlots.Num() - 1))
	{
		CurrentKeyButtonIndex = CurrentKeyButtonIndex - GridWidth * (GridHeight - 1);
		if (CurrentKeyButtonIndex < 0)
		{
			CurrentKeyButtonIndex = KeyGridSlots.Num() - 1;
		}
	}
	else
	{
		CurrentKeyButtonIndex = CurrentKeyButtonIndex + GridWidth;
	}

	USingleKeyOfOnscreenKeyboard* nextKey = Cast<USingleKeyOfOnscreenKeyboard>(KeyGridSlots[CurrentKeyButtonIndex]->Content);
	if (IsValid(nextKey))
	{
		nextKey->SetColor(ActiveColor);
	}
	PlayButtonSound();
}

/*
bool UGamepadOnscreenKeyboard::BindTextBox(UEditableText* textBox)
{
	OutputTextBox = textBox;

	if (IsValid(OutputTextBox))
	{
		return true;;
	}
	return false;
}
*/

void UGamepadOnscreenKeyboard::InputKey()
{
	USingleKeyOfOnscreenKeyboard* currentKey = Cast<USingleKeyOfOnscreenKeyboard>(KeyGridSlots[CurrentKeyButtonIndex]->Content);
	FString newText{};

	switch (currentKey->GetKeyFunction())
	{
	case EKeyType::EKT_Close:
		Close();
		break;

	case EKeyType::EKT_Backspace:
		OutputTextBox->SetFocus();
		newText = OutputTextBox->GetText().ToString();
		newText.RemoveAt((newText.Len() - 1), 1, true);
		OutputTextBox->SetText(FText::FromString(newText));
		break;

	case EKeyType::EKT_Shift:
		Shift();
		break;

	case EKeyType::EKT_Char:
		OutputTextBox->SetFocus();
		newText = OutputTextBox->GetText().ToString() + currentKey->GetSymbol().ToString();
		OutputTextBox->SetText(FText::FromString(newText));
		break;
	}
	PlayButtonSound();
}

void UGamepadOnscreenKeyboard::KeyboardSwitcher()
{
	if (GetVisibility() == ESlateVisibility::Visible)
	{
		Close();
	}
	else
	{
		SetIsEnabled(true);
		SetVisibility(ESlateVisibility::Visible);
		AddBinding("MoveCursorRight", MoveCursorRightButton, this, &UGamepadOnscreenKeyboard::RightKey);
		AddBinding("MoveCursorLeft", MoveCursorLeftButton, this, &UGamepadOnscreenKeyboard::LeftKey);
		AddBinding("MoveCursorUp", MoveCursorUpButton, this, &UGamepadOnscreenKeyboard::UpKey);
		AddBinding("MoveCursorDown", MoveCursorDownButton, this, &UGamepadOnscreenKeyboard::DownKey);
		AddBinding("InputCharacter", InputKeyButton, this, &UGamepadOnscreenKeyboard::InputKey);
	}

}

void UGamepadOnscreenKeyboard::Shift()
{
	USingleKeyOfOnscreenKeyboard* currentKey = Cast<USingleKeyOfOnscreenKeyboard>(KeyGridSlots[CurrentKeyButtonIndex]->Content);
	ShiftPressed = !ShiftPressed;

	if (ShiftPressed)
	{
		currentKey->SetColor(ActiveColor);
	}

	for (UGridSlot* slot : KeyGridSlots)
	{
		USingleKeyOfOnscreenKeyboard* keyWidget = Cast<USingleKeyOfOnscreenKeyboard>(slot->Content);
		if (IsValid(keyWidget))
		{
			keyWidget->PressedShift(ShiftPressed);
		}
	}
}


void UGamepadOnscreenKeyboard::Close()
{
	SetIsEnabled(false);
	SetVisibility(ESlateVisibility::Hidden);
	RemoveBinding();
}


