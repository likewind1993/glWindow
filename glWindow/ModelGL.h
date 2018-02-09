#ifndef MODEL_GL_H
#define MODEL_GL_H
#if _WIN32
#include <windows.h>
#endif 
#include <GL/GL.h>
#include <gl/GLU.h>
#include "Sphere.h"
#pragma comment(lib, "glut.lib")
#pragma comment(lib, "freeglut.lib")

class ModelGL
{
public:
	ModelGL();
	~ModelGL();

	void Init();
	void CreateTexture(int width, int height, int bitCount, const void * data);
	void SetCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);
	void SetViewport(int width, int height);
	void ResizeWindow(int width, int height);
	void Draw();

	void SetMouseLeft(bool flag);
	void SetMouseRight(bool flag);
	void SetMousePosition(int x, int y);
	void SetDrawMode(int mode);
	void Animate(bool flag);

	void RotateCamera(int x, int y);
	void ZoomCamera(int dist);
	void ZoomCameraByWheel(float delta);

	void SetBackgroundRed(float value);
	void SetBackgroundGreen(float value);
	void SetBackgroundBlue(float value);

private:
	void InitLights();
	unsigned int InitEarthDL();
	unsigned int LoadTextureBmp(const char * filename);
	
	int window_width_;
	int window_height_;
	bool animate_flag_;
	bool change_draw_mode_;
	int draw_mode_;
	Sphere sphere_;

	bool mouse_left_down_;
	bool mouse_right_down_;
	int mouse_x_;
	int mouse_y_;
	float camera_angle_x_;
	float camera_angle_y_;
	float camera_distance_;
	float bg_color_[4];
	unsigned int texture_id_;
	bool bg_flag_;
	bool window_resized_;
	unsigned char * frame_buffer_;
	int buffer_size_;
};

#endif


