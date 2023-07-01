#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include<string>
#include<sstream>
#include<fstream>
#include<iostream>

class Shader
{
public:
	// O Id do programa
	unsigned int ID;

	//Construtor l� e constroi o shader
	Shader(const char* vertexPath, const char* fragmentPath);
	//Usa/ativa o shader
	void use();
	// fun��es de utilidade para uniforms
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string& name, const glm::vec2 &value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;
	void setMat2(const std::string& name, const glm::mat2& mat) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
private:
	//fun��es de utilidade para checar erros de compila��o ou link de shaders.
	void checkCompileErrors(GLuint, std::string type);
};

#endif