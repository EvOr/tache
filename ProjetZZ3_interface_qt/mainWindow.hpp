
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
#include <QMessageBox>
#include <QPushButton>
#include <QtGui>
#include <QGroupBox>
#include <QPixmap>
#include <QAction>
#include <QFileDialog>
#include <QString>
#include <QInputDialog>

#include <iostream>
#include <sstream>
#include <ctime>
#include <string>
#include "aboutWindow.hpp"
#include "grapheZone.hpp"
#include "./calculWindow.hpp"

#include "./controler/controler.hpp"
#include "./graph/graph.hpp"
#include "exceptions/ReaderException.hpp"
#include "utils/logger.hpp"

#define X 800
#define Y 600

class dialog;

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
      calculWindow _calcul;

      QAction * _openAct;
      QAction * _stubAct;
      QAction * _quitAct;
      QAction * _aboutAct;
      QAction * _eraseAct;
      QAction * _infoAct;
      QAction * _zoomAct;
      QAction * _unzoomAct;
      QAction * _infWeightAct;
      QAction * _supWeightAct;
      QAction * _infASNumAct;
      QAction * _supASNumAct;
      QAction * _cliqueAct;
      QAction * _centralityAct;

      Controler * _controler;

      void enableAction() { _stubAct->setEnabled(true); _infoAct->setEnabled(true); _eraseAct->setEnabled(true); _zoomAct->setEnabled(true); _unzoomAct->setEnabled(true); _infASNumAct->setEnabled(true); _supASNumAct->setEnabled(true); }
      void disableAction() { _stubAct->setEnabled(false); _infoAct->setEnabled(false); _eraseAct->setEnabled(false); _zoomAct->setEnabled(false); _unzoomAct->setEnabled(false); _infWeightAct->setEnabled(false); _supWeightAct->setEnabled(false);  _infASNumAct->setEnabled(false);  _supASNumAct->setEnabled(false); _cliqueAct->setEnabled(false); _centralityAct->setEnabled(false); }


   public :
      mainWindow() {}
      void init();
      void initAction();
      void initMenu();
      void initStatus();
      void drawPoint(double x, double y, QColor c = Qt::red);
      void drawLine(double a, double b, double c, double d, QColor col = Qt::blue);

      inline void setNbSommets(int n) { _nbsommet.setText(QString::number(n)); }
      inline void setNbArete(int n) { _nbarete.setText(QString::number(n)); }
      inline void setTemps(double n) { _tps.setText(QString::number(n)); }
      inline void setNbClique(int n) { _nbclique.setText(QString::number(n)); }
      void razCompteur();
      void afficherPoint();
      void drawGraphTmp();

   public slots :
      void afficherAbout();
      void choixFichier();
      void eraseGraph();
      void afficherInfoAs();
      void afficherNonStub();
      void zoom();
      void unzoom();
      void infWeight();
      void supWeight();
      void infASNum();
      void supASNum();
      void clique();
      void centrality();

};


#endif
