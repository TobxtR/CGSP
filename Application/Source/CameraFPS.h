#ifndef CAMERA_FPS_H

#define CAMERA_FPS_H​

#include "Camera.h"
class CameraFPS :

    public Camera
{
public:
    
    CameraFPS();
    ~CameraFPS();
    void Init(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up);

        void Reset();

        void Update(double dt);
        glm::vec3* playerPosPtr;
        glm::vec3 yawView;
        glm::vec3 view;
        glm::vec3 right;
        float angleX;
        float angleY;
        bool firstperson = true;

private:

        void Refresh();
      
        float zoom;
 
};

#endif // !CAMERA_FPS_H