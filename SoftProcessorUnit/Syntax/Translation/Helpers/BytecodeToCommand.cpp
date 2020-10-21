//
//  BytecodeToCommand.cpp
//  SPUDisAsm
//
//  Created by Александр Дремов on 13.10.2020.
//

#include <string.h>
#include "BytecodeToCommand.hpp"
#include "DisAssemblyDTypes.hpp"
#include "TranslationDTypes.hpp"
#include "AssemblyHelpers.hpp"
#include "CommandsParser.hpp"
#include "Syntax.hpp"

int checkBytesEnough(const SyntaxEntity* thou, BinaryFile* binary, char* SPI) {
    size_t neededBytes = 1;
    
    neededBytes += (size_t)(thou->flagBytes);
    for (size_t i = 0; i < strlen(thou->format); i++) {
        if (thou->format[i] == '*')
            neededBytes++;
    }
    
    return checkBytesEnoughNumber(binary, SPI, neededBytes);
}

int checkBytesEnoughNumber(BinaryFile* binary, char* SPI, size_t bytes) {
    if (SPI + bytes > binary->code + binary->currentSize)
        return 0;
    return 1;
}

#undef OPBACKTRANSLATE_FUNC

#define OPBACKTRANSLATE_FUNC(name, code) DisassemblyParseResult CMDBTC_ ## name (const SyntaxEntity* thou, DisassemblyParams* params, BinaryFile* binary, char** SPI) { code }

#include "BTC.h"

