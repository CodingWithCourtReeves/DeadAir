#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

// --- New Code Start ---
class UItemDefinition;
// --- New Code End ---

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Tool UMETA(DisplayName = "Tool"),
	Consumable UMETA(DisplayName = "Consumable")
};

// Contains textual data about the item.
USTRUCT(BlueprintType)
struct FItemText
{
	GENERATED_BODY()

	// The text name of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	// The text description of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;
};