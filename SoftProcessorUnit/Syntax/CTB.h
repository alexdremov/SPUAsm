//
//  CTB.h
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 19.10.2020.
//

#include "CTBDefs.h"

// (const struct SyntaxEntity* thou, AssemblyParams* compileParams, BinaryFile* binary, int argc, const char** argv)

OPTRANSLATE_FUNC(push, {
    LSTDUMPED({
        APPENDCHAR(thou->code);
        const char* firstArgument = argv[1];
        if (isdigit(*firstArgument) || *firstArgument == '-') {
            APPENDCHAR(0);
            double number = 0;
            int parsed = sscanf(firstArgument, "%lg", &number);
            if (parsed <= 0)
                return SPU_CTB_INVALID_NUMBER;
            APPENDDATA(&number, sizeof(number));
        } else {
            APPENDCHAR(1); // flag is 1 if there's register
            
            int registerNo = registerNoFromName((char*)firstArgument);
            if (registerNo == -1)
                return SPU_CTB_UNKNOWN_REGISTER;
            char registerNoCh = (char)registerNo;
            
            APPENDDATA(&registerNoCh, sizeof(registerNoCh));
        }
    })
    return SPU_CTB_OK;
});

OPTRANSLATE_FUNC(pop, {
    ZEROORREGISTERNO;
}) ;

OPTRANSLATE_FUNC(in, {
    ZEROORREGISTERNO;
});

OPTRANSLATE_FUNC(dump, {
    JUSTCOMMAND
});

OPTRANSLATE_FUNC(clear, {
    JUSTCOMMAND
});

OPTRANSLATE_FUNC(add, {
    JUSTCOMMAND
});

OPTRANSLATE_FUNC(sub, {
    JUSTCOMMAND
});

OPTRANSLATE_FUNC(mul, {
    JUSTCOMMAND
});

OPTRANSLATE_FUNC(div, {
    JUSTCOMMAND
});

OPTRANSLATE_FUNC(sin, {
    JUSTCOMMAND
});

OPTRANSLATE_FUNC(cos, {
    JUSTCOMMAND
});

OPTRANSLATE_FUNC(sqrt, {
    JUSTCOMMAND
});

OPTRANSLATE_FUNC(pow, {
    JUSTCOMMAND
});

OPTRANSLATE_FUNC(het, {
    JUSTCOMMAND
});

OPTRANSLATE_FUNC(out, {
    ZEROORREGISTERNO;
});

OPTRANSLATE_FUNC(jmp, {
    LSTDUMPED({
        APPENDCHAR(thou->code);
        SETLABELPOS;
        int jumpOffset = (int)( GETLABELPOS );
        APPENDDATA(&jumpOffset, sizeof(jumpOffset));
    })
    return SPU_CTB_OK;
});

OPTRANSLATE_FUNC(jb, {
    LSTDUMPED({
        APPENDCHAR(thou->code);
        SETLABELPOS;
        int jumpOffset = (int)( GETLABELPOS );
        APPENDDATA(&jumpOffset, sizeof(jumpOffset));
    })
    return SPU_CTB_OK;
});

OPTRANSLATE_FUNC(jbe, {
    LSTDUMPED({
        APPENDCHAR(thou->code);
        SETLABELPOS;
        int jumpOffset = (int)( GETLABELPOS );
        APPENDDATA(&jumpOffset, sizeof(jumpOffset));
    })
    return SPU_CTB_OK;
});

OPTRANSLATE_FUNC(je, {
    LSTDUMPED({
        APPENDCHAR(thou->code);
        SETLABELPOS;
        int jumpOffset = (int)( GETLABELPOS );
        APPENDDATA(&jumpOffset, sizeof(jumpOffset));
    })
    return SPU_CTB_OK;
});

OPTRANSLATE_FUNC(jne, {
    LSTDUMPED({
        APPENDCHAR(thou->code);
        SETLABELPOS;
        int jumpOffset = (int)( GETLABELPOS );
        APPENDDATA(&jumpOffset, sizeof(jumpOffset));
    })
    return SPU_CTB_OK;
});

OPTRANSLATE_FUNC(ja, {
    LSTDUMPED({
        APPENDCHAR(thou->code);
        SETLABELPOS;
        int jumpOffset = (int)( GETLABELPOS );
        APPENDDATA(&jumpOffset, sizeof(jumpOffset));
    })
    return SPU_CTB_OK;
});

OPTRANSLATE_FUNC(jae, {
    LSTDUMPED({
        APPENDCHAR(thou->code);
        SETLABELPOS;
        int jumpOffset = (int)( GETLABELPOS );
        APPENDDATA(&jumpOffset, sizeof(jumpOffset));
    })
    return SPU_CTB_OK;
});

OPTRANSLATE_FUNC(jm, {
    LSTDUMPED({
        APPENDCHAR(thou->code);
        SETLABELPOS;
        int jumpOffset = (int)( GETLABELPOS );
        APPENDDATA(&jumpOffset, sizeof(jumpOffset));
    })
    return SPU_CTB_OK;
});

OPTRANSLATE_FUNC(inc, {
    ZEROORREGISTERNO;
});

OPTRANSLATE_FUNC(dec, {
    ZEROORREGISTERNO;
});
