#ifndef __GL_WINDOW_H
#define __GL_WINDOW_H

#include "qtinc.h"
class MainWindow : public QWindow, protected QOpenGLFunctions
{
	Q_OBJECT;

	QOpenGLContext* context;
	QOpenGLPaintDevice* gl_device;
	QTimer* timer;

public:
	MainWindow(QWindow* parent = 0);
	virtual ~MainWindow();

	void OnInit();
	void OnPaint();
	void OnRender();
	void OnKeyUp(int keycode);
	void OnKeyDown(int keycode);
	void OnMouseMove(int x, int y);
	void OnMouseDown(int button);
	void OnMouseUp(int button);
	
public slots:
	void OnTimer();

protected:
	bool event(QEvent* e);
	void exposeEvent(QExposeEvent* e);
	void resizeEvent(QResizeEvent* e);
   void keyPressEvent(QKeyEvent* e)			{ OnKeyDown(e->key()); };
	void keyReleaseEvent(QKeyEvent* e)		{ OnKeyUp(e->key()); };
	void mouseMoveEvent(QMouseEvent* e)		{ OnMouseMove(e->x(), e->y()); };
	void mousePressEvent(QMouseEvent* e)	{ OnMouseDown(e->button()); };
	void mouseReleaseEvent(QMouseEvent* e)	{ OnMouseUp(e->button()); };
};

#endif //__GL_WINDOW_H
