#include <globaldefs.h>
#include "Combat/Main/BattleList.h"

extern "C" ARM void SetBattleStructField0(BattleStruct* battleStruct, int field0Value)
{
    battleStruct->unk0 = field0Value;
}