#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include "fileio.h"

class myCell {

private:
    std::vector<sf::Vector3f> P{0};
    sf::ConvexShape cShape; // the shape itself
    sf::Vector3f n; // normal vector components
    uint8_t offset = 0, alpha = 255;
    int sizeP; // number of cell vertices

public:
    myCell(const std::vector<points> pt, int thick, sf::Color col);
    ~myCell();
    sf::ConvexShape getShape();
    sf::Vector3f getN();
    void Rotate(sf::Vector3f O, sf::Vector3f W, float theta);

//    void setProjectionMatrix(const float angleOfView, const float near, const float far);

}; // myCell

#endif // CELL_H
