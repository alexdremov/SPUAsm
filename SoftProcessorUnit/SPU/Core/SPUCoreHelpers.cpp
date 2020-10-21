//
//  SPUCoreHelpers.cpp
//  SPU
//
//  Created by Александр Дремов on 14.10.2020.
//

#include "SPUCoreHelpers.hpp"
#include "SPUCore.hpp"
#include "SPUVersion.hpp"
#include <string.h>

int parseSPUArgs(RunParameters* parameters, int argc, const char * argv[]) {
    RunParameters newParams = {0, 0, 0, 0, 0};
    
    if (argc <= 1){
        spuHelp();
        return EXIT_FAILURE;
    }
    
    for(int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--input") == 0) {
            if (i + 1 > argc){
                printf("error: spu: No input file specified after --input\n");
                return EXIT_FAILURE;
            }
            FILE* inputFile = fopen(argv[i + 1], "rb");
            newParams.inputFile = inputFile;
            newParams.inputFileName = *(argv + i + 1);
            if (newParams.inputFile == NULL){
                printf("error: spu: Can't open input file\n");
                return EXIT_FAILURE;
            }
            i++;
        }else if (strcmp(argv[i], "--output") == 0) {
            if (i + 1 > argc){
                printf("error: spu: No output file specified after --output\n");
                return EXIT_FAILURE;
            }
            FILE* outputFile = fopen(argv[i + 1], "wb");
            newParams.outputFile = outputFile;
            newParams.outputFileName = *(argv + i + 1);
            i++;
        }else if (strcmp(argv[i], "--verbose") == 0) {
            newParams.verbose = 1;
        }else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            spuHelp();
        }else {
            if (newParams.inputFile == NULL){
                FILE* inputFile = fopen(argv[i], "rb");
                newParams.inputFile = inputFile;
                newParams.inputFileName = *(argv + i);
                if (newParams.inputFile == NULL){
                    printf("error: spu: Can't open input file %s\n", argv[i]);
                    return EXIT_FAILURE;
                }
            }
        }
    }
    
    if (newParams.inputFile == NULL) {
        printf("error: spu: No input file specified\n");
        return EXIT_FAILURE;
    }
    
    if (newParams.outputFile == NULL) {
        newParams.outputFile = stdout;
        newParams.outputFileName = "stdout";
    }
    
    *parameters = newParams;
    return EXIT_SUCCESS;
}

void spuHelp(void) {
    int SPUAssemblyVersion = SPU_VERSION;
    char* SPUAssemblyVersion_chars = (char*)&SPUAssemblyVersion;
    printf("SPU v%c.%c.%c%c help\n"
           "--input     <input file> input file to be assembled .spub format (spu binary)\n"
           "--output    <output file> output file stdout by default\n"
           "-h, --help  show this help message\n"
           "--verbose   output debug information to the console\n"
           "\n",
           SPUAssemblyVersion_chars[0],
           SPUAssemblyVersion_chars[1],
           SPUAssemblyVersion_chars[2],
           SPUAssemblyVersion_chars[3]);
}

void DestructSPUArgs(RunParameters* parameters) {
    fclose(parameters->inputFile);
    fclose(parameters->outputFile);
}
