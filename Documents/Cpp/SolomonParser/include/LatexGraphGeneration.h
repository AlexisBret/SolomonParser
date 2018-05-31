#ifndef LATEXGRAPHGENERATION_H
#define LATEXGRAPHGENERATION_H

#include<Instance.h>
#include<vector>

class LatexGraphGeneration
{
    public:
        LatexGraphGeneration(Instance* inst);
        Instance* getInstance();
        std::string getName();
        std::string getGroup();
        std::vector<std::vector<int>> pathsIdentification();
        void generateTexFile(bool pictureOnly = false);
        std::string generatePicture();
        std::string compacityDetection(std::vector<std::vector<int>> allPaths, bool draw = false);

        virtual ~LatexGraphGeneration();
    protected:
        Instance* m_instance;
    private:
};

#endif // LATEXGRAPHGENERATION_H
