//
//  InstrExecutors.hpp
//  SPU
//
//  Created by Александр Дремов on 14.10.2020.
//

#ifndef InstrExecutors_hpp
#define InstrExecutors_hpp

#include "EXEDefs.h"

#undef OPEXE_FUNC
#define OPEXE_FUNC(name, code) InstructionExeResult CMDEXE_ ## name (SPUCore* core, RunParameters* params, BinaryFile* binary, char** SPI);

#include "EXE.h"

#undef OPEXE_FUNC

#endif /* InstrExecutors_hpp */
