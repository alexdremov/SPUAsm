//
//  AssemblyHelpers.cpp
//  SPUAsm
//
//  Created by Александр Дремов on 12.10.2020.
//

#include <string.h>
#include <assert.h>
#include "AssemblyHelpers.hpp"
#include "CommandsParser.hpp"
#include "AssemblyDTypes.hpp"
#include "SPUVersion.hpp"

#define MAXPATHLEN 512

int parseArgs(int argc, const char* argv[], AssemblyParams* params) {
    AssemblyParams newParams = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (argc <= 1){
        printAssemblyHelpData();
    }
    
    newParams.inputFileRealName = (char*)calloc(MAXPATHLEN, 1);

    for(int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--input") == 0) {
            if (i + 1 > argc){
                printf("error: assembly: No input file specified after --input\n");
                return EXIT_FAILURE;
            }
            FILE* inputFile = fopen(argv[i + 1], "rb");
            newParams.inputFile = inputFile;
            newParams.inputFileName = *(argv + i + 1);
            realpath((const char*)newParams.inputFileName, newParams.inputFileRealName);
            if (newParams.inputFile == NULL){
                printf("error: assembly: Can't open input file %s\n", newParams.inputFileName);
                return EXIT_FAILURE;
            }
            i++;
        }else if (strcmp(argv[i], "--output") == 0) {
            if (i + 1 > argc){
                printf("error: assembly: No output file specified after --output\n");
                return EXIT_FAILURE;
            }
            FILE* outputFile = fopen(argv[i + 1], "wb");
            newParams.outputFile = outputFile;
            newParams.outputFileName = *(argv + i + 1);
            i++;
        }else if (strcmp(argv[i], "--verbose") == 0) {
            newParams.verbose = 1;
        }else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            printAssemblyHelpData();
        }else if (strcmp(argv[i], "--lstfile") == 0) {
            if (i + 1 > argc){
                printf("error: assembly: No lstfile file specified after --lstfile\n");
                return EXIT_FAILURE;
            }
            FILE* lstFile = fopen(argv[i + 1], "wb");
            newParams.lstFile = lstFile;
            newParams.lstFileName = *(argv + i + 1);
            i++;
        }else if (strcmp(argv[i], "-E") == 0) {
            newParams.prepFile = (FILE*) 1;
        } else {
            if (newParams.inputFile == NULL){
                FILE* inputFile = fopen(argv[i], "rb");
                newParams.inputFile = inputFile;
                newParams.inputFileName = *(argv + i);
                realpath((const char*)newParams.inputFileName, newParams.inputFileRealName);
                if (newParams.inputFile == NULL){
                    printf("error: assembly: Can't open input file %s\n", argv[i]);
                    return EXIT_FAILURE;
                }
            }
        }
    }
    
    if (newParams.inputFile == NULL) {
        printf("error: assembly: No input file specified\n");
        return EXIT_FAILURE;
    }
    
    if (newParams.outputFile == NULL) {
        newParams.outputFile = fopen("output.spub", "wb");
        newParams.outputFileName = "output.spub";
        if (newParams.outputFile == NULL){
            printf("error: assembly: No output file specified\n");
            return EXIT_FAILURE;
        }
    }
    
    if (newParams.lstFile == NULL) {
        newParams.lstFile = fopen("assembly.lst", "wb");
        newParams.lstFileName = "assembly.lst";
        if (newParams.lstFile == NULL){
            printf("error: assembly: No lstFile file specified\n");
            return EXIT_FAILURE;
        }
    }
    
    if (newParams.prepFile != NULL) {
        newParams.prepFile = fopen("assembly.spuprep", "wb");
        newParams.prepFileName = "assembly.spuprep";
        if (newParams.prepFileName == NULL) {
            printf("error: assembly: Can't open assembly.spuprep\n");
            return EXIT_FAILURE;
        }
    }
    
    newParams.labelsStore = new JMPLabelsStore();
    *params = newParams;
    
    return EXIT_SUCCESS;
}


BinaryFile* NewBinaryFile(){
    BinaryFile* newBin = (BinaryFile*)calloc(1, sizeof(BinaryFile));
    newBin->code = (char*)calloc(256, sizeof(char));
    
    newBin->currentSize = 0;
    newBin->maxSize     = 256;
    newBin->prepend     = SPU_BIN_PREPEND;
    newBin->version     = SPU_VERSION;
    newBin->signature   = SPU_SIGNATURE;
    newBin->codeOffset  = sizeof(newBin->prepend) +
                          sizeof(newBin->version) +
                          sizeof(newBin->signature) +
                          sizeof(newBin->stackSize) +
                          sizeof(newBin->currentSize);
    
    return newBin;
}


int appendToBinFile(BinaryFile* binFile, void* block, size_t size) {
    int resizeResult = resizeBinFile(binFile, size + 1);
    if (resizeResult != EXIT_SUCCESS)
        return resizeResult;
    
    memcpy(binFile->code + binFile->currentSize, block, size);
    
    (binFile->currentSize) += size;
    
    return EXIT_SUCCESS;
}

int appendToBinFile(BinaryFile* binFile, char block) {
    int resizeResult = resizeBinFile(binFile, 2);
    if (resizeResult != EXIT_SUCCESS)
        return resizeResult;
    
    binFile->code[binFile->currentSize] = block;
    binFile->currentSize += 1;
    
    return EXIT_SUCCESS;
}

int appendToBinFile(BinaryFile* binFile, double block) {
    return appendToBinFile(binFile, (void*) &block, sizeof(double));
}

int resizeBinFile(BinaryFile* binFile, size_t spaceNeeded){
    if (binFile->currentSize + spaceNeeded >= binFile->maxSize){
        char* newCode = (char*) realloc(binFile->code, binFile->maxSize + spaceNeeded);
        if (newCode == NULL)
            return EXIT_FAILURE;
        binFile->code = newCode;
        binFile->maxSize += spaceNeeded;
    }
    return EXIT_SUCCESS;
}


void printAssemblyHelpData(void) {
    int SPUAssemblyVersion = SPU_VERSION;
    char* SPUAssemblyVersion_chars = (char*)&SPUAssemblyVersion;
    printf("SPUAssembly v%c.%c.%c%c help\n"
           "--input     <input file> input file to be assembled .spus format (spu source)\n"
           "--output    <output file> output file. output.spub by default (spu binary)\n"
           "-h, --help  show this help message\n"
           "--verbose   output assembly debug information to the console\n"
           "--lstfile   <.lst file> file to output .lst assembly data assembly.lst by default\n"
           "-E          generate preprocessed file assembly.spuprep\n"
           "\n",
           SPUAssemblyVersion_chars[0],
           SPUAssemblyVersion_chars[1],
           SPUAssemblyVersion_chars[2],
           SPUAssemblyVersion_chars[3]);
}


void DestructBinaryFile(BinaryFile* binFile) {
    assert(binFile);
    free(binFile->code);
    free(binFile);
}

void DestructAssemblyParams(AssemblyParams* params) {
    fclose(params->inputFile);
    fclose(params->lstFile);
    fclose(params->outputFile);
    free(params->inputFileRealName);
    if (params->prepFile != NULL)
        fclose(params->prepFile);
    if (params->labelsStore != NULL)
        delete params->labelsStore;
}

int flushBinFile(BinaryFile* binFile, FILE* output) {
    size_t size = binFile->currentSize;
    
    fwrite((char*)&binFile->prepend, 1, sizeof(binFile->prepend), output);
    fwrite((char*)&binFile->version, 1, sizeof(binFile->version), output);
    fwrite((char*)&binFile->signature, 1, sizeof(binFile->signature), output);
    fwrite((char*)&binFile->stackSize, 1, sizeof(binFile->stackSize), output);
    fwrite((char*)&binFile->currentSize, 1, sizeof(binFile->currentSize), output);
    
    fwrite(binFile->code, 1, size, output);
    
    return EXIT_SUCCESS;
}

BinFileLoadResult loadBinFile(BinaryFile* binFile, FILE* inputFile) {
    size_t size = 0;
    char* data = getSourceFileData(inputFile, &size);
    
    int currentVersion       = SPU_VERSION;
    int currentSignature     = SPU_SIGNATURE;
    short int currentPrepend = SPU_BIN_PREPEND;
    
    if (size < sizeof(binFile->prepend) + sizeof(binFile->signature)
                                         + sizeof(binFile->version)) {
        return SPU_BINLOAD_WRONG_SIGNATURE;
    }
    
    char* curPos = data;
    binFile->prepend    = *((short int*) curPos);
    curPos += sizeof(binFile->prepend);
    
    binFile->version    = *((int*) curPos);
    curPos += sizeof(binFile->version);
    
    binFile->signature  = *((int*) curPos);
    curPos += sizeof(binFile->signature);
    
    if (binFile->prepend != currentPrepend) {
        return SPU_BINLOAD_WRONG_SIGNATURE;
    }
    
    if (binFile->signature != currentSignature) {
        return SPU_BINLOAD_WRONG_SIGNATURE;
    }
    
    if (binFile->version != currentVersion) {
        return SPU_BINLOAD_WRONG_VERSION;
    }
    
    binFile->stackSize    = *((size_t*) curPos);
    curPos += sizeof(binFile->stackSize);
    
    binFile->currentSize    = *((size_t*) curPos);
    curPos += sizeof(binFile->currentSize);
    
    resizeBinFile(binFile, binFile->currentSize + 20);
    memcpy(binFile->code, (char*) curPos, binFile->currentSize);
    
    return SPU_BINLOAD_OK;
}


void printAssemblyVersion(AssemblyParams* params) {
    int SPUAssemblyVersion = SPU_VERSION;
    char* SPUAssemblyVersion_chars = (char*)&SPUAssemblyVersion;
    if (params->verbose) {
        
        printf("SPUAssembly v%c.%c.%c%c\n",
               SPUAssemblyVersion_chars[0],
               SPUAssemblyVersion_chars[1],
               SPUAssemblyVersion_chars[2],
               SPUAssemblyVersion_chars[3]);
    }
    
    if (params->lstFile != NULL) {
        fprintf(params->lstFile,
                "SPUAssembly v%c.%c.%c%c ",
                SPUAssemblyVersion_chars[0],
                SPUAssemblyVersion_chars[1],
                SPUAssemblyVersion_chars[2],
                SPUAssemblyVersion_chars[3]);
        fprintf(params->lstFile, "%s -> %s\n", params->inputFileName , params->outputFileName);
    }
}
