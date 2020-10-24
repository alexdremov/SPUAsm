//
//  ComplexValueTools.hpp
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 24.10.2020.
//

#ifndef ComplexValueTools_hpp
#define ComplexValueTools_hpp

#include "CommandsDTypes.hpp"
#include "AssemblyHelpers.hpp"
#include "Syntax.hpp"

ComplexValue retrieveComplexValueFromArg(char* argument);

ComplexValue retrieveComplexValueFromFlow(char* SPI);

void writeComplexArg(ComplexValue* cvalue, BinaryFile* binary);

void renderComplexValue(ComplexValue* cvalue, FILE* output);

int complexValueAssignable(ComplexValue* value);

int charAdress(ComplexValue* value);

ComplexValueResult retrieveComplexValue(SPUCore* core, char** SPI, double* value);

ComplexValueResult retrieveComplexValue(char** SPI, ComplexValue* value);

ComplexValueResult pointerToComplexValue(SPUCore* core, char** SPI, char** value, ComplexValue* cvalue);

ComplexValueResult pointerToComplexValue(SPUCore* core, char** SPI, double** value, ComplexValue* cvalue);

#endif /* ComplexValueTools_hpp */
