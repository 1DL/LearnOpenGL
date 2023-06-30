#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

//Define opções de movimento da camera. Usado como abstração para ficar longe de implementações de input específicas dos sistemas de janela e operacional
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// valores padrão da camera
const float YAW			= -90.0f;
const float PITCH		= 0.00f;
const float SPEED		= 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM		= 45.0f;

// uma classe abstrata de camera que processa input e calcula os angulos de euler, vetores e matrizes para usar no opengl.

class Camera
{
public:
	//atributos da camera
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	//Angulos de Euler
	float Yaw;
	float Pitch;
	
	//Opções de camera
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	//Construtor com vetores
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	//Construtor com valores scalar
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yay, float pitch);
	//retorna a matriz de visualização (view) calculadas com angulos de euler e a matriz LookAt
	glm::mat4 GetViewMatrix();
	//Processa input recebido de qualquer sistema baseado em teclado. Aceita inputs na forma da camera no enum definido (para abstrair dos sistemas de janelas)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	// processa input recebido do mouse. Espera um offset em ambos eixos x e y.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	// processa input do scroll(bolinha) do mouse. Apenas exige o input no eixo vertical y
	void ProcessMouseScroll(float yoffset);
private:
	//calcula o vetor frontal da camera com angulos euler atualizados
	void updateCameraVectors();
public:

};

#endif