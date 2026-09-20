#pragma once

#include "Resource/GameResources.h"
#include <globaldefs.h>

void InitializeBrightnessState(GameResources* resources);

void UpdateBrightnessTransitions(GameResources* resources);

void ApplyBrightness(GameResources* resources);

void UpdateAndApplyBrightness(GameResources* resources);

void SetMainBrightness(GameResources* resources, int brightness, int duration);

void SetSubBrightness(GameResources* resources, int brightness, int duration);

void SetBrightness(GameResources* resources, int brightness, int duration);

void SetAndLockMainBrightness(GameResources* resources, int brightness, int duration);

void SetAndLockSubBrightness(GameResources* resources, int brightness, int duration);

void SetAndLockBrightness(GameResources* resources, int brightness, int duration);

void UnlockAndSetMainBrightness(GameResources* resources, int brightness, int duration);

void UnlockAndSetSubBrightness(GameResources* resources, int brightness, int duration);

void UnlockAndSetBrightness(GameResources* resources, int brightness, int duration);

void SetMainBrightnessWithDurationMs(GameResources* resources, int brightness, unsigned int durationMs);

// might be returning bool instead of int
int IsMainBrightnessTransitionActive(GameResources* resources);
int IsSubBrightnessTransitionActive(GameResources* resources);
int IsBrightnessTransitionActive(GameResources* resources);

int GetMainBrightnessTransitionState(GameResources* resources);
int GetSubBrightnessTransitionState(GameResources* resources);

unsigned short GetBrightnessTransitionStates(GameResources* resources);

unsigned int GetFlags00(GameResources* resources);
void SetFlags00(GameResources* resources, unsigned int mask);
void ClearFlags00(GameResources* resources, unsigned int mask);
unsigned int TestFlags00(GameResources* resources, unsigned int mask);

unsigned int GetFlags04(GameResources* resources);
void SetFlags04(GameResources* resources, unsigned int mask);
void ClearFlags04(GameResources* resources, unsigned int mask);
unsigned int TestFlags04(GameResources* resources, unsigned int mask);

unsigned int GetFlags08(GameResources* resources);
void SetFlags08(GameResources* resources, unsigned int mask);
void ClearFlags08(GameResources* resources, unsigned int mask);
unsigned int TestFlags08(GameResources* resources, unsigned int mask);

void WriteBrightnessToHardware(GameResources* gameResources);
int GetBrightness(GameResources* gameResources, bool useSubScreen);
bool IsBrightnessWithinValidRange(GameResources* gameResources, bool useSubScreen);
bool IsBrightnessOutsideValidRange(GameResources* gameResources, bool useSubScreen);
bool IsBrightnessZero(GameResources* gameResources, bool useSubScreen);
