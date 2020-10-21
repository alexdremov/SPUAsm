/**
 * @mainpage
 * @author Aleksandr Dremov
 * @brief This Stack is almost impossible to kill and fool. All undefined behaviour memory accesses will be spoted and reported.
 * @attention Prerequisites.\n Before including .h file, you need to define  StackElementDump(FILE, VALUE) and StackElementType. \n
 * Example:\n
 * #define StackElementDump(FILE, VALUE) {fprintf(FILE, "%g", VALUE);}\n
 * #define StackElementType double\n
 * The system must have uint32_t type available\n
 * @warning Stack can be fully moved in memory during reallocations
 * @copyright Aleksandr Dremov, MIPT 2020
 */

#include <stdlib.h>

#ifndef StackRigid_h
#define StackRigid_h

#define IGNORE_VALIDITY


#define StackElementDump(FILE, VALUE) {fprintf(FILE, "%g", VALUE);}
#define StackElementType double



/**
 * Default element dump instruction
 */
#ifndef StackElementDump
    #define StackElementDump(FILE, VALUE) {fprintf(FILE, "%d", VALUE);}
#endif

/**
 * By default, it will be stack of ints
 */
#ifndef StackElementType
    #define StackElementType int
#endif

#ifdef __overload
    #undef __overload
#endif
#ifdef PASTER
    #undef PASTER
#endif
#ifdef EVALUATOR
    #undef EVALUATOR
#endif
#define PASTER(x,y)      x ## _ ## y
#define EVALUATOR(x,y)   PASTER(x,y)
#define __overload(FUNC) EVALUATOR(FUNC, StackElementType)

/**
 * The main StackRigid struct
 */
struct __overload(StackRigid) {
    uint32_t checkSum;
    uint32_t checkSumVital;
    size_t capacity;
    size_t size;
    FILE* logFile;
    StackElementType data[1];
};



/**
 * Codes returned after operations on Stack
 */
typedef enum StackRigidOperationCodes{
    //! Succesful operation
    STACK_OP_OK,

    //! Tried to get value from the empty stack
    STACK_OP_UNDERFLOW,

    //! Stack overflow and new memory allocation failed
    STACK_OP_OVERFLOW,

    //! No memory for stack alocations
    STACK_OP_NOMEMORY,

    //! Stack memory was altered by some outer access
    STACK_OP_INTEGRITYERR,

    //! Found NULL pointer during the operation
    STACK_OP_NULL,

    //!  Found invalid pointer during the operation
    STACK_OP_PTRINVALID
} StackRigidOperationCodes;


/**
 * Codes characterizing Stack state
 */
typedef enum StackRigidState{
    //! Stack is running as expected
    STACK_ST_OK,

    //! Stack was altered by some outer access
    STACK_ST_INTEGRITYERR,

    //! Stack is uninitialized
    STACK_ST_UNINITIALIZED,

    //! Found NULL pointer during the operation
    STACK_ST_NULL
} StackRigidState;



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
 * Clear the stack
 * @param[in,out] stack Stack to be changed
 * @return the outcome of the operation
 */
StackRigidOperationCodes StackClear( __overload(StackRigid)* stack);



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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"

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
#pragma clang diagnostic pop

#endif /* StackRigid_h general models */
