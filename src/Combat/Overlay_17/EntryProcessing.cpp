#include "Combat/Overlay_17/EntryProcessing.h"
#include "Resource/GameResources.h"

extern "C" {

void func_02046968(EntryContext *context);

void func_ov017_021acdf4(EntryNode *entry, EntryContext *context);
void func_ov017_021a1284(EntryNode *entry, EntryContext *context);
void func_ov017_0219e384(EntryNode *entry, EntryContext *context);
void func_ov017_021bb1a4(EntryNode *entry, EntryContext *context);
void func_ov017_021b8e8c(EntryNode *entry, EntryContext *context);
void func_ov017_021ab280(EntryNode *entry, EntryContext *context);
void func_ov017_021b790c(EntryNode *entry, EntryContext *context);
void func_ov017_021a5600(EntryNode *entry, EntryContext *context);
void func_ov017_021bf534(EntryNode *entry, EntryContext *context);
void func_ov017_021b8c84(EntryNode *entry, EntryContext *context);
void func_ov017_021bacd8(EntryNode *entry, EntryContext *context);
void func_ov017_021ba998(EntryNode *entry, EntryContext *context);
void func_ov003_0217e3b8(EntryNode *entry, EntryContext *context);
void func_ov017_021b2ce8(EntryNode *entry, EntryContext *context);
void func_ov017_021b2fac(EntryNode *entry, EntryContext *context);
void func_ov017_021b4710(EntryNode *entry, EntryContext *context);
void func_ov017_021b58b8(EntryNode *entry, EntryContext *context);

// Already decoded, but dispatcher passes two arguments.
void func_ov017_021b6290(EntryNode *entry, EntryContext *context);

void func_ov017_021b688c(EntryNode *entry, EntryContext *context);
void func_ov003_0217e6b0(EntryNode *entry, EntryContext *context);
void func_ov017_021aa41c(EntryNode *entry, EntryContext *context);
void func_ov017_021aa59c(EntryNode *entry, EntryContext *context);
void func_ov017_021abba8(EntryNode *entry, EntryContext *context);
void func_ov017_021ac3b0(EntryNode *entry, EntryContext *context);
void func_ov017_021acce4(EntryNode *entry, EntryContext *context);
void func_ov017_021c01a4(EntryNode *entry, EntryContext *context);
void func_ov017_021adcb0(EntryNode *entry, EntryContext *context);
void func_ov017_021ae85c(EntryNode *entry, EntryContext *context);
void func_ov017_021aef0c(EntryNode *entry, EntryContext *context);
void func_ov017_021af66c(EntryNode *entry, EntryContext *context);
void func_ov017_021b11d8(EntryNode *entry, EntryContext *context);
void func_ov017_021c03a4(EntryNode *entry, EntryContext *context);
void func_ov017_021c0850(EntryNode *entry, EntryContext *context);
void func_ov003_0217ef58(EntryNode *entry, EntryContext *context);
void func_ov017_021b1564(EntryNode *entry, EntryContext *context);
void func_ov017_021b1e24(EntryNode *entry, EntryContext *context);
void func_ov017_021b228c(EntryNode *entry, EntryContext *context);
void func_ov017_021c1404(EntryNode *entry, EntryContext *context);
void func_ov017_021c17fc(EntryNode *entry, EntryContext *context);
void func_ov017_021c16cc(EntryNode *entry, EntryContext *context);
void func_ov017_021bdc34(EntryNode *entry, EntryContext *context);
void func_ov017_021be0c4(EntryNode *entry, EntryContext *context);
void func_ov017_021bec00(EntryNode *entry, EntryContext *context);
void func_ov017_021bf014(EntryNode *entry, EntryContext *context);
void func_ov004_0216fa3c(EntryNode *entry, EntryContext *context);
void func_ov017_021c1af0(EntryNode *entry, EntryContext *context);
void func_ov017_021a86d0(EntryNode *entry, EntryContext *context);
void func_ov017_021a9454(EntryNode *entry, EntryContext *context);
void func_ov017_021a9768(EntryNode *entry, EntryContext *context);
void func_ov017_021a9bf8(EntryNode *entry, EntryContext *context);
void func_ov017_021aa1ac(EntryNode *entry, EntryContext *context);
void func_ov017_021a6648(EntryNode *entry, EntryContext *context);
void func_ov017_021a6c2c(EntryNode *entry, EntryContext *context);
void func_ov017_021a7378(EntryNode *entry, EntryContext *context);
void func_ov017_021a7b38(EntryNode *entry, EntryContext *context);
void func_ov017_021a7e14(EntryNode *entry, EntryContext *context);
void func_ov017_021c1e6c(EntryNode *entry, EntryContext *context);
void func_020d80b0(EntryNode *entry, EntryContext *context);
void func_ov017_021c26ac(EntryNode *entry, EntryContext *context);
void func_ov017_021c2784(EntryNode *entry, EntryContext *context);
void func_ov017_021c2f3c(EntryNode *entry, EntryContext *context);
void func_ov017_021c3194(EntryNode *entry, EntryContext *context);
void func_020d9870(EntryNode *entry, EntryContext *context);
void func_020d9e44(EntryNode *entry, EntryContext *context);
void func_020d9b34(EntryNode *entry, EntryContext *context);
void func_020dac94(EntryNode *entry, EntryContext *context);
void func_020dbcc4(EntryNode *entry, EntryContext *context);
void func_020e3c94(EntryNode *entry, EntryContext *context);
void func_ov017_021be468(EntryNode *entry, EntryContext *context);

unsigned int data_ov017_021d6a34[];
}

// usa: func_ov017_021a3498
void ProcessEntryContext(EntryContext *context) {
    unsigned int *values = data_ov017_021d6a34;

    EntryNode *entry = context->currentEntry;

    if (entry != 0 && entry->type != 0) {
        GameResources *gameResources = GetGameResources();

        if (gameResources != 0) {
            unsigned int *current = values;

            while (*current != 0xFFFF) {
                if (entry->type == *current) {
                    gameResources->unknown_4354 = 0x0C;
                    break;
                }

                current++;
            }
        }
    }

    // void AdvanceToNextActiveEntry(EntryContext *context);
    func_02046968(context);

    // void DispatchCurrentEntry(EntryContext *context, EntryNode *entry);
    DispatchEntry(context, entry);
}

// usa: func_ov017_021a3544
void DispatchEntry(EntryContext *context, EntryNode *entry) {
    if (entry == 0) {
        return;
    }

    signed char type = entry->type;

    switch (type) {
        case 0x00: return;

        case 0x01: func_ov017_021acdf4(entry, context); return;

        case 0x02: func_ov017_021a1284(entry, context); return;

        case 0x03: func_ov017_0219e384(entry, context); return;

        case 0x04: func_ov017_021bb1a4(entry, context); return;

        case 0x05: func_ov017_021b8e8c(entry, context); return;

        case 0x06: func_ov017_021ab280(entry, context); return;

        case 0x07:
        case 0x08:
        case 0x09: return;

        case 0x0A: func_ov017_021b790c(entry, context); return;

        case 0x0B: return;

        case 0x0C: func_ov017_021a5600(entry, context); return;

        case 0x0D: func_ov017_021bf534(entry, context); return;

        case 0x0E: func_ov017_021b8c84(entry, context); return;

        case 0x0F: func_ov017_021bacd8(entry, context); return;

        case 0x10: func_ov017_021ba998(entry, context); return;

        case 0x11: func_ov003_0217e3b8(entry, context); return;

        case 0x12: func_ov017_021b2ce8(entry, context); return;

        case 0x13: func_ov017_021b2fac(entry, context); return;

        case 0x14: func_ov017_021b4710(entry, context); return;

        case 0x15: func_ov017_021b58b8(entry, context); return;

        case 0x16: func_ov017_021b6290(entry, context); return;

        case 0x17: func_ov017_021b688c(entry, context); return;

        case 0x18: func_ov003_0217e6b0(entry, context); return;

        case 0x19: func_ov017_021aa41c(entry, context); return;

        case 0x1A: func_ov017_021aa59c(entry, context); return;

        case 0x1B: return;

        case 0x1C: func_ov017_021abba8(entry, context); return;

        case 0x1D: return;

        case 0x1E: func_ov017_021ac3b0(entry, context); return;

        case 0x1F: func_ov017_021acce4(entry, context); return;

        case 0x20: func_ov017_021c01a4(entry, context); return;

        case 0x21: func_ov017_021adcb0(entry, context); return;

        case 0x22: return;

        case 0x23: func_ov017_021ae85c(entry, context); return;

        case 0x24: return;

        case 0x25: func_ov017_021aef0c(entry, context); return;

        case 0x26: func_ov017_021af66c(entry, context); return;

        case 0x27: func_ov017_021b11d8(entry, context); return;

        case 0x28: func_ov017_021c03a4(entry, context); return;

        case 0x29: func_ov017_021c0850(entry, context); return;

        case 0x2A: func_ov003_0217ef58(entry, context); return;

        case 0x2B: func_ov017_021b1564(entry, context); return;

        case 0x2C: func_ov017_021b1e24(entry, context); return;

        case 0x2D: func_ov017_021b228c(entry, context); return;

        case 0x2E: func_ov017_021c1404(entry, context); return;

        case 0x2F: func_ov017_021c17fc(entry, context); return;

        case 0x30: func_ov017_021c16cc(entry, context); return;

        case 0x31: return;

        case 0x32: func_ov017_021bdc34(entry, context); return;

        case 0x33: func_ov017_021be0c4(entry, context); return;

        case 0x34: func_ov017_021bec00(entry, context); return;

        case 0x35: func_ov017_021bf014(entry, context); return;

        case 0x36: func_ov004_0216fa3c(entry, context); return;

        case 0x37: func_ov017_021c1af0(entry, context); return;

        case 0x38: func_ov017_021a86d0(entry, context); return;

        case 0x39: func_ov017_021a9454(entry, context); return;

        case 0x3A: func_ov017_021a9768(entry, context); return;

        case 0x3B: func_ov017_021a9bf8(entry, context); return;

        case 0x3C: func_ov017_021aa1ac(entry, context); return;

        case 0x3D: func_ov017_021a6648(entry, context); return;

        case 0x3E: func_ov017_021a6c2c(entry, context); return;

        case 0x3F: func_ov017_021a7378(entry, context); return;

        case 0x40: func_ov017_021a7b38(entry, context); return;

        case 0x41: func_ov017_021a7e14(entry, context); return;

        case 0x42: func_ov017_021c1e6c(entry, context); return;

        case 0x43: func_020d80b0(entry, context); return;

        case 0x44: func_ov017_021c26ac(entry, context); return;

        case 0x45: func_ov017_021c2784(entry, context); return;

        case 0x46: func_ov017_021c2f3c(entry, context); return;

        case 0x47: func_ov017_021c3194(entry, context); return;

        case 0x48: func_020d9870(entry, context); return;

        case 0x49: func_020d9e44(entry, context); return;

        case 0x4A: func_020d9b34(entry, context); return;

        case 0x4B: func_020dac94(entry, context); return;

        case 0x4C: func_020dbcc4(entry, context); return;

        case 0x4D: func_020e3c94(entry, context); return;

        case 0x4E: func_ov017_021be468(entry, context); return;

        default: return;
    }
}