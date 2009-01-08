#include <QtGui>

#include "grapheZone.hpp"

grapheZone::grapheZone(QWidget *parent)
   : QWidget(parent)
{
   setBackgroundRole(QPalette::Base);
   setAutoFillBackground(true);
}

QSize grapheZone::minimumSizeHint() const
{
   return QSize(100, 100);
}

QSize grapheZone::sizeHint() const
{
   return QSize(400, 200);
}

void grapheZone::setPen(const QPen &pen)
{
   this->_pen = pen;
   update();
}

void grapheZone::setBrush(const QBrush &brush)
{
   this->_brush = brush;
   update();
}

// void grapheZone::drawLine(int a, int b, int c, int d)
// {
//    _lineOrPoint = true;
//    _x1 = a;
//    _y1 = b;
//    _x2 = c;
//    _y2 = d;
// 
//    update();
// }

void grapheZone::drawPoint(double a, double b)
{
   std::pair<double, double> p(a, b);

   _points.push_back(p);

   update();
//   repaint(a, b, 6, 6);
}

void grapheZone::paintEvent(QPaintEvent * )
{
   QPainter painter(this);
   painter.setPen(QPen(Qt::red, 2));
   painter.setBrush(_brush);
   double x, y;
   double cx = width() / 2.0;
   double cy = (height() - 10.0) / 2.0 ;

//    if(_lineOrPoint) //draw line
//    {
//       painter.drawLine(_x1, _x2, _y1, _y2);
//    }
//    else //draw point
//    {
//       painter.drawEllipse(_x1, _y1, 6, 6);
//    }
std::cout << width() << "  " << height() << std::endl;
   for(uint i = 0; i < _points.size(); ++i)
   {
      x = _points[i].first * cx / 2.0 + cx;
      y = _points[i].second * cy / 2.0 + cy;
// std::cout << x << "   " << y << std::endl;
      painter.drawEllipse( x, y, 6, 6);
   }


   painter.setPen(palette().dark().color());
   painter.setBrush(Qt::NoBrush);
   painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
