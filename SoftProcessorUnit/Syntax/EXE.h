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
    char* localSPI = *SPI;
    char flagByte = *(localSPI + 1);
    if(flagByte == 0){
        if (!HASBYTES(sizeof(double) + 2))
            return SPU_EXE_NOARGS;
        double value = getDoubleFromBuffer(localSPI + 2);
        StackRigidOperationCodes result = PUSH(value);
        
        STACKRESULT
        
        ADDSPI(sizeof(double) + 2);
    } else {
        char reg = *(localSPI + 2);
        
        StackRigidOperationCodes result = PUSH(core->REG[reg]);
        
        STACKRESULT
        
        ADDSPI(3);
    }
    return SPU_EXE_OK;
})


OPEXE_FUNC(pop,  {
    if (!HASBYTES(2))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    char flagByte = *(localSPI + 1);
    if (flagByte == 0) {
        double tmp = 0;
        StackRigidOperationCodes result = POP(&tmp);
        STACKRESULT
        ADDSPI(2);
    } else {
        char reg = *(localSPI + 2);
        StackRigidOperationCodes result = POP(core->REG + reg);
        STACKRESULT
        ADDSPI(3);
    }
    return SPU_EXE_OK;
})


OPEXE_FUNC(in,  {
    if (!HASBYTES(2))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    char flagByte = *(localSPI + 1);
    
    double newVal = 0;
    printf("Requested value: ");
    int scanned = scanf("%lg", &newVal);
    if (scanned == 0){
        return SPU_EXE_INVALIDINPUT;
    }
    
    if (flagByte == 0) {
        StackRigidOperationCodes result = PUSH(newVal);
        STACKRESULT
        ADDSPI(2);
    } else {
        char reg = *(localSPI + 2);
        core->REG[reg] = newVal;
        ADDSPI(3);
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


OPEXE_FUNC(het,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    core->terminated = 1;
    INCSPI;
    return SPU_EXE_OK;
})


OPEXE_FUNC(out,  {
    if (!HASBYTES(2))
        return SPU_EXE_NOARGS;
    
    char* localSPI = *SPI;
    char flagByte = *(localSPI + 1);
    if(flagByte == 0){
        double value = 0;
        StackRigidOperationCodes result = StackBack(core->stack, &value);
        
        STACKRESULT
        
        printf("%lf\n", value);
        ADDSPI(2);
    } else {
        if (!HASBYTES(3))
            return SPU_EXE_NOARGS;
        char reg = *(localSPI + 2);
        
        printf("%lf\n", core->REG[reg]);
        
        ADDSPI(3);
    }
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
    char* localSPI = *SPI;
    char flagByte = *(localSPI + 1);
    
    if (flagByte == 0) {
        double value = 0;
        StackRigidOperationCodes result = POP(&value);
        
        STACKRESULT
        
        result = PUSH(value + 1);
        
        STACKRESULT

        ADDSPI(2);
    } else {
        char reg = *(localSPI + 2);
        core->REG[reg] += 1;
        ADDSPI(3);
    }
    return SPU_EXE_OK;
})

OPEXE_FUNC(dec,  {
    if (!HASBYTES(2))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    char flagByte = *(localSPI + 1);
    
    if (flagByte == 0) {
        double value = 0;
        StackRigidOperationCodes result = POP(&value);
        
        STACKRESULT
        
        result = PUSH(value - 1);
        
        STACKRESULT

        ADDSPI(2);
    } else {
        char reg = *(localSPI + 2);
        core->REG[reg] -= 1;
        ADDSPI(3);
    }
    return SPU_EXE_OK;
})

#pragma clang diagnostic pop
