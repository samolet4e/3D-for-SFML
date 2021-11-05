#include "cell.h"

int main() {
int i, j;

    std::vector<points> pp{0};
    std::vector<cells> cc{0};

// Load diamond

    int errCode = readBlock("diamond.vtk", "POINTS", "CELLS", pp, cc);
    if (errCode != 0) return -1;

    for (i = 0; i < (int)pp.size(); i++) {
        pp.at(i).x += 550.;
        pp.at(i).y += 250.;
    }//for_i

    // http://www.cplusplus.com/forum/general/7950/
    std::vector<myCell> cellDia;//(0, myCell(pt));
    for (i = 0; i < (int)cc.size(); i++) {
        std::vector<points> pt{0};
        for (j = 0; j < 4; j++) pt.push_back(pp.at(cc.at(i).n[j]));
        int thick = -1;
        if ((i > 11 && i < 20) || (i > 19 && i < 28)) thick = 0;
        myCell ct(pt, thick, sf::Color(sf::Color::Green));
        pt.clear();
        cellDia.push_back(ct);
//        ct.~myCell();
    }//for_i

    pp.clear();
    cc.clear();

// End loading diamond
// Load quad

    errCode = readBlock("quad.vtk", "POINTS", "CELLS", pp, cc);
    if (errCode != 0) return -1;

    std::vector<myCell> cellQua;//(0, myCell(pt));
    for (i = 0; i < (int)cc.size(); i++) {
        std::vector<points> pt{0};
        for (j = 0; j < 4; j++) pt.push_back(pp.at(cc.at(i).n[j]));
        int thick = -1;
        myCell ct(pt, thick, sf::Color(sf::Color::Red));
        pt.clear();
        cellQua.push_back(ct);
    }//for_i

    pp.clear();
    cc.clear();

// End loading quad
// Load pyramid

    errCode = readBlock("pyramid.vtk", "POINTS", "CELLS", pp, cc);
    if (errCode != 0) return -1;

    for (i = 0; i < (int)pp.size(); i++) {
        pp.at(i).x += 1050.;
        pp.at(i).y += 550.;
    }//for_i

    // http://www.cplusplus.com/forum/general/7950/
    std::vector<myCell> cellPyr;//(0, myCell(pt));
    for (i = 0; i < (int)cc.size(); i++) {
        std::vector<points> pt{0};
        for (j = 0; j < 4; j++) pt.push_back(pp.at(cc.at(i).n[j]));
        int thick = -1;
        if ((i > 11 && i < 20) || (i > 19 && i < 28)) thick = 0;
        myCell ct(pt, thick, sf::Color(sf::Color::Blue));
        pt.clear();
        cellPyr.push_back(ct);
    }//for_i

    pp.clear();
    cc.clear();

// End loading pyramid

    const sf::Vector3f Wqua = {1., 1., 1.}; // rotation vector components
    const sf::Vector3f Oqua = {100., 100., 0.}; // rotation vector origin

    const sf::Vector3f Wdia = {1., 1., 0.};
    const sf::Vector3f Odia = {1280./2., 340., 0.};

    const sf::Vector3f Wpyr = {0., 1., 1.};
    const sf::Vector3f Opyr = {1100., 400., 0.};

    int imageWidth = 1280, imageHeight = 720;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    sf::RenderWindow window(sf::VideoMode(imageWidth, imageHeight), "Rodrigues", sf::Style::Default, settings);
/*
    sf::Texture t;
    t.loadFromFile("Sofia.jpg");
    sf::Sprite s(t);
*/
    window.setVerticalSyncEnabled(true);
    window.setActive(true); // activate the window

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

//        window.draw(s);

        for (i = 0; i < (int)cellDia.size(); i++) {
            cellDia.at(i).Rotate(Odia, Wdia, 1.);
            if (cellDia.at(i).getN().z > 0.) window.draw(cellDia.at(i).getShape());
//            window.draw(cellDia.at(i).getShape());
        }//for_i

        for (i = 0; i < (int)cellQua.size(); i++) {
            cellQua.at(i).Rotate(Oqua, Wqua, 1.);
            if (cellQua.at(i).getN().z > 0.) window.draw(cellQua.at(i).getShape());
        }//for_i

        for (i = 0; i < (int)cellPyr.size(); i++) {
            cellPyr.at(i).Rotate(Opyr, Wpyr, 1.);
            if (cellPyr.at(i).getN().z > 0.) window.draw(cellPyr.at(i).getShape());
        }//for_i

        window.display();

    }//while

    window.close();

    cellPyr.clear();
    cellQua.clear();
    cellDia.clear();

    return 0;
}//main
