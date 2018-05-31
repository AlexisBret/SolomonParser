#include "LatexGraphGeneration.h"

#include<iostream>
#include<string>
#include<vector>
#include <fstream>

using namespace std;

LatexGraphGeneration::LatexGraphGeneration(Instance* inst) : m_instance(inst)
{
    //ctor
}

Instance* LatexGraphGeneration::getInstance()
{
    return m_instance;
}

string LatexGraphGeneration::getName()
{
    return getInstance()->getName();
}

string LatexGraphGeneration::getGroup()
{
    return getInstance()->getGroup();
}

vector<vector<int>> LatexGraphGeneration::pathsIdentification()
{
    vector<vector<int>> allPaths;
    string filename ="solution" + getName().substr(0,getName().size()-3) + "out";

    string filepath = "C:/Users/Alexis/Documents/Cpp/SolomonParser/solutions/" + getGroup()+ "/"+filename;
    cout << filepath << endl;
    ifstream fichier(filepath.c_str());
    if(fichier)
    {
        //L'ouverture s'est bien passée, on peut donc lire

        string line; //Une variable pour stocker les lignes lues
        string temp;

        while (line != "Paths = {")
        {
            getline(fichier, line);
        }
        while (!fichier.eof() && !(line.find("nSrc") != std::string::npos))
        {
            getline(fichier, line);

            if (line.find("nSrc") != std::string::npos)
            {

                getline(fichier, line);
                vector<int> path;
                path.push_back(0);
                int next(-1);
                bool stop = false;
                while (!stop)
                {
                    fichier >>temp;
                    stop = (temp.find("nSnk") != std::string::npos);
                    if(!stop)
                    {
                        next = stoi(temp.substr(9, temp.size()));
                        path.push_back(next);
                        getline(fichier, line);
                        getline(fichier, line);
                    }
                    else
                    {
                        path.push_back(0);
                        allPaths.push_back(path);
                    }
                }

            }
        }

    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }

    for (vector<int> pa : allPaths)
    {
        for (int p : pa)
        {
            cout << to_string(p) << ", ";
        }
        cout << endl;
    }

    return allPaths;
}

void LatexGraphGeneration::generateTexFile(bool pictureOnly)
{
    string res("");
    if (!pictureOnly)
    {
        res+= "\\documentclass{article}\n\\usepackage[french]{babel}\n\\usepackage[T1]{fontenc}\n\\usepackage[utf8]{inputenc}\n\\usepackage{geometry}\n\\usepackage{tikz}\n";
        res+= "\\title{Solution for instance" + getName() +"}\n";
        res+="\\geometry{top=1cm, bottom=1cm, left=1cm , right=1cm}\n";
        res+= "\\begin{document}\n\\maketitle\n";
    }
    res+= generatePicture();
    if (!pictureOnly)
    {
        res+="\n\\end{document}";
    }
    string texFileName = "solution" + getName().substr(0,getName().size()-3) + "tex";
    string const filepath = "C:/Users/Alexis/Documents/Cpp/SolomonParser/solutions/" + getGroup()+ "/" + texFileName;
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

    cout << res << endl;
}

string LatexGraphGeneration::generatePicture()
{
    vector<string> colors {"blue", "red", "green", "pink", "yellow", "brown"};
    int pathIdx(0);

    string res("");
    res+="\\newpage\n";
    res+="\\begin{figure}[h!]\n    \\centering\n\\begin{tikzpicture}[scale = 0.2]\n";
    for (int i(0); i < getInstance()->getNbPts(); i++)
    {
        res+= "\\node[draw] (C"+to_string(i)+") at ("+to_string(getInstance()->getPoint(i)->getX())+", "+ to_string(getInstance()->getPoint(i)->getY())+") {C"+to_string(i)+"};\n";
    }
    vector<vector<int>> allPaths = pathsIdentification();
    for (vector<int> pa : allPaths)
    {
        string color = colors[pathIdx % (int) (colors.size())];
        //string color ("black");
        //if (pathIdx<(int)colors.size())
        //{
        //    color = colors[pathIdx];
        //}
        int idx(1);
        int from(0);
        int to(pa[idx]);
        res+= "\\draw[dashed,"+color+",->,>=latex] (C"+to_string(from)+") -- (C"+to_string(to)+");\n";
        from = to;
        idx++;
        to = pa[idx];
        while (to != 0)
        {
            res+= "\\draw["+color+",->,>=latex] (C"+to_string(from)+") -- (C"+to_string(to)+");\n";
            from = to;
            idx++;
            to = pa[idx];
        }
        res+= "\\draw[dashed,"+color+",->,>=latex] (C"+to_string(from)+") -- (C"+to_string(to)+");\n";
        pathIdx++;
    }

    res+= compacityDetection(allPaths, true);
    res+="\\end{tikzpicture}\n\\end{figure}";



    return res;

}

string LatexGraphGeneration::compacityDetection(vector<vector<int>> allPaths, bool draw)
{
string res = "";
    for (vector<int> path : allPaths)
    {
        int from(0);
        int to(0);
        int distComp(0);
        //for each path
        for(int i : path)
        {
            for (int j : path)
            {
                if (i!= 0 && j!=0 && getInstance()->getDistance(i,j)>distComp)
                {
                    distComp = getInstance()->getDistance(i,j);
                    from = i;
                    to = j;
                }
            }
        }
        cout << "Compacity for path : " << to_string(distComp) << " between " << to_string(from) << " and " << to_string(to) << endl;
   if (draw){
        double centerX = ((double) (getInstance()->getPoint(from)->getX()) + (double)(getInstance()->getPoint(to)->getX()))/2.0;
        double centerY = ((double) (getInstance()->getPoint(from)->getY()) + (double)(getInstance()->getPoint(to)->getY()))/2.0;
        res+= "\\draw [thick] (" + to_string(centerX) + "," + to_string(centerY) +") circle ("+to_string((double)(distComp)/2.0) +");\n";
   }

    }
    cout << res << endl;
    return res;
}


LatexGraphGeneration::~LatexGraphGeneration()
{
    //dtor
}
