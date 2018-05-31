#ifndef PROBLEMGENERATION_H
#define PROBLEMGENERATION_H

#include<Instance.h>
#include<string>

class ProblemGeneration
{
    public:
        ProblemGeneration(std::string filename,std::string group = "solomon_50");
        std::string getGroup();
        std::string getFilename();
        Instance* generateInstance(int nbPts = 51);
        void generateProblemFile(Instance* inst);
        virtual ~ProblemGeneration();
    protected:
    private:
        std::string m_filename;
        std::string m_group;


};

#endif // PROBLEMGENERATION_H
