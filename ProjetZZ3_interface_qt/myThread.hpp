
#ifndef _MYTHREAD_
#define _MYTHREAD_

#include <QMessageBox>
#include <QThread>
#include <QMainWindow>
#include "mainWindow.hpp"

class myThread : public QThread
{
   //Q_OBJECT

   protected:
      QMainWindow * _mainWin;

   public:
      myThread(QMainWindow * mw)
      {
          _mainWin = mw;
      }

      void run();
};



#endif

