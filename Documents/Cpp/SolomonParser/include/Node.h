#ifndef NODE_H
#define NODE_H

#include<string>
#include<vector>


class Node
{
public:
    Node(int id=-1, int x = 0, int y = 0, int demand =0, int startW = 0, int endW = 10000, int service = 0);
    int getId();
    void setId(int id);
    int getX();
    int getY();
    int getDemand();
    int getStartW();
    int getEndW();
    int getService();
    std::string toString();

    virtual ~Node();
protected:
    int m_id;
    int m_x;
    int m_y;
    int m_demand;
    int m_startW;
    int m_endW;
    int m_service;

private:


};



#endif // NODE_H
