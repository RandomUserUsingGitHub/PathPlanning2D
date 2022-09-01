#include "AStar.h"

void aStar::setup(int m, int D, vector<vector<int>> base, Point s, Point g, int H, int V, int p) {
    duration = 0.0;
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
    pixel = p;
    temp = 9999999.9;
    saveG.insert({(make_pair(agent.x, agent.y)), 0.0});
    stepTime = clock() - stepTime;
    duration += stepTime;
}
void aStar::changeG(int x, int y, double distance) {
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
    parent.insert({make_pair(x,y), make_pair(exploring.x,exploring.y)});
    saveG.insert({make_pair(x, y), (saveG.find(make_pair(parent.find(make_pair(x, y))->second.first, parent.find(make_pair(x, y))->second.second))->second) + distance});
    if(Goal == false) {
        baseMap[x][y] = 4;
        calculate(x, y);
    } else {
        baseMap[x][y] = 6;
    }
}

vector<vector<int>> aStar::createLeaf()
{
    stepTime = clock();
    if (((exploring.x + 1) < V_ratio)) {
        switch (baseMap[exploring.x + 1][exploring.y]) {
        case (0):
            giveValues(exploring.x + 1, exploring.y, 1.0, false);
            break;
        case (4):
            changeG(exploring.x + 1, exploring.y, 1.0);
            break;
        case (3):
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

    if (exploring != agent && exploring != goal) {
        baseMap[exploring.x][exploring.y] = 5;
    }
    if (leaf.empty()) {
        baseMap[goal.x][goal.y] = -1;
    }
    exploreNode();
    stepTime = clock() - stepTime;
    duration += stepTime;
    return baseMap;
}

void aStar::calculate(int x, int y)
{
    Dx = abs(double(x - goal.x));
    Dy = abs(double(y - goal.y));
    if(mode == 1) {
        G = saveG.find(make_pair(x, y))->second;
        if(diagonal == -1) {
            H = (Dx + Dy);
        }
        else if(diagonal == 1) {
            H = (Dx + Dy) + (sqrt(2) - 2) * minimum();
            // H = sqrt(pow(Dx,2) + pow(Dy,2));
        }
    }
    else if(mode == 2) {
        G = saveG.find(make_pair(x, y))->second;
        H = 0;

    }
    else if(mode == 3) {
        G = 0;
        if(diagonal == -1) {
            H = (Dx + Dy);
        }
        else if(diagonal == 1) {
            H = sqrt(pow(Dx, 2) + pow(Dy, 2));
        }    
    }

    leaf.insert({make_pair(x, y), (H + G)});
}
void aStar::exploreNode()
{
    for (auto itr = leaf.begin(); itr != leaf.end(); itr++)
    {
        if (itr->second < temp)
        {
            temp = itr->second;
            exploring.x = itr->first.first;
            exploring.y = itr->first.second;
        }
    }
    leaf.erase(make_pair(exploring.x,exploring.y));
    temp = 9999999.9;
}

vector<Point> aStar::accessRoute() {
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