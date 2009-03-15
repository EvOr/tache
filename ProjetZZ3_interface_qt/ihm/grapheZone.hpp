#ifndef _GRAPHEZONE_
#define _GRAPHEZONE_

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <vector>
#include <iostream>

class grapheZone : public QWidget
{
   Q_OBJECT

   public:

      grapheZone(QWidget *parent = 0);
      QSize minimumSizeHint() const;
      QSize sizeHint() const;

   public slots:

      void drawLine(double a, double b, double c, double d, QColor col);
      void drawPoint(double a, double b, QColor col);
      void eraseGraph();

   protected:

      void paintEvent(QPaintEvent * );

   private:

      std::vector<std::pair<double, double> > _lines;
      std::vector<std::pair<double, double> > _points;
      std::vector<QColor> _pointsColor;
      std::vector<QColor> _linesColor;
};

#endif
