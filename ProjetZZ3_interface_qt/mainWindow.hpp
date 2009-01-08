
#ifndef _MAINWINDOW_
#define _MAINWINDOW_

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
#include <QFileDialog>
#include <QString>

#include <iostream>
#include <sstream>
#include <ctime>
#include "aboutWindow.hpp"
#include "grapheZone.hpp"

#include "./controler/controler.hpp"
#include "./graph/graph.hpp"
#include "exceptions/ReaderException.hpp"
#include "utils/logger.hpp"

#define X 800
#define Y 600

class mainWindow : public QMainWindow
{
   Q_OBJECT

   protected :
      QWidget _fenetre;
      QMenuBar _menu;
      QMenu _fileMenu;
      QMenu _optionMenu;
      QMenu _aboutMenu;
      grapheZone _graphe;
      QGroupBox _status;
      QLabel _nbsommet;
      QLabel _nbclique;
      QLabel _nbarete;
      QLabel _tps;
      QLabel _labelsommet;
      QLabel _labelarete;
      QLabel _labelclique;
      QLabel _labeltps;
      QString _datafile; //conversion en std::string via toStdString()
      aboutWindow _about;

      QAction * _openAct;
      QAction * _quitAct;
      QAction * _aboutAct;

      Controler * _controler;


   public :
      void init();
      void initAction();
      void initMenu();
      void initStatus();
      void drawPoint(double x, double y, QColor c = Qt::red);

      inline void setNbSommets(int n) { _nbsommet.setText(QString::number(n)); }
      inline void setNbArete(int n) { _nbarete.setText(QString::number(n)); }
      inline void setTemps(double n) { _tps.setText(QString::number(n)); }
      inline void setNbClique(int n) { _nbclique.setText(QString::number(n)); }
      void afficherPoint();

   public slots :
      void afficherAbout();
      void choixFichier();


};


#endif
