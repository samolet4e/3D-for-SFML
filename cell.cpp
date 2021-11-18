#include "cell.h"
#include <cmath>

// #define PERSPECTIVE

Shape::Shape() {

    n = sf::Vector3f(0., 0., 0.); // normal vector components
    mc = sf::Vector3f(0., 0., 0.); // mass center coordinates

} // constructor

void Cell::get_projected_point(float &x, float &y, float &z) {

    float x_ = x;// - imageWidth;
    float y_ = y;// - imageHeight;
    float z_ = z;

    float Z0 = 512.;
    float Z = (Z0 + z_) / Z0;

    float x1 = x_ * Z;
    float y1 = y_ * Z;
    float z1 = z_;

//    x = x1 + imageWidth; y = y1 + imageHeight; z = z1;
    x = x1; y = y1; z = z1;

    return;
} // Cell::get_projected_point

Cell::Cell(const std::vector<sf::Vector3f> pt, sf::Color col) : Shape() {
int i;

    (*this).sizeP = (int)pt.size();

    // Fill in P vector
    for (i = 0; i < sizeP; i++) {
        sf::Vector3f Pt;
        Pt.x = pt.at(i).x;
        Pt.y = pt.at(i).y;
        Pt.z = pt.at(i).z;
        (*this).P.push_back(Pt);
    }//for_i

    (*this).cShape.setPointCount(sizeP);
    (*this).cShape.setFillColor(col);
    (*this).cShape.setOutlineColor(sf::Color::Black);
    (*this).cShape.setOutlineThickness(-1);

    // Define corner points of the ConvexShape instance
    for (i = 0; i < sizeP; i++) {

        float x = P.at(i).x, y = P.at(i).y, z = P.at(i).z;
#if defined PERSPECTIVE
        (*this).get_projected_point(x, y, z);
#else
#endif // PERSPECTIVE
        (*this).cShape.setPoint(i, sf::Vector2f(x, y)); z = z; // avoid warning

    }//for_i

    // Compute normal vector components
    float p[3] = {0., 0., 0.}, q[3] = {0., 0., 0.}; // p[x,y,z], q[x,y,z]
    if (sizeP == 4) { // quadrangle

        p[0] = P[0].x - P[2].x;
        p[1] = P[0].y - P[2].y;
        p[2] = P[0].z - P[2].z;
        q[0] = P[1].x - P[3].x;
        q[1] = P[1].y - P[3].y;
        q[2] = P[1].z - P[3].z;

    }//if
    else if (sizeP == 3) { // triangle

        p[0] = P[0].x - P[1].x;
        p[1] = P[0].y - P[1].y;
        p[2] = P[0].z - P[1].z;

        q[0] = P[0].x - P[2].x;
        q[1] = P[0].y - P[2].y;
        q[2] = P[0].z - P[2].z;

    }//else_if
    else {}

    float Sx = 0.5 * (p[1] * q[2] - p[2] * q[1]);
    float Sy = 0.5 * (-p[0] * q[2] + p[2] * q[0]);
    float Sz = 0.5 * (p[0] * q[1] - p[1] * q[0]);
    float S = sqrt(Sx * Sx + Sy * Sy + Sz * Sz);
    float nx = Sx / S;
    float ny = Sy / S;
    float nz = Sz / S;

    (*this).setN(sf::Vector3f{nx, ny, nz});

    // Compute mass center coordinates
    float xc = 0., yc = 0., zc = 0.;

    i = 0;
    while (i < sizeP) {
        xc += P.at(i).x;
        yc += P.at(i).y;
        zc += P.at(i).z;
        i++;
    } // while_i
    xc /= (float)i; yc /= (float)i; zc /= (float)i;

    (*this).setMC(sf::Vector3f{xc, yc, zc});

} // constructor

Cell::~Cell() {

    (*this).P.clear();

} // destructor

Shape::~Shape() {

} // destructor

sf::ConvexShape Cell::getCell() {

    return (*this).cShape;

} // Cell::getCell

sf::Vector3f Shape::getN() {

    return (*this).n;

} // Shape::getN

sf::Vector3f Shape::getMC() {

    return (*this).mc;

} // Shape::getMC

void Shape::setN(sf::Vector3f n) {

    (*this).n = n;

} // Shape::setN

void Shape::setMC(sf::Vector3f mc) {

    (*this).mc = mc;

} // Shape :: setMC

void Cell::Rotate(sf::Vector3f O, sf::Vector3f W, float theta) {
int i;

    float norm = sqrt(W.x * W.x + W.y * W.y + W.z * W.z);
    theta *= M_PI / 180.;

    float one_cosT = 1. - cos(theta);
    float sinT = sin(theta);
    float cosT = cos(theta);
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
    // Shift points to the origin
    for (i = 0; i < (*this).sizeP; i++) Psh.push_back(P.at(i) - O); // push matrix
    // Rotate the shifted points
    std::vector<sf::Vector3f> Prot{0};
    for (i = 0; i < (*this).sizeP; i++) {

        sf::Vector3f x0 = {Psh.at(i).x, Psh.at(i).y, Psh.at(i).z};
        sf::Vector3f x1;
        x1.x = R[0][0] * x0.x + R[0][1] * x0.y + R[0][2] * x0.z;
        x1.y = R[1][0] * x0.x + R[1][1] * x0.y + R[1][2] * x0.z;
        x1.z = R[2][0] * x0.x + R[2][1] * x0.y + R[2][2] * x0.z;
        // Now that points are rotated, take them back to where they are coming from
        Prot.push_back(x1 + O); // pop matrix

    }//for_i

    Psh.clear();
    // Keep track of the corner points!
    P = Prot;
    Prot.clear();

    // Update corner points of the ConvexShape instance
    for (i = 0; i < sizeP; i++) {

        float x = P.at(i).x, y = P.at(i).y, z = P.at(i).z;
#if defined PERSPECTIVE
        (*this).get_projected_point(x, y, z);
#else
#endif // PERSPECTIVE
        (*this).cShape.setPoint(i, sf::Vector2f(x, y)); z = z; // avoid warning

    }//for_i

    // Update normal vector components
    sf::Vector3f n0 = (*this).getN(); // no push matrix is necessary
    sf::Vector3f n1;

    n1.x = R[0][0] * n0.x + R[0][1] * n0.y + R[0][2] * n0.z;
    n1.y = R[1][0] * n0.x + R[1][1] * n0.y + R[1][2] * n0.z;
    n1.z = R[2][0] * n0.x + R[2][1] * n0.y + R[2][2] * n0.z;

    (*this).setN(sf::Vector3f{n1.x, n1.y, n1.z}); // no pop matrix is necessary

    // Update mass center coordinates
    sf::Vector3f xc0 = getMC(); xc0 -= O; // push matrix
    sf::Vector3f xc1;

    xc1.x = R[0][0] * xc0.x + R[0][1] * xc0.y + R[0][2] * xc0.z;
    xc1.y = R[1][0] * xc0.x + R[1][1] * xc0.y + R[1][2] * xc0.z;
    xc1.z = R[2][0] * xc0.x + R[2][1] * xc0.y + R[2][2] * xc0.z;

    (*this).setMC(xc1 + O); // pop matrix

} // myCell::Rotate
