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
        ComplexValue val = GETCOMPLEXVALNO(1);
        COMPLEXVALOK
        writeComplexArg(&val, binary);
    })
    return SPU_CTB_OK;
});

OPTRANSLATE_FUNC(pop, {
    ZEROORSTORAGE;
}) ;

OPTRANSLATE_FUNC(in, {
    ZEROORSTORAGE;
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

OPTRANSLATE_FUNC(hlt, {
    JUSTCOMMAND
});

OPTRANSLATE_FUNC(out, {
    ZEROORVAL;
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
    ZEROORSTORAGE;
});

OPTRANSLATE_FUNC(dec, {
    ZEROORSTORAGE;
});

OPTRANSLATE_FUNC(call, {
    LSTDUMPED({
        APPENDCHAR(thou->code);
        SETLABELPOS;
        int jumpOffset = (int)( GETLABELPOS );
        APPENDDATA(&jumpOffset, sizeof(jumpOffset));
    })
    return SPU_CTB_OK;
});

OPTRANSLATE_FUNC(ret, {
    JUSTCOMMAND;
});

OPTRANSLATE_FUNC(mov, {
    LSTDUMPED({
        APPENDCHAR(thou->code);
        ComplexValue val = GETCOMPLEXVALNO(1);
        COMPLEXVALOK
        int assignable = complexValueAssignable(&val);
        if (assignable != 1) return SPU_CTB_NONASSIGNABLE;
        writeComplexArg(&val, binary);
        val = GETCOMPLEXVALNO(2);
        COMPLEXVALOK;
        writeComplexArg(&val, binary);
    })
    return SPU_CTB_OK;
});

OPTRANSLATE_FUNC(rend, {
    JUSTCOMMAND;
});

OPTRANSLATE_FUNC(slp, {
    LSTDUMPED({
        APPENDCHAR(thou->code);
        ComplexValue val = GETCOMPLEXVALNO(1);
        COMPLEXVALOK
        writeComplexArg(&val, binary);
    })
    return SPU_CTB_OK;
});

OPTRANSLATE_FUNC(abs, {
    JUSTCOMMAND
});


OPTRANSLATE_FUNC(pixset, {
    LSTDUMPED({
        APPENDCHAR(thou->code);
        ComplexValue val = GETCOMPLEXVALNO(1);
        COMPLEXVALOK
        writeComplexArg(&val, binary);
        val = GETCOMPLEXVALNO(2);
        COMPLEXVALOK;
        writeComplexArg(&val, binary);
        val = GETCOMPLEXVALNO(3);
        COMPLEXVALOK;
        writeComplexArg(&val, binary);
    })
    return SPU_CTB_OK;
});

OPTRANSLATE_FUNC(clrscr, {
    JUSTCOMMAND
});
