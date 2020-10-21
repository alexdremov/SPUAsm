//
//  StackRigid.cpp
//  SPU
//
//  Created by Александр Дремов on 14.10.2020.
//

#include <stdio.h>

#include "StackRigid.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>


#define IGNORE_VALIDITY

#ifdef StackDumpWrapper
    #undef StackDumpWrapper
#endif
#define StackDumpWrapper(stack) { StackDump(stack, __LINE__, __FILE__, ""); }

#ifdef StackDumpWrapperWhy
    #undef StackDumpWrapperWhy
#endif
#define StackDumpWrapperWhy(stack, why) { StackDump(stack, __LINE__, __FILE__, why); }


/**
 * @attention Not for the manual use!
 * @brief Calculates Adler-32 checksum from the firstBlock to the firstBlock + len
 * @param[in] firstBlock first block to include to the checksum
 * @param[in] len length of byte sequence
 * @return checksum
 */
static uint32_t adlerChecksum(const void* firstBlock, size_t len) {
    uint32_t a = 1, b = 0;
    const uint32_t MOD_ADLER = 65521;
    for (size_t index = 0; index < len; ++index) {
        a = (a + ((unsigned char*)firstBlock)[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }
    return (b << 16) | a;
}


/**
 * @attention Adjust this for your OS to increase security!
 * @brief Checks for pointer validity
 * @param[in] addr address to be checked
 * @param[in] size of the address
 * @return checksum
 */
static bool istack_pointer_valid(void* addr, int size) {
    if ((uint64_t)addr < 4096 || (uint64_t)addr % (uint64_t)size != 0) {
        return false;
    }
    return true;
}

/**
 * Create new stack with pre-defined capacity
 * @param[in] capacity initial stack capacity. Set to 0 if you want the stack to adopt automaticaly.
 * @param[in,out] logFile file for logging
 * @return new stack pointer or NULL if impossible
 */
 __overload(StackRigid)* __overload(NewStackRigid)(const size_t capacity, FILE* logFile);


/**
 * Perform all stack checks: checksums, general constrains.
 * @param[in] stack Stack to be validated
 * @return calculated state
 */
StackRigidState StackValidate( __overload(StackRigid)* stack);


/**
 * Push the value to the stack
 * The operation can perform reallocations if there is not enough space
 * @param[in,out] stack Stack to be changed
 * @param[in] value value to be pushed
 * @return the outcome of the operation
 */
StackRigidOperationCodes StackPush( __overload(StackRigid)** stack, StackElementType value);


/**
 * Pop value from the end of the stack
 * The operation can perform reallocations if there is too much space
 * @param[in,out] stack Stack to be distructed
 * @param[out] value value to be pushed
 * @return the outcome of the operation
 */
StackRigidOperationCodes StackPop( __overload(StackRigid)** stack, StackElementType* value);


/**
 * Free stack memory
 * @param[in,out] stack Stack to be distructed
 * @return the outcome of the operation
 */
StackRigidOperationCodes StackDestruct( __overload(StackRigid)** stack);


/**
 * Free stack memory
 * @param[out] stack Stack to be used
 * @return the outcome of the operation
 */
StackRigidOperationCodes StackBack( __overload(StackRigid)* stack, StackElementType* value);


/**
 * Dumps debug information about the stack.
 * @param[in] stack Stack to be dumped
 */
void StackDump( __overload(StackRigid)* stack, const int line, const char* file, const char* why);


/**
 * Memory alocated for the Stack
 * @param[in] stack Stack to be checked
 * @return alocated bytes
 */
size_t StackRigidMemoryUse( __overload(StackRigid)* stack);


/**
 * @attention Not for the manual use!
 * @brief Updates Stack checksums. Does not take into account bytes inside the stack but outside of its last element.
 * @verbatim
 * Stack memory :  [ __stack area__ | value 1, value 2, ..., value n || ___garbage area___]
 * ____________________________________________________________________^ alterations in this area are not checked
 * @endverbatim
 * @param[in,out] stack Stack that checksums are needed to be updated
 */
static void __StackUpdateChecksum( __overload(StackRigid)* stack);


/**
 * @attention Not for the manual use!
 * @brief Claculates big Stack checksum. Uses Adler-32 method
 * @verbatim
 * Stack memory : [ checkSum checkSumVital capacity size logFile | value 1, value 2, ..., value n || ___garbage area___]
 * Release:
 * ________________from here ^__________________________________________________________^to here
 * Debug:
 * ________________from here ^______________________________________________________________________________^to here
 * @endverbatim
 * @param[in] stack Stack that checksums are needed to be updated
 */
static uint32_t __StackGetChecksum( __overload(StackRigid)* stack);


/**
 * @attention Not for the manual use!
 * @brief Uses Adler-32 method. Calculates Stack checksum only for the vital parameters.
 * This is necessary because __StackGetChecksum() relies on capacity and size. If they were changed, behaviour is undefined
 *
 * @verbatim
 * Stack memory : [ checkSum checkSumVital capacity size logFile | value 1, value 2, ..., value n || ___garbage area___]
 * ______________________________from here ^__________________^to here
 * @endverbatim
 * @param[in] stack Stack that checksums are needed to be updated
 */
static uint32_t __StackGetChecksumVital( __overload(StackRigid)* stack);


/**
 * @attention Not for the manual use!
 * @brief Reallocates Stack if needed
 * @param[in,out] stack Stack to be reallocated
 * @param[in] direction which direction reallocations are available.  > 0 -> expand space if needed, < 0 -> shrink space if needed
 */
static StackRigidOperationCodes __StackReallocate( __overload(StackRigid)** stack, short int direction);


StackRigidOperationCodes StackPush( __overload(StackRigid)** stack, StackElementType value){
    if (!istack_pointer_valid(stack, sizeof(stack)))
        return STACK_OP_PTRINVALID;
    if (!istack_pointer_valid(*stack, sizeof(*stack)))
        return STACK_OP_PTRINVALID;
    
    
    StackRigidState integrityChecks = StackValidate(*stack);
    
    if (integrityChecks != STACK_ST_OK) {
        StackDumpWrapperWhy(*stack, "StackPush operation spotted integrity error");
        return STACK_OP_INTEGRITYERR;
    }
    
    
    StackRigidOperationCodes reallocResult = __StackReallocate(stack, 1);
    
    if (reallocResult != STACK_OP_OK) {
        StackDumpWrapperWhy(*stack, "StackPop operation spotted integrity error during the reallocation");
        return reallocResult;
    }
    
    (*stack)->data[(*stack)->size] = value;
    (*stack)->size += 1;
    
    __StackUpdateChecksum(*stack);
    
    if ((*stack)->size == 0) {
        return STACK_OP_OVERFLOW;
    }
    return STACK_OP_OK;
}


 __overload(StackRigid)* __overload(NewStackRigid)(size_t capacity, FILE* logFile){
     if (capacity == 0)
         capacity = 1;
     size_t memory = sizeof( __overload(StackRigid));
     size_t added = memory + (capacity - 1) * sizeof(StackElementType);
     if (added < memory) {
         return NULL;
     }
     if (!istack_pointer_valid(logFile, sizeof(logFile))) {
         return NULL;
     }
     memory = added;
     
     __overload(StackRigid)* pointer = ( __overload(StackRigid)*)calloc(memory, 1);
     
    if (!istack_pointer_valid(pointer, sizeof(pointer))) {
        if (pointer != NULL)
            free(pointer);
        return NULL;
    }
    
    pointer->capacity = capacity;
    pointer->size = 0;
    pointer->logFile = logFile;
    pointer->checkSum = 0;
    pointer->checkSumVital = 0;
     
     
    __StackUpdateChecksum(pointer);
    return pointer;
}


StackRigidOperationCodes StackPop( __overload(StackRigid)** stack, StackElementType* value) {
    if (!istack_pointer_valid(stack, sizeof(stack)))
        return STACK_OP_NULL;
    
    StackRigidState integrityChecks = StackValidate(*stack);
    
    if (integrityChecks != STACK_ST_OK) {
        StackDumpWrapperWhy(*stack, "StackPop operation spotted integrity error");
        return STACK_OP_INTEGRITYERR;
    }
    
    if((*stack)->size == 0)
        return STACK_OP_UNDERFLOW;
    
    *value = (*stack)->data[(*stack)->size - 1];
    (*stack)->size -= 1;
    
    StackRigidOperationCodes realocRes = __StackReallocate(stack, -1);
    if (realocRes == STACK_OP_OK)
        __StackUpdateChecksum(*stack);
    else
        return realocRes;
    
    return STACK_OP_OK;
}


StackRigidOperationCodes StackBack( __overload(StackRigid)* stack, StackElementType* value){
    if (!istack_pointer_valid(stack, sizeof(stack)))
        return STACK_OP_NULL;
    
    
    StackRigidState integrityChecks = StackValidate(stack);
    
    if (integrityChecks != STACK_ST_OK) {
        StackDumpWrapperWhy(stack, "StackBack operation spotted integrity error");
        return STACK_OP_INTEGRITYERR;
    }
    
    if(stack->size == 0)
        return STACK_OP_UNDERFLOW;
    
    *value = stack->data[stack->size - 1];
    return STACK_OP_OK;
}

StackRigidOperationCodes StackClear( __overload(StackRigid)* stack){
    if (!istack_pointer_valid(stack, sizeof(stack)))
        return STACK_OP_NULL;
    
    
    StackRigidState integrityChecks = StackValidate(stack);
    
    if (integrityChecks != STACK_ST_OK) {
        StackDumpWrapperWhy(stack, "StackClear operation spotted integrity error");
        return STACK_OP_INTEGRITYERR;
    }
    
    stack->size = 0;
    
    return STACK_OP_OK;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"


StackRigidState StackValidate( __overload(StackRigid)* stack) {
    if (!istack_pointer_valid(stack, sizeof(stack)))
        return STACK_ST_NULL;
    
    #ifdef IGNORE_VALIDITY
        return STACK_ST_OK;
    #endif
    
    #ifndef IGNORE_VALIDITY
        if (stack->size > stack->capacity || stack->checkSum == 0 || stack->checkSumVital == 0)
            return STACK_ST_INTEGRITYERR;
    #endif
    #ifndef IGNORE_VALIDITY
        uint32_t currentChecksumVital = __StackGetChecksumVital(stack);
        if (currentChecksumVital != stack->checkSumVital || currentChecksumVital == 0)
            return STACK_ST_INTEGRITYERR;
        
        uint32_t currentChecksum = __StackGetChecksum(stack);
        if (currentChecksum != stack->checkSum || currentChecksum == 0)
            return STACK_ST_INTEGRITYERR;
    #endif

    return STACK_ST_OK;
}


static void __StackUpdateChecksum( __overload(StackRigid)* stack) {
    assert(stack);
    #ifndef IGNORE_VALIDITY
        stack->checkSumVital = __StackGetChecksumVital(stack);
        stack->checkSum      = __StackGetChecksum(stack);
    #endif
}


static uint32_t __StackGetChecksumVital( __overload(StackRigid)* stack) {
    assert(stack);
    
    void* firstBlock = (char*)stack + sizeof(stack->checkSum) + sizeof(stack->checkSumVital);
    
    const size_t memory = (size_t)((char*)(stack->data) - (char*)firstBlock);
    if (stack->size > stack->capacity) {
        return 0;
    }
    return adlerChecksum(firstBlock, memory);
}


static uint32_t __StackGetChecksum( __overload(StackRigid)* stack) {
    assert(stack);
    
    void* firstBlock = (char*)stack + sizeof(stack->checkSum);
    
    // Memory used by Stack excluding checkSum and free space
    #ifndef DEBUG
        const size_t memory = StackRigidMemoryUse(stack) - sizeof(stack->checkSum) - (stack->capacity - stack->size) * sizeof(StackElementType);
    #endif
    #ifdef DEBUG
        const size_t memory = StackRigidMemoryUse(stack) - sizeof(stack->checkSum);
    #endif
    
    if (stack->size > stack->capacity) {
        return 0;
    }
    return adlerChecksum(firstBlock, memory);
}

#pragma clang diagnostic push


static StackRigidOperationCodes __StackReallocate( __overload(StackRigid)** stack, short int direction) {
    if ((*stack)->capacity == 0) {
        (*stack)->capacity = 16; // capacity if was 0
        
        const size_t memory = StackRigidMemoryUse(*stack);
        
         __overload(StackRigid)* newStack = ( __overload(StackRigid)*) realloc((*stack), memory);
        if (!istack_pointer_valid(newStack, sizeof(newStack))){
            if (newStack != NULL)
                free(newStack);
            return STACK_OP_NOMEMORY;
        }
        
        (*stack) = newStack;
    }else if(((*stack)->capacity <= (*stack)->size) && direction > 0) { // Up reallocation
        size_t newCapacity = (*stack)->size * 2;
        
        if (newCapacity <= (*stack)->size) { //   If we exceeded size_t range
            newCapacity = (*stack)->size + 16; // Try to add 16 free spaces
            if (newCapacity < (*stack)->size) //  Even if in this case we still exceed size_t
                return STACK_OP_OVERFLOW;
        }
        
        const size_t memoryNow = StackRigidMemoryUse(*stack);
        const size_t memoryNew = sizeof(__overload(StackRigid)) + (newCapacity - 1) * sizeof(StackElementType);
        
        if (memoryNew >= memoryNow) {
             __overload(StackRigid)* newStack = ( __overload(StackRigid)*) realloc((*stack), memoryNew);
            if (!istack_pointer_valid(newStack, sizeof(newStack)))
                return STACK_OP_NOMEMORY;
            
            (*stack) = newStack;
        }else{
            return STACK_OP_OVERFLOW; // Exceded size_t memory
        }
        (*stack)->capacity = newCapacity;
        
    }else if (((*stack)->capacity / 2.2 > (*stack)->size) && direction < 0) { // Down reallocation
        size_t newCapacity = (size_t)((*stack)->capacity / 2.2);
        
        const size_t memoryNow = StackRigidMemoryUse(*stack);
        const size_t memoryNew = sizeof(__overload(StackRigid)) + (newCapacity - 1) * sizeof(StackElementType);
        
        if (memoryNew <= memoryNow) {
             __overload(StackRigid)* newStack = ( __overload(StackRigid)*) realloc((*stack), memoryNew);
            if (!istack_pointer_valid(newStack, sizeof(newStack))){
                if (newStack != NULL)
                    free(newStack);
                return STACK_OP_NOMEMORY;
            }
            
            (*stack) = newStack;
            (*stack)->capacity = newCapacity;
        }else
            return STACK_OP_OVERFLOW; // Exceded size_t memory
    }
    return STACK_OP_OK;
}

size_t StackRigidMemoryUse( __overload(StackRigid)* stack) {
    assert(stack);
    return sizeof(__overload(StackRigid)) + (stack->capacity - 1) * sizeof(StackElementType);
}


void StackDump( __overload(StackRigid)* stack, const int line, const char* file, const char* why) {
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);
    
    if (!istack_pointer_valid(stack, sizeof(stack))){
        fprintf(stdin, "\nStack dump is impossible: NULL pointer\n");
        return;
    }
    
    FILE* output = stack->logFile;
    if (!istack_pointer_valid(output, sizeof(output))) {
        output = stdout;
        printf("\nWarning! Specified dump output is inavailbale! Selecting stdout.\n");
    }
    
    fprintf(output, "=================================\n");
    fprintf(output, "Stack dump %s", asctime(ptm));
    fprintf(output, "Line: %d\nFile: %s\n", line, file);
    if (why[0] != '\0')
    fprintf(output, "Problem: %s\n", why);
    
    if (istack_pointer_valid(stack, sizeof(stack))) {
        fprintf(output, "Stack (");
        const char *status = "ok";
        StackRigidState checks = StackValidate(stack);
        switch (checks) {
            case STACK_ST_INTEGRITYERR:
                status = "INTEGRITY ERROR SPOTTED";
                break;
            case STACK_ST_UNINITIALIZED:
                status = "UNINITIALIZED";
                break;
            case STACK_ST_OK:
                status = "ok";
                break;
            case STACK_ST_NULL:
                status = "NULL POINTER";
                break;
        }
        fprintf(output, "%s", status);
        fprintf(output, ")");
        fprintf(output, " [%p]: {\n", (void*)stack);
        if (checks != STACK_ST_OK) {
            fprintf(output, "ERROR! Stack structure was corrupted.\nThe data below was changed from the outside.\nThis can fail!\n");
        }
        fprintf(output, "\t         size : %lu\n", stack->size);
        fprintf(output, "\t     capacity : %lu\n", stack->capacity);
        fprintf(output, "\t     checkSum : %x\n", stack->checkSumVital);
        fprintf(output, "\tcheckSumVital : %x\n", stack->checkSum);
        
        fprintf(output, "\tdata [%p]: {\n", (void*)stack->data);
        if (checks == STACK_ST_OK) {
        size_t i = 0;
        for (i = 0; i < stack->size; i++) {
            fprintf(output, "\t\t");
            fprintf(output, "*[%lu] : ", i);
            fprintf(output, "[%p] ",(void*)( stack->data + i));
            StackElementDump(stack->logFile, stack->data[i]);
            fprintf(output, "\n");
        }
        fprintf(output, "\t\t _______\n");
        if (stack->size  < stack->capacity) {
            fprintf(output, "\t\t [%lu] : GARBAGE(", i);
            fprintf(output, "[%p] ",(void*)( stack->data + i));
            StackElementDump(stack->logFile, stack->data[i]);
            fprintf(output, ")\n");
        }
        if (stack->size + 1< stack->capacity && stack->size + 1 > stack->size) {
            fprintf(output, "\t\t [%lu] : GARBAGE(", i + 1);
            fprintf(output, "[%p] ", (void*)(stack->data + i + 1));
            StackElementDump(stack->logFile, stack->data[i + 1]);
            fprintf(output, ")\n");
        }
        } else{
            fprintf(output, "\t\tDATA CAN'T BE READED\n");
        }
        
        fprintf(output, "\t}\n");
        fprintf(output, "}\n");
        
        const size_t memory = StackRigidMemoryUse(stack);
        fprintf(output, "Size allocated : %lu bytes\n", memory);
        fprintf(output, "Raw Stack size : %lu bytes\n", sizeof(__overload(StackRigid)));
        fprintf(output, "  Element size : %lu bytes\n", sizeof(StackElementType));
        fprintf(output, "     Block end : %p\n", (void*)((char*)stack + memory));
    }
    fprintf(output, "=================================\n");
    fflush(NULL);
    
}


StackRigidOperationCodes StackDestruct( __overload(StackRigid)** stack) {
    if (!istack_pointer_valid(stack, sizeof(stack))) {
        return STACK_OP_NULL;
    }
    if (!istack_pointer_valid(*stack, sizeof(*stack))) {
        return STACK_OP_NULL;
    }
    StackRigidState checks = StackValidate(*stack);
    if (checks == STACK_ST_OK){
        const size_t memoryNow = StackRigidMemoryUse(*stack);
        for(char* cursor = (char*)(*stack); cursor < (char*)(*stack) + memoryNow; cursor++)
            *cursor = 0;
    }
    free(*stack);
    return STACK_OP_OK;
}
