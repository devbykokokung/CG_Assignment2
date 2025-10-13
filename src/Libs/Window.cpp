#include "Window.h"

Window::Window()
{
    width = 800;
    height = 600;
    glfwMajorVersion = 3;
    glfwMinorVersion = 1;

    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }

    for (size_t i = 0; i < 8; i++)
    {
        mouseButtons[i] = 0;
    }

    xChange = 0.0f;
    yChange = 0.0f;
    mouseFirstMoved = true;
}

Window::Window(GLint windowWidth, GLint windowHeight, GLint majorVersion, GLint minorVersion)
{
    width = windowWidth;
    height = windowHeight;
    glfwMajorVersion = majorVersion;
    glfwMinorVersion = minorVersion;

    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }

    for (size_t i = 0; i < 8; i++)
    {
        mouseButtons[i] = 0;
    }

    xChange = 0.0f;
    yChange = 0.0f;
    mouseFirstMoved = true;
}

Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

int Window::initialise()
{
    //init GLFW
    if (!glfwInit())
    {
        printf("GLFW initialisation failed!");
        glfwTerminate();
        return 1;
    }

    //Setup GLFW window properties
    //OpenGL version (using 3.1)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfwMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfwMinorVersion);

    //Core Profile = No Backwards Compatibility
    glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);

    if (!mainWindow)
    {
        printf("GLFW window creation failed!");
        glfwTerminate();
        return 1;
    }

    //Get Buffer size information
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    //Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    //Allow modern extension features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        printf("GLEW initialisation failed!");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    //Setup Viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    glfwSetWindowUserPointer(mainWindow, this);
    createCallbacks();

    return 0;
}

void Window::createCallbacks()
{
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
    glfwSetMouseButtonCallback(mainWindow, handleMouseButton);
}

GLfloat Window::getXChange()
{
    GLfloat theChange = xChange;
    xChange = 0.0f;
    return theChange;
}

GLfloat Window::getYChange()
{
    GLfloat theChange = yChange;
    yChange = 0.0f;
    return theChange;
}

bool Window::isMouseButtonPressed(int button)
{
    if (button >= 0 && button < 8)
    {
        return mouseButtons[button];
    }
    return false;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            theWindow->keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            theWindow->keys[key] = false;
        }
    }
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (theWindow->mouseFirstMoved)
    {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = false;
    }

    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
}

void Window::handleMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (button >= 0 && button < 8)
    {
        if (action == GLFW_PRESS)
        {
            theWindow->mouseButtons[button] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            theWindow->mouseButtons[button] = false;
        }
    }
}