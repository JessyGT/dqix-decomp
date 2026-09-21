#include "Combat/Main/EventBattleScript.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "Resource/Script.h"

extern "C" {
extern EventBattleConfig *data_02108dd8;
extern int data_020f0d2c;
extern Script::OpcodeLookupEntry data_020f0d30[];
extern const char data_020f0d40[];
}

// usa: func_02074060
int HandleBattleDefinitionOpcode(Script::Parameter *parameter) {
    int eventBattleId = (parameter++)->ToInt();

    if (eventBattleId != data_020f0d2c) {
        return 1;
    }

    data_02108dd8->eventBattleId = eventBattleId;

    for (int i = 0; i < 3; i++) {
        data_02108dd8->field_02[i] = parameter->ToInt();
        Script::Parameter *second  = parameter + 1;
        parameter += 2;
        data_02108dd8->field_08[i] = second->ToInt();
    }

    data_02108dd8->field_0E = parameter->ToInt();
    data_02108dd8->field_10 = (parameter + 1)->ToInt();
    data_02108dd8->field_12 = 0;

    return 1;
}

// usa: func_02074114
int LoadEventBattleConfig(EventBattleConfig *config, int eventBattleId) {
    BackgroundLoader::AddLockGlobal();

    unsigned int fileSize;
    void *fileData = LoadFileIntoMemory(data_020f0d40, data_0211e33c, &fileSize);

    if (fileData != 0) {
        ExecuteEventBattleScript(config, eventBattleId, fileData, fileSize);
        BackgroundLoader::RemoveLockGlobal();
        return 1;
    }

    BackgroundLoader::RemoveLockGlobal();
    return 0;
}

// usa: func_0207416c
int ExecuteEventBattleScript(void *context, int eventBattleId, void *scriptData, unsigned int scriptSize) {
    Script script;

    data_02108dd8 = (EventBattleConfig *) context;
    data_020f0d2c = eventBattleId;

    script.Initialize();
    script.SetOpcodeLookup(data_020f0d30);
    script.Load(scriptData, scriptSize);
    script.Execute();

    return 1;
}
