//
//  SPUDtypes.h
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 14.10.2020.
//

#ifndef SPUDtypes_h
#define SPUDtypes_h

#include "StackRigid.h"

#define SCREEN_WIDTH  64
#define SCREEN_HEIGHT 32
#define VRAM_OFFSET   512
#define RAM_SIZE      (VRAM_OFFSET + (SCREEN_WIDTH * SCREEN_HEIGHT) / sizeof(double))


struct SPUCore {
    double             RAM  [RAM_SIZE];
    double             REG  [8];
    int            terminated;
    StackRigid_double*  stack;
    StackRigid_double*  callStack;
};


struct RunParameters {
    int         verbose;
    int         vsync;
    
    FILE*       inputFile;
    const char* inputFileName;
    
    FILE*       outputFile;
    const char* outputFileName;
};

enum InstructionExeResult {
    SPU_EXE_OK              = 800,
    SPU_EXE_STACK_UNDERFLOW = 801,
    SPU_EXE_STACK_OVERFLOW  = 802,
    SPU_EXE_CORRUPTED       = 803,
    SPU_EXE_ZERODIV         = 804,
    SPU_EXE_UNKNOWN         = 805,
    SPU_EXE_NOARGS          = 806,
    SPU_EXE_NOMEMORY        = 807,
    SPU_EXE_INVALIDINPUT    = 808
};

#endif /* SPUDtypes_h */
