//-----------------------------------------------------------------------------
//   main.c
//
//   Project:  EPA SWMM5
//   Version:  5.2
//   Date:     03/24/2021
//   Author:   L. Rossman

//   Main stub for the command line version of EPA SWMM 5.2
//   to be run with swmm5.dll.

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "swmm5.h"
#include "headers.h"
#include "spo.h"

#define SubcatchNum 75
#define LinkNum 102

int  main(int argc, char *argv[])
//
//  Input:   argc = number of command line arguments
//           argv = array of command line arguments
//  Output:  returns error status
//  Purpose: runs the command line version of EPA SWMM 5.2.
//
//  Command line is: runswmm f1  f2  f3
//  where f1 = name of input file, f2 = name of report file, and
//  f3 = name of binary output file if saved (or blank if not saved).
//
{
    char *inputFile;
    char *reportFile;
    char *binaryFile;
    char *arg1;
    char blank[] = "";
    int  version, vMajor, vMinor, vRelease;
    char errMsg[128];
    int  msgLen = 127;
    time_t start;
    double runTime;

    // New defined variable
    double elapsedTime;
    float runoffErr, routeErr, qualErr;
    float ParamArr[SubcatchNum * 11 + LinkNum * 5];
    float FRACIMPERVN[SubcatchNum];
    float IMPERV01_N[SubcatchNum];
    float PERV01_N[SubcatchNum];
    float IMPERV1_DSTORE[SubcatchNum];
    float PERV_DSTORE[SubcatchNum];
    float IMPERV0_FAREA[SubcatchNum];
    float F0[SubcatchNum];
    float FMIN[SubcatchNum];
    float DECAY[SubcatchNum];
    float REGEN[SubcatchNum];
    float FMAX[SubcatchNum];
    float ROUGHNESS[LinkNum];
    float CLOSSINLET[LinkNum];
    float CLOSSOUTLET[LinkNum];
    float CLOSSAVG[LinkNum];
    float SEEPLOSSRATE[LinkNum];
    // New defined variable
    
    version = swmm_getVersion();
    vMajor = version / 10000;
    vMinor = (version - 10000 * vMajor) / 1000;
    vRelease = (version - 10000 * vMajor - 1000 * vMinor);
    start = time(0);

    // --- check for proper number of command line arguments
    if (argc == 1)
    {
        printf("\nNot Enough Arguments (See Help --help)\n\n");
    }
    else if (argc == 2)
    {
        // --- extract first argument
        arg1 = argv[1];

        if (strcmp(arg1, "--help") == 0 || strcmp(arg1, "-h") == 0)
        {
            // Help
            printf("\n\nSTORMWATER MANAGEMENT MODEL (SWMM) HELP\n\n");
            printf("COMMANDS:\n");
            printf("\t--help (-h)       SWMM Help\n");
            printf("\t--version (-v)    Build Version\n");
            printf("\nRUNNING A SIMULATION:\n");
            printf("\t runswmm <input file> <report file> <optional output file>\n\n");
        }
        else if (strcmp(arg1, "--version") == 0 || strcmp(arg1, "-v") == 0)
        {
            // Output version number
            printf("\n%d.%d.%0d\n\n", vMajor, vMinor, vRelease);
        }
        else
        {
            printf("\nUnknown Argument (See Help --help)\n\n");
        }
    }
    else
    {
        // --- extract file names from command line arguments
        inputFile = argv[1];
        reportFile = argv[2];
        if (argc > 3) binaryFile = argv[3];
        else          binaryFile = blank;
        printf("\n... EPA SWMM %d.%d (Build %d.%d.%0d)\n", vMajor, vMinor,
            vMajor, vMinor, vRelease);
//---------------------------------------original code---------------------------------------
/*
        // --- run SWMM
        swmm_run(inputFile, reportFile, binaryFile);
        
        // Display closing status on console
        runTime = difftime(time(0), start);
        printf("\n\n... EPA SWMM completed in %.2f seconds.", runTime);
        if      ( swmm_getError(errMsg, msgLen) > 0 ) printf(" There are errors.\n");
        else if ( swmm_getWarnings() > 0 ) printf(" There are warnings.\n");
        else printf("\n");
*/
//---------------------------------------original code---------------------------------------

//---------------------------------------revised code---------------------------------------
//---------------------------------------Modified history--------------------------------------------------------
// (2023.02.02) Try swmm_getCount, swmm_getName, swmm_getIndex, swmm_getValue
// (2023.02.16) Try swmm_getSavedValue, swmm_setValue, swmm_writeLine, swmm_decodeDate
// (2023.02.23) Include "link.c", "node.c", "infil.c", "subcatch.c" to get and set the parameter (Incorrect way!!)
// (2023.03.01) Add fopen() to read file (Don't do it in this porject. It could cause segamentaion fault!!)
// (2023.03.15) Successfully setup the parameter of node and link
// (2023.03.21) Successfully setup the parameter of subcatchment
// (2023.05.26) Add function of decimal to binary
//-------------------------------------------------------------------------------------------------------
        // -- run SWMM

        // --- open the files & read input data
        printf("\n======================================================================================");
        printf("\n                       - - - Retrieving project data - - - \n");
        printf("======================================================================================\n");
        swmm_open(inputFile, reportFile, binaryFile);

        // --- initialize values
        swmm_start(TRUE);

        for(int SubcatchIndex = 0; SubcatchIndex < SubcatchNum; SubcatchIndex++){
            FRACIMPERVN[SubcatchIndex] = swmm_getValue(swmm_SUBCATCH_FRACIMPERV, SubcatchIndex);
            IMPERV01_N[SubcatchIndex] = swmm_getValue(swmm_SUBCATCH_IMPERV01_N, SubcatchIndex);
            PERV01_N[SubcatchIndex] = swmm_getValue(swmm_SUBCATCH_PERV_N, SubcatchIndex);
            IMPERV1_DSTORE[SubcatchIndex] = swmm_getValue(swmm_SUBCATCH_IMPERV1_DSTORE, SubcatchIndex);
            PERV_DSTORE[SubcatchIndex] = swmm_getValue(swmm_SUBCATCH_PERV_DSTORE, SubcatchIndex);
            IMPERV0_FAREA[SubcatchIndex] = swmm_getValue(swmm_SUBCATCH_IMPERV0_FAREA, SubcatchIndex);
            F0[SubcatchIndex] = swmm_getValue(swmm_SUBCATCH_F0, SubcatchIndex);
            FMIN[SubcatchIndex] = swmm_getValue(swmm_SUBCATCH_FMIN, SubcatchIndex);
            DECAY[SubcatchIndex] = swmm_getValue(swmm_SUBCATCH_DECAY, SubcatchIndex);
            REGEN[SubcatchIndex] = swmm_getValue(swmm_SUBCATCH_REGEN, SubcatchIndex);
            FMAX[SubcatchIndex] = swmm_getValue(swmm_SUBCATCH_FMAX, SubcatchIndex);

        }

        for(int LinkIndex = 0; LinkIndex < LinkNum; LinkIndex++){
            ROUGHNESS[LinkIndex] = swmm_getValue(swmm_LINK_ROUGHNESS, LinkIndex);
            CLOSSINLET[LinkIndex] = swmm_getValue(swmm_LINK_CLOSSINLET, LinkIndex);
            CLOSSOUTLET[LinkIndex] = swmm_getValue(swmm_LINK_CLOSSOUTLET, LinkIndex);
            CLOSSAVG[LinkIndex] = swmm_getValue(swmm_LINK_CLOSSAVG, LinkIndex);
            SEEPLOSSRATE[LinkIndex] = swmm_getValue(swmm_LINK_SEEPLOSSRATE, LinkIndex);

        }

        for(int count = 0; count < (SubcatchNum*11 + LinkNum*5); count++){
            if(count < SubcatchNum){
                ParamArr[count] = FRACIMPERVN[count];
            }
            else if(count >= SubcatchNum*1 && count < SubcatchNum*2){
                ParamArr[count] = IMPERV01_N[count - SubcatchNum*1];
            }
            else if(count >= SubcatchNum*2 && count < SubcatchNum*3){
                ParamArr[count] = PERV01_N[count - SubcatchNum*2];
            }
            else if(count >= SubcatchNum*3 && count < SubcatchNum*4){
                ParamArr[count] = IMPERV1_DSTORE[count - SubcatchNum*3];
            }
            else if(count >= SubcatchNum*4 && count < SubcatchNum*5){
                ParamArr[count] = PERV_DSTORE[count - SubcatchNum*4];
            }
            else if(count >= SubcatchNum*5 && count < SubcatchNum*6){
                ParamArr[count] = IMPERV0_FAREA[count - SubcatchNum*5];
            }
            else if(count >= SubcatchNum*6 && count < SubcatchNum*7){
                ParamArr[count] = F0[count - SubcatchNum*6];
            }
            else if(count >= SubcatchNum*7 && count < SubcatchNum*8){
                ParamArr[count] = FMIN[count - SubcatchNum*7];
            }
            else if(count >= SubcatchNum*8 && count < SubcatchNum*9){
                ParamArr[count] = DECAY[count - SubcatchNum*8];
            }
            else if(count >= SubcatchNum*9 && count < SubcatchNum*10){
                ParamArr[count] = REGEN[count - SubcatchNum*9];
            }
            else if(count >= SubcatchNum*10 && count < SubcatchNum*11){
                ParamArr[count] = FMAX[count - SubcatchNum*10];
            }
            else if(count >= SubcatchNum*11 && count < (SubcatchNum*11 + LinkNum*1)){
                ParamArr[count] = ROUGHNESS[count - SubcatchNum*11];
            }
            else if(count >= (SubcatchNum*11 + LinkNum*1) && count < (SubcatchNum*12 + LinkNum*2)){
                ParamArr[count] = CLOSSINLET[count - SubcatchNum*11 - LinkNum*1];
            }
            else if(count >= (SubcatchNum*11 + LinkNum*2) && count < (SubcatchNum*13 + LinkNum*3)){
                ParamArr[count] = CLOSSOUTLET[count - SubcatchNum*11 - LinkNum*2];
            }
            else if(count >= (SubcatchNum*11 + LinkNum*3) && count < (SubcatchNum*14 + LinkNum*4)){
                ParamArr[count] = CLOSSAVG[count - SubcatchNum*11 - LinkNum*3];
            }
            else if(count >= (SubcatchNum*11 + LinkNum*4) && count < (SubcatchNum*15 + LinkNum*5)){
                ParamArr[count] = SEEPLOSSRATE[count - SubcatchNum*11 - LinkNum*4];
            }

        }

        int* binParamArr = Dec2BinFunc(ParamArr, SubcatchNum*11 + LinkNum*3);

        // for(int i = 0; i < (SubcatchNum*11 + LinkNum*4); i++){
            
        //     printf("%i\n", binParamArr[i]);
        // }
        

        // --- execute each time step until elapsed time is re-set to 0
        do {
            swmm_step(&elapsedTime);
        } while (elapsedTime > 0);

        printf("\n======================================================================================");
        printf("\n                         - - - Simulation complete - - - \n");
        printf("======================================================================================");
                                                                                            
        // --- clean up
        swmm_end();
        
        // --- reports a simulation's mass balance errors 
        swmm_getMassBalErr(&runoffErr, &routeErr, &qualErr);
        printf("\n\n o  Runoff Error: %.4f", runoffErr);
        printf("\n o  Routing Error: %.4f\n", routeErr);

        // Display closing status on console
        runTime = difftime(time(0), start);
        printf("\n\n... EPA SWMM completed in %.2f seconds.", runTime);
        if      ( swmm_getError(errMsg, msgLen) > 0 ) printf(" There are errors.\n");
        else if ( swmm_getWarnings() > 0 ) printf(" There are warnings.\n");
        else printf("\n");

        // --- report results
        printf("\n======================================================================================");
        printf("\n                         - - - Writing output report - - - \n");
        printf("======================================================================================\n");
        swmm_report();

        // --- close the system
        swmm_close();
        
        
        // Display closing status on console
//---------------------------------------revised code----------------------------------------------------

    }

// --- Use the code below if you need to keep the console window visible
/* 
    printf("    Press Enter to continue...");
    getchar();
*/

    return 0;
}

//====================================================================================================================================================
//                                                       Revised code for copy and paste
//====================================================================================================================================================

        // printf("\n =>  Original link roughness of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_ROUGHNESS, 35));
        // printf("\n =>  Original link inlet loss coeff. of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_CLOSSINLET, 35));
        // printf("\n =>  Original maximum depth of the cross section of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_YWMAX, 35));
        // printf("\n =>  Original impervious manning's N of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_IMPERV_N, 0));
        
        // printf("\n =>  Adjusted link roughness of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_ROUGHNESS, 35));
        // printf("\n =>  Adjusted link inlet loss coeff. of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_CLOSSINLET, 35));
        // printf("\n =>  Adjusted maximum depth of the cross section of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_YWMAX, 35));
        // printf("\n =>  Adjusted impervious manning's N of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_IMPERV_N, 0));

        // double x[] = {15, 15, 15};
        // node_setparam(0, JUNCTION, 0, x);

        // double y[] = {15, 15, 15, 15, 15, 15};
        // link_setparam(35, CONDUIT, 0, 1, 0, y);

        // double y1[] = {15, 15, 15, 15};
        // link_setLossparam(35, CONDUIT, 0, y);
        
        // double z[] = {15, 15, 15, 15, 15, 15, 15, 15, 15};
        // subcatch_setparam(0, z);

        // double z1[] = {15, 15};
        // xsect_setparam(&Link[35].xsect, Link[35].xsect.type, z1, 1);

        
        // double w[] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
        // subcatch_setparam(0, w);

        // double v[] = {15, 15, 15, 15, 15};
        // horton_setparam(&Subcatch[0].infilparam, v);


        /*Node*/
        // printf("\n =>  Original elevation of junction's invert of NODE{%s}: %f\n", Node[0].ID, swmm_getValue(swmm_NODE_ELEV, 0));
        // printf("\n =>  Original maximum water depth of NODE{%s}: %f\n", Node[0].ID, swmm_getValue(swmm_NODE_MAXDEPTH, 0));
        // printf("\n =>  Original initial water depth of NODE{%s}: %f\n", Node[0].ID, swmm_getValue(swmm_NODE_INITDEPTH, 0));

        // printf("\n =>  Adjusted elevation of junction's invert of NODE{%s}: %f\n", Node[0].ID, swmm_getValue(swmm_NODE_ELEV, 0));
        // printf("\n =>  Adjusted maximum water depth of NODE{%s}: %f\n", Node[0].ID, swmm_getValue(swmm_NODE_MAXDEPTH, 0));
        // printf("\n =>  Adjusted initial water depth of NODE{%s}: %f\n", Node[0].ID, swmm_getValue(swmm_NODE_INITDEPTH, 0));
        /*Node*/

        /*Link*/
        // printf("\n =>  Original link maximum depth of cross section of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_YWMAX, 35));
        // printf("\n =>  Original link length of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_LENGTH, 35));
        // printf("\n =>  Original link roughness of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_ROUGHNESS, 35));
        // printf("\n =>  Original link inlet offset of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_OFFSET1, 35));
        // printf("\n =>  Original link outlet offset of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_OFFSET2, 35));
        // printf("\n =>  Original link initial flow of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_Q0, 35));
        // printf("\n =>  Original link maximum flow allowed of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_QLIMIT, 35));
        // printf("\n =>  Original link entry loss coef. of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_CLOSSINLET, 35));
        // printf("\n =>  Original link exit loss coef. of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_CLOSSOUTLET, 35));
        // printf("\n =>  Original link avg. loss coeff. of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_CLOSSINLET, 35));
        // printf("\n =>  Original link seepage loss rate of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_SEEPLOSSRATE, 35));

        // printf("\n =>  Adjusted link maximum depth of cross section of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_YWMAX, 35));
        // printf("\n =>  Adjusted link length of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_LENGTH, 35));
        // printf("\n =>  Adjusted link roughness of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_ROUGHNESS, 35));
        // printf("\n =>  Adjusted link inlet offset of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_OFFSET1, 35));
        // printf("\n =>  Adjusted link outlet offset of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_OFFSET2, 35));
        // printf("\n =>  Adjusted link initial flow of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_Q0, 35));
        // printf("\n =>  Adjusted link maximum flow allowed of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_QLIMIT, 35));
        // printf("\n =>  Adjusted link entry loss coef. of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_CLOSSINLET, 35));
        // printf("\n =>  Adjusted link exit loss coef. of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_CLOSSOUTLET, 35));
        // printf("\n =>  Adjusted link avg. loss coeff. of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_CLOSSINLET, 35));
        // printf("\n =>  Adjusted link seepage loss rate of LINK{%s}: %f\n", Link[35].ID, swmm_getValue(swmm_LINK_SEEPLOSSRATE, 35));
        /*Link*/

        /*Subcatchment*/
        // printf("\n =>  Original area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_AREA, 0));
        // printf("\n =>  Original width of overland flow path of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_WIDTH, 0));
        // printf("\n =>  Original average surface slope of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_SLOPE, 0));
        // printf("\n =>  Original percent of impervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_FRACIMPERV, 0));
        // printf("\n =>  Original manning's N for impervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_IMPERV01_N, 0));
        // printf("\n =>  Original manning's N for pervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_PERV_N, 0));
        // printf("\n =>  Original depth of depression storage on impervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_IMPERV1_DSTORE, 0));
        // printf("\n =>  Original depth of depression storage on pervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_PERV_DSTORE, 0));
        // printf("\n =>  Original perentage of impervious area with no depression storage of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_IMPERV0_FAREA, 0));

        // printf("\n =>  Adjusted area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_AREA, 0));
        // printf("\n =>  Adjusted width of overland flow path of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_WIDTH, 0));
        // printf("\n =>  Adjusted average surface slope of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_SLOPE, 0));
        // printf("\n =>  Adjusted percent of impervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_FRACIMPERV, 0));
        // printf("\n =>  Adjusted manning's N for impervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_IMPERV01_N, 0));
        // printf("\n =>  Adjusted manning's N for pervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_PERV_N, 0));
        // printf("\n =>  Adjusted depth of depression storage on impervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_IMPERV1_DSTORE, 0));
        // printf("\n =>  Adjusted depth of depression storage on pervious area of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_PERV_DSTORE, 0));
        // printf("\n =>  Adjusted perentage of impervious area with no depression storage of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_IMPERV0_FAREA, 0));
        /*Subcatchment*/

        /*Infiltration*/
        // printf("\n =>  Original maximum rate on the Horton infiltration curve of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_F0, 0));
        // printf("\n =>  Original minimum rate on the Horton infiltration curve of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_FMIN, 0));
        // printf("\n =>  Original decay constant for the Horton infiltration curve of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_DECAY, 0));
        // printf("\n =>  Original drying time of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_REGEN, 0));
        // printf("\n =>  Original maximum infiltration volume of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_FMAX, 0));

        // printf("\n =>  Adjusted maximum rate on the Horton infiltration curve of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_F0, 0));
        // printf("\n =>  Adjusted minimum rate on the Horton infiltration curve of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_FMIN, 0));
        // printf("\n =>  Adjusted decay constant for the Horton infiltration curve of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_DECAY, 0));
        // printf("\n =>  Adjusted drying time of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_REGEN, 0));
        // printf("\n =>  Adjusted maximum infiltration volume of a subcatchment{%s}: %f\n", Subcatch[0].ID, swmm_getValue(swmm_SUBCATCH_FMAX, 0));
        /*Infiltration*/