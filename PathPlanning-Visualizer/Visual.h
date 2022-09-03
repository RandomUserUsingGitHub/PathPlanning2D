#pragma once
#include "AStar.h"

class visuals {
/*
--- size settings
*/
    const int size = 30; //------------ size of each block in pixels
    const int H_ratio = 30; //--------- amount of blocks horizontally
    const int V_ratio = 30; //--------- amount of blocks vertically
    const int borderThickness = 1; //-- thickness of border of each block
    const int routeThickness = 3; //--- thickness of the final route
    const int speed = 1; //------------ length of each frame in milliseconds
/*
--- integer variables
*/
    int xBlock; //------------- refers to the x axis of the block that we are editing (on the base map)
    int yBlock; //------------- refers to the y axis of the block that we are editing (on the base map)
    int changeX; //------------ a value that showcases the amount of blocks we moved on x axis
    int changeY; //------------ a value that showcases the amount of blocks we moved on y axis
    int grabType; //----------- a value that show cases which block type we are grabbing with mouse
    int lastKnown; //---------- a value to save the last known block type to recreate after the block changes
    int allowDiagonal; //------ a flag that showcases if the program is allowed to move diagonally
/*
--- boolean variables
*/
    bool drag; //--------- a flag that changes to true every time the right button of mouse stays pushed
    bool grabPoints; //--- a flag that showcases that the user is dragging agent/goal
/*
--- cv::Point variables
*/
    Point save; //----- saving the clicked block position (to calculate changeX ans changeY)
    Point goal; //----- goal position on base map (not in pixels)
    Point agent; //---- agent position on base map (not in pixels)
/*
--- cv::Scalar variables (color)
*/
    Scalar black    = Scalar(50,50,50);
    Scalar white    = Scalar(210,210,210);
    Scalar agentCol = Scalar(0,150,0);
    Scalar goalCol  = Scalar(0,0,200);
    Scalar explored = Scalar(190, 190, 190);
    Scalar leaf     = Scalar(150,220,150);
    Scalar route    = Scalar(150, 100, 80);
    Scalar gridLine = Scalar(150,150,150);
/*
--- vectors
*/
    vector<Point> wayPoints; //------- the points of the route that the program has found
    vector<vector<int>> baseMap; //--- the core of the code
/*
--- cv::Mat 
*/
    Mat visual; //---- the output

    aStar A;

public :

    visuals();
    void setup();
    void printMap();
    void resetWalls();
    void makeBlocks();
    void changeBlock();
    void printOptions();
    void aStarSetup(int);
    void drawWayPoints();
    void changeColor(int, int);
    void Mouse(int ,int ,int ,int);
    static void mouseAttacher(int ,int ,int ,int ,void *);
};