//
//  CommandToBytecode.cpp
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 13.10.2020.
//

#include "AssemblyHelpers.hpp"
#include "CommandsParser.hpp"
#include "Syntax.hpp"
#include <string.h>
#include <ctype.h>
#include "CTBDefs.h"


#undef OPTRANSLATE_FUNC

#define OPTRANSLATE_FUNC(name, code) CommandToBytesResult CMDCTB_ ## name (const struct SyntaxEntity* thou, AssemblyParams* compileParams, BinaryFile* binary, int argc, const char** argv) { code }

#include "CTB.h"

#undef OPTRANSLATE_FUNC
