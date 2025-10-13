#undef GLFW_DLL
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

#include <vector>
#include <cmath>

#include "Libs/Shader.h"
#include "Libs/Window.h"
#include "Libs/Mesh.h"
#include "Libs/Material.h"
#include "Libs/Object.h"
#include "Libs/World.h"
#include "Libs/Projection.h"
#include "Libs/Camera.h"
#include "Libs/Renderer.h"
#include "Libs/Light.h"

const GLint WIDTH = 800, HEIGHT = 600;


int main()
{
    Window mainWindow = Window(WIDTH, HEIGHT, 3, 3);
    mainWindow.initialise();

    World world = World();

    Projection projection = Projection(70.0f, (float)mainWindow.getBufferWidth() / (float)mainWindow.getBufferHeight(), 0.1f, 1000.0f);

    // Initialize camera with FPS controls
//     Camera Position: (-189.14, 136.00, 254.48)
// Up Vector: (0.38, 0.81, -0.44)
// Yaw: -48.75 degrees
// Pitch: -35.50 degrees
// Movement Speed: 50.00
// Turn Speed: 0.10
    Camera camera = Camera(
        glm::vec3(-189.14, 136.00, 254.48),  // position
        glm::vec3(0.38, 0.81, -0.44),     // up vector
        -48.75f,                         // yaw
        -35.5f,                          // pitch
        50.0f,                           // movement speed
        0.1f                             // turn speed
    );

    // island terrain
    Object island = Object();
    island.loadOBJ("Models/islandsnow.obj");

    Material island_mat = Material();
    island_mat.loadShader("Shaders/shader.vert", "Shaders/shader.frag");
    island_mat.loadTexture("Textures/islandsnow.jpg", true);
    island_mat.enableAlpha(false);

    island.setMaterial(&island_mat);

    int island_world = world.addObject(&island);
    world.setTransform(island_world, [&]() {
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -200.0f, 0.0f));
        // model = glm::rotate(model, glm::radians(2.0f), glm::vec3(1.0f, 0.3f, 0.5f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        return model;
        }());


    // helicopter
    Object helicopter = Object();
    helicopter.loadOBJ("Models/helicopter.obj");

    Material helicopter_mat = Material();
    helicopter_mat.loadShader("Shaders/shader.vert", "Shaders/shader.frag");
    helicopter_mat.loadTexture("Textures/helicopter.png", true);
    helicopter_mat.enableAlpha(false);

    helicopter.setMaterial(&helicopter_mat);

    int helicopter_world = world.addObject(&helicopter);
    world.setTransform(helicopter_world, [&]() {
        glm::mat4 model(1.0f);
        model[0] = glm::vec4(0.498913f, -0.133145f, 0.305551f, 0.0f);
        model[1] = glm::vec4(0.160218f, 0.578133f, -0.00968605f, 0.0f);
        model[2] = glm::vec4(-0.292266f, 0.0896464f, 0.516283f, 0.0f);
        model[3] = glm::vec4(-166.208f, 91.6584f, 195.154f, 1.0f);
        return model;
        }());

    // ajmo
    Object ajmo = Object();
    ajmo.loadOBJ("Models/ajmo.obj");

    Material ajmo_mat = Material();
    ajmo_mat.loadShader("Shaders/shader.vert", "Shaders/shader.frag");
    ajmo_mat.loadTexture("Textures/human.png", true);
    ajmo_mat.enableAlpha(false);

    ajmo.setMaterial(&ajmo_mat);

    int ajmo_world = world.addObject(&ajmo);
    world.setTransform(ajmo_world, [&]() {
        glm::mat4 model(1.0f);
        model[0] = glm::vec4(4.63685, -0.117812, 7.94104, 0);
        model[1] = glm::vec4(2.50064, 8.74964, -1.33029, 0);
        model[2] = glm::vec4(-7.53812, 2.83, 4.44337, 0);
        model[3] = glm::vec4(-146.087, 81.9261, 210.82, 1);

        return model;
        }());


    // face ajmo
    Object face_ajmo = Object();
    face_ajmo.loadOBJ("Models/face_ajmo.obj");

    Material face_ajmo_mat = Material();
    face_ajmo_mat.loadShader("Shaders/shader.vert", "Shaders/shader.frag");
    face_ajmo_mat.loadTexture("Textures/face_ajmo.png", true);
    face_ajmo_mat.enableAlpha(false);

    face_ajmo.setMaterial(&face_ajmo_mat);

    int face_ajmo_world = world.addObject(&face_ajmo);
    world.setTransform(face_ajmo_world, [&]() {
        glm::mat4 model(1.0f);
        model[0] = glm::vec4(5.87182, -2.4146, 12.2237, 0);
        model[1] = glm::vec4(5.2733, 12.7248, -0.0195468, 0);
        model[2] = glm::vec4(-11.2889, 4.68813, 6.3488, 0);
        model[3] = glm::vec4(-146.818, 76.6361, 206.903, 1);
        return model;
        }());

    // aurora
    // Object aurora = Object();
    // aurora.loadOBJ("Models/aurora.obj");

    // Material aurora_mat = Material();
    // aurora_mat.loadShader("Shaders/shader.vert", "Shaders/shader.frag");
    // aurora_mat.loadTexture("Textures/Aurora_Rainbow.png", true);

    // aurora.setMaterial(&aurora_mat);

    // int aurora_world = world.addObject(&aurora);
    // world.setTransform(aurora_world, [&]() {
    //     glm::mat4 model(1.0f);
    //     model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
    //     return model;
    //     }());

    // aurora 01
// 23.9181 0 11.255 0 
// 0 26.4342 0 0 
// -11.255 0 23.9181 0 
// 617.015 -240.63 -121.785 1 

    Object aurora_1 = Object();
    aurora_1.loadOBJ("Models/aurora.obj");

    Material aurora_1_mat = Material();
    aurora_1_mat.loadShader("Shaders/shader.vert", "Shaders/shader.frag");
    aurora_1_mat.loadTexture("Textures/Aurora_Rainbow_transparent.png", true);

    aurora_1.setMaterial(&aurora_1_mat);

    int aurora_1_world = world.addObject(&aurora_1);
    world.setTransform(aurora_1_world, [&]() {
        glm::mat4 model(1.0f);
        model[0] = glm::vec4(23.9181, 0, 11.255, 0);
        model[1] = glm::vec4(0, 26.4342, 0, 0);
        model[2] = glm::vec4(-11.255, 0, 23.9181, 0);
        model[3] = glm::vec4(617.015, -240.63, -121.785, 1);
        return model;
        }());


    // aurora 02
//         21.1386 0 15.8713 0 
// 0 26.4342 0 0 
// -15.8713 0 21.1386 0 
// 599.77 -240.63 38.8487 1 
    Object aurora_2 = Object();
    aurora_2.loadOBJ("Models/aurora.obj");

    Material aurora_2_mat = Material();
    aurora_2_mat.loadShader("Shaders/shader.vert", "Shaders/shader.frag");
    aurora_2_mat.loadTexture("Textures/Aurora_Rainbow_transparent.png", true);

    aurora_2.setMaterial(&aurora_2_mat);

    int aurora_2_world = world.addObject(&aurora_2);
    world.setTransform(aurora_2_world, [&]() {
        glm::mat4 model(1.0f);
        model[0] = glm::vec4(21.1386, 0, 15.8713, 0);
        model[1] = glm::vec4(0, 26.4342, 0, 0);
        model[2] = glm::vec4(-15.8713, 0, 21.1386, 0);
        model[3] = glm::vec4(599.77, -240.63, 38.8487, 1);
        return model;
        }());


    // aurora 03
// 22.2936 0 14.2026 0 
// 0 26.4342 0 0 
// -14.2026 0 22.2936 0 
// 525.241 -240.63 78.0279 1 
    Object aurora_3 = Object();
    aurora_3.loadOBJ("Models/aurora.obj");

    Material aurora_3_mat = Material();
    aurora_3_mat.loadShader("Shaders/shader.vert", "Shaders/shader.frag");
    aurora_3_mat.loadTexture("Textures/Aurora_Rainbow_transparent.png", true);

    aurora_3.setMaterial(&aurora_3_mat);

    int aurora_3_world = world.addObject(&aurora_3);
    world.setTransform(aurora_3_world, [&]() {
        glm::mat4 model(1.0f);
        model[0] = glm::vec4(22.2936, 0, 14.2026, 0);
        model[1] = glm::vec4(0, 26.4342, 0, 0);
        model[2] = glm::vec4(-14.2026, 0, 22.2936, 0);
        model[3] = glm::vec4(525.241, -240.63, 78.0279, 1);
        return model;
        }());

    // aurora 04
// 25.5561 0 6.75222 0 
// 0 26.4342 0 0 
// -6.75222 0 25.5561 0 
// 530.763 -240.63 -20.5035 1 

    Object aurora_4 = Object();
    aurora_4.loadOBJ("Models/aurora.obj");

    Material aurora_4_mat = Material();
    aurora_4_mat.loadShader("Shaders/shader.vert", "Shaders/shader.frag");
    aurora_4_mat.loadTexture("Textures/Aurora_Rainbow_transparent.png", true);

    aurora_4.setMaterial(&aurora_4_mat);

    int aurora_4_world = world.addObject(&aurora_4);
    world.setTransform(aurora_4_world, [&]() {
        glm::mat4 model(1.0f);
        model[0] = glm::vec4(25.5561, 0, 6.75222, 0);
        model[1] = glm::vec4(0, 26.4342, 0, 0);
        model[2] = glm::vec4(-6.75222, 0, 25.5561, 0);
        model[3] = glm::vec4(530.763, -240.63, -20.5035, 1);
        return model;
        }());

    // Light source (positioned above the scene)
    Light mainLight = Light(
        glm::vec3(0.0f, 100.0f, 0.0f),
        glm::vec3(1.0f, 0.6f, 0.3f),  // Warm orange/yellow sunset color
        2.0f
    );

    world.addLight(&mainLight);

    // Time variables for delta time calculation
    GLfloat deltaTime = 0.0f;
    GLfloat lastTime = 0.0f;

    // Game loop
    while (!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        // Get + Handle user input events
        glfwPollEvents();

        // Handle keyboard input (WASD movement)
        camera.keyControl(mainWindow.getKeys(), deltaTime);

        // Handle mouse input (only when left button is pressed)
        if (mainWindow.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            camera.mouseControl(mainWindow.getXChange() * 2.5, mainWindow.getYChange() * 2.5);
        }
        else
        {
            // Clear mouse changes when not pressing left button
            mainWindow.getXChange();
            mainWindow.getYChange();
        }


        // // glm::mat4 modelMatrix = world.getModelMatrix(ajmo_world);

        // // Get current model matrix for aurora only
        // glm::mat4 auroraMatrix = world.getModelMatrix(aurora_world);

        // // Translation controls (Arrow keys)
        // glm::vec3 translation(0.0f);
        // if (mainWindow.getKeys()[GLFW_KEY_UP]) translation.z -= 0.01f;
        // if (mainWindow.getKeys()[GLFW_KEY_DOWN]) translation.z += 0.01f;
        // if (mainWindow.getKeys()[GLFW_KEY_LEFT]) translation.x -= 0.01f;
        // if (mainWindow.getKeys()[GLFW_KEY_RIGHT]) translation.x += 0.01f;
        // if (mainWindow.getKeys()[GLFW_KEY_PAGE_UP]) translation.y += 0.01f;
        // if (mainWindow.getKeys()[GLFW_KEY_PAGE_DOWN]) translation.y -= 0.01f;

        // // Rotation controls (Q/E for Y-axis, Z/X for X-axis, C/V for Z-axis)
        // glm::vec3 rotation(0.0f);
        // if (mainWindow.getKeys()[GLFW_KEY_Q]) rotation.y += 0.1f;
        // if (mainWindow.getKeys()[GLFW_KEY_E]) rotation.y -= 0.1f;
        // if (mainWindow.getKeys()[GLFW_KEY_Z]) rotation.x += 0.1f;
        // if (mainWindow.getKeys()[GLFW_KEY_X]) rotation.x -= 0.1f;
        // if (mainWindow.getKeys()[GLFW_KEY_C]) rotation.z += 0.1f;
        // if (mainWindow.getKeys()[GLFW_KEY_V]) rotation.z -= 0.1f;

        // // Scale controls (O to increase, P to decrease)
        // static float scale = 1.0f;
        // if (mainWindow.getKeys()[GLFW_KEY_O]) {
        //     scale += 0.0005f;
        //     if (scale > 2.0f) scale = 2.0f;
        // }
        // if (mainWindow.getKeys()[GLFW_KEY_P]) {
        //     scale -= 0.0005f;
        //     if (scale < 0.1f) scale = 0.1f;
        // }

        // // Apply transformations to aurora only
        // if (glm::length(translation) > 0.0f || glm::length(rotation) > 0.0f || mainWindow.getKeys()[GLFW_KEY_O] || mainWindow.getKeys()[GLFW_KEY_P]) {
        //     world.setTransform(aurora_world, [&]() {
        //         glm::mat4 model = auroraMatrix;
        //         model = glm::translate(model, translation);
        //         if (rotation.x != 0.0f) model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        //         if (rotation.y != 0.0f) model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        //         if (rotation.z != 0.0f) model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        //         if (mainWindow.getKeys()[GLFW_KEY_O] || mainWindow.getKeys()[GLFW_KEY_P]) {
        //             model = glm::scale(model, glm::vec3(scale, scale, scale));
        //         }
        //         return model;
        //         }());

        //     auroraMatrix = world.getModelMatrix(aurora_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << auroraMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }

        // // คุมใหญ่ เล็กของ ajmo_world ด้วย key o และ p
        // if (mainWindow.getKeys()[GLFW_KEY_O]) {
        //     world.setTransform(ajmo_world, [&]() {
        //         static float scale = 1.0f;
        //         scale += 0.000005f;
        //         if (scale > 2.0f) scale = 2.0f;
        //         glm::mat4 model = modelMatrix;
        //         model = glm::scale(model, glm::vec3(scale, scale, scale));
        //         return model;
        //         }());
        //     modelMatrix = world.getModelMatrix(ajmo_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << modelMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }
        // if (mainWindow.getKeys()[GLFW_KEY_P]) {
        //     world.setTransform(ajmo_world, [&]() {
        //         static float scale = 1.0f;
        //         scale -= 0.000005f;
        //         if (scale < 0.1f) scale = 0.1f;
        //         glm::mat4 model = modelMatrix;
        //         model = glm::scale(model, glm::vec3(scale, scale, scale));
        //         return model;
        //         }());
        //     // print current vector
        //     modelMatrix = world.getModelMatrix(ajmo_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << modelMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }

        // if (mainWindow.getKeys()[GLFW_KEY_UP]) {
        //     world.setTransform(ajmo_world, [&]() {
        //         glm::mat4 model = modelMatrix;
        //         model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.001f));
        //         return model;
        //         }());
        //     modelMatrix = world.getModelMatrix(ajmo_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << modelMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }
        // if (mainWindow.getKeys()[GLFW_KEY_DOWN]) {
        //     world.setTransform(ajmo_world, [&]() {
        //         glm::mat4 model = modelMatrix;
        //         model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.001f));
        //         return model;
        //         }());
        //     modelMatrix = world.getModelMatrix(ajmo_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << modelMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }
        // if (mainWindow.getKeys()[GLFW_KEY_LEFT]) {
        //     world.setTransform(ajmo_world, [&]() {
        //         glm::mat4 model = modelMatrix;
        //         model = glm::translate(model, glm::vec3(-0.001f, 0.0f, 0.0f));
        //         return model;
        //         }());
        //     modelMatrix = world.getModelMatrix(ajmo_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << modelMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }
        // if (mainWindow.getKeys()[GLFW_KEY_RIGHT]) {
        //     world.setTransform(ajmo_world, [&]() {
        //         glm::mat4 model = modelMatrix;
        //         model = glm::translate(model, glm::vec3(0.001f, 0.0f, 0.0f));
        //         return model;
        //         }());
        //     modelMatrix = world.getModelMatrix(ajmo_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << modelMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }
        // if (mainWindow.getKeys()[GLFW_KEY_PAGE_UP]) {
        //     world.setTransform(ajmo_world, [&]() {
        //         glm::mat4 model = modelMatrix;
        //         model = glm::translate(model, glm::vec3(0.0f, 0.001f, 0.0f));
        //         return model;
        //         }());
        //     modelMatrix = world.getModelMatrix(ajmo_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << modelMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }
        // if (mainWindow.getKeys()[GLFW_KEY_PAGE_DOWN]) {
        //     world.setTransform(ajmo_world, [&]() {
        //         glm::mat4 model = modelMatrix;
        //         model = glm::translate(model, glm::vec3(0.0f, -0.001f, 0.0f));
        //         return model;
        //         }());
        //     modelMatrix = world.getModelMatrix(ajmo_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << modelMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }


        // // rotate ajmo_world with key q and e
        // if (mainWindow.getKeys()[GLFW_KEY_Q]) {
        //     world.setTransform(ajmo_world, [&]() {
        //         glm::mat4 model = modelMatrix;
        //         model = glm::rotate(model, glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
        //         return model;
        //         }());
        //     modelMatrix = world.getModelMatrix(ajmo_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << modelMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }
        // if (mainWindow.getKeys()[GLFW_KEY_E]) {
        //     world.setTransform(ajmo_world, [&]() {
        //         glm::mat4 model = modelMatrix;
        //         model = glm::rotate(model, glm::radians(-0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
        //         return model;
        //         }());
        //     modelMatrix = world.getModelMatrix(ajmo_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << modelMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }

        // // rotate ajmo_world with key z and x
        // if (mainWindow.getKeys()[GLFW_KEY_Z]) {
        //     world.setTransform(ajmo_world, [&]() {
        //         glm::mat4 model = modelMatrix;
        //         model = glm::rotate(model, glm::radians(0.1f), glm::vec3(1.0f, 0.0f, 0.0f));
        //         return model;
        //         }());
        //     modelMatrix = world.getModelMatrix(ajmo_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << modelMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }
        // if (mainWindow.getKeys()[GLFW_KEY_X]) {
        //     world.setTransform(ajmo_world, [&]() {
        //         glm::mat4 model = modelMatrix;
        //         model = glm::rotate(model, glm::radians(-0.1f), glm::vec3(1.0f, 0.0f, 0.0f));
        //         return model;
        //         }());
        //     modelMatrix = world.getModelMatrix(ajmo_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << modelMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }

        // // rotate ajmo_world with key c and v
        // if (mainWindow.getKeys()[GLFW_KEY_C]) {
        //     world.setTransform(ajmo_world, [&]() {
        //         glm::mat4 model = modelMatrix;
        //         model = glm::rotate(model, glm::radians(0.1f), glm::vec3(0.0f, 0.0f, 1.0f));
        //         return model;
        //         }());
        //     modelMatrix = world.getModelMatrix(ajmo_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << modelMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }


        // if (mainWindow.getKeys()[GLFW_KEY_V]) {
        //     world.setTransform(ajmo_world, [&]() {
        //         glm::mat4 model = modelMatrix;
        //         model = glm::rotate(model, glm::radians(-0.1f), glm::vec3(0.0f, 0.0f, 1.0f));
        //         return model;
        //         }());
        //     modelMatrix = world.getModelMatrix(ajmo_world);
        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << modelMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }

        // /////////////////////////////////
        // /////////////////////////////////
        // /////////////////////////////////
        // /////////////////////////////////
        // /////////////////////////////////
        // /////////////////////////////////


        // // Get current model matrices
        // glm::mat4 helicopterMatrix = world.getModelMatrix(helicopter_world);
        // glm::mat4 ajmoMatrix = world.getModelMatrix(ajmo_world);

        // // Translation controls (Arrow keys)
        // glm::vec3 translation(0.0f);
        // if (mainWindow.getKeys()[GLFW_KEY_UP]) translation.z -= 0.1f;
        // if (mainWindow.getKeys()[GLFW_KEY_DOWN]) translation.z += 0.1f;
        // if (mainWindow.getKeys()[GLFW_KEY_LEFT]) translation.x -= 0.1f;
        // if (mainWindow.getKeys()[GLFW_KEY_RIGHT]) translation.x += 0.1f;
        // if (mainWindow.getKeys()[GLFW_KEY_PAGE_UP]) translation.y += 0.1f;
        // if (mainWindow.getKeys()[GLFW_KEY_PAGE_DOWN]) translation.y -= 0.1f;

        // // Rotation controls (Q/E for Y-axis, Z/X for X-axis, C/V for Z-axis)
        // glm::vec3 rotation(0.0f);
        // if (mainWindow.getKeys()[GLFW_KEY_Q]) rotation.y += 1.0f;  // Rotate left
        // if (mainWindow.getKeys()[GLFW_KEY_E]) rotation.y -= 1.0f;  // Rotate right
        // if (mainWindow.getKeys()[GLFW_KEY_Z]) rotation.x += 1.0f;  // Pitch up
        // if (mainWindow.getKeys()[GLFW_KEY_X]) rotation.x -= 1.0f;  // Pitch down
        // if (mainWindow.getKeys()[GLFW_KEY_C]) rotation.z += 1.0f;  // Roll left
        // if (mainWindow.getKeys()[GLFW_KEY_V]) rotation.z -= 1.0f;  // Roll right

        // // Scale controls (O to increase, P to decrease)
        // static float scale = 1.0f;
        // if (mainWindow.getKeys()[GLFW_KEY_O]) {
        //     scale += 0.01f;
        //     if (scale > 2.0f) scale = 2.0f;
        // }
        // if (mainWindow.getKeys()[GLFW_KEY_P]) {
        //     scale -= 0.01f;
        //     if (scale < 0.1f) scale = 0.1f;
        // }

        // // Apply transformations to helicopter
        // if (glm::length(translation) > 0.0f || glm::length(rotation) > 0.0f || mainWindow.getKeys()[GLFW_KEY_O] || mainWindow.getKeys()[GLFW_KEY_P]) {
        //     world.setTransform(helicopter_world, [&]() {
        //         glm::mat4 model = helicopterMatrix;
        //         model = glm::translate(model, translation);
        //         if (rotation.x != 0.0f) model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        //         if (rotation.y != 0.0f) model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        //         if (rotation.z != 0.0f) model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        //         if (mainWindow.getKeys()[GLFW_KEY_O] || mainWindow.getKeys()[GLFW_KEY_P]) {
        //             model = glm::scale(model, glm::vec3(scale, scale, scale));
        //         }
        //         return model;
        //         }());

        //     // Apply same transformations to ajmo
        //     world.setTransform(ajmo_world, [&]() {
        //         glm::mat4 model = ajmoMatrix;
        //         model = glm::translate(model, translation);
        //         if (rotation.x != 0.0f) model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        //         if (rotation.y != 0.0f) model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        //         if (rotation.z != 0.0f) model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        //         if (mainWindow.getKeys()[GLFW_KEY_O] || mainWindow.getKeys()[GLFW_KEY_P]) {
        //             model = glm::scale(model, glm::vec3(scale, scale, scale));
        //         }
        //         return model;
        //         }());

        //     glm::mat4 helicopterMatrix = world.getModelMatrix(helicopter_world);

        //     for (int i = 0; i < 4; ++i) {
        //         for (int j = 0; j < 4; ++j) {
        //             std::cout << helicopterMatrix[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }

        // Render scene
        Renderer::RenderScene(&world, &camera, &projection);

        mainWindow.swapBuffers();
    }

    return 0;
}
