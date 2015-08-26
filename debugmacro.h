#ifndef DEBUGMACRO_H
#define DEBUGMACRO_H

//#define _DEBUG

#include <iostream>

#ifdef _DEBUG

#define MYGLERRORMACRO {	\
	GLenum errCode; \
	const GLubyte *errString; \
	if ((errCode = glGetError()) != GL_NO_ERROR) \
	{ \
		errString = gluErrorString(errCode); \
		printf("\n%s\n", errString); \
		printf("in function %s at %s, line %d.\n", __FUNCTION__, __FILE__, __LINE__); \
		std::cin.ignore();	\
		exit(1);	\
	} \
}

#define PRINTLINEMACRO {	\
	printf("%d in %s\n", __LINE__, __FILE__); \
}	

#else
#define MYGLERRORMACRO ;
#define PRINTLINEMACRO ;
#endif //ifdef _DEBUG

#define PRINTLINEMACRO {	\
	printf("%d in %s\n", __LINE__, __FILE__); \
}	\

#endif //debugmacro_h