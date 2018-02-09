#include "ModelGL.h"
#include "Bmp.h"
#include "Log.h"



ModelGL::ModelGL() : window_width_(0), window_height_(0), animate_flag_(false),
					 change_draw_mode_(false), draw_mode_(0),
					 mouse_left_down_(false), mouse_right_down_(false),
					 mouse_x_(0), mouse_y_(0), camera_angle_x_(0), camera_angle_y_(0),
					 camera_distance_(5), texture_id_(0), bg_flag_(0),
					 window_resized_(false), frame_buffer_(0), buffer_size_(0)
{
	bg_color_[0] = bg_color_[1] = bg_color_[2] = bg_color_[3] = bg_color_[3] = 0;
	//sphere_.set(1.0f, 72, 36);
}

ModelGL::~ModelGL()
{
}

void ModelGL::Init()
{
	glShadeModel(GL_SMOOTH);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glClearColor(bg_color_[0], bg_color_[1],bg_color_[2],bg_color_[3]);
	glClearStencil(0);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);

	InitLights();
	SetCamera(0, 0, 8, 0, 0, 0);

	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 10.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void ModelGL::InitLights()
{
	GLfloat light_ka[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_kd[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat light_ks[] = { 1, 1, 1, 1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ka);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_kd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_ks);

	float light_pos[4] = { -10, 0, 5, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	glEnable(GL_LIGHT0);
}
void ModelGL::SetCamera(float pos_x, float pos_y, float pos_z, float target_x, float target_y, float target_z)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pos_x, pos_y, pos_z, target_x, target_y, target_z, 0, 1, 0);
}

void ModelGL::SetViewport(int width, int height)
{
	window_width_ = width;
	window_height_ = height;

	glViewport(0, 0, (GLsizei) width, (GLsizei)height);

	float aspect_ratio = (float) width / height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)(width) / height, 0.1f, 20.f);

	glMatrixMode(GL_MODELVIEW);
}

void ModelGL::ResizeWindow(int width, int height)
{
	window_width_ = width;
	window_height_ = height;
	window_resized_ = true;
}

void ModelGL::RotateCamera(int x, int y)
{
	if(mouse_left_down_)
	{
		camera_angle_y_ += (x - mouse_x_);
		camera_angle_x_ += (y - mouse_y_);

		mouse_x_ = x;
		mouse_y_ = y;
	}
}
