#pragma once
#include "World/Object3D.h"

struct EntryNode {
    signed char type;               // +0x00 dispatch type = [0x01..0x4E]
    unsigned char completed;        // +0x01 nonzero when entry is finished
    unsigned char field_02;         // +0x02 reset when advancing past entry
    unsigned char active;           // +0x03 set to 1 for current active entry
    EntryNode *next;                // +0x04 next entry
};

// func_02046b24 --> GetCurrentEntryType(EntryContext):
// Returns -1 when currentEntry is null,
// otherwise returns currentEntry->type.
struct EntryContext {
    EntryNode *currentEntry;        // +0x00
    EntryNode *lastEntry;           // +0x04
};

struct EntryNode16Data {
    unsigned int field_00;          // +0x00
    int field_04;                   // +0x04

    float rotationDegrees;          // +0x08
    float field_0C;                 // +0x0C

    int field_10;                   // +0x10
    int field_14;                   // +0x14
    int field_18;                   // +0x18

    unsigned char field_1C;         // +0x1C
    unsigned char embeddedObjectEnabled;    // +0x1D
    unsigned char unknown_1E[2];    // +0x1E..0x1F

    int field_20;                   // +0x20

    SafeAllocator allocator;        // +0x24..0x37
    SafeAllocator *allocatorOverride; // +0x38

    Object3D object3D;              // +0x3C..0xE7

    Object3D *objectOverride;       // +0xE8
    int loaderTaskId;               // +0xEC
};

// Used by DispatchEntry when EntryNode::type == 0x16.
struct EntryNode16 {
    EntryNode base;                  // +0x000..0x007

    unsigned char field_08;          // +0x008
    unsigned char unknown_09[3];     // +0x009..0x00B

    EntryNode16Data data;            // +0x00C..0x0FB

    unsigned char state;             // +0x0FC
    unsigned char delay;             // +0x0FD
    short parameter;                 // +0x0FE
    short loaderTaskId;              // +0x100
};

void ResetEntryNode(EntryNode *entry);
void InitializeEntryContext(EntryContext *context);
void AdvanceToNextActiveEntry(EntryContext *context);
void InsertEntryAsLast(EntryContext *context, EntryNode *entry);
void InsertEntryBeforeCurrent(EntryContext *context, EntryNode *entry);
void InsertEntryAfterCurrent(EntryContext *context, EntryNode *entry);
void RemoveEntry(EntryContext *context, EntryNode *entry);
bool IsEntryContextEmpty(EntryContext *context);
EntryNode *GetCurrentEntry(EntryContext *context);
signed char GetCurrentEntryType(EntryContext *context);
bool ContainsEntry(EntryContext *context, EntryNode *target);
bool HasEntryType(EntryContext *context, int type);
void MoveEntriesOfTypeToFront(EntryContext *context, int type);
int CountEntries(EntryContext *context);

void QueueEntryObjectLoad(EntryNode16Data *data);
bool FinishEntryObjectLoad(EntryNode16Data *data);
void InitializeEntryObjectData(EntryNode16Data *data);
void InitializeEntryObjectDataWithOverrides(EntryNode16Data *data, SafeAllocator *allocatorOverride,
                                          Object3D *objectOverride);
void CleanupEntryObjectData(EntryNode16Data *data);
bool UpdateEntryObjectData(EntryNode16Data *data);
void DrawEntryObjectData(EntryNode16Data *data);
void EntryNode16DataNOOPStub(EntryNode16Data *data);
