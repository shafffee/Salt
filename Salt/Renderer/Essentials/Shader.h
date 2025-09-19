#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <Logging.h>
#include <glm/gtc/type_ptr.hpp>
#include <Material.h>

namespace salt {
    class Shader
    {
    public:
        unsigned int ID;
        // constructor generates the shader on the fly
        // ------------------------------------------------------------------------

        Shader()
        {
          ID = 0; //mb refactor this
        }
        Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
        {

            const char* vShaderCode = vertexShaderCode.c_str();
            const char* fShaderCode = fragmentShaderCode.c_str();
            // 2. compile shaders
            unsigned int vertex, fragment;
            // vertex shader
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);
            checkCompileErrors(vertex, "VERTEX");
            // fragment Shader
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);
            checkCompileErrors(fragment, "FRAGMENT");
            // shader Program
            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            glLinkProgram(ID);
            checkCompileErrors(ID, "PROGRAM");
            // delete the shaders as they're linked into our program now and no longer necessary
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }
        // activate the shader
        // ------------------------------------------------------------------------
        void bind()
        {
            glUseProgram(ID);
        }
        // utility uniform functions
        void setBool(const std::string& name, bool value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        }
        void setInt(const std::string& name, int value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }
        void setFloat(const std::string& name, float value) const
        {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }
        void setMat4(const std::string& name, const glm::mat4& matrix) const {
          glUniformMatrix4fv(
            glGetUniformLocation(ID, name.c_str()), // Get uniform location
            1,                                      // Number of matrices
            GL_FALSE,                               // Transpose? (GL_TRUE for row-major)
            glm::value_ptr(matrix)                  // Pointer to matrix data
          );
        }
        void setVec3(const std::string& name, const glm::vec3& value) const
        {
          glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
        void setUint64Array(const std::string& name, int size, const GLuint64* values) const
        {
            GLint location = glGetUniformLocation(ID, name.c_str());
            if (location != -1) {
                glUniformHandleui64vARB(location, 8, values);
            }
        }
        void setMaterial(const Material& material) {
          setVec3("material.ambient", material.ambient);
          setVec3("material.diffuse", material.diffuse);
          setVec3("material.specular", material.specular);
          setFloat("material.shininess", material.shininess);
        }
    private:
        // utility function for checking shader compilation/linking errors.
        // ------------------------------------------------------------------------
        void checkCompileErrors(unsigned int shader, std::string type)
        {
            int success;
            char infoLog[1024];
            if (type != "PROGRAM")
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    Logging::Error("Shader compilation error:\t" + type + "\n\tInfoLog:" + infoLog);
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    Logging::Error("Shader program linking error:\t" + type + "\n\tInfoLog:" + infoLog);
                }
            }
        }
    };
}