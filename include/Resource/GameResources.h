#pragma once

#include "Memory/SafeAllocator.h"

// sizeof == 0x44c8, or 0x4218 in JPN version.
//
// Referenced in a huge number of places and appears to contain many kinds
// of global game/resource state:
// - memory allocators
// - persistent/runtime state
// - scene/battle state
// - display/brightness state
// - various object/state tables
//
// An instance is allocated in func_ov030_021d8a40 (USA), which is where
// much of the current type information comes from.
//
// Runtime tracing confirms that the same object is:
// - returned by func_ov017_0218b5b0()
// - passed to the brightness-management functions
// - stored at BattleStruct + 0x0
struct GameResources
{
    // +0x00
    //
    // First 32-bit flag bank.
    //
    // Dedicated helpers exist to:
    // - return the whole word
    // - OR/set bits
    // - clear bits
    // - test masked bits
    //
    // Used by many unrelated callers, so this should not be considered
    // brightness-specific.
    unsigned int flags_00;

    // +0x04
    //
    // Second 32-bit flag bank, with the same getter/set/clear/test helpers.
    // This is the most heavily-used of the first three flag banks currently
    // observed.
    unsigned int flags_04;

    // Constants for known masks within flags_08.
    //
    // These are masks only and occupy no space in a GameResources instance.
    struct Flags08
    {
        // +0x08 mask 0x02
        //
        // Affects candidate filtering in func_ov017_0218e8c8.
        //
        // The function compares:
        //
        //     candidate->field_06
        //
        // against the field_06 value of the currently selected BattleStruct
        // entry.
        //
        // Normally the values must match unless the candidate has
        // flags_6c & 0x00800000.
        //
        // When this flag is SET, that field_06 comparison is relaxed outside
        // battle. During battle, BATTLE_ACTIVE still forces the field_06
        // comparison.
        //
        // Exact higher-level semantic meaning is still unknown.
        static const unsigned int UNK_02 = 0x02;

        // +0x08 mask 0x04
        //
        // Strong runtime evidence identifies this as a battle-active flag.
        //
        // Observed repeatedly:
        //
        //   battle start:
        //       flags_08 |= 0x04;
        //
        //   battle end:
        //       flags_08 &= ~0x04;
        //
        // Confirmed across tutorial and normal field battles.
        //
        // It is also tested by func_ov017_0218e8c8 and causes candidate
        // field_06 to be required to match the currently selected
        // BattleStruct entry.
        static const unsigned int BATTLE_ACTIVE = 0x04;

        // +0x08 mask 0x08
        //
        // Persistent/pending-like state used by func_ov017_0219ca88.
        //
        // It can remain set across updates and its clearing is gated by
        // several conditions, including completion of a main-screen
        // brightness transition.
        //
        // Exact higher-level purpose is still unknown.
        static const unsigned int UNK_08 = 0x08;
    };

    // +0x08
    //
    // Third 32-bit flag bank.
    //
    // Known masks are defined in Flags08 above.
    //
    // This remains one 32-bit word; the individual flags are boolean
    // conditions packed into individual bits.
    unsigned int flags_08;

    // +0x0c
    //
    // Current main-screen master brightness, stored as float internally.
    // Converted to integer when written to REG_MASTER_BRIGHT.
    float mainBrightness;

    // +0x10
    //
    // Requested/final main-screen brightness value.
    int mainBrightnessTarget;

    // +0x14
    //
    // Remaining main-screen brightness transition time/count.
    // > 0 means a main brightness transition is active.
    int mainBrightnessTimeRemaining;

    // +0x18
    //
    // Current sub-screen master brightness.
    // Converted to integer when written to REG_MASTER_BRIGHT_SUB.
    float subBrightness;

    // +0x1c
    //
    // Requested/final sub-screen brightness value.
    int subBrightnessTarget;

    // +0x20
    //
    // Remaining sub-screen brightness transition time/count.
    // > 0 means a sub brightness transition is active.
    int subBrightnessTimeRemaining;

    // +0x24
    //
    // Checked by the main-brightness setter before allowing an update.
    // "Locked" is a reasonable working interpretation, but the exact
    // higher-level meaning is not yet proven.
    bool mainBrightnessLocked;

    // +0x25
    //
    // Same role as +0x24 for the sub screen.
    bool subBrightnessLocked;

    // +0x26
    //
    // Set when the current mainBrightness value needs to be applied
    // to the hardware register.
    bool mainBrightnessDirty;

    // +0x27
    //
    // Same role as +0x26 for the sub screen.
    bool subBrightnessDirty;

    // +0x28
    //
    // Acts as a higher-level gate around applying brightness changes.
    // Exact semantics are not yet fully understood.
    bool allowBrightnessApply;

    char unknown_29[0x38 - 0x29];

    // +0x38
    SafeAllocator allocator_array_38[17];

    // +0x18c
    SafeAllocator lootableContainerAllocator_18c_;

#if defined(usa)
    SafeAllocator allocator_array_1a0[15];
    char unknown_2cc[0xe70];
#elif defined(jpn)
    SafeAllocator allocator_array_1a0[11];
    char unknown_2cc[0xcb0];
#endif

    SafeAllocator allocator_113c; // JPN: +0xf2c
    char unknown_1150[0x70];

    SafeAllocator allocator_11c0; // JPN: +0xfb0
    char unknown_11d4[0x70];

    SafeAllocator allocator_1244; // JPN: +0x1034
    char unknown_1258[0x70];

    // USA: +0x12c8
    // JPN: +0x10b8
    struct Substruct_12C8
    {
        char unknown_0[4];

        SafeAllocator allocator_array_4[10];

        char unknown_cc[0x460];

        SafeAllocator allocator_52c;
        SafeAllocator allocator_540;
        SafeAllocator allocator_554;

        char unknown_568[0x70];

        SafeAllocator allocator_5d8;

    } substruct_array_12c8[4];

    // USA: +0x2a78
    // JPN: +0x2868
    char unknown_2a78[0x94];

    // USA: +0x2b0c
    // JPN: +0x28fc
    SafeAllocator allocator_2b0c;

    // USA: +0x2b20
    // JPN: +0x2910
    char unknown_2b20[0x70];

    // USA: +0x2b90
    // JPN: +0x2980
    struct Substruct_2b90
    {
        char unknown[0x88];

    } substruct_array_2b90[0x12];

    // USA: +0x3520
    // JPN: +0x3310
    char unknown_3520[0x88];

    // USA: +0x35a8
    // JPN: +0x3398
    char unknown_35a8[0x120];

    void *unknown_ptr_36c8; // JPN: +0x34b8
    void *unknown_ptr_36cc; // JPN: +0x34bc
    void *unknown_ptr_36d0; // JPN: +0x34c0

    char unknown_36d4[4];   // JPN: +0x34c4

    void *unknown_ptr_36d8; // JPN: +0x34c8

    // +0x36dc USA / +0x34cc JPN
    //
    // Indexed byte-state range.
    //
    // func_ov017_0219219c(resources, index) returns a pointer into this
    // array when index is 0..3:
    //
    //     &resources->unknown_state_36dc[index]
    //
    // func_ov017_02191b58 subsequently reads the selected byte.
    //
    // Exact semantic meaning of these four values is still unknown.
    unsigned char unknown_state_36dc[4];

    // +0x36e0 USA / +0x34d0 JPN
    //
    // Not part of either indexed range currently understood.
    char unknown_36e0;

    // +0x36e1 USA / +0x34d1 JPN
    //
    // Second indexed byte-state range.
    //
    // func_ov017_0219219c maps indices 0xC0..0xC7 to:
    //
    //     &resources->unknown_state_36e1[index - 0xC0]
    //
    // Exact semantic meaning is still unknown.
    unsigned char unknown_state_36e1[8];

    // +0x36e9 .. +0x36fb
    char unknown_36e9[0x13];

    // +0x36fc
    // JPN: +0x34ec
    void *unknown_ptr_array_36fc[7];

    void *unknown_ptr_3718;
    void *unknown_ptr_array_371c[8];

    // USA: +0x373c
    // JPN: +0x352c
    struct Substruct_373c
    {
        char unknown[0x48];

    } substruct_array_373c[0xc];

    // USA: +0x3a9c
    // JPN: +0x388c
    struct Substruct_3a9c
    {
#if defined(usa)
        char unknown[0x18];
#elif defined(jpn)
        char unknown[0x14];
#endif

    } substruct_array_3a9c[4];

    // USA: +0x3afc
    // JPN: +0x38dc
    void *unknown_ptr_array_3afc[0x33];

    // USA: +0x3bc8
    // JPN: +0x39a8
    struct Substruct_3bc8
    {
        char unknown[0x14];

    } substruct_array_3bc8[3];

    // USA: +0x3c04
    // JPN: +0x39e4
    struct Substruct_3c04
    {
        char unknown[0x28];

    } substruct_array_3c04[4];

    // USA: +0x3ca4
    // JPN: +0x3a84
    void *unknown_ptr_array_3ca4[4];

    char unknown_3cb4[0x3d4];

    // USA: +0x4088
    // JPN: +0x3e68
    void *unknown_ptr_array_4088[3];

    char unknown_4094[0x130];

    // USA: +0x41c4
    // JPN: +0x3fa4
    void *unknown_ptr_41c4;

    // Previously part of unknown_41c8[0x160].
    //
    // USA: +0x41c8 .. +0x431f
    char unknown_41c8[0x158];

    // +0x4320 (USA)
    //
    // 32-bit boolean-like state field.
    //
    // It must remain a 4-byte type rather than C++ bool because the game
    // accesses it with 32-bit LDR/STR instructions.
    //
    // Initialized to 1 during GameResources initialization.
    //
    // func_ov017_02195530:
    //     field_4320 = 1;
    //
    // func_ov017_02195540:
    //     field_4320 = 0;
    //
    // func_ov000_021688dc sets this field to 1 shortly before clearing
    // flags_08::BATTLE_ACTIVE.
    //
    // This strongly suggests that the two states participate in the same
    // transition/lifecycle, but the exact semantic relationship remains
    // unknown.
    unsigned int field_4320;

    // +0x4324
    char unknown_4324[4];

    // +0x4328
    // JPN: +0x4108
    void *unknown_ptr_4328;

#if defined(usa)
    char unknown_432c[0xf0];
#elif defined(jpn)
    // JPN: +0x410c
    char unknown_432c[0x60];
#endif

    // USA: +0x441c
    // JPN: +0x416c
    void *unknown_ptr_441c;

    char unknown_4420[0x6c];

    // USA: +0x448c
    // JPN: +0x41dc
    struct TreasureMapLanguageDataOffsets *pTMapLanguageOffsets;

    char unknown_4490[0x34];

    // USA: +0x44c4
    void *unknown_ptr_44c4;
};


// sizeof == 0x44
//
// Needs to eventually be moved back to the grotto-related code.
struct TreasureMapLanguageDataOffsets
{
    unsigned int bossRangesByQuality;
    unsigned int bossIDsAndWeights;
    unsigned int environs;
    unsigned int prefixRangesByMonsterRank;
    unsigned int prefixNames;
    unsigned int floorRangesByQuality;
    unsigned int unknown_18;
    unsigned int startingMonsterRanksByQuality;
    unsigned int mapLocations;
    unsigned int seeminglyChestRanksByMonsterRank;
    unsigned int localeRankRangesByFloorCount;
    unsigned int localeNames;
    unsigned int suffixRangesByBoss;
    unsigned int suffixNames;
    unsigned int grottoBossDrops;  // flat, size 0x0C per boss
    unsigned int legacyBossDrops;  // flat, size 0x5C per boss
    unsigned int legacyBossData;
};


// --------------------------------------------------------------------------
// GameResources global-instance accessors
// --------------------------------------------------------------------------
//
// These functions remain undecompiled Overlay 17 functions.
//
// func_ov017_0218b5a0 stores the supplied GameResources pointer into a
// globally-held slot.
//
// func_ov017_0218b5b0 returns the pointer stored in that same slot.
//
// Runtime tracing confirms that the returned object is the same instance
// passed to the brightness-management functions and stored at
// BattleStruct + 0x0.
//
// Working semantic names:
//     func_ov017_0218b5a0 -> SetGameResources
//     func_ov017_0218b5b0 -> GetGameResources
//
// Keep the original function symbols for now because Overlay 17 has not
// been renamed/decompiled.

#ifdef jpn
    #define func_ov017_0218b5b0 func_ov017_0218c1d0
#endif

// USA: func_ov017_0218b5a0
extern "C" void func_ov017_0218b5a0(GameResources *gameResources);

// USA: func_ov017_0218b5b0
extern "C" GameResources *func_ov017_0218b5b0();