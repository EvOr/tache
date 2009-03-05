
#ifndef _MYTHREAD_
#define _MYTHREAD_

#include <Qt>
#include <QMessageBox>
#include <QThread>
#include <QMainWindow>

#include <iostream>

#include "./calculWindow.hpp"

class mainWindow;

class myThread : public QThread
{
   //Q_OBJECT

   public:
      myThread() {}
      
      void run();
};


#endif

	
