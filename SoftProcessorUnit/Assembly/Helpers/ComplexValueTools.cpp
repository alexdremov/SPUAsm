//
//  ComplexValueTools.cpp
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 24.10.2020.
//

#include "ComplexValueTools.hpp"
#include "CommandsDTypes.hpp"
#include "AssemblyHelpers.hpp"
#include "Syntax.hpp"
#include <ctype.h>
#include <cstring>

ComplexValue retrieveComplexValueFromArg(char* argument){
    ComplexValue result = {0,0,0, SPU_CV_OK};
    result.success = SPU_CV_OK;
    
    int size = (int)strlen(argument);
    
    char argMask = 0;
    
    char* ramFound = strchr(argument, '[');
    char* closeBrackRam = nullptr;
    if (ramFound != nullptr){
        argMask |= (char)4;
        argument++;
        closeBrackRam = strchr(argument, ']');
        if (closeBrackRam == nullptr){
            result.success = SPU_CV_WRONGSTRUCT;
            return result;
        }
        *closeBrackRam = '\0';
    }
    
    char* vidFound = strchr(argument, '(');
    char* closeBrackVid = nullptr;
    if (vidFound != nullptr){
        argMask |= (char)8;
        argument++;
        closeBrackVid = strchr(argument, ')');
        if (closeBrackVid == nullptr){
            result.success = SPU_CV_WRONGSTRUCT;
            return result;
        }
        *closeBrackVid = '\0';
    }
    size = (int)strlen(argument);
    if (size == 0){
        result.success = SPU_CV_WRONGSTRUCT;
        return result;
    }
    
    // Try finding register
    if (size >= 3) {
        char tmpThird = *(argument + 3);
        *(argument + 3) = '\0';
        int regNo = registerNoFromName(argument);
        *(argument + 3) = tmpThird;
        if (regNo != -1) {
            result.reg = (char)regNo;
            argMask |= (char)2;
            if (tmpThird == '+' || tmpThird == '-'){
                double value = 0;
                if (size >= 4){
                    int scanfRes = sscanf(argument + 4, "%lg", &value);
                    if (scanfRes == -1) {
                        result.success = SPU_CV_WRONGSTRUCT;
                        return result;
                    } else {
                        result.value += value * ((tmpThird == '-')? -1: 1);
                        argMask |= (char)1;
                    }
                } else {
                    result.success = SPU_CV_WRONGOP;
                    return result;
                }
            }else if (tmpThird != '\0'){
                result.success = SPU_CV_WRONGREG;
                return result;
            }
        } else {
            
            double value = 0;
            int scanfRes = sscanf(argument, "%lg", &value);
            if (scanfRes <= 0) {
                result.success = SPU_CV_WRONGSTRUCT;
                return result;
            } else {
                result.value += value;
                argMask |= (char)1;
            }
            
        }
    } else {
        double value = 0;
        int scanfRes = sscanf(argument, "%lg", &value);
        if (scanfRes <= 0) {
            result.success = SPU_CV_WRONGSTRUCT;
            return result;
        } else {
            result.value += value;
            argMask |= (char)1;
        }
    }
    
    if (closeBrackVid != nullptr){
        *closeBrackVid = ')';
    }

    if (closeBrackRam != nullptr){
        *closeBrackRam = ']';
    }
    
    result.argMask = argMask;
    
    return result;
}

void writeComplexArg(ComplexValue* cvalue, BinaryFile* binary) {
    appendToBinFile(binary, cvalue->argMask);
    
    if ((cvalue->argMask & 1) == 1){
        appendToBinFile(binary, &(cvalue->value), sizeof(cvalue->value));
    }
    
    if ((cvalue->argMask & 2) == 2){
        appendToBinFile(binary, &(cvalue->reg), sizeof(cvalue->reg));
    }
}

ComplexValue retrieveComplexValueFromFlow(char* SPI) {
    ComplexValue result = {0,0,0,SPU_CV_OK};
    result.success = SPU_CV_OK;
    
    char argMask = *SPI;
    
    result.argMask = argMask;
    
    SPI += 1;
    
    if (argMask == 0) {
        result.success = SPU_CV_NOARG;
        return result;
    }
    
    if ((argMask & 1) == 1){
        memcpy(&(result.value), SPI, sizeof(double));
        SPI += sizeof(double);
    }
    
    if ((argMask & 2) == 2){
        result.reg = *SPI;
    }
    
    return result;
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

ComplexValueResult retrieveComplexValue(char** SPI, ComplexValue* value) {
    ComplexValue cvalue = retrieveComplexValueFromFlow(*SPI);
    
    if (cvalue.success != SPU_CV_OK)
        return cvalue.success;
    
    *SPI += 1;
    
    if ((cvalue.argMask & 1) == 1){
        *SPI += sizeof(cvalue.value);
    }
    
    if ((cvalue.argMask & 2) == 2){
        *SPI += 1;
    }

    
    *value = cvalue;
    
    return SPU_CV_OK;
}

int complexValueAssignable(ComplexValue* value) {
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

void renderComplexValue(ComplexValue* cvalue, FILE* output){
    if ((cvalue->argMask & 4) == 4){
        fprintf(output, "[");
    } else if ((cvalue->argMask & 8) == 8){
        fprintf(output, "(");
    }
    
    if ((cvalue->argMask & 2) == 2){
        const char* name = registerNameFromNo(cvalue->reg);
        fprintf(output, "%s", name);
    }
    
    if ((cvalue->argMask & 1) == 1){
        if (cvalue->value >= 0){
            if ((cvalue->argMask & 2) == 2)
                fprintf(output, "+");
        } else {
            fprintf(output, "-");
        }
        fprintf(output, "%lf", cvalue->value);
    }
    
    
    if ((cvalue->argMask & 4) == 4){
        fprintf(output, "]");
    } else if ((cvalue->argMask & 8) == 8){
        fprintf(output, ")");
    }
    fprintf(output, " ");
}
