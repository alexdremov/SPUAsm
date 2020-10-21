//
//  BTCDefs.h
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 19.10.2020.
//

#ifndef BTCDefs_h
#define BTCDefs_h

#define OPBACKGENERAL(code) { \
fprintf(params->outputFile, "%s ", thou->naming);\
if (checkBytesEnough(thou, binary, *SPI) == 0) {return SPU_DISASM_NOTENOUGHARGS;}\
code \
fprintf(params->outputFile, "\n"); }

#define ADDSPI(n) (*SPI) += n
#define MOVSPI(n) (*SPI) = n
#define INCSPI (*SPI)++

int checkBytesEnough(const SyntaxEntity* thou, BinaryFile* binary, char* SPI);

int checkBytesEnoughNumber(BinaryFile* binary, char* SPI, size_t bytes);


#endif /* BTCDefs_h */
