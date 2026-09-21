#include "Combat/Main/EventBattleScript.h"
#include "Resource/Script.h"

extern "C" {
extern void *data_02108dd8;
extern int data_020f0d2c;
extern Script::OpcodeLookupEntry data_020f0d30[];
}

// usa: func_0207416c
int ExecuteEventBattleScript(void *context, int eventBattleId, void *scriptData, unsigned int scriptSize) {
    Script script;

    data_02108dd8 = context;
    data_020f0d2c = eventBattleId;

    script.Initialize();
    script.SetOpcodeLookup(data_020f0d30);
    script.Load(scriptData, scriptSize);
    script.Execute();

    return 1;
}
