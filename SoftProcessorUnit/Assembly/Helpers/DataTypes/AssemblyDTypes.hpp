//
//  AssemblyDTypes.h
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 13.10.2020.
//

#ifndef AssemblyDTypes_h
#define AssemblyDTypes_h

#include "LabelsStore.hpp"
#include "ParseHelpers.hpp"

struct AssemblyParams {
    FILE* inputFile;
    const char* inputFileName;
    char* inputFileRealName;
    
    FILE* outputFile;
    const char* outputFileName;
    
    FILE* lstFile;
    const char* lstFileName;
    
    FILE* prepFile;
    const char* prepFileName;
    
    char* codeText;
    
    JMPLabelsStore* labelsStore;
    
    int   verbose;
};

struct BinaryFile {
    short int  prepend;
    int        version;
    int        signature;
    size_t     stackSize;
    size_t     currentSize;
    
    // code
    char*      code;
    
    // unrecorded
    size_t     maxSize;
    size_t     codeOffset;
};

struct ComplexValue {
    double value;
    char reg;
    char argMask;
    ComplexValueResult success;
};

enum BinFileLoadResult{
    SPU_BINLOAD_OK              = 500,
    SPU_BINLOAD_WRONG_VERSION   = 501,
    SPU_BINLOAD_WRONG_SIGNATURE = 502,
    SPU_BINLOAD_CORRUPTED       = 503
};

enum LabelParse {
    SPU_LABEL_DUBLICATE         = 900,
    SPU_LABEL_OK                = 901,
    SPU_LABEL_NOTFOUND          = 902,
    SPU_LABEL_INVALID           = 903
};

int complexValueAssignable(ComplexValue* value);

int charAdress(ComplexValue* value);

ComplexValueResult retrieveComplexValue(SPUCore* core, char** SPI, double* value);

ComplexValueResult pointerToComplexValue(SPUCore* core, char** SPI, char** value, ComplexValue* cvalue);

ComplexValueResult pointerToComplexValue(SPUCore* core, char** SPI, double** value, ComplexValue* cvalue);

#endif /* AssemblyDTypes_h */
