#include "cell.h"
#include "fileio.h"

int main() {
/*
    // Front
    std::vector<sf::Vector3f> q0 = {{100., 100., 0.}, {200., 100., 0.}, {200., 200., 0.}, {100., 200., 0.}};
    // Back
    std::vector<sf::Vector3f> q1 = {{200., 100., -100.}, {100., 100., -100.}, {100., 200., -100.}, {200., 200., -100.}};
    // Top
    std::vector<sf::Vector3f> q2 = {{100., 100., -100.}, {200., 100., -100.}, {200., 100., 0.}, {100., 100., 0.}};
    // Bottom
    std::vector<sf::Vector3f> q3 = {{100., 200., 0.}, {200., 200., 0.}, {200., 200., -100.}, {100., 200., -100.}};
    // Right
    std::vector<sf::Vector3f> q4 = {{200., 100., 0.}, {200., 100., -100.}, {200., 200., -100.}, {200., 200., 0.}};
    // Left
    std::vector<sf::Vector3f> q5 = {{100., 100., -100.}, {100., 100., 0.}, {100., 200., 0.}, {100., 200., -100.}};
*/

    std::vector<points> pp{0};
    std::vector<cells> cc{0};
    readData(pp, cc, "quad.vtk");
/*
ITER(pp, i) std::cout << pp.at(i).x << '\t' << pp.at(i).y << '\t' << pp.at(i).z << std::endl;
ITER(cc, i) std::cout << cc.at(i).n[0] << '\t' << cc.at(i).n[1] << '\t' << cc.at(i).n[2] << '\t' << cc.at(i).n[3] << std::endl;
*/
    std::vector<std::vector<sf::Vector3f>> q{6};
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 4; j++)
            q.at(i).push_back({pp.at(cc.at(i).n[j]).x, pp.at(cc.at(i).n[j]).y, pp.at(cc.at(i).n[j]).z});

    std::vector<Cell> cellQua; // (0, Cell(q0, sf::Color::Green));
    Cell c0(q.at(0), sf::Color(0, 255, 0, 255)); cellQua.push_back(c0);
    Cell c1(q.at(1), sf::Color(255, 0, 0, 255)); cellQua.push_back(c1);
    Cell c2(q.at(2), sf::Color(0, 0, 255, 255)); cellQua.push_back(c2);
    Cell c3(q.at(3), sf::Color(255, 255, 0, 255)); cellQua.push_back(c3);
    Cell c4(q.at(4), sf::Color(0, 255, 255, 255)); cellQua.push_back(c4);
    Cell c5(q.at(5), sf::Color(255, 0, 255, 255)); cellQua.push_back(c5);

    pp.clear();
    cc.clear();
    readData(pp, cc, "tri.vtk");
/*
std::cout << std::endl;
ITER(pp, i) std::cout << pp.at(i).x << '\t' << pp.at(i).y << '\t' << pp.at(i).z << std::endl;
ITER(cc, i) std::cout << cc.at(i).n[0] << '\t' << cc.at(i).n[1] << '\t' << cc.at(i).n[2] << '\t' << cc.at(i).n[3] << std::endl;
*/
    std::vector<std::vector<sf::Vector3f>> t{4};

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            t.at(i).push_back({pp.at(cc.at(i).n[j]).x, pp.at(cc.at(i).n[j]).y, pp.at(cc.at(i).n[j]).z});
/*
    std::vector<sf::Vector3f> t0 = {{300., 100., 28.8675}, {400., 100., 28.8675}, {350., 100., -57.7350}};
    std::vector<sf::Vector3f> t1 = {{300., 100., 28.8675}, {350., 181.6497, 0.}, {400., 100., 28.8675}};
    std::vector<sf::Vector3f> t2 = {{400., 100., 28.8675}, {350., 181.6497, 0.}, {350., 100., -57.7350}};
    std::vector<sf::Vector3f> t3 = {{350., 100., -57.7350}, {350., 181.6497, 0.}, {300., 100., 28.8675}};
*/
    std::vector<Cell> cellTri;
    Cell c6(t.at(0), sf::Color(0, 255, 0, 255)); cellTri.push_back(c6);
    Cell c7(t.at(1), sf::Color(255, 0, 0, 255)); cellTri.push_back(c7);
    Cell c8(t.at(2), sf::Color(0, 0, 255, 255)); cellTri.push_back(c8);
    Cell c9(t.at(3), sf::Color(0, 255, 255, 255)); cellTri.push_back(c9);

    pp.clear();
    cc.clear();
    readData(pp, cc, "penta.vtk");

    ITER(pp, i) { pp.at(i).x += 550.; pp.at(i).y += 100.; }

    std::vector<std::vector<sf::Vector3f>> m{15};
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 4; j++)
            if (cc.at(i).n[j] != -1) m.at(i).push_back({pp.at(cc.at(i).n[j]).x, pp.at(cc.at(i).n[j]).y, pp.at(cc.at(i).n[j]).z});

    std::vector<Cell> cellPenta;
    Cell c10(m.at(0), sf::Color(0, 255, 255, 255)); cellPenta.push_back(c10);
    Cell c11(m.at(1), sf::Color(255, 255, 0, 255)); cellPenta.push_back(c11);
    Cell c12(m.at(2), sf::Color(255, 0, 255, 255)); cellPenta.push_back(c12);
    Cell c13(m.at(3), sf::Color(0, 255, 255, 255)); cellPenta.push_back(c13);
    Cell c14(m.at(4), sf::Color(255, 255, 0, 255)); cellPenta.push_back(c14);
    Cell c15(m.at(5), sf::Color(255, 0, 255, 255)); cellPenta.push_back(c15);
    Cell c16(m.at(6), sf::Color(0, 255, 255, 255)); cellPenta.push_back(c16);
    Cell c17(m.at(7), sf::Color(255, 255, 0, 255)); cellPenta.push_back(c17);
    Cell c18(m.at(8), sf::Color(255, 0, 255, 255)); cellPenta.push_back(c18);
    Cell c19(m.at(9), sf::Color(0, 255, 255, 255)); cellPenta.push_back(c19);
    Cell c110(m.at(10), sf::Color(255, 255, 0, 255)); cellPenta.push_back(c110);
    Cell c111(m.at(11), sf::Color(255, 0, 255, 255)); cellPenta.push_back(c111);
    Cell c112(m.at(12), sf::Color(255, 0, 0, 255)); cellPenta.push_back(c112);
    Cell c113(m.at(13), sf::Color(0, 0, 255, 255)); cellPenta.push_back(c113);
    Cell c114(m.at(14), sf::Color(0, 255, 0, 255)); cellPenta.push_back(c114);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    sf::RenderWindow window(sf::VideoMode(imageWidth, imageHeight), "Rodrigues", sf::Style::Default, settings);

    window.setVerticalSyncEnabled(true);
    window.setActive(true); // activate the window

    const sf::Vector3f Wquad = {1., 1., -1.}; // rotation vector components
    const sf::Vector3f Oquad = {100., 100., 0.}; // rotation vector origin
    const sf::Vector3f Wtri = {-1., -1., 1.}; // rotation vector components
    const sf::Vector3f Otri = {350., 100., 0.}; // rotation vector origin
    const sf::Vector3f Wpenta = {0., -1., 1.}; // rotation vector components
    const sf::Vector3f Openta = {550., 100., 0.}; // rotation vector origin

//    https://en.sfml-dev.org/forums/index.php?topic=15360.0

    bool running = true;
    while (running) {

        sf::Event event;
        while (window.pollEvent(event)) {
                 if (event.type == sf::Event::Closed) running = false;
            else if (event.type == sf::Event::Resized) window.setSize({static_cast<unsigned int>(event.size.width), static_cast<unsigned int>(event.size.height)});
            else if (event.type == sf::Event::KeyPressed) { if (event.key.code == sf::Keyboard::Escape) running = false; }
            else {}
        }//while

        // clear the buffers
        window.clear(sf::Color::White);

        ITER(cellQua, i) cellQua.at(i).Rotate(Oquad, Wquad, 1.);
        ITER(cellTri, i) cellTri.at(i).Rotate(Otri, Wtri, 2.);
        ITER(cellPenta, i) cellPenta.at(i).Rotate(Openta, Wpenta, -1.);

        ITER(cellQua, i)
            if (cellQua.at(i).getN().z > 0.02)
                window.draw(cellQua.at(i).getCell());
        ITER(cellTri, i)
            if (cellTri.at(i).getN().z > 0.02)
                window.draw(cellTri.at(i).getCell());
        ITER(cellPenta, i)
            if (cellPenta.at(i).getN().z > 0.02)
                window.draw(cellPenta.at(i).getCell());

        window.display();
    }//while

    window.close();

    pp.clear();
    cc.clear();

    cellPenta.clear();
    cellTri.clear();
    cellQua.clear();

    ITER(m, i) m.at(i).clear();
    m.clear();

    ITER(q, i) q.at(i).clear();
    q.clear();

    ITER(t, i) t.at(i).clear();
    t.clear();

    return 0;
}//main
