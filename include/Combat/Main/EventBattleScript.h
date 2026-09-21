#pragma once

#include "Resource/Script.h"

// sizeof == 0x14
struct EventBattleConfig {
    unsigned short eventBattleId; // +0x00
    unsigned short field_02[3];   // +0x02
    unsigned short field_08[3];   // +0x08
    unsigned short field_0E;      // +0x0E
    unsigned short field_10;      // +0x10
    unsigned short field_12;      // +0x12
};

// usa: func_02074060
int HandleBattleDefinitionOpcode(Script::Parameter *parameter);

// usa: func_02074114
int LoadEventBattleConfig(EventBattleConfig *config, int eventBattleId);

// usa: func_0207416c
int ExecuteEventBattleScript(void *context, int eventBattleId, void *scriptData, unsigned int scriptSize);