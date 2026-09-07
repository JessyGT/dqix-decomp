#include <globaldefs.h>
#include "Combat/Main/BattleList.h"
#include "Combat/Main/UnknownContext.h"

extern "C" ARM void SetBattleStructField0(BattleStruct* battleStruct, UnknownContext* unk0)
{
    battleStruct->unk0 = unk0;
}

extern "C" ARM UnknownContext* GetBattleStructField0(BattleStruct* battleStruct)
{
    return battleStruct->unk0;
}