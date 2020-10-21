//
//  Syntax.c
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 12.10.2020.
//
#include "Syntax.hpp"
#include "CommandToBytecode.hpp"
#include "AssemblyHelpers.hpp"
#include "string.h"

#undef OPTRANSLATE_FUNC
#undef OPBACKTRANSLATE_FUNC

#define EVALUATE(a) a
#define CONCAT(a, b)  EVALUATE(a) ## EVALUATE(b)

#define OPTRANSLATE_FUNC(name) CommandToBytesResult name (const struct SyntaxEntity* thou, AssemblyParams* compileParams, BinaryFile* binary, int argc, const char** argv)

#define OPBACKTRANSLATE_FUNC(name) DisassemblyParseResult name (const SyntaxEntity* thou, DisassemblyParams* params, BinaryFile* binary, char** SPI)

static SyntaxEntity makeEntity(const char* name, const char code, const char* format, const char flagBytes,
                               OPTRANSLATE_FUNC((*cProcessor)),
                               OPBACKTRANSLATE_FUNC((*bProcessor))){
    SyntaxEntity newEntity = {name, code, format, flagBytes, cProcessor, bProcessor};
    return newEntity;
}


SyntaxMapping getSyntaxMapping(void) {
    static SyntaxEntity operations[] = {

#define COMMAND_INFO(name, code, args, flags) makeEntity(#name, code , args, flags, &EVALUATE(CMDCTB_ ## name  ) ,&EVALUATE(CMDBTC_ ## name)),
#include "INFO.h"
        
#undef COMMAND_INFO
    };
    static SyntaxMapping mapping = {operations, sizeof(operations) / sizeof(SyntaxEntity)};
    
    return mapping;
}


int getSyntaxCode(const SyntaxMapping* mapping, const char* name) {
    for(size_t i = 0; i < mapping->number; i++){
        if (strcmp(mapping->entities[i].naming, name) == 0){
            return mapping->entities[i].code;
        }
    }
    return -1;
}


const char* getSyntaxName(const SyntaxMapping* mapping, const char code) {
    for(size_t i = 0; i < mapping->number; i++){
        if (code == mapping->entities[i].code){
            return mapping->entities[i].naming;
        }
    }
    return "";
}

const SyntaxEntity* getSyntaxEntityByCode(const SyntaxMapping* mapping, const char code) {
    for(size_t i = 0; i < mapping->number; i++){
        if (code == mapping->entities[i].code){
            return &mapping->entities[i];
        }
    }
    return NULL;
}

const SyntaxEntity* getSyntaxEntityByName(const SyntaxMapping* mapping, const char* name) {
    for(size_t i = 0; i < mapping->number; i++){
        if (strcmp(mapping->entities[i].naming, name) == 0){
            return &mapping->entities[i];
        }
    }
    return NULL;
}
