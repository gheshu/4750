#ifndef INPUT_H
#define INPUT_H

#include "myglheaders.h"

class Camera;

class Input
{
private:
GLFWwindow* m_glwindow;

static bool m_rightMouseDown, m_leftMouseDown;
static float m_scrollOffset, m_cursorX, m_cursorY, m_relCursorX, m_relCursorY;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

public:
    Input(GLFWwindow* window);
    ~Input();
    void poll(Camera& cam);
	void poll();
    static bool rightMouseDown();
    static bool leftMouseDown();
    static float scrollOffset();
    static float cursorX();
    static float cursorY();
    static float relCursorX();
    static float relCursorY();
    static int activeKey();

};
#endif
