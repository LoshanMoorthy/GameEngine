/**
   @brief Purpose of util.h:
   This header file defines utility macros for error handling, 
   which simplify the process of reporting errors
   and exiting/returning from functions within the game engine.

   Props to jdh for inspiration.
*/

#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#define ERROR_EXIT(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define ERROR_RETURN(R, ...) { fprintf(stderr, __VA_ARGS__); return R; }


#endif
