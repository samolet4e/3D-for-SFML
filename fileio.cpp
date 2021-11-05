#include <fstream>
#include <sstream>
#include <vector>
#include "fileio.h"

int readBlock(std::string fileName, std::string magicWord1, std::string magicWord2, std::vector<points> &fooP, std::vector<cells> &fooC) {

    std::ifstream fileToRead(fileName, std::ifstream::in);
    if ((fileToRead.rdstate() & std::ifstream::failbit) != 0) return -1;

    std::string lineToRead;

    bool goRead = false;
    while (getline(fileToRead, lineToRead)) {

        if (goRead == true) {
            if (lineToRead.compare("") == 0) { goRead = false; continue; }
            std::stringstream lineStream(lineToRead);
            points p;
            lineStream >> p.x >> p.y >> p.z;
            fooP.push_back(p);
        } // if

        std::stringstream ss(lineToRead);
        std::string s0;//, s1, s2;
//        ss >> s0 >> s1 >> s2;
        ss >> s0;
        if (s0.compare(magicWord1) == 0) goRead = true;

    }//while

    fileToRead.clear();
    fileToRead.seekg(0, std::ios::beg);

    goRead = false;
    while (getline(fileToRead, lineToRead)) {

        if (goRead == true) {
            if (lineToRead.compare("") == 0) { goRead = false; continue; }
            std::stringstream lineStream(lineToRead);
            cells c; int n; // dummy
//            lineStream >> n >> c.n[0] >> c.n[1] >> c.n[2] >> c.n[3];
            lineStream >> n;
            for (int i = 0; i < n; i++) lineStream >> c.n[i];
            fooC.push_back(c);
        } // if

        std::stringstream ss(lineToRead);
        std::string s0;//, s1, s2;
        ss >> s0;// >> s1 >> s2;
        if (s0.compare(magicWord2) == 0) goRead = true;

    }//while

    fileToRead.close();

    return 0;
}//readBlock
