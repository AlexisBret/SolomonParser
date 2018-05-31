#include <iostream>
#include <ProblemGeneration.h>
#include <Instance.h>
#include <LatexGraphGeneration.h>

using namespace std;

int main()
{
    /*vector<int> idxC{101, 102, 103, 104, 105, 106, 107, 108, 109,201, 202, 203, 204, 205,206, 207, 208};
    vector<int> idxR{101, 102, 103, 104, 105, 106, 107, 108, 109,110, 111, 112,201, 202, 203, 204, 205,206, 207, 208,209,210, 211};
    vector<int> idxRC{101, 102, 103, 104, 105, 106, 107, 108,201, 202, 203, 204, 205,206, 207, 208};
    vector<string> instances;
    for (int i : idxC){
        instances.push_back("C"+to_string(i)+".txt");
    }
        for (int i : idxR){
        instances.push_back("R"+to_string(i)+".txt");
    }
        for (int i : idxRC){
        instances.push_back("RC"+to_string(i)+".txt");
    }
    for (string instName : instances){
    ProblemGeneration pg(instName, "solomon_100");
    Instance* inst = pg.generateInstance(101);
    inst->processDistances();
    //inst->printDistances();
    pg.generateProblemFile(inst);
    }*/
    int nbPts = 100;
    ProblemGeneration pg("R101.txt", "solomon_"+to_string(nbPts));
    Instance* inst = pg.generateInstance(nbPts+1);
    inst->processDistances();
    LatexGraphGeneration lgg(inst);
    lgg.pathsIdentification();
    lgg.generateTexFile(true);
    return 0;
}
