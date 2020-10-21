//
//  TranslationDTypes.h
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 13.10.2020.
//

#ifndef TranslationDTypes_h
#define TranslationDTypes_h

enum CommandToBytesResult {
    SPU_CTB_OK               = 400,
    SPU_CTB_ERROR            = 401,
    SPU_CTB_UNKNOWN_REGISTER = 402,
    SPU_CTB_INVALID_NUMBER   = 403
};

#endif /* TranslationDTypes_h */
