//
//  SPUCore.hpp
//  SPU
//
//  Created by Александр Дремов on 14.10.2020.
//

#ifndef SPUCore_hpp
#define SPUCore_hpp
#include <stdio.h>

#include "Syntax.hpp"
#include "SPUDtypes.hpp"
#include "StackRigid.h"
#include "CommandsParser.hpp"
#include "CommandsDTypes.hpp"
#include "InstrExecutors.hpp"

void ConstructSPUCore(SPUCore* core, size_t initStackSize);

InstructionExeResult runCode(SPUCore* core, RunParameters* params, BinaryFile* binary);

InstructionExeResult executeInstruction(SPUCore* core, RunParameters* params, BinaryFile* binary, char** SPI);

#endif /* SPUCore_hpp */
