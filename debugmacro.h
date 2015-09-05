#ifndef DEBUGMACRO_H
#define DEBUGMACRO_H

#define _DEBUG

#include "myglheaders.h"
#include "stdio.h"
#include <iostream>

#ifdef _DEBUG

#define MYGLERRORMACRO ;

#define PRINTLINEMACRO {	\
	printf("%d in %s\n", __LINE__, __FILE__); \
}	

#else
#define MYGLERRORMACRO ;
#define PRINTLINEMACRO ;
#endif //ifdef _DEBUG

#endif //debugmacro_h