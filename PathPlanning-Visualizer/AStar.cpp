#include "AStar.h"

void aStar::setup(int m, int D, vector<vector<int>> base, Point s, Point g, int H, int V, int p) {
    duration = 0.0;
//  setting up a clock to calculate the time
    stepTime = clock();
    saveG.clear();
    leaf.clear();
    parent.clear();
    actualRoute.clear();
    diagonal = D;
    mode = m;
    baseMap = base;
    agent = s;
    goal = g;
    exploring = agent;
    H_ratio = H;
    V_ratio = V;
    temp = 9999999.9;
    saveG.insert({(make_pair(agent.x, agent.y)), 0.0});
    stepTime = clock() - stepTime;
    duration += stepTime;
}

void aStar::changeG(int x, int y, double distance) {
//  this method changes the parent of a leaf if the G value is better nad therefor the value of it's G changes
    if(saveG.find(make_pair(x,y))->second > saveG.find(make_pair(exploring.x,exploring.y))->second + distance) {
        parent.erase(make_pair(x,y));
        parent.insert({make_pair(x,y),make_pair(exploring.x,exploring.y)});
        saveG.erase(make_pair(x,y));
        saveG.insert({make_pair(x, y),(saveG.find(make_pair(parent.find(make_pair(x, y))->second.first, parent.find(make_pair(x, y))->second.second))->second) + distance});
        leaf.erase(make_pair(x, y));
        calculate(x,y);
    }
}

void aStar::giveValues(int x, int y,double distance, bool Goal) {
//  saving the parent of point(x,y)
    parent.insert({make_pair(x,y), make_pair(exploring.x,exploring.y)});
//  saving the G of point(x,y) based on the G of the parent
    saveG.insert({make_pair(x, y), (saveG.find(make_pair(parent.find(make_pair(x, y))->second.first, parent.find(make_pair(x, y))->second.second))->second) + distance});
//  if we haven't reached the goal yet
    if(Goal == false) {
//      change the base map to 4 (= leaf block)
        baseMap[x][y] = 4;
//      and then calculate the H and G for point(x,y)
        calculate(x, y);
    } else {
//      if the goal has been reached the ID of it changes to 6 (= goal found)
        baseMap[x][y] = 6;
    }
}

vector<vector<int>> aStar::createLeaf() {
//  clock start
    stepTime = clock();
//  before creating the leafs, the ID of block should change to 5 (= explored)
    if (exploring != agent && exploring != goal) {
        baseMap[exploring.x][exploring.y] = 5;
    }
//  the conditions for each and every direction possible
    if (((exploring.x + 1) < V_ratio)) {
        switch (baseMap[exploring.x + 1][exploring.y]) {
        case (0):
//          if the block ID is 0 and it's not black
            giveValues(exploring.x + 1, exploring.y, 1.0, false);
            break;
        case (4):
//          if the ID is 4 (= leaf) check if the parent should be changed
            changeG(exploring.x + 1, exploring.y, 1.0);
            break;
        case (3):
//          if the ID is 3 (= goal)
            giveValues(exploring.x + 1, exploring.y, 1.0, true);
            break;
        }
    }

    if (((exploring.x - 1) >= 0)) {
        switch (baseMap[exploring.x - 1][exploring.y]) {
        case (0):
            giveValues(exploring.x - 1, exploring.y, 1.0, false);
            break;
        case (4):
            changeG(exploring.x - 1, exploring.y, 1.0);
            break;
        case (3):
            giveValues(exploring.x - 1, exploring.y, 1.0, true);
            break;
        }
    }

    if (((exploring.y + 1) < V_ratio)) {
        switch (baseMap[exploring.x][exploring.y + 1]) {
        case (0):
            giveValues(exploring.x, exploring.y + 1, 1.0, false);
            break;
        case (4):
            changeG(exploring.x, exploring.y + 1, 1.0);
            break;
        case (3):
            giveValues(exploring.x, exploring.y + 1, 1.0, true);
            break;
        }
    }

    if (((exploring.y - 1) >= 0)) {
        switch (baseMap[exploring.x][exploring.y - 1]) {
        case (0):
            giveValues(exploring.x, exploring.y - 1, 1.0, false);
            break;
        case (4):
            changeG(exploring.x, exploring.y - 1, 1.0);
            break;
        case (3):
            giveValues(exploring.x, exploring.y - 1, 1.0, true);
            break;
        }
    }
    if (((exploring.x + 1) < V_ratio) && ((exploring.y + 1) < V_ratio) && (diagonal == 1) && !(baseMap[exploring.x + 1][exploring.y] == 1 && baseMap[exploring.x][exploring.y + 1] == 1))
    {
        switch (baseMap[exploring.x + 1][exploring.y + 1]) {
        case (0):
            giveValues(exploring.x + 1, exploring.y + 1, sqrt(2), false);
            break;
        case (4):
            changeG(exploring.x + 1, exploring.y + 1, sqrt(2));
            break;
        case (3):
            giveValues(exploring.x + 1, exploring.y + 1, sqrt(2), true);
            break;
        }
    }

    if (((exploring.x - 1) >= 0) && ((exploring.y + 1) < V_ratio) && (diagonal == 1) && !(baseMap[exploring.x - 1][exploring.y] == 1 && baseMap[exploring.x][exploring.y + 1] == 1))
    {
        switch (baseMap[exploring.x - 1][exploring.y + 1]) {
        case (0):
            giveValues(exploring.x - 1, exploring.y + 1, sqrt(2), false);
            break;
        case (4):
            changeG(exploring.x - 1, exploring.y + 1, sqrt(2));
            break;
        case (3):
            giveValues(exploring.x - 1, exploring.y + 1, sqrt(2), true);
            break;
        }
    }

    if (((exploring.x + 1) < V_ratio) && ((exploring.y - 1) >= 0) && (diagonal == 1) && !(baseMap[exploring.x + 1][exploring.y] == 1 && baseMap[exploring.x][exploring.y - 1] == 1))
    {
        switch (baseMap[exploring.x + 1][exploring.y - 1]) {
        case (0):
            giveValues(exploring.x + 1, exploring.y - 1, sqrt(2), false);
            break;
        case (4):
            changeG(exploring.x + 1, exploring.y - 1, sqrt(2));
            break;
        case (3):
            giveValues(exploring.x + 1, exploring.y - 1, sqrt(2), true);
            break;
        }
    }

    if (((exploring.x - 1) >= 0) && ((exploring.y - 1) >= 0) && (diagonal == 1) && !(baseMap[exploring.x - 1][exploring.y] == 1 && baseMap[exploring.x][exploring.y - 1] == 1))
    {
        switch (baseMap[exploring.x - 1][exploring.y - 1]) {
        case (0):
            giveValues(exploring.x - 1, exploring.y - 1, sqrt(2), false);
            break;
        case (4):
            changeG(exploring.x - 1, exploring.y - 1, sqrt(2));
            break;
        case (3):
            giveValues(exploring.x - 1, exploring.y - 1, sqrt(2), true);
            break;
        }
    }
//  if there is no other leaf to explore
    if (leaf.empty()) {
//      change the goal ID to -1
        baseMap[goal.x][goal.y] = -1;
    }
    exploreNode();
//  calculating the time it has taken
    stepTime = clock() - stepTime;
    duration += stepTime;
    return baseMap;
}

void aStar::calculate(int x, int y) {
//  calculate the distance in x and y axis
    Dx = abs(double(x - goal.x));
    Dy = abs(double(y - goal.y));
//  A* has both G and H
    if(mode == 1) {
        G = saveG.find(make_pair(x, y))->second;
//      if diagonal mode is disabled heuristic is manhattan distance
        if(diagonal == -1) {
            H = (Dx + Dy);
        }
//      if diagonal mode is disabled heuristic is a straight line
        else if(diagonal == 1) {
            H = (Dx + Dy) + (sqrt(2) - 2) * minimum();
            // H = sqrt(pow(Dx,2) + pow(Dy,2));
        }
    }
//  ucs doesn't have heuristic
    else if(mode == 2) {
        G = saveG.find(make_pair(x, y))->second;
        H = 0;
    }
//  Greedy has only H
    else if(mode == 3) {
        G = 0;
        if(diagonal == -1) {
            H = (Dx + Dy);
        }
        else if(diagonal == 1) {
            H = sqrt(pow(Dx, 2) + pow(Dy, 2));
        }    
    }
//  attaching the H + G value to the point
    leaf.insert({make_pair(x, y), (H + G)});
}

void aStar::exploreNode() {
//  going through all of the leafs and picking which one has the lowest value
    for (auto itr = leaf.begin(); itr != leaf.end(); itr++) {
        if (itr->second < temp) {
            temp = itr->second;
            exploring.x = itr->first.first;
            exploring.y = itr->first.second;
        }
    }
//  erasing the explored leaf from the leaf map
    leaf.erase(make_pair(exploring.x,exploring.y));
    temp = 9999999.9;
}

vector<Point> aStar::accessRoute() {
//  saving the route in a vector and passing it to the visuals
    Point current = goal;
    actualRoute.push_back(current);
    while(saveG.find(make_pair(current.x,current.y))->second != 0.0) {
        current = Point(parent.find(make_pair(current.x, current.y)) -> second.first, parent.find(make_pair(current.x, current.y)) -> second.second);
        actualRoute.push_back(current);
    }
    return actualRoute;
}

double aStar::accessG() {
    return saveG.find(make_pair(goal.x,goal.y))->second;
}

float aStar::accessTime() {
    return (float)duration / CLOCKS_PER_SEC * 1000;
}

double aStar::minimum() {
    if(Dx < Dy) return Dx;
    else if(Dy <= Dx) return Dy;
}