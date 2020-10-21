//
//  Syntax.h
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 12.10.2020.
//

#ifndef Syntax_h
#define Syntax_h

#include <stdlib.h>
#include "TranslationDTypes.hpp"
#include "AssemblyHelpers.hpp"
#include "CommandToBytecode.hpp"
#include "BytecodeToCommand.hpp"

#define SPU_CMD_MAXARGS 5

struct SyntaxEntity {
    const char*             naming;
    const char              code;
    const char*             format;
    const char              flagBytes;
    CommandToBytesResult    (*cProcessor) (const struct SyntaxEntity* thou,
                                           AssemblyParams* compileParams,
                                           BinaryFile* binary,
                                           int argc,
                                           const char** argv);
    
    DisassemblyParseResult  (*bProcessor) (const struct SyntaxEntity* thou,
                                           DisassemblyParams* params,
                                           BinaryFile* binary,
                                           char** SPI);
};

struct SyntaxMapping{
    const SyntaxEntity* entities;
    const size_t        number;
};

SyntaxMapping getSyntaxMapping(void);

int   getSyntaxCode(const SyntaxMapping* mapping, const char* name);

const char* getSyntaxName(const SyntaxMapping* mapping,  const char code);

const SyntaxEntity* getSyntaxEntityByCode(const SyntaxMapping* mapping, const char code);

const SyntaxEntity* getSyntaxEntityByName(const SyntaxMapping* mapping, const char* name);

#endif /* Syntax_h */
