#ifndef PAINTABLE_H
#define PAINTABLE_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QThread>
#include <QTimer>


class paintable : public QMainWindow
{
   Q_OBJECT
   private:
      // Interface
      QToolBar* zoomingOptions;
      QAction* zoomInAction;
      QAction* zoomOutAction;

      QGraphicsScene scene;
      QGraphicsView view;

      QList<QGraphicsItem *> graphicItems;
      QTimer* timer;

   public slots:
      void zoomIn();
      void zoomOut();
      virtual void run() = 0;

   protected:

   public:
      paintable();
      ~paintable();

      // Interface
      void createActions();
      void createToolBars();

      void setSceneBounds(); 
      void setAntialiasing(const bool);
      void setCrossPatterBackground(const bool);
      void setTitle(const QString&);
      
      // Painting 
      void drawPoint(const double coordx, const double coordy, const double radius = 0.0, const QString colour = "black");
      void drawLine(const double, const double, const double, const double);
      void drawLine(const double x1, const double x2, const double y1, const double y2, 
                    const unsigned r, const unsigned g, const unsigned b);
      void drawRectangle(const double, const double, const double, const double);
      void drawEllipse(const double, const double, const double, const double);
      void drawText(const char*, const double, const double);
      // void drawPath();
      // void drawPolygon();
      // void drawSimpleText();

      // Misc
      void display();
      void resizeWindow(const unsigned, const unsigned);
      void scale(const unsigned, const unsigned);
      void clearScene(); 
   
      virtual void paint() = 0;

};

#endif
