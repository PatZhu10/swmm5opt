//-----------------------------------------------------------------------------
//   macros.h
//
//   Project: EPA SWMM5
//   Version: 5.2
//   Date:    11/01/21  (Build 5.2.0)
//   Author:  L. Rossman
//-----------------------------------------------------------------------------

#ifndef MACROS_H
#define MACROS_H


//--------------------------------------------------
// Macro to test for successful allocation of memory
//--------------------------------------------------
#define  MEMCHECK(x)  (((x) == NULL) ? 101 : 0 )

//--------------------------------------------------
// Macro to free a non-null pointer
//--------------------------------------------------
#define  FREE(x) { if (x) { free(x); x = NULL; } }

//---------------------------------------------------
// Conversion macros to be used in place of functions
//---------------------------------------------------
#define ABS(x)   (((x)<0) ? -(x) : (x))          /* absolute value of x   */
#define MIN(x,y) (((x)<=(y)) ? (x) : (y))        /* minimum of x and y    */
#define MAX(x,y) (((x)>=(y)) ? (x) : (y))        /* maximum of x and y    */
#define MOD(x,y) ((x)%(y))                       /* x modulus y           */
#define LOG10(x) ((x) > 0.0 ? log10((x)) : (x))  /* safe log10 of x       */
#define SQR(x)   ((x)*(x))                       /* x-squared             */
#define SGN(x)   (((x)<0) ? (-1) : (1))          /* sign of x             */
#define SIGN(x,y) ((y) >= 0.0 ? fabs(x) : -fabs(x))
#define UCHAR(x) (((x) >= 'a' && (x) <= 'z') ? ((x)&~32) : (x))
                                                 /* uppercase char of x   */
#define ARRAY_LENGTH(x) (sizeof(x)/sizeof(x[0])) /* length of array x     */

//-------------------------------------------------
// Macro to evaluate function x with error checking
//-------------------------------------------------
#define CALL(x) (ErrorCode = ((ErrorCode>0) ? (ErrorCode) : (x)))


#endif //MACROS_H
