
#include "CameraFPS.h"
#include "KeyboardController.h"
#include "MouseController.h"

//Include GLFW​

#include <GLFW/glfw3.h>
#include <iostream>

CameraFPS::CameraFPS()
{

}

CameraFPS::~CameraFPS()
{

}

void CameraFPS::Init(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up)
{
	Camera::Init(pos, target, up);
	zoom = 0.2;
	angleX = 0;
}

void CameraFPS::Reset()
{

}

void CameraFPS::Update(double dt)
{
	static const float ROTATE_SPEED = 100.0f;

	static const float ZOOM_SPEED = 10.0f;

	view = glm::normalize(target - position); // calculate the new view vector​
	right = glm::normalize(glm::cross(view, up));
	//Implement the camera rotations​
	double deltaX = MouseController::GetInstance()->GetMouseDeltaX();
	double deltaY = MouseController::GetInstance()->GetMouseDeltaY();
	angleX = -deltaX * ROTATE_SPEED * 1 * static_cast<float>(dt);
	float angleY = -deltaY * ROTATE_SPEED * 1 * static_cast<float>(dt);

	glm::mat4 yawX = glm::rotate(glm::mat4(1.f), glm::radians(angleX), glm::vec3(up.x, up.y, up.z));
	glm::mat4 yawY = glm::rotate(glm::mat4(1.f), glm::radians(angleY), glm::vec3(-right.x, -right.y, -right.z));
	yawView = (yawX + yawY) * glm::vec4(view, 0.f) * zoom;
	target = (position + yawView);


	isDirty = true;


	//change camera 
	if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) == 1)
	{
		zoom += -0.1;
		//change to first person
		if (zoom <= 0.2)
		{
			zoom = 0.2;
			firstperson = true;
		}

	}
	if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) == -1)
	{
		firstperson = false;
		zoom += 0.1;
		//limit zoom out distance
		if (zoom >= 2)
		{
			zoom =2;
		}
	}
	//firstperson properties
	if (firstperson == true)
	{
		//fps
		zoom = 0.2;
		position = *playerPosPtr;
		position.y = 1;
		target = position + yawView;
	}
	else
	{
		//tps
		target = *playerPosPtr;
		target.y = 0.8;
		position = target - yawView;
	}
}


void CameraFPS::Refresh()
{
    Camera::Refresh();
}
