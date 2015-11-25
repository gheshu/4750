#ifndef DEBUGMACRO_H
#define DEBUGMACRO_H

#include "myglheaders.h"
#include "stdio.h"

#ifdef DEBUG

#define MYGLERRORMACRO {	\
	GLenum err = GL_NO_ERROR; \
	while((err = glGetError()) != GL_NO_ERROR){ \
		switch(err){	\
			case 0x0500:	\
				printf("invalid enumeration at ");	\
				PRINTLINEMACRO	\
				break;	\
			case 0x501:	\
				printf("invalid value at ");	\
				PRINTLINEMACRO	\
				break; 	\
			case 0x502: \
				printf("invalid operation at ");	\
				PRINTLINEMACRO	\
				break;	\
			case 0x503: \
				printf("stack overflow at ");	\
				PRINTLINEMACRO	\
				break;	\
			case 0x504: \
				printf("stack underflow at ");	\
				PRINTLINEMACRO	\
				break;	\
			case 0x505: \
				printf("out of memory at ");	\
				PRINTLINEMACRO	\
				break;	\
			case 0x506: \
				printf("invalid framebuffer operation at ");	\
				PRINTLINEMACRO	\
				break;	\
			case 0x507: \
				printf("context lost at ");	\
				PRINTLINEMACRO	\
				break;	\
			case 0x508: \
				printf("table too large at ");	\
				PRINTLINEMACRO	\
				break;	\
		}	\
	}	\
}

#define PRINTLINEMACRO {	\
	printf("%d in %s\n", __LINE__, __FILE__); \
}	

#else
#define MYGLERRORMACRO ;
#define PRINTLINEMACRO ;
#endif //ifdef _DEBUG

#endif //debugmacro_h
