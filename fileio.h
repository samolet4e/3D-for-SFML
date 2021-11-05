#ifndef FILEIO_H
#define FILEIO_H

typedef struct _points {
    float x, y, z;
} points;

typedef struct _cells {
    int n[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
} cells;

int readBlock(std::string fileName, std::string line1, std::string line2, std::vector<points> &fooP, std::vector<cells> &fooC);

#endif // FILEIO_H
