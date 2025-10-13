#ifndef RENDER____H
#define RENDER____H

#include "World.h"
#include "Camera.h"
#include "Projection.h"
#include "Shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer
{
public:
    static void RenderScene(World* world, Camera* camera, Projection* projection)
    {
        // Clear window
        glClearColor(1.0f, 0.4f, 0.2f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
        
        if (world->getLightCount() > 0) {
            Light* light = world->getLight(0);
            if (light) {
                lightPos = light->getPosition();
                lightColour = light->getColour();
            }
        }

        for (int i = 0; i < world->getMeshCount(); i++)
        {
            Object* obj = world->getObject(i);
            if (!obj) continue;

            Material* material = obj->getMaterial();
            if (!material) continue;

            Shader* shader = material->getShader();
            if (!shader) continue;

            if (material->hasAlpha()) {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }

            shader->UseShader();

            GLuint uniformModel = shader->GetUniformLocation("model");
            GLuint uniformView = shader->GetUniformLocation("view");
            GLuint uniformProjection = shader->GetUniformLocation("projection");
            GLuint uniformTexture1 = shader->GetUniformLocation("texture1");
            GLuint uniformLightColour = shader->GetUniformLocation("lightColour");
            GLuint uniformLightPos = shader->GetUniformLocation("lightPos");
            GLuint uniformViewPos = shader->GetUniformLocation("viewPos");

            glm::mat4 view = camera->getViewMatrix();
            glm::mat4 proj = projection->getProjectionMatrix();
            glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(proj));

            glm::mat4 model = world->getModelMatrix(i);
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

            glUniform3fv(uniformLightColour, 1, glm::value_ptr(lightColour));
            glUniform3fv(uniformLightPos, 1, glm::value_ptr(lightPos));
            glm::vec3 cameraPos = camera->getPosition();
            glUniform3fv(uniformViewPos, 1, glm::value_ptr(cameraPos));

            if (material->hasTexture()) {
                glUniform1i(uniformTexture1, 0);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, material->getTexture());
            }

            Mesh* mesh = obj->getMesh();
            if (mesh) {
                mesh->RenderMesh();
            }

            if (material->hasAlpha()) {
                glDisable(GL_BLEND);
            }

            glUseProgram(0);
        }
    }

private:

};

#endif