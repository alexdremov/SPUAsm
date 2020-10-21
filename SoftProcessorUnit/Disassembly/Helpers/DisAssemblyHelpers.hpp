//
//  DisAssemblyHelpers.hpp
//  SPUDisAsm
//
//  Created by Александр Дремов on 13.10.2020.
//

#ifndef DisAssemblyHelpers_hpp
#define DisAssemblyHelpers_hpp

#include <stdio.h>
#include "DisAssemblyDTypes.hpp"
#include "TranslationDTypes.hpp"
#include "AssemblyHelpers.hpp"
#include "CommandsParser.hpp"
#include "Syntax.hpp"


int  parseArgs(int argc, const char* argv[], DisassemblyParams* params);

void printDisAssemblyHelpData(void);

void DestructDisAssemblyParams(DisassemblyParams* params);

DisassemblyParseResult disAssamblyCode(DisassemblyParams* params,
                                       SyntaxMapping* mapping,
                                       BinaryFile* binary);

DisassemblyParseResult disAssamblyInstruction(DisassemblyParams* params,
                                              SyntaxMapping* mapping,
                                              BinaryFile* binary,
                                              char** instruction);

#endif /* DisAssemblyHelpers_hpp */
