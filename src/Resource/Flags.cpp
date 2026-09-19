#include "Resource/GameResources.h"

// ========================================================
// =                      Flags 00                        =
// ========================================================

// usa: func_0203b498
unsigned int GetFlags00(GameResources* resources)
{
    return resources->flags_00;
}

// usa: func_0203b4a0
void SetFlags00(GameResources* resources, unsigned int mask)
{
    resources->flags_00 |= mask;
}

// usa: func_0203b4b0
void ClearFlags00(GameResources* resources, unsigned int mask)
{
    resources->flags_00 &= ~mask;
}

// usa: func_0203b4c4
unsigned int TestFlags00(GameResources* resources, unsigned int mask)
{
    return resources->flags_00 & mask;
}

// ========================================================
// =                      Flags 04                        =
// ========================================================
// usa: func_0203b4d0
unsigned int GetFlags04(GameResources* resources)
{
    return resources->flags_04;
}

// usa: func_0203b4d8
void SetFlags04(GameResources* resources, unsigned int mask)
{
    resources->flags_04 |= mask;
}

// usa: func_0203b4e8
void ClearFlags04(GameResources* resources, unsigned int mask)
{
    resources->flags_04 &= ~mask;
}

// usa: func_0203b4fc
unsigned int TestFlags04(GameResources* resources, unsigned int mask)
{
    return resources->flags_04 & mask;
}

// ========================================================
// =                      Flags 08                        =
// ========================================================

// usa: func_0203b508
unsigned int GetFlags08(GameResources* resources)
{
    return resources->flags_08;
}

// usa: func_0203b510
void SetFlags08(GameResources* resources, unsigned int mask)
{
    resources->flags_08 |= mask;
}

// usa: func_0203b520
void ClearFlags08(GameResources* resources, unsigned int mask)
{
    resources->flags_08 &= ~mask;
}

// usa: func_0203b534
unsigned int TestFlags08(GameResources* resources, unsigned int mask)
{
    return resources->flags_08 & mask;
}