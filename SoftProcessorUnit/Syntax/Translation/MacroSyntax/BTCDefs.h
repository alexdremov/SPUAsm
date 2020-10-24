//
//  BTCDefs.h
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 19.10.2020.
//

#ifndef BTCDefs_h
#define BTCDefs_h

#include "ParseHelpers.hpp"

#define OPBACKGENERAL(code) { \
fprintf(params->outputFile, "%s ", thou->naming);\
if (checkBytesEnough(thou, binary, *SPI) == 0) {return SPU_DISASM_NOTENOUGHARGS;}\
code \
fprintf(params->outputFile, "\n"); }

#define ADDSPI(n) (*SPI) += n
#define MOVSPI(n) (*SPI) = n
#define INCSPI (*SPI)++

int checkBytesEnough(const SyntaxEntity* thou, BinaryFile* binary, char* SPI);

int checkBytesEnoughNumber(BinaryFile* binary, const char* SPI, size_t bytes);

#undef COMPLEXVALOK
#define COMPLEXVALOK switch(valResult) { \
case SPU_CV_WRONGSTRUCT: \
return SPU_DISASM_WRONG_CMDFORMAT;\
case SPU_CV_WRONGREG: \
return SPU_DISASM_WRONG_CMDFORMAT; \
case SPU_CV_WRONGNUM: \
return SPU_DISASM_WRONG_CMDFORMAT; \
case SPU_CV_WRONGOP: \
return SPU_DISASM_WRONG_CMDFORMAT; \
case SPU_CV_NOARG:\
return SPU_DISASM_WRONG_CMDFORMAT; \
case SPU_CV_OK: \
break;\
} \



#endif /* BTCDefs_h */
