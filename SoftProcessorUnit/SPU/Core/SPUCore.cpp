//
//  SPUCore.cpp
//  SPU
//
//  Created by Александр Дремов on 14.10.2020.
//

#include "SPUCore.hpp"

#define CALLEXE(name) return name (core,  params, binary, SPI)
#define EVALUATE(a) a

void ConstructSPUCore(SPUCore* core, size_t initStackSize) {
    core->stack = NewStackRigid_double(initStackSize, stderr);
    core->terminated = 0;
}

InstructionExeResult runCode(SPUCore* core, RunParameters* params, BinaryFile* binary) {
    core->terminated = 0;
    
    char* SPI = binary->code;
    
    while (!core->terminated && SPI < binary->code + binary->currentSize) {
        char* prevOffset = SPI;
        InstructionExeResult cmdResult = executeInstruction(core, params, binary, &SPI);
        if (cmdResult != SPU_EXE_OK){
            core->terminated = 1;
            fprintf(stderr, "error: spu: terminated at offset: %d reached: %d\n",
                    (int)((int)(prevOffset - binary->code) + (int)(binary->codeOffset)), (int)((int)(SPI - binary->code) + (int)(binary->codeOffset)));
            return cmdResult;
        }
    }
    
    return SPU_EXE_OK;
}


InstructionExeResult executeInstruction(SPUCore* core,
                                        RunParameters* params,
                                        BinaryFile* binary,
                                        char** SPI) {
//    printf("NOW: %d\n", binary->codeOffset + (int)(*SPI - binary->code));
    switch (**SPI) {
        #define COMMAND_INFO(name, code, args, flags) case code : EVALUATE(CALLEXE(EVALUATE(CMDEXE_ ## name)));
            
        #include "INFO.h"
            
        #undef COMMAND_INFO
            
        default:
            return SPU_EXE_UNKNOWN;
    }
    return SPU_EXE_OK;
}
