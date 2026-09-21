#include "Combat/Main/EventBattleScript.h"
#include "Combat/Overlay_17/EntryProcessing.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "Resource/Brightness.h"
#include "Resource/EntryContext.h"
#include "Resource/GameResources.h"
#include <globaldefs.h>

extern "C" {

void func_020397cc(void *param_1, int param_2);
void *func_02012fe4();
void func_02017c58();

void *func_020704fc();

void func_0209c678(void *param_1, int param_2);
void func_0209c480(void *param_1, int param_2);
void func_0209c2e0(void *param_1, int param_2, int param_3);
void func_0205e944(void *param_1, int param_2);

void *func_ov017_021b8478(void *param_1);

void *func_020421a0();
void func_02043124();
void *func_0203cf4c();
void func_0203e5d8(void *param_1, int param_2);

float func_020709ac(void *param_1);

void *func_020d6c00();
void func_020466e4(void *param_1, int param_2);

void func_ov017_0218d274(GameResources *param_1);
void func_ov017_0218f79c(GameResources *param_1);
void func_ov017_021a2840(GameResources *param_1);

extern unsigned char data_02109bf4[];
extern unsigned char data_02108760[];
extern char data_ov017_021d7c10[];

// ARM runtime helper.
// Kept as-is according to project convention: ARM/runtime-specific
// implementation is not decompiled here.
int _ffix(float value);
}

// usa: func_ov017_021b6290
//
// Handler for EntryNode type 0x16.
//
// EntryContext is part of the common dispatcher handler signature,
// but this particular handler does not use it.
void HandleEventBattleEntry(EntryNode *entry, EntryContext *context) {
    EntryNode16 *entry16 = (EntryNode16 *) entry;

    GameState *gameState         = GameState::GetInstance();
    GameResources *gameResources = GetGameResources();

    func_02012fe4();

    void *unknownGameObject = gameState->GetUnknownGameObject();
    void *unk_704fc         = func_020704fc();

    BackgroundLoader *backgroundLoader = BackgroundLoader::GetInstance();

    void *unk_3718 = gameResources->unknown_ptr_3718;

    if (entry16->state == 0) {
        func_020397cc(unknownGameObject, 1);

        *(unsigned short *) ((unsigned char *) unknownGameObject + 0xB2) = 0;

        if (entry16->parameter >= 0) {
            int taskId = backgroundLoader->QueueLoadFile(data_ov017_021d7c10, 0);

            entry16->loaderTaskId = taskId;

            func_0209c678(data_02109bf4, 10);
        }

        if (entry16->parameter <= 0) entry16->delay = 0;

        if (entry16->field_08 != 0) {
            func_02012fe4();
            func_02017c58();
        }

        entry16->state = 1;
    }

    if (entry16->delay != 0) entry16->delay--;

    if (entry16->state == 1) {
        if (FinishEntryObjectLoad(&entry16->data) != 0) entry16->state = 2;

        return;
    }

    if (entry16->state == 2) {
        if (entry16->delay != 0) return;

        short taskId = entry16->loaderTaskId;

        int unk = 0x17;

        if (taskId > -1) {
            if (backgroundLoader->GetTaskStatus(taskId) == 0) return;

            void *local_3c;
            unsigned int local_40;
            EventBattleConfig battleConfig;

            backgroundLoader->GetLoadedFileByID(entry16->loaderTaskId, &local_3c, &local_40);

            EventBattleConfig *dataPtr = &battleConfig;

            if (HasEntryType(gameResources->entryContext_36FC, 10) != 0) {
                void *result = func_ov017_021b8478(unk_3718);

                if (result != 0) dataPtr = (EventBattleConfig *) ((unsigned char *) result + 0x10);
            }

            if (ExecuteEventBattleScript(dataPtr, entry16->parameter, local_3c, local_40) != 0) {
                unk = dataPtr->field_0E;
            }

            taskId = entry16->loaderTaskId;

            backgroundLoader->RemoveTask(taskId);

            entry16->loaderTaskId = -1;
        }

        func_0209c480(data_02109bf4, unk);
        func_0209c2e0(data_02109bf4, 0x7F, 0);
        func_0205e944(data_02108760, 0x7F);

        SetFlags04(gameResources, 0x40);

        func_020421a0();
        func_02043124();

        void *unk_0203cf4c = func_0203cf4c();
        func_0203e5d8(unk_0203cf4c, 0);

        if (_ffix(func_020709ac(unk_704fc)) > 30 || abs(GetBrightness(gameResources, false)) == 16) {
            SetMainBrightness(gameResources, -16, 0);

            if (GetBrightness(gameResources, true) == 0) SetSubBrightness(gameResources, -16, 15);

            entry16->state = 4;
        } else {
            entry16->state = 3;
        }

        return;
    }

    if (entry16->state == 3) {
        if (UpdateEntryObjectData(&entry16->data) != 0) entry16->state = 4;

        return;
    }

    if (entry16->state == 4) {
        if (IsBrightnessTransitionActive(gameResources) != 0) return;

        SetFlags04(gameResources, 0x04);
        SetFlags04(gameResources, 0x10);
        SetFlags04(gameResources, 0x02);
        SetFlags00(gameResources, 0x04);

        void *unk = func_020d6c00();
        func_020466e4(unk, 1);

        EntryNode16DataNOOPStub(&entry16->data);
        CleanupEntryObjectData(&entry16->data);

        func_ov017_0218d274(gameResources);
        func_ov017_0218f79c(gameResources);
        func_ov017_021a2840(gameResources);

        unk = func_0203cf4c();
        func_0203e5d8(unk, 1);

        entry16->base.completed = 1;
    }
}
