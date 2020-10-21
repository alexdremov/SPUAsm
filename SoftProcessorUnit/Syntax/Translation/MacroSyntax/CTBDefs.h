//
//  CTBDefs.h
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 19.10.2020.
//

#include <stdio.h>
#include "Syntax.hpp"
#include "TranslationDTypes.hpp"
#include "AssemblyHelpers.hpp"


#define DUMPCODEBLOCK for (;starting < ending; starting++) { fprintf(compileParams->lstFile, "%-3d ", (unsigned char)binary->code[starting]); }

#define DUMPCODEBLOCKHEX for (;starting < ending; starting++) { fprintf(compileParams->lstFile, "%2x ", (unsigned char)binary->code[starting]); }

#define LSTDUMPED(code) { \
    size_t starting = binary->currentSize; \
    { code } \
    \
    size_t ending = binary->currentSize;\
    if (compileParams->lstFile != NULL){\
    fprintf(compileParams->lstFile, "%-5zu -> %5zu | ", starting + binary->codeOffset, ending + binary->codeOffset - 1);\
    fprintf(compileParams->lstFile, "%-3zu | ", ending - starting);\
    char* dumpedOp = (char*)calloc(50, 1);\
    char* curPtr = dumpedOp;\
    sprintf(curPtr, "%s  ", argv[0]);\
    curPtr += strlen(argv[0]) + 1;\
    for (int i = 1; i < argc; i++) {sprintf(curPtr, "<%s>", argv[i]); curPtr += strlen(argv[i]) + 1;}\
    fprintf(compileParams->lstFile, "%-25s | ", dumpedOp);\
    free(dumpedOp);\
    DUMPCODEBLOCKHEX\
    fprintf(compileParams->lstFile, "\n");}\
}

#define APPENDDATA(pointer, size) appendToBinFile(binary, (void*)(pointer), size)

#define APPENDCHAR(data) appendToBinFile(binary, (char)(data))

#define JUSTCOMMAND  LSTDUMPED({ APPENDCHAR(thou->code); }) return SPU_CTB_OK;

#define SETLABELPOS if (compileParams->labelsStore != NULL) compileParams->labelsStore->setLabelFromPosition((char*)argv[1], (unsigned int)binary->currentSize)

#define GETLABELPOS (int)(compileParams->labelsStore->getLabelToPosition((char*)argv[1])) - (int)(binary->currentSize) + 1

#define ZEROORREGISTERNO LSTDUMPED({{\
APPENDCHAR(thou->code);\
if (argc == 1) {\
    APPENDCHAR(0);\
} else {\
    const char* firstArgument = argv[1];\
    APPENDCHAR(1);\
    \
    int registerNo = registerNoFromName((char*)firstArgument);\
    if (registerNo == -1)\
        return SPU_CTB_UNKNOWN_REGISTER;\
    \
    char registerNoCh = (char)registerNo;\
    APPENDDATA(&registerNoCh, sizeof(registerNoCh));\
}}}) return SPU_CTB_OK;\

