//
//  ParseHelpers.hpp
//  SoftProcessorUnit
//
//  Created by Александр Дремов on 22.10.2020.
//

#ifndef ParseHelpers_hpp
#define ParseHelpers_hpp

#include "SPUDtypes.hpp"

enum ComplexValueResult {
    SPU_CV_OK                = 1200,
    SPU_CV_WRONGREG          = 1201,
    SPU_CV_WRONGNUM          = 1202,
    SPU_CV_WRONGSTRUCT       = 1203,
    SPU_CV_WRONGOP           = 1204,
    SPU_CV_NONASSIGNABLE     = 1204,
    SPU_CV_NOARG             = 1205
};

double getDoubleFromBuffer(char* start);

int getIntFromBuffer(char* start);


#endif /* ParseHelpers_hpp */
