#include <string>

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFont>
#include <QtGui>
#include <QVBoxLayout>
#include <QTimer>

#include "paintable.h"

paintable::paintable() 
{
   this->view.setScene(&(this->scene));

   QVBoxLayout *layout = new QVBoxLayout;
   layout->addWidget(&(this->view));

   QWidget *widget = new QWidget;
   widget->setLayout(layout);

   setCentralWidget(widget);
   setWindowTitle(tr("Diagramscene"));
 
   createActions();
   createToolBars();

   this->view.scale(5, 5);
   this->view.centerOn(0.0, 0.0);
   this->view.setRenderHints(QPainter::Antialiasing);

   timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(run()));
   timer->start(1000);

};

paintable::~paintable() 
{
   clearScene();
}

inline QColor getQtColour(const QString colour)
{
   if (colour == "red")
      return Qt::red;
   return Qt::black;
}

inline void paintable::createActions()
{
   zoomInAction = new QAction(QIcon(":/graphics/images/zoom-in.png"), tr("&zoomIn..."), this);
   zoomInAction->setShortcut(tr("Ctrl+Z"));
   zoomInAction->setStatusTip(tr("Zoom in"));
   connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));

   zoomOutAction = new QAction(QIcon(":/graphics/images/zoom-out.png"), tr("&zoomOut..."), this);
   zoomOutAction->setShortcut(tr("Ctrl+X"));
   zoomOutAction->setStatusTip(tr("Zoom out"));
   connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut())); 
}

inline void paintable::createToolBars()
{
   zoomingOptions = addToolBar(tr("Zooming"));
   zoomingOptions->addAction(zoomInAction);
   zoomingOptions->addAction(zoomOutAction);
}

void paintable::setSceneBounds()
{ }

void paintable::setTitle(const QString& title)
{
   setWindowTitle(title);
}

void paintable::drawPoint(const double coordx, const double coordy, const double radius, const QString colour)
{
   QGraphicsEllipseItem *item = scene.addEllipse(QRectF(coordx - (radius / 2), coordy - (radius / 2), radius, radius));
   item->setPen(QPen(getQtColour(colour)));   
}

void paintable::drawLine(const double x1, const double x2, const double y1, const double y2)
{
   scene.addLine(x1, x2, y1, y2);
}

void paintable::drawLine(const double x1, const double x2, const double y1, const double y2, 
                         const unsigned r, const unsigned g, const unsigned b)
{
   QGraphicsLineItem *item = scene.addLine(x1, x2, y1, y2);
   item->setPen(QPen(QColor(r, g, b)));
}

void paintable::drawEllipse(const double coordx, const double coordy, const double width, const double height)
{
   scene.addRect(QRectF(coordx, coordy, width, height));
}
 
void paintable::drawText(const char* text, const double x, const double y)
{
   QFont sansFont(0, 1);
   sansFont.setWeight(QFont::Light);
   QGraphicsTextItem *textItem = scene.addText(QString(text), sansFont);
   QRectF rec = textItem->boundingRect();
   textItem->setPos(x - (int)(rec.width() / 2), y - (int)(rec.height() / 2));
}

// - Misc

void paintable::clearScene()
{
   QList<QGraphicsItem *> list = scene.items();
   QList<QGraphicsItem *>::Iterator it = list.begin();
   for (; it != list.end(); ++it) 
      if ( *it )
         delete *it;
}

void paintable::display() 
{
   show();
}

void paintable::resizeWindow(const unsigned width, const unsigned height)
{
   resize(width, height);
}

void paintable::scale(const unsigned x, const unsigned y)
{
   this->view.scale(x, y);
}

// - Slots

void paintable::zoomIn()
{
   this->view.scale(1.2, 1.2);
}

void paintable::zoomOut()
{
   this->view.scale(1 / 1.2, 1 / 1.2);
}

