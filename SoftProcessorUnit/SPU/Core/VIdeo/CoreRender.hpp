//
//  CoreRender.hpp
//  SPU
//
//  Created by Александр Дремов on 24.10.2020.
//

#ifndef CoreRender_hpp
#define CoreRender_hpp

#include <stdio.h>
#include "SPUDtypes.hpp"
#include "SPUCore.hpp"
#include "SPUCoreHelpers.hpp"

void renderVRAM(SPUCore* core);

void fillBlank(SPUCore* core);

int vramSetPixel(SPUCore* core, int x, int y, char val);

#endif /* CoreRender_hpp */
