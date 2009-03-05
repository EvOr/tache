
#ifndef _MYTHREAD_
#define _MYTHREAD_

#include <Qt>
#include <QMessageBox>
#include <QThread>
#include <QMainWindow>
#include "./mainWindow.hpp"

class MyThread : public QThread
{
   //Q_OBJECT

   protected:
      QMainWindow * _mainWin;

   public:
      MyThread() {}
      MyThread(QMainWindow * mw)
      {
          _mainWin = mw;
      }

      void run();
};


#endif

	
