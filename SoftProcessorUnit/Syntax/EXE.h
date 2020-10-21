//
//  EXE.h
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 19.10.2020.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

// (SPUCore* core, RunParameters* params, BinaryFile* binary, char** SPI)

OPEXE_FUNC(push,  {
    if (!HASBYTES(3))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    char flagByte = *(localSPI + 1);
    if(flagByte == 0){
        if (!HASBYTES(sizeof(double) + 2))
            return SPU_EXE_NOARGS;
        double value = *((double*)(localSPI + 2));
        StackRigidOperationCodes result = StackPush(&(core->stack), value);
        
        STACKRESULT
        
        (*SPI) += sizeof(double) + 2;
    } else {
        char reg = *(localSPI + 2);
        
        StackRigidOperationCodes result = StackPush(&(core->stack), core->REG[reg]);
        
        STACKRESULT
        
        (*SPI) += 3;
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
        StackRigidOperationCodes result = StackPop(&(core->stack), &tmp);
        STACKRESULT
        (*SPI) += 2;
    } else {
        char reg = *(localSPI + 2);
        StackRigidOperationCodes result = StackPop(&(core->stack), core->REG + reg);
        STACKRESULT
        (*SPI) += 3;
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
        StackRigidOperationCodes result = StackPush(&(core->stack), newVal);
        
        STACKRESULT

        (*SPI) += 2;
    } else {
        char reg = *(localSPI + 2);
        core->REG[reg] = newVal;
        (*SPI) += 3;
    }
    return SPU_EXE_OK;
})


OPEXE_FUNC(dump,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    StackDump(core->stack, -1, params->inputFileName, "dump requested");
    (*SPI)++;
    return SPU_EXE_OK;
})


OPEXE_FUNC(clear,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    StackRigidOperationCodes result = StackClear(core->stack);
    STACKRESULT
    (*SPI)++;
    return SPU_EXE_OK;
})


OPEXE_FUNC(add,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    
    double left = 0;
    double right = 0;
    
    StackRigidOperationCodes result = StackPop(&(core->stack), &right);
    
    STACKRESULT
    
    result = StackPop(&(core->stack), &left);
    
    STACKRESULT
    
    result = StackPush(&(core->stack), left + right);
    STACKRESULT
    (*SPI)++;
    return SPU_EXE_OK;
})


OPEXE_FUNC(sub,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    
    double left = 0;
    double right = 0;
    StackRigidOperationCodes result = StackPop(&(core->stack), &right);
    
    STACKRESULT
    
    result = StackPop(&(core->stack), &left);
    STACKRESULT
    
    result = StackPush(&(core->stack), left - right);
    STACKRESULT
    (*SPI)++;
    return SPU_EXE_OK;
})


OPEXE_FUNC(mul,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    double left = 0;
    double right = 0;
    StackRigidOperationCodes result = StackPop(&(core->stack), &right);
    
    STACKRESULT
    
    result = StackPop(&(core->stack), &left);
    
    STACKRESULT
    
    result = StackPush(&(core->stack), left * right);
    STACKRESULT
    (*SPI)++;
    return SPU_EXE_OK;
})


OPEXE_FUNC(div,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    double left = 0;
    double right = 0;
    StackRigidOperationCodes result = StackPop(&(core->stack), &right);
    
    STACKRESULT
    
    result = StackPop(&(core->stack), &left);
    
    STACKRESULT
    
    result = StackPush(&(core->stack), left / right);
    STACKRESULT
    (*SPI)++;
    return SPU_EXE_OK;
})


OPEXE_FUNC(sin,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    double left = 0;
    StackRigidOperationCodes result = StackPop(&(core->stack), &left);
    STACKRESULT
    
    result = StackPush(&(core->stack), sin(left));
    STACKRESULT
    (*SPI)++;
    return SPU_EXE_OK;
})


OPEXE_FUNC(cos,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    double left = 0;
    StackRigidOperationCodes result = StackPop(&(core->stack), &left);
    STACKRESULT
    
    result = StackPush(&(core->stack), cos(left));
    STACKRESULT
    (*SPI)++;
    return SPU_EXE_OK;
})


OPEXE_FUNC(sqrt,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    double left = 0;
    StackRigidOperationCodes result = StackPop(&(core->stack), &left);
    STACKRESULT
    
    result = StackPush(&(core->stack), sqrt(left));
    STACKRESULT
    (*SPI)++;
    return SPU_EXE_OK;
})


OPEXE_FUNC(pow,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    double left = 0;
    double right = 0;
    StackRigidOperationCodes result = StackPop(&(core->stack), &right);
    STACKRESULT
    result = StackPop(&(core->stack), &left);
    STACKRESULT
    
    result = StackPush(&(core->stack), pow(left, right));
    STACKRESULT
    (*SPI)++;
    return SPU_EXE_OK;
})


OPEXE_FUNC(het,  {
    if (!HASBYTES(1))
        return SPU_EXE_NOARGS;
    core->terminated = 1;
    (*SPI)++;
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
        (*SPI) += 2;
    } else {
        if (!HASBYTES(3))
            return SPU_EXE_NOARGS;
        char reg = *(localSPI + 2);
        
        printf("%lf\n", core->REG[reg]);
        
        (*SPI) += 3;
    }
    return SPU_EXE_OK;
})

OPEXE_FUNC(jmp,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    (*SPI) += *((int*)(localSPI + 1));
    return SPU_EXE_OK;
})

OPEXE_FUNC(jb,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    (*SPI) += *((int*)(localSPI + 1));
    return SPU_EXE_OK;
})

OPEXE_FUNC(jbe,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    (*SPI) += *((int*)(localSPI + 1));
    return SPU_EXE_OK;
})

OPEXE_FUNC(je,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    (*SPI) += *((int*)(localSPI + 1));
    return SPU_EXE_OK;
})

OPEXE_FUNC(jne,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    (*SPI) += *((int*)(localSPI + 1));
    return SPU_EXE_OK;
})

OPEXE_FUNC(ja,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    (*SPI) += *((int*)(localSPI + 1));
    return SPU_EXE_OK;
})

OPEXE_FUNC(jae,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    (*SPI) += *((int*)(localSPI + 1));
    return SPU_EXE_OK;
})

OPEXE_FUNC(jm,  {
    if (!HASBYTES(5))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    (*SPI) += *((int*)(localSPI + 1));
    return SPU_EXE_OK;
})

OPEXE_FUNC(inc,  {
    if (!HASBYTES(2))
        return SPU_EXE_NOARGS;
    char* localSPI = *SPI;
    char flagByte = *(localSPI + 1);
    
    if (flagByte == 0) {
        double value = 0;
        StackRigidOperationCodes result = StackBack(core->stack, &value);
        
        STACKRESULT
        
        result = StackPush(&(core->stack), value + 1);
        
        STACKRESULT

        (*SPI) += 2;
    } else {
        char reg = *(localSPI + 2);
        core->REG[reg] += 1;
        (*SPI) += 3;
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
        StackRigidOperationCodes result = StackBack(core->stack, &value);
        
        STACKRESULT
        
        result = StackPush(&(core->stack), value - 1);
        
        STACKRESULT

        (*SPI) += 2;
    } else {
        char reg = *(localSPI + 2);
        core->REG[reg] -= 1;
        (*SPI) += 3;
    }
    return SPU_EXE_OK;
})

#pragma clang diagnostic pop
