#pragma once

#include "Resource/EntryContext.h"

// EntryContext::currentEntry points to the current node in a linked entry chain.
// The exact higher-level subsystem represented by these entries is not yet confirmed.

// usa: func_ov017_021a3498
// Examines the current entry, advances the context to the next active entry when needed, then dispatches the resulting current
// entry.
void ProcessEntryContext(EntryContext *context);

// usa: func_ov017_021a3544
// Dispatches an EntryNode to its handler based on EntryNode::type.
void DispatchEntry(EntryContext *context, EntryNode *entry);