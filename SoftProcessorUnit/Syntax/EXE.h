//
//  EXE.h
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 19.10.2020.
//

#include <ctime>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wchar-subscripts"

// (SPUCore* core, RunParameters* params, BinaryFile* binary, char** SPI)

OPEXE_FUNC(push,  {
    if (!HASBYTES(3))
        return SPU_EXE_NOARGS;
    double value = 0;
    ADDSPI(1);
    ComplexValueResult val = retrieveComplexValue(core, SPI, &value);
    
    COMPLEXVALOK;
    
    StackRigidOperationCodes result = PUSH(value);
    
    STACKRESULT
    return SPU_EXE_OK;
})

OPEXE_FUNC(out,  {
    if (!HASBYTES(2))
        return SPU_EXE_NOARGS;
    
    double value = 0;
    ADDSPI(1);
    ComplexValueResult val = retrieveComplexValue(core, SPI, &value);
    
    if (val == SPU_CV_NOARG){
        StackRigidOperationCodes result = StackBack(core->stack, &value);
        STACKRESULT
        ADDSPI(1);
//        printf("off: %d\n", (int)(*SPI - binary->code));
        printf("%lf\n", value);
        return SPU_EXE_OK;
    }
    COMPLEXVALOK;
    
    printf("%lf\n", value);

    return SPU_EXE_OK;
})


OPEXE_FUNC(pop,  {
    if (!HASBYTES(2))
        return SPU_EXE_NOARGS;
    double* valueTo = nullptr;
    ComplexValue cvalue = {};
    ADDSPI(1);
    ComplexValueResult val = pointerToComplexValue(core, SPI, &valueTo, &cvalue);
    
    if (val == SPU_CV_NOARG){
        double value = 0;
        StackRigidOperationCodes result = POP(&value);
        STACKRESULT;
        return SPU_EXE_OK;
    }
    
    COMPLEXVALOK;
    
    double value = 0;
    StackRigidOperationCodes result = POP(&value);
    STACKRESULT;
    
    if(charAdress(&cvalue)){
        *((char*)valueTo) = (char)value;
    } else {
        *valueTo = value;
    }
    
    return SPU_EXE_OK;
})


OPEXE_FUNC(in,  {
    if (!HASBYTES(2))
        return SPU_EXE_NOARGS;
    double newVal = 0;
    printf("Requested value: ");
    int scanned = scanf("%lg", &newVal);
    if (scanned <= 0){
        return SPU_EXE_INVALIDINPUT;
    }
    double* valueTo = nullptr;
    ComplexValue cvalue = {};
    ADDSPI(1);
    ComplexValueResult val = pointerToComplexValue(core, SPI, &valueTo, &cvalue);
    
    if (val == SPU_CV_NOARG){
        StackRigidOperationCodes result = PUSH(newVal);
        STACKRESULT;
        return SPU_EXE_OK;
    }
    
    COMPLEXVALOK;
    
    if(charAdress(&cvalue)){
        *((char*)valueTo) = (char)newVal;
    } else {
        *valueTo = newVal;
    }
    
    return SPU_EXE_OK;
})


OPEXE_FUNC(dump,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    StackDump(core->stack, -1, params->inputFileName, "dump requested");
    INCSPI;
    return SPU_EXE_OK;
})


OPEXE_FUNC(clear,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    StackRigidOperationCodes result = StackClear(core->stack);
    STACKRESULT
    INCSPI;
    return SPU_EXE_OK;
})


OPEXE_FUNC(add,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    
    double left = 0;
    double right = 0;
    
    StackRigidOperationCodes result = POP(&right);
    STACKRESULT
    result = POP(&left);
    STACKRESULT
    result = PUSH(left + right);
    STACKRESULT
    INCSPI;
    return SPU_EXE_OK;
})


OPEXE_FUNC(sub,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    
    double left = 0;
    double right = 0;
    StackRigidOperationCodes result = POP(&right);
    
    STACKRESULT
    
    result = POP(&left);
    STACKRESULT
    
    result = PUSH(left - right);
    STACKRESULT
    INCSPI;
    return SPU_EXE_OK;
})


OPEXE_FUNC(mul,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    double left = 0;
    double right = 0;
    StackRigidOperationCodes result = POP(&right);
    
    STACKRESULT
    
    result = POP(&left);
    
    STACKRESULT
    
    result = PUSH(left * right);
    STACKRESULT
    INCSPI;
    return SPU_EXE_OK;
})


OPEXE_FUNC(div,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    double left = 0;
    double right = 0;
    StackRigidOperationCodes result = POP(&right);
    
    STACKRESULT
    
    result = POP(&left);
    
    STACKRESULT
    
    result = PUSH(left / right);
    STACKRESULT
    INCSPI;
    return SPU_EXE_OK;
})


OPEXE_FUNC(sin,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    double left = 0;
    StackRigidOperationCodes result = POP(&left);
    STACKRESULT

    result = PUSH(sin(left));
    STACKRESULT
    INCSPI;
    return SPU_EXE_OK;
})


OPEXE_FUNC(cos,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    double left = 0;
    StackRigidOperationCodes result = POP(&left);
    STACKRESULT
    
    result = PUSH(cos(left));
    STACKRESULT
    INCSPI;
    return SPU_EXE_OK;
})


OPEXE_FUNC(sqrt,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    double left = 0;
    StackRigidOperationCodes result = POP(&left);
    STACKRESULT
    
    result = PUSH(sqrt(left));
    STACKRESULT
    INCSPI;
    return SPU_EXE_OK;
})


OPEXE_FUNC(pow,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    double left = 0;
    double right = 0;
    StackRigidOperationCodes result = POP(&right);
    STACKRESULT
    result = POP(&left);
    STACKRESULT
    
    result = PUSH(pow(left, right));
    STACKRESULT
    INCSPI;
    return SPU_EXE_OK;
})


OPEXE_FUNC(hlt,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    core->terminated = 1;
    INCSPI;
    return SPU_EXE_OK;
})


OPEXE_FUNC(jmp,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    ADDSPI(getIntFromBuffer(localSPI + 1));
    return SPU_EXE_OK;
})

OPEXE_FUNC(jb,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    
    double left = 0;
    double right = 0;
    StackRigidOperationCodes result = StackPop(&(core->stack), &right);
    STACKRESULT
    result = StackPop(&(core->stack), &left);
    STACKRESULT
    if (left < right)
        ADDSPI(getIntFromBuffer(localSPI + 1));
    else
        ADDSPI(5);
    return SPU_EXE_OK;
})

OPEXE_FUNC(jbe,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    double left = 0;
    double right = 0;
    StackRigidOperationCodes result = POP(&right);
    STACKRESULT
    result = POP(&left);
    STACKRESULT
    if (left <= right)
        ADDSPI(getIntFromBuffer(localSPI + 1));
    else
        ADDSPI(5);
    return SPU_EXE_OK;
})

OPEXE_FUNC(je,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    double left = 0;
    double right = 0;
    StackRigidOperationCodes result = POP(&right);
    STACKRESULT
    result = POP(&left);
    STACKRESULT
    if (left == right)
        ADDSPI(getIntFromBuffer(localSPI + 1));
    else
        ADDSPI(5);
    return SPU_EXE_OK;
})

OPEXE_FUNC(jne,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    double left = 0;
    double right = 0;
    StackRigidOperationCodes result = POP(&right);
    STACKRESULT
    result = POP(&left);
    STACKRESULT
    if (left != right)
        ADDSPI(getIntFromBuffer(localSPI + 1));
    else
        ADDSPI(5);
    return SPU_EXE_OK;
})

OPEXE_FUNC(ja,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    double left = 0;
    double right = 0;
    StackRigidOperationCodes result = POP(&right);
    STACKRESULT
    result = POP(&left);
    STACKRESULT
    if (left > right)
        ADDSPI(getIntFromBuffer(localSPI + 1));
    else
        ADDSPI(5);
    return SPU_EXE_OK;
})

OPEXE_FUNC(jae,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    double left = 0;
    double right = 0;
    StackRigidOperationCodes result = POP(&right);
    STACKRESULT
    result = POP(&left);
    STACKRESULT
    if (left >= right)
        ADDSPI(getIntFromBuffer(localSPI + 1));
    else
        ADDSPI(5);
    return SPU_EXE_OK;
})

OPEXE_FUNC(jm,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int d    = tm.tm_mday;
    int m    = tm.tm_mon + 1;
    int y    = tm.tm_year + 1900;

    int weekday  = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;
    
    if (weekday == 1)
        ADDSPI(getIntFromBuffer(localSPI + 1));
    else
        ADDSPI(5);
    return SPU_EXE_OK;
})

OPEXE_FUNC(inc,  {
    if (!HASBYTES(2))
        return SPU_EXE_NOARGS;
    double* valueTo = nullptr;
    ComplexValue cvalue = {};
    ADDSPI(1);
    ComplexValueResult val = pointerToComplexValue(core, SPI, &valueTo, &cvalue);
    
    if (val == SPU_CV_NOARG){
        double value = 0;
        StackRigidOperationCodes result = POP(&value);
        STACKRESULT;
        result = PUSH(value + 1);
        STACKRESULT;
        return SPU_EXE_OK;
    }
    
    COMPLEXVALOK;
    
    double value = *valueTo + 1;
    
    if(charAdress(&cvalue)){
        *((char*)valueTo) = (char)value;
    } else {
        *valueTo = value;
    }
    
    return SPU_EXE_OK;
})

OPEXE_FUNC(dec,  {
    if (!HASBYTES(2))
        return SPU_EXE_NOARGS;
    double* valueTo = nullptr;
    ComplexValue cvalue = {};
    ADDSPI(1);
    ComplexValueResult val = pointerToComplexValue(core, SPI, &valueTo, &cvalue);
    
    if (val == SPU_CV_NOARG){
        double value = 0;
        StackRigidOperationCodes result = POP(&value);
        STACKRESULT;
        result = PUSH(value - 1);
        STACKRESULT;
        return SPU_EXE_OK;
    }
    
    COMPLEXVALOK;
    
    double value = *valueTo - 1;
    
    if(charAdress(&cvalue)){
        *((char*)valueTo) = (char)value;
    } else {
        *valueTo = value;
    }
    
    return SPU_EXE_OK;
})


OPEXE_FUNC(call,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    StackRigidOperationCodes result = callPUSH((int)(localSPI - binary->code) + 5);
    STACKRESULT;
    ADDSPI(getIntFromBuffer(localSPI + 1));
    return SPU_EXE_OK;
})

OPEXE_FUNC(ret,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    double offset = 0;
    StackRigidOperationCodes result = callPOP(&offset);
    STACKRESULT;
//    printf("%d\n", (int)offset);
    MOVSPI(binary->code + (int)offset);
    return SPU_EXE_OK;
})

#pragma clang diagnostic pop
