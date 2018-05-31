#include "ProblemGeneration.h"

#include<Instance.h>
#include<Node.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


ProblemGeneration::ProblemGeneration(string filename, string group): m_filename(filename), m_group(group)
{
}

string ProblemGeneration::getGroup(){
return m_group;
}

string ProblemGeneration::getFilename(){
return m_filename;
}

Instance* ProblemGeneration::generateInstance(int nbPts){
    string filepath = "C:/Users/Alexis/Documents/Cpp/SolomonParser/instances/" + getGroup()+ "/" + getFilename();
    cout << filepath << endl;
    ifstream fichier(filepath.c_str());
 Instance* inst;
   if(fichier)
   {
      //L'ouverture s'est bien passée, on peut donc lire

      string line; //Une variable pour stocker les lignes lues
      string temp;
      int capacity(0);
      int id(0);
      int lastId(-1);
      int x(0);
      int y(0);
      int demand(0);
      int startW(0);
      int endW(0);
      int service(0);

      for (int i =0; i < 3 ; i ++){
        getline(fichier, line);
      }
        getline(fichier, line);
        fichier >> temp;
         fichier >> temp;
         capacity = std::stoi(temp);
         inst = new Instance(nbPts, capacity, getFilename(), getGroup());
         cout << inst->getCapacity() <<endl;
       for (int i =0; i < 4 ; i ++){
        getline(fichier, line);
      }



      while(!fichier.eof()) //Tant qu'on n'est pas à la fin, on lit
      {
          fichier >> id;
          if (id!=lastId){
          fichier >> x;
          fichier >> y;
          fichier >> demand;
          fichier >> startW;
          fichier >> endW;
          fichier >> service;
         Node* n = new Node(id, x, y, demand, startW, endW, service);
         inst->addNode(n);
         lastId = id;
          }
      }
   }
   else
   {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
   }

return inst;
}

void ProblemGeneration::generateProblemFile(Instance* inst){
string res("Rows = {\n");
for (int i(1); i< inst->getNbPts(); i++ ){
    res+= "\tr_Client_"+to_string(i)+ " = 1 TaskStrong;\n";
}
res+="\trCounterT1_  =  0;\n};\n\n";
res+= "Columns = {\n\tcCounterT1_  1000  Int  [0 1e+20]  (rCounterT1_  -1);\n};\n\n";
res+="Resources = {\n\t__rTime  Strong;\n\t__rLoad  Strong;\n};\n\n";
res+="Tasks = {\n";
for (int i(1); i< inst->getNbPts(); i++ ){
    res+= "\tClient_"+to_string(i)+"  r_Client_"+to_string(i)+"  Strong;\n";
}
res+="};\n\nTaskConstraints = {};\n\nNodeTypes = {};\n\nArcTypes = {};\n\n";
res+="Nodes = {\n";
for (int i(1); i< inst->getNbPts(); i++ ){
    res+= "\tn_Client_"+to_string(i)+"  ["+to_string(inst->getPoint(i)->getStartW())+" "+to_string(inst->getPoint(i)->getEndW())+ "] [0 "+to_string(inst->getCapacity())+"] Client_"+to_string(i)+";\n";
}
res+="\tnSrc_    ["+to_string(inst->getPoint(0)->getStartW())+" "+to_string(inst->getPoint(0)->getEndW())+ "] [0 "+to_string(inst->getCapacity())+"];\n";
res+="\tnSnk_    ["+to_string(inst->getPoint(0)->getStartW())+" "+to_string(inst->getPoint(0)->getEndW())+ "] [0 "+to_string(inst->getCapacity())+"];\n};\n\n";
res+="ArcSets = {\n\tas;\n};\n\n";
res+="Arcs = {\n";
for (int j(1); j< inst->getNbPts(); j++ ){
        res+= "\tnSrc_  n_Client_"+to_string(j)+ " "+ to_string(inst->getDistance(0,j)) +" as ["+to_string(inst->getDistance(0,j))+" "+ to_string(inst->getPoint(j)->getDemand()) +"] (rCounterT1_  1);\n";
        res+= "\tn_Client_"+to_string(j)+"  nSnk_ "+ to_string(inst->getDistance(0,j)) +" as ["+to_string(inst->getDistance(0,j))+" 0];\n";
}
for (int i(1); i< inst->getNbPts(); i++ ){
for (int j(1); j< inst->getNbPts(); j++ ){
    if (i!=j){
        res+= "\tn_Client_"+ to_string(i)+"  n_Client_"+to_string(j)+ " "+ to_string(inst->getDistance(i,j)) +" as ["+to_string(inst->getDistance(i,j))+" "+ to_string(inst->getPoint(j)->getDemand()) +"];\n";
    }
}
}
res+= "};\n\n";
res+="Networks = {\n\tnet_  nSrc_  ( nSnk_ )  ( as );\n};";

    string problemFileName = "problem" + getFilename().substr(0,getFilename().size()-3) + "out";
    cout << problemFileName<< endl;
    string const filepath = "C:/Users/Alexis/Documents/Cpp/SolomonParser/problems/" + getGroup()+ "/" + problemFileName;
    cout << filepath << endl;
    ofstream monFlux(filepath.c_str());

    if(monFlux)
    {
       monFlux << res <<endl;
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}

ProblemGeneration::~ProblemGeneration()
{
    //dtor
}


