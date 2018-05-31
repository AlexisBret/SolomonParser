#include "Node.h"

#include<string>
#include <sstream>


using namespace std;

Node::Node(int id, int x, int y, int demand, int startW, int endW, int service) : m_id(id), m_x(x), m_y(y), m_demand(demand), m_startW(startW), m_endW(endW), m_service(service)
{
}

int Node::getId()
{
    return m_id;
}

void Node::setId(int id)
{
    m_id = id;
}

int Node::getX(){
return m_x;
}

int Node::getY(){
return m_y;
}

int Node::getDemand(){
return m_demand;
}

int Node::getStartW(){
return m_startW;}

int Node::getEndW(){
return m_endW;
}



int Node::getService(){
return m_service;
}



std::string Node::toString()
{
    return to_string(getId()) + " (" + to_string(getX()) +", " + to_string(getY()) + ")  ["+to_string(getStartW())+", "+to_string(getEndW()) +"]";
}




Node::~Node()
{
    //dtor
}
