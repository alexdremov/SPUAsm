//
//  SPUCoreHelpers.hpp
//  SPU
//
//  Created by Александр Дремов on 14.10.2020.
//

#ifndef SPUCoreHelpers_hpp
#define SPUCoreHelpers_hpp

#include <stdio.h>
#include "SPUDtypes.hpp"

int  parseSPUArgs(RunParameters* parameters, int argc, const char * argv[]);

void spuHelp(void);

void DestructSPUArgs(RunParameters* parameters);

#endif /* SPUCoreHelpers_hpp */
