#include "mainWindow.hpp"


void mainWindow::init()
{
   QVBoxLayout * vlayout = new QVBoxLayout();
   _controler = NULL;
//    _graphe = new QLabel(&_fenetre);

   initStatus();
   initAction();
   initMenu();
   _about.init();

   vlayout->setMenuBar(&_menu);
   vlayout->addWidget(&_graphe);
   vlayout->addWidget(&_status);

   _fenetre.setLayout(vlayout);

   setMinimumSize(640, 480);
   setWindowTitle("Fenetre Principale");
   setCentralWidget(&_fenetre);
   resize(1024,768);
}


void mainWindow::initMenu()
{
   _fileMenu.setTitle("Fichier");
   _optionMenu.setTitle("Options");
   _aboutMenu.setTitle("About");

   _fileMenu.addAction(_openAct);
   _fileMenu.addAction(_quitAct);
   _aboutMenu.addAction(_aboutAct);

   _menu.addMenu(&_fileMenu);
   _menu.addMenu(&_optionMenu);
   _menu.addMenu(&_aboutMenu);
}


void mainWindow::initStatus()
{
   QHBoxLayout * layout = new QHBoxLayout;
//    _status = new QGroupBox("Status");
   _status.setTitle("Status");

   _labelsommet.setText("NB sommet");
   _labelarete.setText("NB arete");
   _labelclique.setText("NB clique");
   _labeltps.setText("Tps calcul");

   layout->addWidget(&_labelsommet);
   layout->addWidget(&_nbsommet);
   layout->addWidget(&_labelarete);
   layout->addWidget(&_nbarete);
   layout->addWidget(&_labelclique);
   layout->addWidget(&_nbclique);
   layout->addWidget(&_labeltps);
   layout->addWidget(&_tps);

   _status.setLayout(layout);

   _status.setMinimumSize(X, 80);
   _status.setMaximumSize(10000, 80);

//    _status.resize(X, 100);
}


void mainWindow::initAction()
{
   _quitAct = new QAction("Quit", this);
   _quitAct->setShortcut(tr("Ctrl+Q"));
   _quitAct->setStatusTip("Quit the program");
   QObject::connect(_quitAct, SIGNAL(triggered()), this, SLOT(close()));

   _openAct = new QAction("Open", this);
   _openAct->setShortcut(tr("Ctrl+O"));
   _openAct->setStatusTip("Open a datafile");
   QObject::connect(_openAct, SIGNAL(triggered()), this, SLOT(choixFichier()));

   _aboutAct = new QAction("About program...", this);
   _aboutAct->setStatusTip("Give information about this program");
   QObject::connect(_aboutAct, SIGNAL(triggered()), this, SLOT(afficherAbout()));
}


void mainWindow::drawPoint(double x, double y, QColor c)
{
   QPen pen;
   QBrush brush;

   pen.setColor(QColor(1,0,0));
   brush.setColor(QColor(1,0,0));

   _graphe.setPen(pen);
   _graphe.setBrush(brush);

   _graphe.drawPoint(x, y);

}


void mainWindow::afficherPoint()
{
   std::map< vertex_descriptor , coordonnes> coords = _controler->get_position();
   std::map< vertex_descriptor , coordonnes>::iterator it;

   for(it = coords.begin(); it != coords.end() ; ++it)
   {
      drawPoint(it->second.x, it->second.y);
   }
   setNbSommets(coords.size());
}



//fonctions correspondant aux Slots
void mainWindow::afficherAbout()
{
   _about.afficher();
}


void mainWindow::choixFichier()
{
   double t;

   _datafile = QFileDialog::getOpenFileName(this,"Choose a file...", "./", "All Files (*.*)");

   if(_controler == NULL)
   {
      _controler = new Controler(_datafile.toStdString());
   }
   else
   {
      _controler->change_file_name(_datafile.toStdString());
   }


    try{
      t = time(0);
      _controler->parse_file();
   }catch(ReaderException & e){
      if(e.getType()==ReaderException::CRITICAL){
	 Logger::getInstance()->logMessage(e.display(),Logger::ERR_UNEXP);
	 //TODO faire un popup
      }else{
	 Logger::getInstance()->logMessage(e.display(),Logger::ERR_UNEXP);
      }
   }
   _controler->displayCircle(1.5);

   t = time(0) - t;
   setTemps(t);

   afficherPoint();
}


