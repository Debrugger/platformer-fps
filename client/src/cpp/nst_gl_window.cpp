#include "sysinc.h"
#include "qtinc.h"
#include "defines.h"
#include "lobby_dialog.h"
#include "connect_dialog.h"
#include "main.h"
#include "vector.h"
#include "matrix.h"
#include "glbuffer.h"
#include "mesh.h"
#include "model.h"
#include "texture.h"
#include "shader.h"
#include "object.h"
#include "platform.h"
#include "glglobals.h"
#include "gl_window.h"
#include "playercontrols.h"
#include "gameinit.h"

double pos_x;
Object* o; 

MainWindow::MainWindow(QWindow* parent)
{
	gl_device = 0;
	context = 0;
	timer = new QTimer(this);
	timer->setInterval(10);
	timer->setSingleShot(false);
	connect(timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
	setSurfaceType(QWindow::OpenGLSurface);
}

MainWindow::~MainWindow()
{
	if (gl_device)
		delete gl_device;
	if (context)
		delete context;
}

void MainWindow::OnInit()
{
	Model m;
	shader.Load("rc/shader/simple_vertexshader.glsl", "rc/shader/simple_pixelshader.glsl");

	cam_to.Set(1.0, 0.0, -1 * -1);
	cam_pos.Set(0.0, 0.0, -1 * -1);
	display_width = size().width();
	display_height = size().height();
	printf("width: %d height: %d\n", display_width, display_height);
	QCursor cursor;
	cursor.setPos(display_width / 2, display_height / 2);
	cursor.setShape(Qt::BlankCursor);
	setCursor(cursor);

	InitGame::InitWorld();
}

void MainWindow::OnRender()
{
	bool on_init;

	if (!isExposed())
		return;

	if (!gl_device)
	{
		gl_device = new QOpenGLPaintDevice;
		gl_device->setSize(size());
	}
	on_init = false;
	if (!context)
	{
		context = new QOpenGLContext(this);
		context->setFormat(requestedFormat());
		context->create();
		on_init = true;
	}
	context->makeCurrent(this);

	if (on_init)
	{
		initializeOpenGLFunctions();
		OnInit();
	}

	glViewport(0, 0, size().width(), size().height());
	timer->start();
	OnPaint();
	context->swapBuffers(this);
}

void MainWindow::OnTimer()
{                     
	PlayerControls();
	requestUpdate();
}

void MainWindow::OnPaint()
{
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)size().width() / (double)size().height(), 0.001, 1e10);
   gluLookAt(cam_pos.x, cam_pos.y, cam_pos.z, cam_to.x, cam_to.y, cam_to.z, 0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	for (o = Object::FirstObject(); o; o = o->NextObject())
	{
		o->Render();
	}
}

bool MainWindow::event(QEvent* e)
{
	switch (e->type())
	{
		case QEvent::UpdateRequest:
			OnRender();
			return true;

		default:
			return QWindow::event(e);
	}
}

void MainWindow::OnKeyDown(int keycode) /* a bis z und 0 bis 9 */
{
	switch (keycode)
	{
		case Qt::Key_Escape: /* Escape */
			app->quit();
			break;
		case Qt::Key_Space: Jump(); break;

		case Qt::Key_W: key_w = true; break;
		case Qt::Key_A: key_a = true; break;
		case Qt::Key_S: key_s = true; break;
		case Qt::Key_D: key_d = true; break;
		case Qt::Key_Q: key_q = true; break;
		case Qt::Key_E: key_e = true; break;
	}
} 

void MainWindow::OnKeyUp(int keycode) /* a bis z und 0 bis 9 */
{
	switch (keycode)
	{
		case Qt::Key_Escape: /* Escape */
			app->quit();
			break;
		case Qt::Key_Space: Jump(); break;

		case Qt::Key_W: key_w = false; break;
		case Qt::Key_A: key_a = false; break;
		case Qt::Key_S: key_s = false; break;
		case Qt::Key_D: key_d = false; break;
		case Qt::Key_Q: key_q = false; break;
		case Qt::Key_E: key_e = false; break;
		case Qt::Key_P: cheat_mode = !cheat_mode; break;
	}
}

void MainWindow::OnMouseDown(int button)
{
}

void MainWindow::OnMouseUp(int button)
{
}

void MainWindow::OnMouseMove(int x, int y)
{
	double horz, vert;
	Vector v;
	x -= display_width / 2;
	y -= display_height / 2;
	y = -y;

	if (x == 0 && y == 0)
		return;

	horz = atan2(cam_to.z - cam_pos.z, cam_to.x - cam_pos.x);

	v = cam_to - cam_pos;
	vert = asin(v.y / v.Len());

	horz += (double)x * MOUSE_SENSITIVITY;

	if ((vert < M_PI * 0.5 - 0.05 && y > 0) || (vert > -M_PI * 0.5 + 0.05 && y < 0))
		vert += (double)y * MOUSE_SENSITIVITY;
	cam_to.x = cam_pos.x + cos(horz) * cos(vert);
	cam_to.y = cam_pos.y + sin(vert);
	cam_to.z = cam_pos.z + sin(horz) * cos(vert);

	QCursor cursor;
	cursor.setPos(mapToGlobal(QPoint(display_width / 2, display_height / 2)));
	cursor.setShape(Qt::BlankCursor);
	setCursor(cursor);

}

void MainWindow::exposeEvent(QExposeEvent* e)
{
	if (isExposed())
		OnRender();
}

void MainWindow::resizeEvent(QResizeEvent* e)
{
	display_width = size().width();
	display_height = size().height();
}
