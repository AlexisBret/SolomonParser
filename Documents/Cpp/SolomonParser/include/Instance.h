#ifndef INSTANCE_H
#define INSTANCE_H

#include<Node.h>

#include<string>
#include<vector>

class Instance
{
    public:
        Instance(int nbPts, int capacity = 1000, std::string name = "test", std::string group = "testGroup");
        int getNbPts();
        int getCapacity();
        std::string getName();
        std::string getGroup();
        Node* getPoint(int i);
        int getDistance(int i, int j);
        void setDistance(int i, int j, int val);
        void processDistances();
        void addNode(Node* n);
        void printDistances();
        std::string toString();

        virtual ~Instance();
    protected:
    private:
        int m_nbPts;
        int m_capacity;
        std::string m_name;
        std::string m_group;
        std::vector<Node*> m_points;
        std::vector<std::vector<int> > m_distances;
};

#endif // INSTANCE_H
