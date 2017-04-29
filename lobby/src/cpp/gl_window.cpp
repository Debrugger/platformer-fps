#include "sysinc.h"
#include "qtinc.h"
#include "lobby_dialog.h"
#include "connect_dialog.h"
#include "globals.h"
#include "gl_window.h"

double pos_x;

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
	requestUpdate();
}

void MainWindow::OnPaint()
{
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.9, 0.9, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)size().width() / (double)size().height(), 0.001, 1e10);

	// geht net:
	// double fov, znear, zfar, aspect, width, height;
	// double fw, fh;
	// width = (double)size().width();
	// height = (double)size().width();
	// fov = 60.0;
	// znear = 0.001;
	// zfar = 1e10;
	// aspect = width / height;

	// fh = tan(fov * 0.5 * M_PI / 360.0) * znear;
	// fw = fh * aspect;
	// glFrustum(-fw, fw, -fh, fh, znear, zfar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	/* a cube */
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f( -0.1 + pos_x, -0.1 - 1.0,  0.1 - 5.0);
	glVertex3f( -0.1 + pos_x,  0.1 - 1.0,  0.1 - 5.0);
	glVertex3f(  0.1 + pos_x,  0.1 - 1.0,  0.1 - 5.0);
	glVertex3f(  0.1 + pos_x, -0.1 - 1.0,  0.1 - 5.0);
	glEnd();

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(  0.1 + pos_x,  0.1 - 1.0, -0.1 - 5.0);
	glVertex3f(  0.1 + pos_x,  0.1 - 1.0,  0.1 - 5.0);
	glVertex3f(  0.1 + pos_x, -0.1 - 1.0,  0.1 - 5.0);
	glVertex3f(  0.1 + pos_x, -0.1 - 1.0, -0.1 - 5.0);
	glEnd();

	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f( -0.1 + pos_x,  0.1 - 1.0, -0.1 - 5.0);
	glVertex3f(  0.1 + pos_x,  0.1 - 1.0, -0.1 - 5.0);
	glVertex3f(  0.1 + pos_x, -0.1 - 1.0, -0.1 - 5.0);
	glVertex3f( -0.1 + pos_x, -0.1 - 1.0, -0.1 - 5.0);
	glEnd();

	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f( -0.1 + pos_x,  0.1 - 1.0,  0.1 - 5.0);
	glVertex3f( -0.1 + pos_x,  0.1 - 1.0, -0.1 - 5.0);
	glVertex3f( -0.1 + pos_x, -0.1 - 1.0, -0.1 - 5.0);
	glVertex3f( -0.1 + pos_x, -0.1 - 1.0,  0.1 - 5.0);
	glEnd();
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

void MainWindow::exposeEvent(QExposeEvent* e)
{
	if (isExposed())
		OnRender();
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_Escape)
		app->quit();
}
