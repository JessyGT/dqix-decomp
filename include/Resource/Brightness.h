#pragma once

#include "Resource/GameResources.h"
#include <globaldefs.h>

void InitializeBrightnessState(GameResources *resources);

void UpdateBrightnessTransitions(GameResources *resources);

void ApplyBrightness(GameResources *resources);

void UpdateAndApplyBrightness(GameResources *resources);

void SetMainBrightness(GameResources *resources, int brightness, int duration);

void SetSubBrightness(GameResources *resources, int brightness, int duration);

void SetBrightness(GameResources *resources, int brightness, int duration);

void SetAndLockMainBrightness(GameResources *resources, int brightness, int duration);

void SetAndLockSubBrightness(GameResources *resources, int brightness, int duration);

void SetAndLockBrightness(GameResources *resources, int brightness, int duration);

void UnlockAndSetMainBrightness(GameResources *resources, int brightness, int duration);

void UnlockAndSetSubBrightness(GameResources *resources, int brightness, int duration);

void UnlockAndSetBrightness(GameResources *resources, int brightness, int duration);

void SetMainBrightnessWithDurationMs(GameResources *resources, int brightness, unsigned int durationMs);

// might be returning bool instead of int
int IsMainBrightnessTransitionActive(GameResources *resources);
int IsSubBrightnessTransitionActive(GameResources *resources);
int IsBrightnessTransitionActive(GameResources *resources);

int GetMainBrightnessTransitionState(GameResources *resources);
int GetSubBrightnessTransitionState(GameResources *resources);

unsigned short GetBrightnessTransitionStates(GameResources *resources);

unsigned int GetFlags00(GameResources *resources);
void SetFlags00(GameResources *resources, unsigned int mask);
void ClearFlags00(GameResources *resources, unsigned int mask);

// ## Known masks:
// ### 0x00000002
//   Normal field baseline state. Present during regular free-roam and
//   restored after scene transitions and battles. Exact meaning unknown.
//
// ### 0x00000004
//   Battle-related runtime state. Set during battle initialization,
//   toggled during setup, and cleared during battle teardown.
//
// ### 0x00000010
//   Temporary state-machine flag. Used during zone/scene transitions,
//   but also during battle command/state transitions. Not battle-specific.
//
// ### 0x00000020
//   Battle-related state. Set during battle setup and cleared during
//   battle teardown. Exact meaning unknown.
//
// ### 0x00000800
//   Combat-entry/handoff state. Set very early when entering combat and
//   cleared before the battle is fully established.
//
// ### 0xFFFFFFFF
//   Used to clear/reset all flags_00 bits.
unsigned int TestFlags00(GameResources *resources, unsigned int mask);

unsigned int GetFlags04(GameResources *resources);
void SetFlags04(GameResources *resources, unsigned int mask);
void ClearFlags04(GameResources *resources, unsigned int mask);

// ## Known masks:
// ### 0x00000001
//   Scene/zone transition state. Set when a transition begins and
//   cleared when normal field control resumes.
//
// ### 0x00000002
//   Battle/runtime state. Set during battle setup, remains active during
//   combat, and is cleared during battle teardown.
//
// ### 0x00000004
//   Battle initialization / world-processing suppression flag.
//   Set during battle setup and cleared once initialization has advanced.
//   Readers skip some normal Object3D/world processing while it is set.
//
// ### 0x00000008
//   Unknown. Seen as part of larger initialization masks.
//
// ### 0x00000010
//   Battle/modal runtime state. Set during battle setup and cleared during
//   battle teardown. Exact subsystem unknown.
//
// ### 0x00000020
//   Unknown. Seen as part of larger initialization masks.
//
// ### 0x00000040
//   Suppresses func_ov017_0219ad84 entirely.
//   That function performs field Object3D positioning/rendering work.
//   Set during both the field menu and battle.
//
// ### 0x00000080
//   Suppresses part of normal field/render/update processing.
//   Observed during menu, battle, and chest interactions.
//
// ### 0x000000C0
//   Combination of 0x40 | 0x80.
//   Used as a menu-active/modal-state mask. Repeatedly set while the
//   field menu is active and cleared when the menu closes.
//
// ### 0x00000100
//   Unknown. Seen as part of larger initialization masks.
//
// ### 0x00000400
//   Unknown. Repeatedly cleared around battle action boundaries,
//   but was not observed being set in the tested battle.
//
// ### 0x00000800
//   Field/map-context property.
//   Its state is the inverse of bit 7 of the current map record's
//   flags_0E field. Present in some field maps, cleared in battle context,
//   and restored when returning to the field.
//
// ### 0x00020000
//   Unknown. Seen as part of larger initialization masks.
//
// ### 0x00040000
//   Unknown. Seen as part of larger initialization masks.
//
// ### 0x00200000
//   Unknown. Cleared during battle exit in the tested flow.
//
// ### 0x000609FE
//   Bulk initialization/runtime mask containing multiple flags_04 bits.
//
// ### 0xFFFFFFFF
//   Used to clear/reset all flags_04 bits.
unsigned int TestFlags04(GameResources *resources, unsigned int mask);

unsigned int GetFlags08(GameResources *resources);
void SetFlags08(GameResources *resources, unsigned int mask);
void ClearFlags08(GameResources *resources, unsigned int mask);

// ## Known masks:
// ### 0x00000002
//   Alters object/candidate matching rules outside battle.
//   When set, some field_06 matching requirements are relaxed.
//   Exact semantic meaning unknown.
//
// ### 0x00000004
//   BATTLE_ACTIVE.
//   Set when battle becomes active and cleared when combat ends.
//   Observed consistently across multiple battle flows.
//
// ### 0x00000008
//   State-machine/pending-related flag.
//   Its clearing is partly associated with brightness-transition state,
//   but its exact meaning is still unknown.
//
// ### 0xFFFFFFFF
//   Used to clear/reset all flags_08 bits.
unsigned int TestFlags08(GameResources *resources, unsigned int mask);

void WriteBrightnessToHardware(GameResources *gameResources);
int GetBrightness(GameResources *gameResources, bool useSubScreen);
bool IsBrightnessWithinValidRange(GameResources *gameResources, bool useSubScreen);
bool IsBrightnessOutsideValidRange(GameResources *gameResources, bool useSubScreen);
bool IsBrightnessZero(GameResources *gameResources, bool useSubScreen);
