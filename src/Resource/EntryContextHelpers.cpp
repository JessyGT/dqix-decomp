#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "Graphics/NSBXX/NSBXX.h"
#include "Resource/Brightness.h"
#include "Resource/EntryContext.h"
#include "Resource/GameResources.h"

extern "C" {
void *func_0207df50(void *context);
void func_0207df90(void *context);
void func_0207dfac(void *context);
void func_020407b4(Object3D *object, int x, int y, int z);
void *func_02012d88(void *param1, unsigned int size);
void *func_0200fb8c(GameState *gameState);
void *func_020100bc(GameState *gameState);
void func_0202e874(void *object, short value);
void func_0202e9a4(void *object, int value);
void func_0202eab8(void *object);
void func_02012da4(unsigned char data_02114e20[], void *allocation);

unsigned char data_02114e20[];
const char data_020f00cc[];
}

// usa: func_0204693c
void ResetEntryNode(EntryNode *entry)
{
    entry->type = -1;
    entry->completed = 0;
    entry->field_02 = 0;
    entry->active = 0;
}

// usa: func_02046958
void InitializeEntryContext(EntryContext *context) {
    context->currentEntry = 0;
    context->lastEntry    = 0;
}

// usa: func_02046968
void AdvanceToNextActiveEntry(EntryContext *context) {
    while (context->currentEntry != 0) {
        if (context->currentEntry->completed != 0) {
            context->currentEntry->field_02 = 0;
            context->currentEntry->active   = 0;
            context->currentEntry           = context->currentEntry->next;
        } else {
            context->currentEntry->active = 1;
            return;
        }
    }
}

// usa: func_020469b4
void InsertEntryAsLast(EntryContext *context, EntryNode *entry) {
    if (context->currentEntry != 0 && context->lastEntry != 0) {
        context->lastEntry->next = entry;
        context->lastEntry       = entry;
        entry->next              = 0;
    } else {
        context->currentEntry = entry;
        context->lastEntry    = entry;
        entry->next           = 0;
    }

    entry->next     = 0;
    entry->field_02 = 1;
}

// usa: func_020469f8
void InsertEntryBeforeCurrent(EntryContext *context, EntryNode *entry) {
    EntryNode *current = context->currentEntry;

    if (current != 0 && context->lastEntry != 0) {
        current->active = 0;

        entry->next           = context->currentEntry;
        context->currentEntry = entry;
    } else {
        context->currentEntry = entry;
        context->lastEntry    = entry;
        entry->next           = 0;
    }

    entry->field_02 = 1;
}

// usa: func_02046a3c
void InsertEntryAfterCurrent(EntryContext *context, EntryNode *entry) {
    if (context->currentEntry != 0 && context->lastEntry != 0) {
        entry->next                 = context->currentEntry->next;
        context->currentEntry->next = entry;

        if (entry->next == 0) {
            context->lastEntry = entry;
        }
    } else {
        context->currentEntry = entry;
        context->lastEntry    = entry;
        entry->next           = 0;
    }

    entry->field_02 = 1;
}

// usa: func_02046a8c
void RemoveEntry(EntryContext *context, EntryNode *entry) {
    EntryNode *current = context->currentEntry;

    if (current == 0) {
        return;
    }

    if (current == entry) {
        context->currentEntry = entry->next;
    } else {
        EntryNode *next = current->next;

        if (next == 0) {
            return;
        }

        while (next != entry) {
            if (next == 0) {
                return;
            }

            current = next;
            next    = next->next;
        }

        current->next = next->next;
    }

    current            = context->currentEntry;
    context->lastEntry = 0;

    while (current != 0) {
        context->lastEntry = current;
        current            = current->next;
    }

    ResetEntryNode(entry);
}

// usa: func_02046b08
bool IsEntryContextEmpty(EntryContext *context) {
    return context->currentEntry == 0;
}

// usa: func_02046b1c
EntryNode *GetCurrentEntry(EntryContext *context) {
    return context->currentEntry;
}

// usa: func_02046b24
signed char GetCurrentEntryType(EntryContext *context) {
    if (context->currentEntry != 0) {
        return context->currentEntry->type;
    }

    return -1;
}

// usa: func_02046b38
bool ContainsEntry(EntryContext *context, EntryNode *target) {
    EntryNode *entry = context->currentEntry;

    while (entry != 0) {
        if (entry == target) {
            return true;
        }

        entry = entry->next;
    }

    return false;
}

// usa: func_02046b60
bool HasEntryType(EntryContext *context, int type) {
    EntryNode *entry = context->currentEntry;

    while (entry != 0) {
        if (entry->type == type) {
            return true;
        }

        entry = entry->next;
    }

    return false;
}

// usa: func_02046b8c
void MoveEntriesOfTypeToFront(EntryContext *context, int type) {
    EntryNode *previous;
    EntryNode *matching;
    EntryNode *current;
    EntryNode *node;

    current = context->currentEntry;
    node    = current;

    while (node != 0) {
        node = node->next;
    }

    previous = 0;
    matching = previous;
    node     = previous;

    while (current != 0) {
        EntryNode *next = current->next;

        if (current->type == type) {
            if (previous != 0) {
                previous->next = next;
            } else {
                context->currentEntry = next;
            }

            current->next = node;

            if (matching != 0) {
                EntryNode *tail = matching;

                while (tail->next != 0) {
                    tail = tail->next;
                }

                tail->next = current;
            } else {
                matching = current;
            }
        } else {
            previous = current;
        }

        current = next;
    }

    if (matching == 0) {
        return;
    }

    node = matching;

    while (node->next != 0) {
        node = node->next;
    }

    node->next = context->currentEntry;

    node                  = matching;
    context->currentEntry = matching;

    while (node->next != 0) {
        node = node->next;
    }

    context->lastEntry = node;

    node = context->currentEntry;

    while (node != 0) {
        node = node->next;
    }
}

// usa: func_02046c78
int CountEntries(EntryContext *context) {
    EntryNode *entry = context->currentEntry;
    int count        = 0;

    while (entry != 0) {
        entry = entry->next;
        count++;
    }

    return count;
}

// usa: func_02046c98
void QueueEntryObjectLoad(EntryNode16Data *data) {
    if (data->objectOverride != 0) {
        return;
    }

    data->loaderTaskId = BackgroundLoader::GetInstance()->QueueLoadFile(data_020f00cc, 0);
}

// usa: func_02046cc8
bool FinishEntryObjectLoad(EntryNode16Data *data) {

    // Partial layout of the resource block at GameResources + 0x2CC.
    // Only the member at +0xC40 is currently known/used.
    //
    // Keep for perfect byte match.
    struct EntryResourceBlock {
        unsigned char unknown_000[0xC40];
        unsigned char field_C40;
    };
    EntryResourceBlock *resourceBlock;
    BackgroundLoader *loader;
    SafeAllocator *allocator;

    if (data->objectOverride != 0) {
        return true;
    }

    if (data->loaderTaskId < 0) {
        return false;
    }

    GameState::GetInstance();

    resourceBlock = (EntryResourceBlock *) GetGameResources();

    allocator = data->allocatorOverride;
    if (allocator == 0) {
        allocator = &data->allocator;
    }

    loader = BackgroundLoader::GetInstance();

    if (loader->GetTaskStatus(data->loaderTaskId) != 0) {
        unsigned char embeddedObjectEnabled = data->embeddedObjectEnabled;

        resourceBlock = (EntryResourceBlock *) ((char *) resourceBlock + 0x2CC);

        if (embeddedObjectEnabled != 0) {
            func_0207df50(&resourceBlock->field_C40);
            func_0207df90(&resourceBlock->field_C40);

            void *fileData;
            unsigned int fileSize;
            ObjectArchiveLoadInfo loadInfo;

            loader->GetLoadedFileByID(data->loaderTaskId, &fileData, &fileSize);

            if (fileData != 0) {
                if (allocator->GetSignedAllocator() != 0) {
                    data->object3D.Initialize();

                    loadInfo.fileData  = fileData;
                    loadInfo.unk_8     = fileSize;
                    loadInfo.allocator = allocator;
                    loadInfo.unk_10    = 1;

                    data->object3D.LoadFromCHRArchive(&loadInfo);

                    NSBXX_Model_SetPolygonID(data->object3D.pModel_->rawInternalModel_, 0x3D);

                    func_020407b4(&data->object3D, 0, -0xA000, 0x1000);

                    data->object3D.MaybeSetBCFGAnimation(0, 0);
                }
            }

            func_0207dfac(&resourceBlock->field_C40);
        }

        loader->RemoveTask(data->loaderTaskId);
        data->loaderTaskId = -1;

        return true;
    }

    return false;
}

// usa: func_02046e08
void InitializeEntryObjectData(EntryNode16Data *data) {
    data->field_00 = 0;
    data->field_04 = 0;
    data->field_20 = 0;

    data->rotationDegrees = 0.0f;
    data->field_0C        = 15.0f;

    data->loaderTaskId = -1;

    data->field_1C              = 1;
    data->embeddedObjectEnabled = 1;

    data->object3D.Initialize();
    data->allocator.ResetAllocatorPointer();

    data->allocatorOverride = 0;
    data->objectOverride    = 0;

    data->field_10 = 0;
    data->field_14 = 0;
    data->field_18 = 0;
}

// usa: func_02046e70
void InitializeEntryObjectDataWithOverrides(EntryNode16Data *data, SafeAllocator *allocatorOverride,
                                            Object3D *objectOverride) {
    EntryNode16Data *entryData = data;

    entryData->field_20 = entryData->field_04 = entryData->field_00 = 0;

    entryData->rotationDegrees = 0.0f;
    entryData->field_0C        = 15.0f;

    entryData->loaderTaskId = -1;

    entryData->field_1C              = 1;
    entryData->embeddedObjectEnabled = 1;

    GameState::GetInstance();

    entryData->object3D.Initialize();
    entryData->allocator.ResetAllocatorPointer();

    entryData->objectOverride = objectOverride;

    if (objectOverride != 0) {
        NSBXX_Model_SetPolygonID(objectOverride->pModel_->rawInternalModel_, 0x3D);

        entryData->objectOverride->SetScale(0x1000, 0x1000, 0x1000);

        func_020407b4(entryData->objectOverride, 0, -0xA000, 0x1000);

        entryData->objectOverride->MaybeSetBCFGAnimation(0, 0);
    }

    entryData->allocatorOverride = allocatorOverride;

    if (allocatorOverride != 0) {
        return;
    }

    void *memory = func_02012d88(data_02114e20, 0x301C);

    if (memory != 0) {
        entryData->allocator.ResetAllocatorPointer();
        entryData->allocator.CreateTypeA(memory, 0x301C);
        entryData->allocator.Reset();
        return;
    }

    entryData->embeddedObjectEnabled = 0;
    entryData->allocator.ResetAllocatorPointer();
    entryData->field_00 = -1;
}

// usa: func_02046f84
void CleanupEntryObjectData(EntryNode16Data *data) {
    GameState *gameState = GameState::GetInstance();

    func_0200fb8c(gameState); // GameState->GameResouces

    void *object = func_020100bc(gameState);

    func_0202e874(object, 0);
    func_0202e9a4(object, 0xF000);
    func_0202eab8(object);

    if (data->allocatorOverride == 0) {
        void *allocation = data->allocator.GetSignedAllocator();

        if (allocation != 0) {
            data->allocator.Reset();
            data->allocator.Destroy();

            func_02012da4(data_02114e20, allocation);
        }
    }

    data->field_00 = 0;
    data->field_04 = 0;
}

// usa: func_0204700c
bool UpdateEntryObjectData(EntryNode16Data *data) {
    if (data->field_00 > 35) {
        return true;
    }

    GameState *gameState   = GameState::GetInstance();
    unsigned int tickCount = gameState->GetTickCount();

    data->rotationDegrees -= 8.0f;

    if (data->rotationDegrees <= -180.0f) {
        data->rotationDegrees = 180.0f;
    }

    float angle = 3.14f * (data->rotationDegrees / 180.0f);

    data->field_0C -= 0.4333f;

    void *object = func_020100bc(gameState);

    func_0202e874(object, (short) fix32ReduceAngle0To2Pi((int) (4096.0f * angle)));

    func_0202e9a4(object, (int) (4096.0f * data->field_0C));

    if (data->objectOverride != 0) {
        data->objectOverride->AdvanceEffects();
    } else {
        data->object3D.AdvanceEffects();
    }

    data->field_00 += tickCount;

    if (data->field_00 > 15 && data->field_1C != 0) {
        GameResources *gameResources = GetGameResources();

        SetMainBrightness(gameResources, -16, 20);
        SetSubBrightness(gameResources, -16, 20);

        data->field_1C = 0;
    }

    return data->field_00 > 35;
}

// usa: func_0204715c
// called only while entry16->state == 3
void DrawEntryObjectData(EntryNode16Data *data) {
    if (data->objectOverride != 0) {
        data->objectOverride->Draw(1);
        return;
    }

    if (data->embeddedObjectEnabled == 0) {
        return;
    }

    data->object3D.Draw(1);
}

// usa: func_02047198 no-op stub
void EntryNode16DataNOOPStub(EntryNode16Data *data) {}
