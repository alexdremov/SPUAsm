//
//  InstrExecutors.cpp
//  SPU
//
//  Created by Александр Дремов on 14.10.2020.
//


#include "InstrExecutors.hpp"
#include <cmath>
#include "EXEDefs.h"
#include "ComplexValueTools.hpp"
#include "CoreRender.hpp"
#include <unistd.h>

#undef OPEXE_FUNC

#define OPEXE_FUNC(name, code) InstructionExeResult CMDEXE_ ## name (SPUCore* core, RunParameters* params, BinaryFile* binary, char** SPI) { code }

#include "EXE.h"

#undef OPEXE_FUNC
