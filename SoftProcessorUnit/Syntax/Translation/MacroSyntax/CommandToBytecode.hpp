//
//  CommandToBytecode.hpp
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 13.10.2020.
//

#ifndef CommandToBytecode_hpp
#define CommandToBytecode_hpp

#include "CTBDefs.h"
#define OPTRANSLATE_FUNC(name, code) CommandToBytesResult CMDCTB_ ## name (const struct SyntaxEntity* thou, AssemblyParams* compileParams, BinaryFile* binary, int argc, const char** argv)

#include "CTB.h"

#endif /* CommandToBytecode_hpp */
