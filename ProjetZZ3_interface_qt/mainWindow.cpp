#include "mainWindow.hpp"


void mainWindow::init()
{
   QVBoxLayout * vlayout = new QVBoxLayout();
   _controler = NULL;
//    _graphe = new QLabel(&_fenetre);

   initStatus();
   initAction();
   initMenu();
   razCompteur();
   _about.init(this);
   _calcul.init(this);

   vlayout->setMenuBar(&_menu);
   vlayout->addWidget(&_graphe);
   vlayout->addWidget(&_status);

   _fenetre.setLayout(vlayout);

   setMinimumSize(740, 480);
   setWindowTitle("Modelisation de Reseau");
   setCentralWidget(&_fenetre);
   resize(640,480);
}


void mainWindow::initMenu()
{
   _fileMenu.setTitle("Fichier");
   _optionMenu.setTitle("Options");
   _aboutMenu.setTitle("About");

   _fileMenu.addAction(_openAct);
   _fileMenu.addAction(_quitAct);

   _optionMenu.addAction(_infoAct);
   _optionMenu.addAction(_cliqueAct);
   _optionMenu.addSeparator();
   _optionMenu.addAction(_stubAct);
   _optionMenu.addAction(_zoomAct);
   _optionMenu.addAction(_unzoomAct);
   _optionMenu.addSeparator();
   _optionMenu.addAction(_centralityAct);
   _optionMenu.addAction(_infWeightAct);
   _optionMenu.addAction(_supWeightAct);
   _optionMenu.addSeparator();
   _optionMenu.addAction(_infASNumAct);
   _optionMenu.addAction(_supASNumAct);
   _optionMenu.addSeparator();
   _optionMenu.addAction(_eraseAct);

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

   _status.setMinimumSize(720, 80);
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

   _eraseAct = new QAction("Erase Graphe", this);
   _eraseAct->setStatusTip("Erase the graph en re-initialize data structures");
   QObject::connect(_eraseAct, SIGNAL(triggered()), this, SLOT(eraseGraph()));
   

   _aboutAct = new QAction("About program...", this);
   _aboutAct->setStatusTip("Give information about this program");
   QObject::connect(_aboutAct, SIGNAL(triggered()), this, SLOT(afficherAbout()));

   _infoAct = new QAction("Information about an As", this);
   _infoAct->setStatusTip("Give informations about a specific AS.");
   QObject::connect(_infoAct, SIGNAL(triggered()), this, SLOT(afficherInfoAs()));
   

   _stubAct = new QAction("Load triplet file", this);
   _stubAct->setStatusTip("Display the graph without its stub.");
   QObject::connect(_stubAct, SIGNAL(triggered()), this, SLOT(afficherNonStub()));

   _zoomAct = new QAction("Zoom", this);
   _zoomAct->setStatusTip("Zoom on the neighborhood of a specific AS.");
   QObject::connect(_zoomAct, SIGNAL(triggered()), this, SLOT(zoom()));

   _unzoomAct= new QAction("Return to global graph", this);
   _unzoomAct->setStatusTip("Return on the global graph.");
   QObject::connect(_unzoomAct, SIGNAL(triggered()), this, SLOT(unzoom()));

   _infWeightAct= new QAction("Display AS by inferior weigth", this);
   _infWeightAct->setStatusTip("Display only AS with a weight inferior to a given one.");
   QObject::connect(_infWeightAct, SIGNAL(triggered()), this, SLOT(infWeight()));

   _supWeightAct= new QAction("Display AS by superior weigth", this);
   _supWeightAct->setStatusTip("Display only AS with a weight superior to a given one.");
   QObject::connect(_supWeightAct, SIGNAL(triggered()), this, SLOT(supWeight()));

   _infASNumAct= new QAction("Display AS by inferior number", this);
   _infASNumAct->setStatusTip("Display only AS with a number inferior to a given one.");
   QObject::connect(_infASNumAct, SIGNAL(triggered()), this, SLOT(infASNum()));

   _supASNumAct= new QAction("Display AS by superior number", this);
   _supASNumAct->setStatusTip("Display only AS with a weight superior to a given one.");
   QObject::connect(_supASNumAct, SIGNAL(triggered()), this, SLOT(supASNum()));

   _cliqueAct= new QAction("compute number of clique", this);
   _cliqueAct->setStatusTip("Compute number of clique in the graph.");
   QObject::connect(_cliqueAct, SIGNAL(triggered()), this, SLOT(clique()));
 
   _centralityAct= new QAction("compute centrality", this);
   _centralityAct->setStatusTip("Compute centrality to weight each edges.");
   QObject::connect(_centralityAct, SIGNAL(triggered()), this, SLOT(centrality()));

   disableAction();
}


void mainWindow::drawPoint(double x, double y, Qt::GlobalColor c)
{
   _graphe.drawPoint(x, y, c);

}

void mainWindow::drawLine(double a, double b, double c, double d, Qt::GlobalColor col)
{
   _graphe.drawLine(a, b, c, d, col);
}

void mainWindow::afficherPoint()
{
   std::map< vertex_descriptor , coordonnes> coords = _controler->get_position();
   std::vector< std::pair<vertex_descriptor , vertex_descriptor> > liens = _controler->get_liens();
   std::map< vertex_descriptor , coordonnes>::iterator it;
   std::vector< std::pair<vertex_descriptor , vertex_descriptor> >::iterator it2;

   //affichage des points
   for(it = coords.begin(); it != coords.end() ; ++it)
   {
// std::cout << "point : " << "(" << it->second.x << ";" << it->second.y << ")" << std::endl;
      drawPoint(it->second.x, it->second.y);
   }
   setNbSommets(coords.size());

   
   //affichage des liens
   int nbliens = 0;
   for(it2 = liens.begin(); it2 != liens.end() ; ++it2)
   {
// std::cout << "line : " << "(" << coords[(*it2).first].x << ";" << coords[(*it2).first].y << ") (" << coords[(*it2).second].x << ";" << coords[(*it2).second].y << ")" << std::endl;
      drawLine(coords[(*it2).first].x, coords[(*it2).first].y, coords[(*it2).second].x, coords[(*it2).second].y);
      nbliens++;
   }
   setNbArete(nbliens);
}



//fonctions correspondant aux Slots
void mainWindow::afficherAbout()
{
   _about.afficher();
}


void mainWindow::choixFichier()
{
   double t;
   std::string s;
//   size_t found = 0, prec = 0;

   _datafile = QFileDialog::getOpenFileName(this,"Choose a file...", "./", "All Files (*.*)");
   
   //petit traitement pour récupérer le nom du fichier sans le chemin
//   s = _datafile.toStdString();
//   while(found!=std::string::npos)
//   {
//      prec = found;
//      found = s.find('/');
//   }
//   s = s.substr(prec);

   _status.setTitle("Status : " + _datafile);

   if(_controler == NULL)
   {
      _controler = new Controler(_datafile.toStdString());
   }
   else
   {
      _graphe.eraseGraph();
      _controler->change_file_name(_datafile.toStdString());
   }

    try{
     // _calcul.afficher();
      t = time(0);
      _controler->parse_file();
   }catch(ReaderException & e){
      if(e.getType()==ReaderException::CRITICAL){
	 Logger::getInstance()->logMessage(e.display(),Logger::ERR_UNEXP);
	 QMessageBox::warning(this, QString::fromStdString("Erreur Critique !"), QString::fromStdString(e.display()), QMessageBox::Ok, QMessageBox::NoButton);
      }else{
	 Logger::getInstance()->logMessage(e.display(),Logger::ERR_UNEXP);
         QMessageBox::warning(this, QString::fromStdString("Attention !"), QString::fromStdString(e.display()), QMessageBox::Ok, QMessageBox::NoButton);
      }
   }


   _controler->displayCircle(1.5);

   //_calcul.cacher();

   t = time(0) - t;
   setTemps(t);
   afficherPoint();
   enableAction();
}

void mainWindow::eraseGraph()
{
   _graphe.eraseGraph();
   _status.setTitle("Status");
   razCompteur();
   disableAction();
}

void mainWindow::razCompteur()
{
   //setTemps(0);
   setNbSommets(0);
   setNbArete(0);
   setNbClique(0);
}

void mainWindow::afficherInfoAs()
{
   bool ok;
   int value = -1;
   value = QInputDialog::getInteger(this, "Information about an AS", "AS Number : ", 0, 0, _controler->getNumberOfAs(), 1, &ok);    
   if (ok && value > -1)
       QMessageBox::information(this, QString::fromStdString("AS Information"), QString::fromStdString(_controler->getInfoAS(value)), QMessageBox::Ok, QMessageBox::NoButton);

}

void mainWindow::afficherNonStub()
{
   QString tripletFile = QFileDialog::getOpenFileName(this,"Choose a triplet file...", "./", "All Files (*.*)");
   

   _centralityAct->setEnabled(true);
   _cliqueAct->setEnabled(true);
   _stubAct->setEnabled(false);

   if(tripletFile.isEmpty())
   {
      Logger::getInstance()->logMessage("File error",Logger::ERR_UNEXP);
      QMessageBox::warning(this, QString::fromStdString("file Error !"), QString::fromStdString("You must chose a triplet file to display graph without its stub !"), QMessageBox::Ok, QMessageBox::NoButton);
   }
   else
   {
      try{
         _controler->load_triplet(tripletFile.toStdString());
         _controler->getSubGraph(0, 0);
         drawGraphTmp();
      }
      catch(ReaderException & e)
      {
         Logger::getInstance()->logMessage(e.display(),Logger::ERR_UNEXP);
         QMessageBox::warning(this, QString::fromStdString("Erreur Critique !"), QString::fromStdString(e.display()), QMessageBox::Ok, QMessageBox::NoButton);
      }
   }
   
}

void mainWindow::drawGraphTmp()
{
   std::map< vertex_descriptor , coordonnes> coords = _controler->get_position_tmp();
   std::vector< std::pair<vertex_descriptor , vertex_descriptor> > liens = _controler->get_liens_tmp();
   std::map< vertex_descriptor , coordonnes>::iterator it;
   std::vector< std::pair<vertex_descriptor , vertex_descriptor> >::iterator it2;

   _graphe.eraseGraph();

std::cout << "dessin du graph tmp" << std::endl;
   //affichage des points
   for(it = coords.begin(); it != coords.end() ; ++it)
   {
      drawPoint(it->second.x, it->second.y);
   }
   setNbSommets(coords.size());

   
   //affichage des liens
   int nbliens = 0;
   for(it2 = liens.begin(); it2 != liens.end() ; ++it2)
   {
      drawLine(coords[(*it2).first].x, coords[(*it2).first].y, coords[(*it2).second].x, coords[(*it2).second].y);
      nbliens++;
   }
   setNbArete(nbliens);

std::cout << "fin de dessin du graph tmp avec : " << nbliens << " liens." << std::endl;
}   

void mainWindow::zoom()
{
   //on demande à l'utilisateur l'AS sur lequel il veut zoomer.
   bool ok;
   int value = -1;
   double t;
   std::map< vertex_descriptor , coordonnes> coords = _controler->get_position();

   value = QInputDialog::getInteger(this, "Zoom on AS number ?", "AS Number : ", 0, 0, _controler->getNumberOfAs(), 1, &ok);

   if (ok && value > -1)
   {
      int l = _controler->findAS(value);  

      if( l > -1)
      {
         t = time(0);
         _controler->getSubGraph(value, 5);
         t = t - time(0);
         setTemps(t);

         drawGraphTmp();

          _cliqueAct->setEnabled(false);
      }
      else
      {
         QMessageBox::warning(this, QString::fromStdString("Zoom"), "Bad request : AS number " + QString::number(value) + " not in the graph !", QMessageBox::Ok, QMessageBox::NoButton);
      }

   }
   else
   {
    QMessageBox::warning(this, QString::fromStdString("Zoom"), "Bad request !" + QString::number(value), QMessageBox::Ok, QMessageBox::NoButton);
   }   
}

void mainWindow::unzoom()
{
   afficherPoint();
    _cliqueAct->setEnabled(true);
}

void mainWindow::infWeight()
{
   //on demande à l'utilisateur l'AS sur lequel il veut zoomer.
   bool ok;
   int value = -1;
   double t;

   value = QInputDialog::getInteger(this, "Display by weight", "Maximum weight : ", 0, 0, 10000, 1, &ok);

   if (ok && value > -1)
   {
      t = time(0);
      _controler->getSubGraph(value, 1);
      t = t - time(0);
      setTemps(t);

      drawGraphTmp();
   }
   else
   {
    QMessageBox::warning(this, QString::fromStdString("Display by Weight"), "Bad request !", QMessageBox::Ok, QMessageBox::NoButton);
   }  
}

void mainWindow::supWeight()
{
   //on demande à l'utilisateur l'AS sur lequel il veut zoomer.
   bool ok;
   int value = -1;
   double t;

   value = QInputDialog::getInteger(this, "Display by weight", "Minimum weight : ", 0, 0, 10000, 1, &ok);

   if (ok && value > -1)
   {
      t = time(0);
      _controler->getSubGraph(value, 2);
      t = t - time(0);
      setTemps(t);

      drawGraphTmp();
   }
   else
   {
    QMessageBox::warning(this, QString::fromStdString("Display by Weight"), "Bad request !", QMessageBox::Ok, QMessageBox::NoButton);
   }
}

void mainWindow::infASNum()
{
   //on demande à l'utilisateur l'AS sur lequel il veut zoomer.
   bool ok;
   int value = -1;
   double t;

   value = QInputDialog::getInteger(this, "Display by AS number", "Maximum AS number : ", 0, 0, _controler->getNumberOfAs(), 1, &ok);

   if (ok && value > -1)
   {
      t = time(0);
      _controler->getSubGraph(value, 3);
      t = t - time(0);
      setTemps(t);

      drawGraphTmp();
   }
   else
   {
    QMessageBox::warning(this, QString::fromStdString("Display by AS number"), "Bad request !", QMessageBox::Ok, QMessageBox::NoButton);
   }
}

void mainWindow::supASNum()
{
//on demande à l'utilisateur l'AS sur lequel il veut zoomer.
   bool ok;
   int value = -1;
   double t;

   value = QInputDialog::getInteger(this, "Display by AS number", "Minimum AS number : ", 0, 0, _controler->getNumberOfAs(), 1, &ok);

   if (ok && value > -1)
   {
      t = time(0);
      _controler->getSubGraph(value, 4);
      t = t - time(0);
      setTemps(t);

      drawGraphTmp();
   }
   else
   {
    QMessageBox::warning(this, QString::fromStdString("Display by AS number"), "Bad request !", QMessageBox::Ok, QMessageBox::NoButton);
   }
}


void mainWindow::clique()
{
   QMessageBox::information(this, QString::fromStdString("Program information."), "This may take some minutes.", QMessageBox::Ok, QMessageBox::NoButton);

   _controler->computeClique();
   setNbClique(_controler->getNbClique());

   _cliqueAct->setEnabled(false);
}


void mainWindow::centrality()
{
   _infWeightAct->setEnabled(true);
   _supWeightAct->setEnabled(true);
   _centralityAct->setEnabled(false);

   _controler->computeCentrality();

   //QMessageBox::information(this, QString::fromStdString("Program information."), "Not implemented yet.", QMessageBox::Ok, QMessageBox::NoButton);


}


