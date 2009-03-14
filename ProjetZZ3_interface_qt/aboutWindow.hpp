

#ifndef _ABOUTWINDOW_
#define _ABOUTWINDOW_

#include <Qt>
#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>
#include <QtGui>
#include <QGroupBox>
#include <QPixmap>

class aboutWindow : public QObject
{
   Q_OBJECT
 
 
   protected :
      QWidget _fenetre;
      QLabel _desc;
      QPushButton * _quit;

   public :
      void init(QWidget * parent)
      {
         QVBoxLayout * vlayout = new QVBoxLayout();
         _fenetre.setParent(parent);
         _fenetre.setWindowFlags(Qt::Window);
         //_fenetre.setGeometry(100,100,200,250);
         _fenetre.setWindowTitle("A propos...");
         _fenetre.setMinimumSize(300, 75);

         _desc.setText("Jan Villeminot, Bastien Legrand, projet de troisième année.");

         _quit = new QPushButton("Quitter", &_fenetre);
         QObject::connect( _quit, SIGNAL(clicked()), &_fenetre, SLOT(close()) );

         vlayout->addWidget(&_desc);
         vlayout->addWidget(_quit);

         _fenetre.setLayout(vlayout);
         _fenetre.resize(350,75);

         _fenetre.hide();
      }

      void setText(std::string text) { _desc.setText(QString::fromStdString(text)); }

      void afficher()
      {
         _fenetre.show();
      }

};



#endif

