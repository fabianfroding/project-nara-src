// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Core/NaraGameplayTags.h"

#include "GameplayTagsManager.h"

FNaraGameplayTags FNaraGameplayTags::GameplayTags;

void FNaraGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Health"));
	GameplayTags.Attributes_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.MaxHealth"));

	GameplayTags.Attributes_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Mana"), 
		FString("Mana is used as an ambigious term for whatever resource the entity needs to consume to use abilities."));

	GameplayTags.Attributes_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.MaxMana"));
	GameplayTags.Attributes_MoveSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.MoveSpeed"));

	GameplayTags.Cooldown_FireBlast = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FireBlast"));
	GameplayTags.Cooldown_Player_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Player.Attack"));

	GameplayTags.CombatEvent_EnemyDeath = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatEvent.EnemyDeath"));

	GameplayTags.GameplayCue_FireBlast = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.FireBlast"));
	GameplayTags.GameplayCue_MeleeImpact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.MeleeImpact"));
	
	GameplayTags.GameplayEvent_PlayerAttackEnd = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayEvent.PlayerAttackEnd"));

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"));

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"));
	GameplayTags.Damage_Default = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Default"));
	GameplayTags.Damage_Projectile = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Projectile"));

	GameplayTags.Debuff = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff"));
	GameplayTags.Debuff_Slow = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Slow"));
	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Stun"));

	GameplayTags.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Chance"));
	GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Damage"));
	GameplayTags.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Duration"));
	GameplayTags.Debuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Frequency"));

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"));

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"));
	GameplayTags.Abilities_Dash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Dash"));
	GameplayTags.Abilities_Heal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Heal"));
	GameplayTags.Abilities_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Jump"));
	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Summon"));

	GameplayTags.Abilities_ArcaneShards = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.ArcaneShards"));
	GameplayTags.Abilities_FireBlast = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FireBlast"));

	GameplayTags.Abilities_Passive_LifeSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.LifeSiphon"));
	GameplayTags.Abilities_Passive_ManaSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.ManaSiphon"));
	GameplayTags.Abilities_Passive_HaloOfProtection = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.HaloOfProtection"));

	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.None"));
	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Passive"));

	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Weapon"));
	GameplayTags.CombatSocket_HandLeft = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.HandLeft"));
	GameplayTags.CombatSocket_HandRight = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.HandRight"));
	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Tail"));

	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.1"));
	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.2"));
	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.3"));
	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.4"));

	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputHeld"));
	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputPressed"));
	GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputReleased"));
}
