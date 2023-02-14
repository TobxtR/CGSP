
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "SceneAssignment2.h"

class Application
{
public:
	

	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);



private:

	//Declare a window object
	StopWatch m_timer;

	
	bool enablePointer = false;
	bool showPointer = false;




};

#endif