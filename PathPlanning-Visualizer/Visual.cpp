#include "Visual.h"

visuals::visuals() {
    setup();
    makeBlocks();
    imshow("Path Planning Visualizer", visual);
    setMouseCallback("Path Planning Visualizer", mouseAttacher, this);
    printOptions();
}

void visuals::setup() {
    baseMap.resize(V_ratio, vector<int>(H_ratio, 0));
    visual = Mat(V_ratio * size, H_ratio * size, CV_8UC3, white);
    init = false;
    grabPoints = false;
    lastKnown = 0;
    agent = Point((V_ratio - 1) / 2, H_ratio / 4);
    goal = Point((V_ratio - 1) / 2, H_ratio * 3 / 4);
    baseMap[agent.x][agent.y] = 2;
    baseMap[goal.x][goal.y] = 3;
    allowDiagonal = -1;
}

void visuals::makeBlocks() {
    for(int i = 0; i < V_ratio; i++) {
        for(int j = 0; j < H_ratio; j++) {
            Point p1(j * size, i * size);
            Point p2((j + 1) * size, (i + 1) * size);

            if(baseMap[i][j] == 0) {
                rectangle(visual, p1, p2, white, FILLED);
                rectangle(visual, p1, p2, gridLine, borderThickness, LINE_8);
            }
            else if(baseMap[i][j] == 1) {
                rectangle(visual, p1, p2, black, FILLED); 
            }
            else if(baseMap[i][j] == 2) {
                rectangle(visual, p1, p2, agentCol, FILLED);
                rectangle(visual, p1, p2, gridLine, borderThickness, LINE_8);
            }
            else if(baseMap[i][j] == 3) {
                rectangle(visual, p1, p2, goalCol, FILLED);
                rectangle(visual, p1, p2, gridLine, borderThickness, LINE_8);
            }
            else if (baseMap[i][j] == 4)
            {
                rectangle(visual, p1, p2, leaf, FILLED);
                rectangle(visual, p1, p2, gridLine, borderThickness, LINE_8);
            }
            else if (baseMap[i][j] == 5)
            {
                rectangle(visual, p1, p2, explored, FILLED);
                rectangle(visual, p1, p2, gridLine, borderThickness, LINE_8);
            }
        }
    }
}

void visuals::mouseAttacher(int event, int x, int y, int flags, void *data) {
    visuals * pointer = reinterpret_cast<visuals* >(data);
    pointer -> Mouse(event, x, y, flags);
}

void visuals::Mouse(int event, int x, int y, int flags) {
    save = Point(x,y);
    if(event == EVENT_LBUTTONDOWN) {
        yBlock = x / size;
        xBlock = y / size;
        init = true;
        grabType = baseMap[xBlock][yBlock];
        if(grabType > 1) {
            grabPoints = true;
        }
        changeColor(xBlock,yBlock);
    }

    if (event == EVENT_LBUTTONUP) {
        grabPoints = false;
        init = false;
    }
        changeBlock();
        if (init && event == EVENT_MOUSEMOVE)
        {
            if (changeX >= 1 || changeY >= 1)
            {
                yBlock = x / size;
                xBlock = y / size;
                if (grabType == baseMap[xBlock][yBlock])
                {
                    changeColor(xBlock, yBlock);
                }
                if (grabPoints == true)
                {
                    changeColor(xBlock, yBlock);
                }
            }
        }
    }

void visuals::changeColor(int X, int Y) {
    if (baseMap[X][Y] == 0 && grabPoints == false) {
        Point p1(Y * size, X * size); 
        Point p2((Y + 1) * size, (X + 1) * size); 
        rectangle(visual, p1, p2, black, FILLED);
        baseMap[X][Y] = 1; 
    }

    else if (baseMap[X][Y] == 1 && grabPoints == false) {
        Point p1(Y * size, X * size); 
        Point p2((Y + 1) * size, (X + 1) * size); 
        rectangle(visual, p1, p2, white, FILLED);
        rectangle(visual, p1, p2, gridLine, borderThickness, LINE_8);
        baseMap[X][Y] = 0; 
    }

    else if (baseMap[X][Y] != 3 && grabType == 2 && grabPoints == true) {
        baseMap[agent.x][agent.y] = lastKnown;
        Point p1(agent.y * size, agent.x * size); 
        Point p2((agent.y + 1) * size, (agent.x + 1) * size); 
        if(lastKnown == 0) {
            rectangle(visual, p1, p2, white, FILLED);
            rectangle(visual, p1, p2, gridLine, borderThickness, LINE_8);
        }
        else if(lastKnown == 1) {
            rectangle(visual, p1, p2, gridLine, FILLED);
        }
        Point pp1(Y * size, X * size);
        Point pp2((Y + 1) * size, (X + 1) * size);
        rectangle(visual, pp1, pp2, agentCol, FILLED);
        rectangle(visual, pp1, pp2, gridLine, borderThickness, LINE_8);
        lastKnown = baseMap[X][Y];
        baseMap[X][Y] = 2;
        agent = Point(X,Y);
    }

    else if (baseMap[X][Y] != 2 && grabType == 3 && grabPoints == true) {
        baseMap[goal.x][goal.y] = lastKnown;
        Point p1(goal.y * size, goal.x * size); 
        Point p2((goal.y + 1) * size, (goal.x + 1) * size); 
        if(lastKnown == 0) {
            rectangle(visual, p1, p2, white, FILLED);
            rectangle(visual, p1, p2, gridLine, borderThickness, LINE_8);
        }
        else if(lastKnown == 1) {
            rectangle(visual, p1, p2, gridLine, FILLED);
        }
        Point pp1(Y * size, X * size); 
        Point pp2((Y + 1) * size, (X + 1) * size); 
        rectangle(visual, pp1, pp2, goalCol, FILLED);
        rectangle(visual, pp1, pp2, gridLine, borderThickness, LINE_8);
        lastKnown = baseMap[X][Y];
        baseMap[X][Y] = 3; 
        goal = Point(X,Y);
    }
    imshow("Path Planning Visualizer", visual);
    // printMap();
}

void visuals::changeBlock() {
    int currentMousePos = baseMap[floor((save.y / size))][floor((save.x / size))];
    changeY = abs(floor((save.x / size)) - (xBlock));
    changeX = abs(floor((save.y / size)) - (yBlock));
    if(currentMousePos != grabType && grabType < 2) {
        changeX = 0;
        changeY = 0;
    }
    if(currentMousePos == grabType && grabType > 1) {
        changeX = 0;
        changeY = 0;
    }
}

void visuals::printMap() {
    system("clear");
    for(int i = 0; i < V_ratio; i++) {
        for(int j = 0; j < H_ratio; j++) {
            if (baseMap[i][j] == 1) {
                cout << "\033[1;93m" << baseMap[i][j] << " ";
            } else if (baseMap[i][j] == 0) {
                cout << "\033[1;30m" << baseMap[i][j] << " ";
            } else if (baseMap[i][j] == 3 || baseMap[i][j] == 2) {
                cout << "\033[1;96m" << baseMap[i][j] << " ";
            }
        }
        cout << "" << endl;
    }
    cout << "\033[0m" << endl;

}

void visuals::printOptions() {
    system("clear");
    imshow("Path Planning Visualizer", visual);
    if(allowDiagonal == -1) {
    cout << "Diagonal mode: Off\n" << endl;
    } 
    else if(allowDiagonal == 1) {
        cout << "Diagonal mode:  On\n" << endl;
    }
    cout << "A*    Search :   1" << endl;
    cout << "UCS          :   2" << endl;
    cout << "Greedy Search:   3" << endl;
    cout << "                  " << endl;
    cout << "Remove walls :   W" << endl;
    cout << "Allow   Diag :   D" << endl;
    cout << "Exit the app :   Q" << endl;
    switch (waitKey(0)) {
    case (int('1')):
        aStarSetup(1);
        break;
    case (int('2')):
        aStarSetup(2);
        break;
    case (int('3')):
        aStarSetup(3);
        break;
    case (int('w')):
        for (int i = 0; i < V_ratio; i++) {
            for (int j = 0; j < H_ratio; j++) {
                if (baseMap[i][j] == 1) {
                    baseMap[i][j] = 0;
                }
            }
        }
        makeBlocks();
        printOptions();
        break;
    case (int('d')):
        allowDiagonal *= -1;
        printOptions();
        break;
    case (int('q')):
        system("clear");
        exit(0);
        break;
    default:
        printOptions();
        break;
    }
}

void visuals::aStarSetup(int mode) {
    float duration = 0.0;
    cout << "\nSelected Mode: " << mode << endl;
    A.setup(mode, allowDiagonal, baseMap, agent, goal, H_ratio, V_ratio, size);
    while(true) {
        baseMap = A.createLeaf();
        makeBlocks();
        imshow("Path Planning Visualizer", visual);
        waitKey(1);

        if (baseMap[goal.x][goal.y] == 6) {
            wayPoints = A.accessRoute();
            drawWayPoints();
            cout << "Total  Length: " << A.accessG() << endl;
            break;
        }
        else if(baseMap[goal.x][goal.y] == -1) {
            cout << "Unable to find the goal!" << endl;
            break;
        }
        // waitKey(0);
    }
    for (int i = 0; i < V_ratio; i++) {
        for (int j = 0; j < H_ratio; j++) {
            if (baseMap[i][j] >= 4) {
                baseMap[i][j] = 0;
            }
        }
    }
    cout << "Total    Time: " << A.accessTime() << " ms" << endl;
    waitKey(0);
    baseMap[agent.x][agent.y] = 2;
    baseMap[goal.x][goal.y] = 3;
    makeBlocks();
    printOptions();

}

void visuals::drawWayPoints() {
    for(int i = 0; i < wayPoints.size() - 1; i++) {
        Point p1((wayPoints[i].y + 0.5) * size, (wayPoints[i].x + 0.5) * size);
        Point p2((wayPoints[i + 1].y + 0.5) * size, (wayPoints[i + 1].x + 0.5) * size);
        line(visual, p1, p2, route, 2);
        waitKey(20);
        imshow("Path Planning Visualizer", visual);
    }
    Point p1((wayPoints[wayPoints.size() - 1].y + 0.5) * size, (wayPoints[wayPoints.size() - 1].x + 0.5) * size);
    Point p2((agent.y + 0.5) * size, (agent.x + 0.5) * size);
    line(visual, p1, p2, route, 2);
    imshow("Path Planning Visualizer", visual);
}