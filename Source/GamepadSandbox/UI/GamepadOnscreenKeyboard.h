// Parent class for UserWidget blueprint

#pragma once

#include "CoreMinimal.h"
#include "GamepadControlWidget.h"
#include "GamepadOnscreenKeyboard.generated.h"

class UEditableText;
class USingleKeyOfOnscreenKeyboard;
class UGridPanel;
class UGridSlot;

UCLASS()
class GAMEPADSANDBOX_API UGamepadOnscreenKeyboard : public UGamepadControlWidget
{
	GENERATED_BODY()
	
public:
	
protected:
	void KeyboardSwitcher();
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UEditableText* OutputTextBox{};

	UPROPERTY(meta = (BindWidget))
	UGridPanel* KeysGrid{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Keyboard Properties")
	FColor InactiveColor{ 200, 200, 200, 255 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Keyboard Properties")
	FColor ActiveColor{ 255, 255, 255, 255 };

	UPROPERTY(EditAnywhere, Category = "Keyboard Properties")
	FKey MoveCursorRightButton{ EKeys::Gamepad_LeftStick_Right };

	UPROPERTY(EditAnywhere, Category = "Keyboard Properties")
	FKey MoveCursorLeftButton{ EKeys::Gamepad_LeftStick_Left };

	UPROPERTY(EditAnywhere, Category = "Keyboard Properties")
	FKey MoveCursorUpButton{ EKeys::Gamepad_LeftStick_Up };

	UPROPERTY(EditAnywhere, Category = "Keyboard Properties")
	FKey MoveCursorDownButton{ EKeys::Gamepad_LeftStick_Down };

	UPROPERTY(EditAnywhere, Category = "Keyboard Properties")
	FKey InputKeyButton{ EKeys::Gamepad_FaceButton_Top };


private:
	void GetKeys();
	void LeftKey();
	void RightKey();
	void UpKey();
	void DownKey();
	void Close();
	void Shift();
	void InputKey();

	TArray<UGridSlot*> KeyGridSlots;
	int32 CurrentKeyButtonIndex{ 0 };
	int32 GridWidth{ 0 };
	int32 GridHeight{ 0 };
	bool ShiftPressed{ false };


};
