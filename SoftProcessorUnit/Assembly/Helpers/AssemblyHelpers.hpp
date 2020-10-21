//
//  AssemblyHelpers.hpp
//  SPUAsm
//
//  Created by Александр Дремов on 12.10.2020.
//

#ifndef AssemblyHelpers_hpp
#define AssemblyHelpers_hpp
#include <stdlib.h>
#include <stdio.h>
#include "AssemblyDTypes.hpp"
#include "LabelsStore.hpp"

int parseArgs(int argc, const char* argv[], AssemblyParams* params);

BinaryFile* NewBinaryFile();

int appendToBinFile(BinaryFile* binFile, void* block, size_t size);

int appendToBinFile(BinaryFile* binFile, char block);

int appendToBinFile(BinaryFile* binFile, double block);

int flushBinFile(BinaryFile* binFile, FILE* output);

int resizeBinFile(BinaryFile* binFile, size_t spaceNeeded);

BinFileLoadResult loadBinFile(BinaryFile* binFile, FILE* inputFile);

int commandParse (BinaryFile* binFile, char* command);

void DestructBinaryFile(BinaryFile* binFile);

void DestructAssemblyParams(AssemblyParams* params);

void printAssemblyHelpData(void);

void printAssemblyVersion(AssemblyParams* params);

#endif /* AssemblyHelpers_hpp */
