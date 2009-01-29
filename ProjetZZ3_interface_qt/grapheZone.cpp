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

void grapheZone::drawLine(double a, double b, double c, double d)
{
   std::pair<double, double> p(a, b);
   std::pair<double, double> p2(c, d);
// std::cout << "line : " << "(" << a << ";" << b << ") (" << c << ";" << d << ")" << std::endl;
   _lines.push_back(p);
   _lines.push_back(p2);

   update();
}

void grapheZone::drawPoint(double a, double b)
{
   std::pair<double, double> p(a, b);
// std::cout << "point : " << "(" << a << ";" << b << ")" << std::endl;
   _points.push_back(p);

   update();

}

void grapheZone::eraseGraph()
{
   _points.clear();

   _lines.clear();

   update();
}

void grapheZone::paintEvent(QPaintEvent * )
{
   QPainter painter(this);
   painter.setPen(QPen(Qt::red, 2));
   painter.setBrush(_brush);
   double x, y, x2, y2;
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

   for(uint i = 0; i < _points.size(); ++i)
   {
      x = _points[i].first * cx / 2.0 + cx;
      y = _points[i].second * cy / 2.0 + cy;
std::cout << "affichage point : " << "(" << x << ";" << y << ")" << std::endl;
      painter.drawEllipse( x, y, 6, 6);
   }

   for(uint i = 0; i < _lines.size(); ++i)
   {
      x = _lines[i].first * cx / 2.0 + cx;
      y = _lines[i].second * cy / 2.0 + cy;
      ++i;
      x2 = _lines[i].first * cx / 2.0 + cx;
      y2 = _lines[i].second * cy / 2.0 + cy;
std::cout << "affichage line : " << "(" << x << ";" << y << ") (" << x2 << ";" << y2 << ")" << std::endl;
      painter.drawLine(x, y, x2, y2);
   }

   painter.setPen(palette().dark().color());
   painter.setBrush(Qt::NoBrush);
   painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
