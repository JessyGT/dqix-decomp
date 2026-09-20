#pragma once

struct EntryNode {
    signed char type;               // +0x00 dispatch type = [0x01..0x4E]
    unsigned char completed;        // +0x01 nonzero when entry is finished
    unsigned char field_02;         // +0x02 reset when advancing past entry
    unsigned char active;           // +0x03 set to 1 for current active entry
    EntryNode *next;                 // +0x04 next entry
};

// func_02046b24 --> GetCurrentEntryType(EntryContext):
// Returns -1 when currentEntry is null,
// otherwise returns currentEntry->type.
struct EntryContext {
    EntryNode *currentEntry;         // +0x00
};

// Used by DispatchEntry when EntryNode::type == 0x16.
struct EntryNode16 {
    EntryNode base;                  // +0x000..0x007

    unsigned char field_08;          // +0x008
    unsigned char unknown_09[3];     // +0x009..0x00B
    unsigned char unknown_0c[0xF0];  // +0x00C..0x0FB

    unsigned char state;             // +0x0FC
    unsigned char delay;             // +0x0FD
    short parameter;                 // +0x0FE
    short loaderTaskId;              // +0x100
};