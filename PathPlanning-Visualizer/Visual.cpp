#include "Visual.h"
/*
-------------------------
Base Map Numbers (IDs): -
--- 0 = white block -----
--- 1 = black block -----
--- 2 = agent block -----
--- 3 = goal block ------
--- 4 = leaf block ------
--- 5 = explored block --
--- 6 = goal found ------
-- -1 = goal not found --
-------------------------
*/
visuals::visuals() {
//  some setups to do before starting the program
    setup();
//  creating the blocks based on the base map
    makeBlocks();
//  showing the result to the user
    imshow("Path Planning Visualizer", visual);
//  setting up the mouse call back on output
    setMouseCallback("Path Planning Visualizer", mouseAttacher, this);
//  printing the settings and getting the user inputs
    printOptions();
}

void visuals::setup() {
//  resizing the base map based on ratios and giving it 0 values
    baseMap.resize(V_ratio, vector<int>(H_ratio, 0));
//  making the Mat based on the ratios and block size
    visual = Mat(V_ratio * size, H_ratio * size, CV_8UC3, white);
//  some default values
    drag = false;
    grabPoints = false;
    lastKnown = 0;
//  the default position of agent and goal block
    agent = Point((V_ratio - 1) / 2, H_ratio / 4);
    goal = Point((V_ratio - 1) / 2, H_ratio * 3 / 4);
//  the base map id for agent (=2) and goal (=3)
    baseMap[agent.x][agent.y] = 2;
    baseMap[goal.x][goal.y] = 3;
//  diagonal mode is off (=-1) by default
    allowDiagonal = -1;
}

void visuals::makeBlocks() {
//  going through all of the base map and
//  drawing blocks on the output based on the base map IDs
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
//  left button down
    if(event == EVENT_LBUTTONDOWN) {
//      calculate the x and y axis of the block we are on
        yBlock = x / size;
        xBlock = y / size;
//      drag flags turns true
        drag = true;
//      grab type = the ID of the base map
        grabType = baseMap[xBlock][yBlock];
//      grab agent, goal flag turns true
        if(grabType == 2 || grabType == 3) grabPoints = true;
//      change the color of the clocked block
        changeColor(xBlock,yBlock);
    }
    if (event == EVENT_LBUTTONUP) {
//      reset the flags
        grabPoints = false;
        drag = false;
    }
    if (drag && event == EVENT_MOUSEMOVE) {
//      calculate if the block has been changed
        changeBlock();
        if (changeX >= 1 || changeY >= 1) {
            yBlock = x / size;
            xBlock = y / size;
//          if the block has been changed, change the color of that block
            if (grabType == baseMap[xBlock][yBlock]) {
                changeColor(xBlock, yBlock);
            }
            if (grabPoints == true) {
                changeColor(xBlock, yBlock);
            }
        }
    }
}

void visuals::changeColor(int X, int Y) {
//  changing the color of the block and it's ID on the base map
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
//      last known is to recreate the block that the agent/goal have crossed over
        if(lastKnown == 0) {
            rectangle(visual, p1, p2, white, FILLED);
            rectangle(visual, p1, p2, gridLine, borderThickness, LINE_8);
        }
        else if(lastKnown == 1) {
            rectangle(visual, p1, p2, black, FILLED);
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
//  calculating the exact block that the mouse is on
    int currentMousePos = baseMap[floor((save.y / size))][floor((save.x / size))];
//  calculating the change in blocks
    changeY = abs(floor((save.x / size)) - (xBlock));
    changeX = abs(floor((save.y / size)) - (yBlock));
//  reseting the change in blocks so the program  doesn't create a block each time the mouse moves
    if(currentMousePos != grabType && (grabType == 1 || grabType == 0)) {
        changeX = 0;
        changeY = 0;
    }
    if(currentMousePos == grabType && (grabType == 2 || grabType == 3)) {
        changeX = 0;
        changeY = 0;
    }
}

void visuals::printMap() {
//  this method prints out the base map and it's pretty useful for debugging
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
//  this method prints out all of the options and settings and gets the user input
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

//  a waitKey(0) is to wait for the user to enter a key
    switch (waitKey(0)) {
//  A* mode
    case (int('1')):
        cout << "\nSelected Mode: A*" << endl;
        aStarSetup(1);
        break;
//  UCS mode
    case (int('2')):
        cout << "\nSelected Mode: UCS" << endl;
        aStarSetup(2);
        break;
//  Greedy mode
    case (int('3')):
        cout << "\nSelected Mode: Greedy" << endl;
        aStarSetup(3);
        break;
//  reset walls
    case (int('w')):
        resetWalls();
        printOptions();
        break;
//  diagonal mode, on or off
    case (int('d')):
        allowDiagonal *= -1;
        printOptions();
        break;
//  exit program
    case (int('q')):
        system("clear");
        exit(0);
        break;
//  don't care (any other key)
    default:
        printOptions();
        break;
    }
}

void visuals::aStarSetup(int mode) {
    A.setup(mode, allowDiagonal, baseMap, agent, goal, H_ratio, V_ratio, size);
    while(true) {
//      updating the base map after leafs gets created in the create leaf method
        baseMap = A.createLeaf();
//      updating the output image (visual) based on the base map
        makeBlocks();
//      showing the result
        imshow("Path Planning Visualizer", visual);
//      a waiting a certain amount of time before moving on
        waitKey(speed);
//      if the goal has been reached
        if (baseMap[goal.x][goal.y] == 6) {
//          saves the route from the goal to the agent
            wayPoints = A.accessRoute();
//          drawing it
            drawWayPoints();
            cout << "Total  Length: " << A.accessG() << endl;
            break;
        }
//      if the goal hasn't been reached
        else if(baseMap[goal.x][goal.y] == -1) {
            cout << "Unable to find the goal!" << endl;
            break;
        }
    }
    cout << "Total    Time: " << A.accessTime() << " ms" << endl;
//  reseting the base map
    for (int i = 0; i < V_ratio; i++) {
        for (int j = 0; j < H_ratio; j++) {
            if (baseMap[i][j] >= 4) {
                baseMap[i][j] = 0;
            }
        }
    }
    baseMap[agent.x][agent.y] = 2;
    baseMap[goal.x][goal.y] = 3;
    waitKey(0);
    makeBlocks();
    printOptions();
}

void visuals::drawWayPoints() {
//  going through all of the way points and drawing a line between them
    for(int i = 0; i < wayPoints.size() - 1; i++) {
        Point p1((wayPoints[i].y + 0.5) * size, (wayPoints[i].x + 0.5) * size);
        Point p2((wayPoints[i + 1].y + 0.5) * size, (wayPoints[i + 1].x + 0.5) * size);
        line(visual, p1, p2, route, routeThickness);
        waitKey(20);
        imshow("Path Planning Visualizer", visual);
    }
    Point p1((wayPoints[wayPoints.size() - 1].y + 0.5) * size, (wayPoints[wayPoints.size() - 1].x + 0.5) * size);
    Point p2((agent.y + 0.5) * size, (agent.x + 0.5) * size);
    line(visual, p1, p2, route, routeThickness);
    imshow("Path Planning Visualizer", visual);
}

void visuals::resetWalls() {
    for (int i = 0; i < V_ratio; i++) {
        for (int j = 0; j < H_ratio; j++) {
            if (baseMap[i][j] == 1) {
                baseMap[i][j] = 0;
            }
        }
    }
    makeBlocks();
}