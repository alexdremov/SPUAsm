//
//  InstrExecutors.cpp
//  SPU
//
//  Created by Александр Дремов on 14.10.2020.
//


#include "InstrExecutors.hpp"
#include <math.h>
#include "EXEDefs.h"

#undef OPEXE_FUNC

#define OPEXE_FUNC(name, code) InstructionExeResult CMDEXE_ ## name (SPUCore* core, RunParameters* params, BinaryFile* binary, char** SPI) { code }

#include "EXE.h"

#undef OPEXE_FUNC
