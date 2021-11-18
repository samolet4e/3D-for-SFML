#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

#define ITER(cell, i) for(int i = 0; i < (int)cell.size(); i++)
#define imageWidth 1280
#define imageHeight 720

class Shape {

private:
    sf::Vector3f n; // normal vector components
    sf::Vector3f mc; // mass center coordinates

public:
    Shape();
    ~Shape();
    sf::Vector3f getN();
    sf::Vector3f getMC();
    void setN(sf::Vector3f n);
    void setMC(sf::Vector3f mc);

}; // Shape

class Cell : public Shape {

private:
    std::vector<sf::Vector3f> P{0};
    sf::ConvexShape cShape; // the shape itself
    int sizeP; // number of cell vertices

public:
    Cell(const std::vector<sf::Vector3f> pt, sf::Color col);
    ~Cell();
    sf::ConvexShape getCell();
    void Rotate(sf::Vector3f O, sf::Vector3f W, float theta);
    void get_projected_point(float &x, float &y, float &z);

}; // Cell

#endif // CELL_H
