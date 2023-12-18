// Single key widget
#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "SingleKeyOfOnscreenKeyboard.generated.h"

class UButton;
class UBorder;
class UTexture2D;
class UImage;

UENUM(BlueprintType)
enum class EKeyType : uint8
{
	EKT_Char UMETA(DisplayName = "Char"),
	EKT_Shift UMETA(DisplayName = "Shift"),
	EKT_Backspace UMETA(DisplayName = "Backspace"),
	EKT_Close UMETA(DisplayName = "Close"),

	EKT_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class GAMEPADSANDBOX_API USingleKeyOfOnscreenKeyboard : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeOnInitialized() override;

public:
	FORCEINLINE EKeyType GetKeyFunction() { return KeyFunction; }
	FORCEINLINE FText GetUpperSymbol() { return KeyUpperSymbol; }
	FText GetSymbol();
	void PressedShift(bool pressed);
	void SetColor(FColor color);

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* KeyButton{};

	UPROPERTY(meta = (BindWidget))
	UImage* KeyImage{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* KeyTexture{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Keyboard")
	FText KeySymbol{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Keyboard")
	FText KeyUpperSymbol{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Keyboard")
	EKeyType KeyFunction{ EKeyType::EKT_Char };
	
	UPROPERTY(meta = (BindWidget))
	UBorder* BorderTop{};

	UPROPERTY(meta = (BindWidget))
	UBorder* BorderBottom{};

	UPROPERTY(meta = (BindWidget))
	UBorder* BorderLeft{};

	UPROPERTY(meta = (BindWidget))
	UBorder* BorderRight{};

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KeyText{};

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CharToShift{};

private:
	bool ShiftPressed{ false };
};
