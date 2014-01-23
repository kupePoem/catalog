#ifndef MYGRAVIEW_H
#define MYGRAVIEW_H

#include <QGraphicsView>

class CMyGraView : public QGraphicsView
{
	Q_OBJECT

public:
	CMyGraView(QWidget * parent);
	~CMyGraView();

	void addRect();
	void initView();

public slots:

	void zoomIn();
	void zoomOut();
	void rotateLeft();
	void rotateRight();


protected:
virtual void	mouseMoveEvent ( QMouseEvent * event );
virtual void	mousePressEvent ( QMouseEvent * event );
virtual void	mouseReleaseEvent ( QMouseEvent * event );
private:


signals:
	void spectralValueChanged( const QList<double> & );
	
};

#endif // MYGRAVIEW_H
