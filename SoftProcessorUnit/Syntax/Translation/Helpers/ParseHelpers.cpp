//
//  ParseHelpers.cpp
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 22.10.2020.
//

#include "ParseHelpers.hpp"
#include "CommandsParser.hpp"
#include "SPUDtypes.hpp"
#include <cstring>

double getDoubleFromBuffer(char* start) {
    double value = 0;
    memcpy(&value, start, sizeof(double));
    return value;
}

int getIntFromBuffer(char* start) {
    int value = 0;
    memcpy(&value, start, sizeof(int));
    return value;
}

ComplexValueResult retrieveComplexValue(SPUCore* core, char** SPI, double* value) {
    ComplexValue cvalue = retrieveComplexValueFromFlow(*SPI);
    
    if (cvalue.success != SPU_CV_OK)
        return cvalue.success;
    
    *SPI += 1;
    
    double tmpVal = 0;
    
    if ((cvalue.argMask & 1) == 1){
        tmpVal += cvalue.value;
        *SPI += sizeof(cvalue.value);
    }
    
    if ((cvalue.argMask & 2) == 2){
        tmpVal += core->REG[(int)cvalue.reg];
        *SPI += 1;
    }
    
    if ((cvalue.argMask & 4) == 4){
        tmpVal = core->RAM[(int)tmpVal];
    }else if ((cvalue.argMask & 8) == 8){
        tmpVal = (double)((char*)core->RAM)[(int)tmpVal];
    }
    
    *value = tmpVal;
    
    return SPU_CV_OK;
}

int complexValueAssignable(ComplexValue* value) {
//    printf("double adress: %d\n", (value->argMask & 4) == 4);
//    printf("char adress: %d\n", (value->argMask & 8) == 8);
//    printf("reg: %d\n", (value->argMask & 2) == 2);
//    printf("val: %d\n", (value->argMask & 1) == 1);
    if (((value->argMask & 4) == 4) || ((value->argMask & 8) == 8)
        || ((value->argMask & 2) == 2 && (value->argMask & 1) == 0)){
        return 1;
    }
    return 0;
}

ComplexValueResult pointerToComplexValue(SPUCore* core, char** SPI, char** value, ComplexValue* cvalue) {
    *cvalue = retrieveComplexValueFromFlow(*SPI);
    *SPI += 1;
    
    if (cvalue->success != SPU_CV_OK)
        return cvalue->success;
    
    if (!complexValueAssignable(cvalue)){
        return SPU_CV_NONASSIGNABLE;
    }
    
    double tmpVal = 0;
    
    if ((cvalue->argMask & 1) == 1){
        tmpVal += cvalue->value;
        *SPI += sizeof(cvalue->value);
    }
    
    if ((cvalue->argMask & 2) == 2){
        tmpVal += core->REG[(int)cvalue->reg];
        *SPI += 1;
    }
    
    if ((cvalue->argMask & 4) == 4){
        *value = (char*)(core->RAM + (int)tmpVal);
    } else if ((cvalue->argMask & 8) == 8){
        *value = ((char*)core->RAM) + (int)tmpVal;
    } else {
        *value = (char*)(core->REG + cvalue->reg);
    }
    
    return SPU_CV_OK;
}

ComplexValueResult pointerToComplexValue(SPUCore* core, char** SPI, double** value, ComplexValue* cvalue) {
    return pointerToComplexValue(core, SPI, (char**)value, cvalue);
}

int charAdress(ComplexValue* value) {
    return (value->argMask & 8) == 8;
}
