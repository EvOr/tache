#include "file_reader.hpp"

//--------------------------------------------
// METHODES PUBLIQUES
//--------------------------------------------

/// \return the AS index correspondant a la cle donnee
/// \param peerKey la cle donne
int File_reader::getPeerASIndex(int peerKey){
   return peers[peerKey][0];
}
///\brief Change le nom du fichier à lire
///\param le nom du fichier
void File_reader::change_file_name(std::string new_name){
   filename=new_name;
   peers.clear();
   peersMap.clear();
   peersVector.clear();
}
/// \brief fonction qui test si un point est un stub ou non
/// \param peersCount nombre de peers de oldVertex
/// \param clientsCount nombre de clients de oldVertex
/// \param currentVertex index du point courant
/// \param oldVertex index du point d'avant
/// \param vertexType identifieur du type de point ajoute
void File_reader::stubs_testing(int & peersCount, int & clientsCount, int currentVertex, int & oldVertex, int vertexType, vertex_descriptor & oldVertex_descriptor){

   if(currentVertex!=oldVertex){
      if(!(peersCount == 0 && clientsCount == 0)){
	 edge_descriptor e;
	 bool found;
	 std::vector< std::pair<vertex_descriptor, int> >::iterator it;
	 for(it=ansa.begin(); it != ansa.end() ; ++it){
	    int uguu = (*it).second;
	    vertex_descriptor vv =  (*it).first;
	    vertex_descriptor v = oldVertex_descriptor;
	    switch(uguu){
	       case PEER:
		  boost::tie(e,found) = boost::add_edge(v, vv, stubsGraph);
		  break;
	       case C2P:
		  boost::tie(e,found) = boost::add_edge(vv, v, stubsGraph);
		  break;
	       case P2C:
		  boost::tie(e,found) = boost::add_edge(v, vv, stubsGraph);
		  break;
	       default:
		  break;
	    } 
	 }   
	 ansa.clear();
	 peersCount=0;
	 clientsCount=0;
      }
   }
   switch(vertexType){
      case P2C:
	 clientsCount++;
	 break;
      case PEER:
	 peersCount++;
	 break;
      default:
	 break;
   }
}



/// \brief Fonction de lecture du fichier d'adjacence
/// \param g Matrice d'adjacence à remplir
/// \throws ReaderException when an error occurs
void File_reader::parse(Graph & g)
{
   int retour = 0;
   int nbPoint = 0, i1, i2;
   bool line_error = false, found= false;
   edge_descriptor e;
   vertex_descriptor oldVertex_descriptor;
   std::string line, tempString, linkType;
   vertex_descriptor v,vv ;

   try
   {
      std::ifstream file(filename.c_str());
      int oldVertex=0, vertexType=-1;
      int peersCount=0, clientsCount=0;
      if( file.is_open() )
      {
	 //remplissage de la matrice
	 while(std::getline(file, line)) {
	    // std::cout << "je lis la ligne" << file.tellg() << std::endl;
	    std::istringstream lineStream(line);
	    if(lineStream >> tempString) {
	       std::istringstream in1(tempString);
	       if(lineStream >> tempString) {
		  std::istringstream in2(tempString);
		  //Si tout rentre dans chacun des conteneurs...
		  if(lineStream >> linkType && in1 >> i1 && in2 >> i2) {
		     v = boost::vertex(i1,g);
		     vv = boost::vertex(i2,g);
		     vertexType=addEdge(v, vv, linkType, found, e, g);
		     if(!found) {
			line_error=true;
		     }else{
			stubs_testing(peersCount, clientsCount, i1, oldVertex, vertexType, oldVertex_descriptor);
			oldVertex=i1;
			oldVertex_descriptor = v;
		     }
		  }
		  else {
		     line_error=true;
		  }
	       }
	    }
	 }
	 if(peersCount == 0 && clientsCount == 0){
	    stubs_testing(peersCount, clientsCount, i1, oldVertex, vertexType, oldVertex_descriptor);
	 }   
	 file.close();

      }
      else{
	 throw ReaderException("Fichier inexistant ou non lisible", filename,ReaderException::CRITICAL);
      }
   }
   catch(const std::exception & e)
   {
      throw ReaderException("Erreur lors de la lecture du fichier", filename, ReaderException::CRITICAL);
   }
   if(line_error)
   {
      throw ReaderException("Erreur lors de la lecture d'une ou plusieurs ligne", filename, ReaderException::NON_BLOCKING);
   }
   //Fais passer la peers'matrice d'adjacence de 3140 à 1850 peers qui n'ont qu'une seule connection progression fulgurante... A tester sur des cas particuliers... On suppose que toutes les relations de peerings sont mises en double a vers b et b vers a il me semble que c'est le cas mais je n'ai évidemment pas tout vérifier...
   // Algo : Pour chque point stocker le ou les full mesh auxquels il appertient pour ça utiliser une map de vector ou autre chose ?
   // for(int i=0; i < peers.size(); i++){
   //   std::cout<<peersVector[i] << " : ";
   //   for(int j=0; j < peers[i].size();j++){
   //	 std::cout<< peers[i][j] << " ; ";
   //     }
   //    std::cout << std::endl;
   // }
   std::cout << peers.size() << std::endl;
   std::vector< std::vector<vertex_descriptor> >::iterator it,next;
   std::vector<vertex_descriptor>::iterator graou, graouNext ;
   graou=peersVector.begin();
   it=peers.begin();
   for(next = it, graouNext=graou ; it<peers.end() ; it=next, graou=graouNext){
      next++;
      graouNext++;
      if((*it).size() <= 1){
	 next=it;
	 graouNext=graou;
	 peers.erase(it);   
	 peersVector.erase(graou);
	 it=next;
	 graou=graouNext;
      }
   }
   std::cout << peers.size() << std::endl;
   //Creation de la map...
   std::vector<vertex_descriptor>::iterator uguu ;
   // for(int i=0; i < peers.size(); i++){
   //   std::cout<<peersVector[i] << " : ";
   //  for(int j=0; j < peers[i].size();j++){
   //	 std::cout<< peers[i][j] << " ; ";
   //     }
   //    std::cout << std::endl;
   // }
   for(uguu=peersVector.begin(); uguu!=peersVector.end();++uguu){
      peersMap[*uguu]=uguu-peersVector.begin();
   }
   // for(int i=1; i<=5;i++){
   //   std::cout << peersMap[i] << std::endl;
   // }
}

//--------------------------------------------
// METHODES PRIVEES
//--------------------------------------------

/// \brief Ajoute une arette
/// \param i1 index du premier point 
/// \param i2 index du deuxieme point
/// \param linkType descripteur du type d'arrete
/// \param found booleen resultat
/// \param e edge_descriptor de l'arrete
/// \param g double pointeur sur le Graph ou il faut ajouter la relation
/// \return le type de point
int File_reader::addEdge(vertex_descriptor & v, vertex_descriptor & vv, std::string linkType, bool & found, edge_descriptor & e, Graph & g){
   int res;
   //si on veut mettre des poids
   // 		if(found) (**g)[e].weight = xx%13 * 2 + 5;
   if(linkType=="PEER"){	
      // Pas besoin d'ajouter deux fois parce que les arcs en PEER sont presents en double
      boost::tie(e,found) = boost::add_edge( v,vv,g);
      res=PEER;
      //  boost::tie(e,found) = boost::add_edge(vv,v,g);
      addToPeersVector(v, vv);
      // Peer vers Client
   }else if(linkType=="C2P"){
      boost::tie(e,found) = boost::add_edge(vv,v,g);
      res=C2P;
   }else if(linkType=="P2C"){
      boost::tie(e,found) = boost::add_edge(v,vv,g);
      res=P2C;
   }
   // Ajout a l'adjacence du currentVertex
   std::pair<vertex_descriptor, int> pai(vv,res);
   ansa.push_back(pai);
   return res;
}
/// \brief ajoute les index de vecteurs a la map de traduction
/// \param index du premier point
/// \param index du deuxieme point
void File_reader::addToPeersVector(vertex_descriptor & v, vertex_descriptor & vv){
   bool i1here=false, i2here=false;
   int index1=0, index2=0;
   // PeerGraph::edge_descriptor e;
   bool found;
   std::vector<vertex_descriptor>::iterator it;
   for(it = peersVector.begin(); it<peersVector.end() && (!index2 || !index1) ; it++){
      if(*it == v) 
      {
	 i1here = true;
	 index1 = it - peersVector.begin(); 
      }
      //   if(*it == i2) {
      //	 i2here = true;
      //	 index2 = it - peersVector.begin();
      //     }
   }
   if(!i1here){
      peersVector.push_back(v);
      peers.push_back(*(new std::vector<vertex_descriptor>()));
      index1=peers.size() - 1;
   }
   // if(!i2here) {
   //   peersVector.push_back(i2);
   // peers.push_back(*(new std::vector<int>()));
   //  index2=peers.size() - 1;
   // }

   peers[index1].push_back(vv);
   // peers[index2].push_back(index1);
}

