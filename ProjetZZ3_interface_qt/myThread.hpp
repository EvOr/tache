
#ifndef _MYTHREAD_
#define _MYTHREAD_

#include <Qt>
#include <QMessageBox>
#include <QThread>
#include <QMainWindow>

#include <iostream>

#include "./calculWindow.hpp"


class myThread : public QThread
{
   //Q_OBJECT

   protected:
      calculWindow _fenetre;

   public:
      myThread(QWidget * parent) { init(parent); QThread::start(); }
      void init(QWidget * parent);      
      void run();
      //void exit();
};


#endif

	
