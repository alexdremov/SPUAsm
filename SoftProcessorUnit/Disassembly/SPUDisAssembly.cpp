//
//  SPUDisAssembly.cpp
//  Disassembly
//
//  Created by Александр Дремов on 12.10.2020.
//

#include <stdio.h>
#include "AssemblyHelpers.hpp"
#include "DisAssemblyDTypes.hpp"
#include "DisAssemblyHelpers.hpp"


int main(int argc, const char **argv) {
    BinaryFile* binary = NewBinaryFile();
    DisassemblyParams parameters = {};
    
    int parsingResult = parseArgs(argc, argv, &parameters);
    
    if (parsingResult != EXIT_SUCCESS) {
        printf("error: disassembly: process finished with EXIT_FAILURE code\n");
        return EXIT_FAILURE;
    }
    
    BinFileLoadResult result = loadBinFile(binary, parameters.inputFile);
    
    if (result != SPU_BINLOAD_OK) {
        switch (result) {
            case SPU_BINLOAD_WRONG_VERSION:
                printf("error: disassembly: binary version is not aligned with current build\n");
                break;
                
            case SPU_BINLOAD_CORRUPTED:
                printf("error: disassembly: file structure corrupted\n");
                break;
            case SPU_BINLOAD_WRONG_SIGNATURE:
                printf("error: disassembly: file signature is wrong\n");
                break;
            case SPU_BINLOAD_OK:
                break;
        }
        DestructBinaryFile(binary);
        DestructDisAssemblyParams(&parameters);
        return EXIT_FAILURE;
    } else {
        if (parameters.verbose) {
            char* SPUAssemblyVersion_chars = (char*)&(binary->version);
            printf("info: disassembly: successfully loaded file\n");
            printf("info: disassembly: specified version v%c.%c.%c%c\n",
                   SPUAssemblyVersion_chars[0],
                   SPUAssemblyVersion_chars[1],
                   SPUAssemblyVersion_chars[2],
                   SPUAssemblyVersion_chars[3]);
            
            printf("info: Scanned code:\n");
            for (size_t i = 0; i < binary->currentSize; i++) {
                printf("%d ", (unsigned char)binary->code[i]);
            }
            printf("\n");
        }
    }
    
    SyntaxMapping syntax = getSyntaxMapping();
    
    DisassemblyParseResult res = disAssamblyCode(&parameters, &syntax, binary);
    if (res != SPU_DISASM_OK){
        printf("error: disassembly: disassambly terminated with code ");
        switch (res) {
            case SPU_DISASM_OK:
                printf("SPU_DISASM_OK\n");
                break;
            case SPU_DISASM_UNKNOWN_CMD:
                printf("SPU_DISASM_UNKNOWN_CMD\n");
                break;
            case SPU_DISASM_WRONG_CMDFORMAT:
                printf("SPU_DISASM_WRONG_CMDFORMAT\n");
                break;
            case SPU_DISASM_NOTENOUGHARGS:
                printf("SPU_DISASM_NOTENOUGHARGS\n");
                break;
        }
        DestructBinaryFile(binary);
        DestructDisAssemblyParams(&parameters);
        return EXIT_FAILURE;
    }

    DestructBinaryFile(binary);
    DestructDisAssemblyParams(&parameters);
    return 0;
}
