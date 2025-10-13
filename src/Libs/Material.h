#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"
#include "stb_image.h"
#include <GL/glew.h>
#include <iostream>
#include <string>

class Material {
public:
    Material() : textureID(0), textureLoaded(false), hasAlphaTransparency(false) {
        shader = new Shader();
    }

    ~Material() {
        if (shader) {
            delete shader;
        }
        if (textureLoaded && textureID != 0) {
            glDeleteTextures(1, &textureID);
        }
    }

    void loadShader(const char* vertexPath, const char* fragmentPath) {
        if (shader) {
            shader->CreateFromFiles(vertexPath, fragmentPath);
        }
    }

    bool loadTexture(const char* texturePath, bool flipV = false) {
        stbi_set_flip_vertically_on_load(flipV);
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        
        
        unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

        if (!data) {
            std::cerr << "Failed to load texture: " << texturePath << " - " << stbi_failure_reason() << "\n";
            return false;
        }

        GLenum format = GL_RGB;
        if (nrChannels == 1) format = GL_RED;
        else if (nrChannels == 3) format = GL_RGB;
        else if (nrChannels == 4) {
            format = GL_RGBA;
            hasAlphaTransparency = true;
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        stbi_image_free(data);
        textureLoaded = true;

        if (flipV) {
            stbi_set_flip_vertically_on_load(false);
        }

        return true;
    }

    void setTexture(GLuint texID) {
        this->textureID = texID;
        this->textureLoaded = true;
    }

    void enableAlpha(bool enable = true) {
        hasAlphaTransparency = enable;
    }

    bool hasAlpha() const {
        return hasAlphaTransparency;
    }

    Shader* getShader() const {
        return shader;
    }

    GLuint getTexture() const {
        return textureID;
    }

    bool hasTexture() const {
        return textureLoaded && textureID != 0;
    }

    void apply() {
        if (shader) {
            shader->UseShader();
        }
        
        if (textureLoaded && textureID != 0) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureID);
        }
    }

private:
    Shader* shader;
    GLuint textureID;
    bool textureLoaded;
    bool hasAlphaTransparency;
};

#endif