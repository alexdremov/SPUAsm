//
//  BytecodeToCommand.hpp
//  SPUDisAsm
//
//  Created by Александр Дремов on 13.10.2020.
//

#ifndef BytecodeToCommand_hpp
#define BytecodeToCommand_hpp

#include <stdio.h>
#include "DisAssemblyDTypes.hpp"
#include "TranslationDTypes.hpp"
#include "AssemblyHelpers.hpp"
#include "CommandsParser.hpp"
#include "Syntax.hpp"


#define OPBACKTRANSLATE_FUNC(name, code) DisassemblyParseResult CMDBTC_ ## name (const SyntaxEntity* thou, DisassemblyParams* params, BinaryFile* binary, char** SPI);

#include "BTC.h"

#undef OPBACKTRANSLATE_FUNC
#endif /* BytecodeToCommand_hpp */
