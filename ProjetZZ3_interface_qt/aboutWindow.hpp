

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
#include <QAction>



class aboutWindow : public QObject
{
   Q_OBJECT


   protected :
      QWidget _fenetre;
      QLabel _desc;
      QPushButton * _quit;

   public :
      void init()
      {
         QVBoxLayout * vlayout = new QVBoxLayout();
         _fenetre.setGeometry(100,100,200,250);
         _fenetre.setWindowTitle("About program...");
         _fenetre.setMinimumSize(300, 75);

         _desc.setText("Jan Villeminot, Bastien Legrand, ZZ3 project.");

         _quit = new QPushButton("Quit", &_fenetre);
         QObject::connect( _quit, SIGNAL(clicked()), &_fenetre, SLOT(close()) );

         vlayout->addWidget(&_desc);
         vlayout->addWidget(_quit);

         _fenetre.setLayout(vlayout);
         _fenetre.resize(300,75);
      }

      void afficher()
      {
         _fenetre.show();
      }

};



#endif

