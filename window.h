#ifndef WINDOW_H
#define WINDOW_H

#include "myglheaders.h"
#include <string>

class Window
{
private:
    GLFWwindow* window;
    static void error_callback(int error, const char* description);
public:
    Window(int width, int height, int major_ver, int minor_ver, int msaa, std::string title);
    ~Window();
    GLFWwindow* getWindow();

};
#endif
