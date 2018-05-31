#include "Instance.h"

#include <iostream>
#include<vector>
#include<math.h>

using namespace std;

Instance::Instance(int nbPts, int capacity, string name, string group) : m_nbPts(nbPts), m_capacity(capacity), m_name(name), m_group(group)
{
   vector<Node*> pts;
   pts.reserve(nbPts);
   m_points = pts;
   vector<vector<int>> dist(nbPts);
   for (int i(0); i < nbPts; i++){
    vector<int> distI(nbPts,0);
    dist[i] = distI;
   }
   m_distances = dist;
}

int Instance::getNbPts(){
return m_nbPts;
}

int Instance::getCapacity(){
return m_capacity;
}

string Instance::getName(){
    return m_name;
}

string Instance::getGroup(){
return m_group;
}

Node* Instance::getPoint(int i){
    return m_points[i];
}

int Instance::getDistance(int i, int j){
return m_distances[i][j];
}

void Instance::setDistance(int i, int j, int val){
m_distances[i][j] = val;
}

void Instance::addNode(Node* n){
m_points.push_back (n);
}

void Instance::processDistances(){
for (int i(0); i < getNbPts(); i++){
    for (int j(i+1); j < getNbPts(); j++){
        int distIJ = sqrt(pow((getPoint(i)->getX()-getPoint(j)->getX()),2) +  pow((getPoint(i)->getY()-getPoint(j)->getY()),2));
        setDistance(i,j, distIJ);
        setDistance(j,i, distIJ);

}
}
}

void Instance::printDistances(){
for (int i(0); i < getNbPts(); i++){
    for (int j(0); j < getNbPts(); j++){
            cout << to_string(getDistance(i,j)) <<" ";
    }
    cout << endl;
}
}

string Instance::toString(){
string res("");
    for (int i = 0; i < getNbPts(); i ++){
        res+= getPoint(i)->toString()+"\n";
    }
    return res;
}

Instance::~Instance()
{
    //dtor
}
