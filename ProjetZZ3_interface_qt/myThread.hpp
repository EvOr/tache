
#ifndef _MYTHREAD_
#define _MYTHREAD_

#include <Qt>
#include <QMessageBox>
#include <QThread>
#include <QMainWindow>
#include "./mainWindow.hpp"

class mainWindow;

class myThread : public QThread
{
   //Q_OBJECT

   protected:
      mainWindow * _mainWin;

   public:
      myThread() {}
      myThread(mainWindow * mw)
      {
          _mainWin = mw;
      }

      void run();
};


#endif

	
