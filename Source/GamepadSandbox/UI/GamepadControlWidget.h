// Basic class for widgets made for using with gamed

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/InputSettings.h"
#include "GamepadControlWidget.generated.h"

class USoundCue;

UCLASS()
class UGamepadControlWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	bool IsGamepadAttached();

protected:
	TArray<FInputActionKeyMapping> MenuMapping{};
	APlayerController* OwnPlayerController{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundCue* ButtonPressedSound{};

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;
	void PlayButtonSound();
	void RemoveBinding();

	template< class UserClass, typename functionType>
	void AddBinding(const FName inActionName, const FKey inKey, UserClass* Object, functionType(UserClass::* func)())
	{
		if (IsValid(OwnPlayerController) && IsValid(InputComponent))
		{
			FInputActionKeyMapping newMapping = FInputActionKeyMapping(inActionName, inKey);
			MenuMapping.Add(newMapping);

			OwnPlayerController->PlayerInput->AddActionMapping(newMapping);
			InputComponent->BindAction(inActionName, IE_Pressed, Object, func);

			newMapping = FInputActionKeyMapping("PlaySound", inKey);
			MenuMapping.Add(newMapping);
			OwnPlayerController->PlayerInput->AddActionMapping(newMapping);
			InputComponent->BindAction(inActionName, IE_Pressed, this, &UGamepadControlWidget::PlayButtonSound);
		}
	}
};