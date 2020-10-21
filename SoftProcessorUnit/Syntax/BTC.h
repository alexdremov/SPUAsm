//
//  BTC.h
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 19.10.2020.
//


#include "BTCDefs.h"

// (const SyntaxEntity* thou, DisassemblyParams* params, BinaryFile* binary, char** SPI)

OPBACKTRANSLATE_FUNC(push, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        char flagByte = *(localSPI + 1);
        if (flagByte == 0) {
            if (!checkBytesEnoughNumber( binary, *SPI, 10)){
                return SPU_DISASM_NOTENOUGHARGS;
            }
            double value = *((double*)(localSPI + 2));
            fprintf(params->outputFile, "%lg", value);
            ADDSPI(sizeof(double) + 2);
        } else {
            const char* reg = registerNameFromNo(*(localSPI + 2));
            fprintf(params->outputFile, "%s", reg);
            ADDSPI(3);
        }
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(pop, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        char flagByte = *(localSPI + 1);
        if (flagByte == 0) {
            ADDSPI(2);
        } else {
            const char* reg = registerNameFromNo(*(localSPI + 2));
            fprintf(params->outputFile, "%s", reg);
            ADDSPI(3);
        }
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(in, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        char flagByte = *(localSPI + 1);
        if (flagByte == 0) {
            ADDSPI(2);
        } else {
            const char* reg = registerNameFromNo(*(localSPI + 2));
            fprintf(params->outputFile, "%s", reg);
            ADDSPI(3);
        }
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(dump, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(clear, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(add, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(sub, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(mul, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(div, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(sin, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(cos, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(sqrt, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(pow, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(het, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(out, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        char flagByte = *(localSPI + 1);
        if (flagByte == 0) {
            ADDSPI(2);
        } else {
            const char* reg = registerNameFromNo(*(localSPI + 2));
            fprintf(params->outputFile, "%s", reg);
            ADDSPI(3);
        }
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(jmp, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        int* val = (int*)(localSPI + 1);
        fprintf(params->outputFile, "%d", *val);
        ADDSPI(5);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(jb, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        int* val = (int*)(localSPI + 1);
        fprintf(params->outputFile, "%d", *val);
        ADDSPI(5);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(jbe, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        int* val = (int*)(localSPI + 1);
        fprintf(params->outputFile, "%d", *val);
        ADDSPI(5);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(je, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        int* val = (int*)(localSPI + 1);
        fprintf(params->outputFile, "%d", *val);
        ADDSPI(5);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(jne, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        int* val = (int*)(localSPI + 1);
        fprintf(params->outputFile, "%d", *val);
        ADDSPI(5);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(ja, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        int* val = (int*)(localSPI + 1);
        fprintf(params->outputFile, "%d", *val);
        ADDSPI(5);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(jae, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        int* val = (int*)(localSPI + 1);
        fprintf(params->outputFile, "%d", *val);
        ADDSPI(5);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(jm, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        int* val = (int*)(localSPI + 1);
        fprintf(params->outputFile, "%d", *val);
        ADDSPI(5);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(inc, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        char flagByte = *(localSPI + 1);
        if (flagByte == 0) {
            ADDSPI(2);
        } else {
            const char* reg = registerNameFromNo(*(localSPI + 2));
            fprintf(params->outputFile, "%s", reg);
            ADDSPI(3);
        }
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(dec, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        char flagByte = *(localSPI + 1);
        if (flagByte == 0) {
            ADDSPI(2);
        } else {
            const char* reg = registerNameFromNo(*(localSPI + 2));
            fprintf(params->outputFile, "%s", reg);
            ADDSPI(3);
        }
    })
    return SPU_DISASM_OK;
})
