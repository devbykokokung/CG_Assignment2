#ifndef WINDOW____H
#define WINDOW____H

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
    public:
        Window();
        Window(GLint windowWidth, GLint windowHeight, GLint majorVersion, GLint minorVersion);
        ~Window();

        int initialise();

        GLint getBufferWidth() {return bufferWidth;}
        GLint getBufferHeight() {return bufferHeight;}

        bool getShouldClose() {return glfwWindowShouldClose(mainWindow);}

        void swapBuffers() {glfwSwapBuffers(mainWindow);}

        GLFWwindow* getWindow() { return mainWindow; }

        void waitClose() { while (!glfwWindowShouldClose(mainWindow)) { glfwPollEvents(); } }

        bool* getKeys() { return keys; }
        
        GLfloat getXChange();
        GLfloat getYChange();
        bool isMouseButtonPressed(int button);

    private:
        GLFWwindow* mainWindow;
        GLint glfwMajorVersion, glfwMinorVersion;
        GLint width, height;
        GLint bufferWidth, bufferHeight;

        bool keys[1024];
        GLfloat lastX;
        GLfloat lastY;
        GLfloat xChange;
        GLfloat yChange;
        bool mouseFirstMoved;
        bool mouseButtons[8];

        void createCallbacks();
        static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
        static void handleMouse(GLFWwindow* window, double xPos, double yPos);
        static void handleMouseButton(GLFWwindow* window, int button, int action, int mods);
};

#endif