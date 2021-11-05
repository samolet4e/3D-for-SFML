#include "cell.h"
#include <cmath>

myCell::myCell(const std::vector<points> pt, int thick, sf::Color col) {
int i;

    (*this).sizeP = (int)pt.size();
    sf::Vector3f Pt;
    // Fill in P vector
    for (i = 0; i < sizeP; i++) {
        Pt.x = pt.at(i).x;
        Pt.y = pt.at(i).y;
        Pt.z = pt.at(i).z;
        (*this).P.push_back(Pt);
    }//for_i

    (*this).cShape.setPointCount(sizeP);
//    (*this).cShape.setFillColor(sf::Color(0, 255, 0, alpha));
    (*this).cShape.setFillColor(col);
    (*this).cShape.setOutlineColor(sf::Color::White);
    (*this).cShape.setOutlineThickness(thick);

    for (i = 0; i < sizeP; i++)
        (*this).cShape.setPoint(i, sf::Vector2f(P.at(i).x + offset, P.at(i).y + offset));

    // front, back, top, bottom, right, left

    float p[3], q[3]; // p[x,y,z], q[x,y,z]
    // compute normal vector components; ACHTUING: quad only!
    p[0] = P[0].x - P[2].x;
    p[1] = P[0].y - P[2].y;
    p[2] = P[0].z - P[2].z;
    q[0] = P[1].x - P[3].x;
    q[1] = P[1].y - P[3].y;
    q[2] = P[1].z - P[3].z;

    float Sx = 0.5 * (p[1] * q[2] - p[2] * q[1]);
    float Sy = 0.5 * (p[0] * q[2] - p[2] * q[0]);
    float Sz = 0.5 * (p[0] * q[1] - p[1] * q[0]);
    float S = sqrt(Sx * Sx + Sy * Sy + Sz * Sz);
    float nx = Sx / S;
    float ny = Sy / S;
    float nz = Sz / S;

    (*this).n = {nx, ny, nz};

} // constructor

myCell::~myCell() {

    (*this).P.clear();

} // destructor

sf::ConvexShape myCell::getShape() {

    return (*this).cShape;

} // myCell::getShape

sf::Vector3f myCell::getN() {

    return (*this).n;

} // myCell::getN

void myCell::Rotate(sf::Vector3f O, sf::Vector3f W, float theta) {
int i;

    float norm = sqrt(W.x * W.x + W.y * W.y + W.z * W.z);

    float one_cosT = 1. - cos(theta * M_PI / 180.);
    float sinT = sin(theta * M_PI / 180.);
    float cosT = cos(theta * M_PI / 180.);
    float wx = W.x / norm, wy = W.y / norm, wz = W.z / norm;

    float R[3][3];

    R[0][0] = cosT + wx * wx * one_cosT;
    R[0][1] = wx * wy * one_cosT - wz * sinT;
    R[0][2] = wy * sinT + wx * wz * one_cosT;

    R[1][0] = wz * sinT + wx * wy * one_cosT;
    R[1][1] = cosT + wy * wy * one_cosT;
    R[1][2] = -wx * sinT + wy * wz * one_cosT;

    R[2][0] = -wy * sinT + wx * wz * one_cosT;
    R[2][1] = wx * sinT + wy * wz * one_cosT;
    R[2][2] = cosT + wz * wz * one_cosT;

    std::vector<sf::Vector3f> Psh{0};

    for (i = 0; i < (*this).sizeP; i++)
        Psh.push_back(P.at(i) - O); // push matrix

    std::vector<sf::Vector3f> Prot{0};
    for (i = 0; i < (*this).sizeP; i++) {

        sf::Vector3f x0 = {Psh.at(i).x, Psh.at(i).y, Psh.at(i).z};
        sf::Vector3f x1;
        x1.x = R[0][0] * x0.x + R[0][1] * x0.y + R[0][2] * x0.z;
        x1.y = R[1][0] * x0.x + R[1][1] * x0.y + R[1][2] * x0.z;
        x1.z = R[2][0] * x0.x + R[2][1] * x0.y + R[2][2] * x0.z;

        Prot.push_back(x1 + O); // pop matrix

    }//for_i

    Psh.clear();

    P = Prot; // don't even mention it
    Prot.clear();

    for (i = 0; i < sizeP; i++)
        (*this).cShape.setPoint(i, sf::Vector2f(P.at(i).x + offset, P.at(i).y + offset));

    float p[3], q[3]; // p[x,y,z], q[x,y,z]
    // compute normal vector components; ACHTUING: quad only!
    p[0] = P[0].x - P[2].x;
    p[1] = P[0].y - P[2].y;
    p[2] = P[0].z - P[2].z;
    q[0] = P[1].x - P[3].x;
    q[1] = P[1].y - P[3].y;
    q[2] = P[1].z - P[3].z;

    float Sx = 0.5 * (p[1] * q[2] - p[2] * q[1]);
    float Sy = 0.5 * (p[0] * q[2] - p[2] * q[0]);
    float Sz = 0.5 * (p[0] * q[1] - p[1] * q[0]);
    float S = sqrt(Sx * Sx + Sy * Sy + Sz * Sz);
    float nx = Sx / S;
    float ny = Sy / S;
    float nz = Sz / S;

    (*this).n = {nx, ny, nz};

} // myCell::Rotate
