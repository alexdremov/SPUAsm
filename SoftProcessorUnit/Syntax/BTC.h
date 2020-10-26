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
        ADDSPI(1);
        ComplexValue val = {};
        ComplexValueResult valResult = retrieveComplexValue(SPI, &val);
        COMPLEXVALOK;
        renderComplexValue(&val, params->outputFile);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(pop, {
    OPBACKGENERAL({
        ADDSPI(1);
        ComplexValue val = {};
        ComplexValueResult valResult = retrieveComplexValue(SPI, &val);
        if (valResult == SPU_CV_NOARG)
            return SPU_DISASM_OK;
        COMPLEXVALOK;
        renderComplexValue(&val, params->outputFile);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(in, {
    OPBACKGENERAL({
        ADDSPI(1);
        ComplexValue val = {};
        ComplexValueResult valResult = retrieveComplexValue(SPI, &val);
        if (valResult == SPU_CV_NOARG)
            return SPU_DISASM_OK;
        COMPLEXVALOK;
        renderComplexValue(&val, params->outputFile);
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

OPBACKTRANSLATE_FUNC(hlt, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(out, {
    OPBACKGENERAL({
        ADDSPI(1);
        ComplexValue val = {};
        ComplexValueResult valResult = retrieveComplexValue(SPI, &val);
        if (valResult == SPU_CV_NOARG)
            return SPU_DISASM_OK;
        COMPLEXVALOK;
        renderComplexValue(&val, params->outputFile);
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
        ADDSPI(1);
        ComplexValue val = {};
        ComplexValueResult valResult = retrieveComplexValue(SPI, &val);
        if (valResult == SPU_CV_NOARG)
            return SPU_DISASM_OK;
        COMPLEXVALOK;
        renderComplexValue(&val, params->outputFile);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(dec, {
    OPBACKGENERAL({
        ADDSPI(1);
        ComplexValue val = {};
        ComplexValueResult valResult = retrieveComplexValue(SPI, &val);
        if (valResult == SPU_CV_NOARG)
            return SPU_DISASM_OK;
        COMPLEXVALOK;
        renderComplexValue(&val, params->outputFile);
    })
    return SPU_DISASM_OK;
})


OPBACKTRANSLATE_FUNC(call, {
    OPBACKGENERAL({
        char* localSPI = *SPI;
        int* val = (int*)(localSPI + 1);
        fprintf(params->outputFile, "%d", *val);
        ADDSPI(5);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(ret, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(mov, {
    OPBACKGENERAL({
        ADDSPI(1);
        ComplexValue val = {};
        ComplexValueResult valResult = retrieveComplexValue(SPI, &val);
        COMPLEXVALOK;
        renderComplexValue(&val, params->outputFile);
        valResult = retrieveComplexValue(SPI, &val);
        COMPLEXVALOK;
        renderComplexValue(&val, params->outputFile);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(rend, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(slp, {
    OPBACKGENERAL({
        ADDSPI(1);
        ComplexValue val = {};
        ComplexValueResult valResult = retrieveComplexValue(SPI, &val);
        COMPLEXVALOK;
        renderComplexValue(&val, params->outputFile);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(abs, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(pixset, {
    OPBACKGENERAL({
        ADDSPI(1);
        ComplexValue val = {};
        ComplexValueResult valResult = retrieveComplexValue(SPI, &val);
        COMPLEXVALOK;
        renderComplexValue(&val, params->outputFile);
        valResult = retrieveComplexValue(SPI, &val);
        COMPLEXVALOK;
        renderComplexValue(&val, params->outputFile);
        valResult = retrieveComplexValue(SPI, &val);
        COMPLEXVALOK;
        renderComplexValue(&val, params->outputFile);
    })
    return SPU_DISASM_OK;
})

OPBACKTRANSLATE_FUNC(clrscr, {
    OPBACKGENERAL({
        INCSPI;
    })
    return SPU_DISASM_OK;
})
