#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include<string>
#include<sstream>
#include<fstream>
#include<iostream>

class Shader
{
public:
	// O Id do programa
	unsigned int ID;

	//Construtor lê e constroi o shader
	Shader(const char* vertexPath, const char* fragmentPath);
	//Usa/ativa o shader
	void use();
	// funções de utilidade para uniforms
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};

#endif
