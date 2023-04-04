#pragma once
#include "Config.h"

class aStar {
    vector<Point> actualRoute; //------ the route that the program finds
    vector<vector<int>> baseMap; //---- the core of the code

    map<pair<int, int>, double> leaf; //--------------- leaf set map
    map<pair<int, int>, double> saveG; //-------------- G save map
    map<pair<int, int>, pair<int, int>> parent; //----- parent set map

    Point goal; //-------- goal node
    Point agent; //------- agent node
    Point exploring; //--- exploring node

    double H; //------- heuristic
    double G; //------- global
    double Dx; //------ distance in x axis
    double Dy; //------ distance in y axis
    double temp; //---- a temporary value

    int mode; //-------------- A* (= 1), UCS (= 2), greedy (=3)
    int H_ratio; //----------- H ratio
    int V_ratio; //----------- V ratio
    int diagonal; //---------- represents if the diagonal mode is enabled or not

    float duration; //-------- the total execution time

    clock_t stepTime; //------ clock_t variable

public : 
    
    void test();
    double accessG();
    double minimum();
    float accessTime();
    void exploreNode();
    void calculate(int, int);
    void changeG(int, int, double);
    void giveValues(int, int,double, bool);
    void setup(int, int, vector<vector<int>>, Point, Point, int, int, int);
    vector<vector<int>> createLeaf();
    vector<Point> accessRoute();
};

