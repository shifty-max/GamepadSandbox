#include "GamepadControlWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/InputSettings.h"
#include "Containers/Array.h"
#include "Sound/SoundCue.h"
//#include "Components/Image.h"
//#include "Blueprint/WidgetTree.h"
//#include "Framework/Application/SlateApplication.h"



void UGamepadControlWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OwnPlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (IsValid(OwnPlayerController))
	{
		InputComponent = OwnPlayerController->InputComponent;
		OwnPlayerController->SetInputMode(FInputModeGameAndUI());
	}
}

void UGamepadControlWidget::NativeDestruct()
{
	RemoveBinding();
	Super::NativeDestruct();
}

void UGamepadControlWidget::PlayButtonSound()
{
	if (IsValid(ButtonPressedSound))
	{
		UGameplayStatics::PlaySound2D(this, ButtonPressedSound);
	}
}

bool UGamepadControlWidget::IsGamepadAttached()
{
	TSharedPtr <GenericApplication> genericApplication = FSlateApplication::Get().GetPlatformApplication();

	if (genericApplication.IsValid() && genericApplication->IsGamepadAttached())
	{
		return true;
	}

	return false;
}

void UGamepadControlWidget::RemoveBinding()
{
	if (IsValid(OwnPlayerController) && IsValid(InputComponent))
	{
		for (FInputActionKeyMapping actionMapping : MenuMapping)
		{
			InputComponent->RemoveActionBinding(actionMapping.ActionName, IE_Pressed);
			OwnPlayerController->PlayerInput->RemoveActionMapping(actionMapping);
		}

	}
}
