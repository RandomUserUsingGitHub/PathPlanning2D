#pragma once
#include "AStar.h"

class visuals {
    const int size = 30;
    vector<Point> wayPoints;
    const int H_ratio = 30;
    const int V_ratio = 30;
    const int borderThickness = 1;

    int xBlock;
    int yBlock;
    int changeY;
    int changeX;
    int lastKnown;
    Point test;
    bool init;
    bool grabPoints;
    int grabType;
    int allowDiagonal;
    string helpWindowText;

    Point save;
    Point agent;
    Point goal;

    Scalar black    = Scalar(50,50,50);
    Scalar white    = Scalar(210,210,210);
    Scalar agentCol = Scalar(0,150,0);
    Scalar goalCol  = Scalar(0,0,200);
    Scalar explored = Scalar(190, 190, 190);
    Scalar leaf     = Scalar(150,220,150);
    Scalar route    = Scalar(150, 100, 80);
    Scalar gridLine = Scalar(150,150,150);


    vector<vector<int>> baseMap;
    Mat visual;
    Mat helpWindow;
    aStar A;

public :

    visuals();
    void setup();
    void changeColor(int, int);
    void makeBlocks();
    static void mouseAttacher(int ,int ,int ,int ,void *);
    void Mouse(int ,int ,int ,int);
    void changeBlock();
    void printMap();
    void printOptions();
    Point accessAgent();
    void aStarSetup(int);
    void drawWayPoints();
};