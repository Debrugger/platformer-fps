#ifndef __GL_WINDOW_H
#define __GL_WINDOW_H

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
	
public slots:
	void OnTimer();
   void renderLater();

protected:
	bool event(QEvent* e);
	void exposeEvent(QExposeEvent* e);
   void keyPressEvent(QKeyEvent* e);
};

#endif //__GL_WINDOW_H
