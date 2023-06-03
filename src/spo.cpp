//-----------------------------------------------------------------------------
//   spo.cpp
//
//   Project:  SWMM Parameter Optimization
//   Version:  1.0
//   Author:   K.Y. Zhu

#include "headers.h"
#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include "spo.h"


int* Dec2BinFunc(float paramArr[], int paramSize)
{
    int* binParamArr = new int[paramSize];

    for (int paramCount = 0; paramCount < paramSize; paramCount++) {
        if (paramArr[paramCount] != static_cast<int>(paramArr[paramCount])) {
            std::bitset<sizeof(float) * 8> binary(paramArr[paramCount]);
            binParamArr[paramCount] = binary.to_ulong();
        }
        else if(paramArr[paramCount] == static_cast<int>(paramArr[paramCount])){
            std::bitset<sizeof(int) * 8> binary(static_cast<int>(paramArr[paramCount]));
            binParamArr[paramCount] = binary.to_ulong();
        }
    }

    return binParamArr;
}

/*Subcatchment*/
// printf("\n =>  Original percent of impervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_FRACIMPERV, 0));
// printf("\n =>  Original manning's N for impervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_IMPERV01_N, 0));
// printf("\n =>  Original manning's N for pervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_PERV_N, 0));
// printf("\n =>  Original depth of depression storage on impervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_IMPERV1_DSTORE, 0));
// printf("\n =>  Original depth of depression storage on pervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_PERV_DSTORE, 0));
// printf("\n =>  Original perentage of impervious area with no depression storage of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_IMPERV0_FAREA, 0));
/*Subcatchment*/

/*Infiltration*/
// printf("\n =>  Original maximum rate on the Horton infiltration curve of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_F0, 0));
// printf("\n =>  Original minimum rate on the Horton infiltration curve of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_FMIN, 0));
// printf("\n =>  Original decay constant for the Horton infiltration curve of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_DECAY, 0));
// printf("\n =>  Original drying time of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_REGEN, 0));
// printf("\n =>  Original maximum infiltration volume of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_FMAX, 0));
/*Infiltration*/

/*Link*/
// printf("\n =>  Original link roughness of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_ROUGHNESS, 35));
// printf("\n =>  Original link entry loss coef. of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_CLOSSINLET, 35));
// printf("\n =>  Original link exit loss coef. of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_CLOSSOUTLET, 35));
// printf("\n =>  Original link avg. loss coeff. of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_CLOSSAVG, 35));
// printf("\n =>  Original link seepage loss rate of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_SEEPLOSSRATE, 35));
/*Link*/