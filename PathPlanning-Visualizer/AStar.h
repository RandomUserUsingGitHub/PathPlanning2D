#pragma once
#include "Config.h"

class aStar {
    vector<vector<int>> baseMap;
    map<pair<int, int>, double> saveG;
    map<pair<int, int>, double> leaf;
    map<pair<int, int>, pair<int, int>> parent;
    vector<Point> actualRoute;
    Point agent;
    Point goal;
    Point exploring;
    double Dx;
    double Dy;
    double min;
    double max;
    int H_ratio;
    int V_ratio;
    int pixel;
    double H;
    double G;
    double temp;
    int mode;
    int diagonal;
    clock_t stepTime;
    float duration;

public : 
    
    void test();
    void setup(int, int, vector<vector<int>>, Point, Point, int, int, int);
    void calculate(int, int);
    vector<vector<int>> createLeaf();
    void exploreNode();
    vector<Point> accessRoute();
    void giveValues(int, int,double, bool);
    void changeG(int, int, double);
    double accessG();
    float accessTime();
    double minimum();
};

