#pragma once

struct EntryNode {
    signed char type;               // +00 dispatch type
    unsigned char field_01;         // +01 if nonzero, entry is skipped/advanced past
    unsigned char field_02;         // +02 reset when skipped
    unsigned char field_03;         // +03 1 for current/active entry, 0 when skipped
    EntryNode *next;                    // +04 next entry
};

// func_02046b24 --> GetCurrentEntryType(EntryContext):
// Returns -1 when currentEntry is null,
// otherwise returns currentEntry->type.
struct EntryContext {
    EntryNode *currentEntry; // +0x00
};