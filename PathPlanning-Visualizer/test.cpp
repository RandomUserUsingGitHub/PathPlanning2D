
// global variables
const int pixel = 100; // the size of each block generated 
vector<vector<bool>> vec;
int H_ratio, V_ratio;
Mat image;

// coordination struct to use in the callback function
struct Coordinates {

  bool init = false; // on off

  // initial coordination based on EVENT_LBUTTONDOWN
  int initX;
  int initY;

  bool grabType; // it's for when you drag a black block, you don't make any blalck blocks white or the other turn around
} SelectedRoi;

// the functions
void CallBackFunc(int event, int x, int y, int flags, void* userdata);
void ChangeColor(Mat image, vector<vector<bool>>& vec, int x, int y);
void MakeBlocks(Mat image, vector<vector<bool>>& vec);
void startEndPoint();

// main
int main() {

    system("clear");

    // getting the ratio of the output. (it's suggested to be a low number otherwise it will crash)
    cout << "Enter the ratio: ";
    cin >> H_ratio >> V_ratio;

    // resizing the vector based on the ratio and giving '0' values to the vector
    vec.resize(H_ratio, vector<bool>(V_ratio, false));

    // making a new mat and copying it to the global one
    Mat img(H_ratio*pixel, V_ratio*pixel, CV_8UC3, Scalar(255, 255, 255));
    image = img;

    MakeBlocks(image, vec); // makes the blocks
    startEndPoint();
    imshow("Output", image); // show the output image
    setMouseCallback("Output", CallBackFunc); // a callback function

    waitKey(0);
    return 0;
}

// this function has the algorithm for the rectangles to be made, and makes them
void MakeBlocks(Mat image, vector<vector<bool>>& vec) {
    int thickness = 2; // thickness of the border of rectangles

    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec[i].size(); j++) {
            Point p1(j*pixel, i*pixel); // upper left corner
            Point p2((j + 1)*pixel, (i + 1)*pixel); // bottom right corner
            rectangle(image, p1, p2, Scalar(0, 0, 0), thickness, LINE_8);
        }
    }
}

// any events happening by the mouse is determined in this function
void CallBackFunc(int event, int x, int y, int flags, void* userdata) {
    int X = x / pixel, Y = y / pixel; // by using these we will know what exact block we are on
    // determines if the left button is down
    if(event == EVENT_LBUTTONDOWN && (X != 0 || Y != 0) && (X != H_ratio - 1 || Y != V_ratio - 1)) {
        SelectedRoi.initX = x; // saving the x value to 'initX'
        SelectedRoi.initY = y; // saving the y value to 'initY'
        SelectedRoi.init = true; // by givin 'init' the value of 'true' we are telling the program that the button is still down
        
        // by doing this we are making the program not to change the blocks that were previously black back to white
        if(vec[X][Y]) {
            SelectedRoi.grabType = false;
        }

        // by doing this we are making the program not to change the blocks that were previously white back to black
        if(!vec[X][Y]) {
            SelectedRoi.grabType = true;
        }
        
        // calls the function that changes the color the blocks
        ChangeColor(image, vec, x, y);
    }

    // determines if the button is not down anymore
    if (event == EVENT_LBUTTONUP) {
        SelectedRoi.init = false; // button is now down anymore (value == false)
    }

    // making two new values to use later on
    int changeY = abs(floor((SelectedRoi.initX / pixel)) - (X)); // knowing the block change in the x axis
    int changeX = abs(floor((SelectedRoi.initY / pixel)) - (Y)); // knowing the block change in the y axis
    
    // if the left button is still down And the mouse moves:
    if(SelectedRoi.init && event == EVENT_MOUSEMOVE) {

        // if the block that mouse is on, is changed:
        if(changeX >= 1 || changeY >= 1) {

            // if the clicked block is not the same color of the current block that mouse is on
            if(SelectedRoi.grabType != vec[X][Y] && (X != 0 || Y != 0) && (X != H_ratio - 1 || Y != V_ratio - 1)) {

                ChangeColor(image, vec, x, y);

                // change the initial values if the color is changed
                SelectedRoi.initX = x;
                SelectedRoi.initY = y;
            }
        }
    }

}

// this function changes the blocks' colors
void ChangeColor(Mat image, vector<vector<bool>>& vec, int x, int y) {
    int thickness = 2; // thickness of the border of rectangles
    int X = x / pixel, Y = y / pixel; // by using these we will know what exact block we are on
    
    // if the block is white it changes to black
    if(!vec[X][Y]) {
        Point p1(X*pixel, Y*pixel); // upper right corner of the rectangle
        Point p2((X + 1) * pixel, (Y + 1) * pixel); // bottom right of the rectangle
        rectangle(image, p1, p2, Scalar(0, 0, 0), FILLED); // making the rectangle
        vec[X][Y] = true; // reseting the value of the block, because is has been changed
    }

    // if the block is black it changes to white
    else if(vec[X][Y]) {
        Point p1(X * pixel, Y * pixel); // upper right corner of the rectangle
        Point p2((X + 1) * pixel, (Y + 1) * pixel); // bottom right of the rectangle
        rectangle(image, p1, p2, Scalar(255, 255, 255), FILLED); // making the base white rectangle
        rectangle(image, p1, p2, Scalar(0, 0, 0), thickness, LINE_8); // making the outer black rectangle
        vec[X][Y] = false; // reseting the value of the block, because is has been changed
    }
    imshow("Output", image);
}

void startEndPoint() {
    // make start point block
    rectangle(image, Point(0, 0), Point(pixel, pixel), Scalar(0, 0, 200), FILLED); 
    rectangle(image, Point(0, 0), Point(pixel, pixel), Scalar(0, 0, 0), 2, LINE_8);

    // make end point block 
    rectangle(image, Point(pixel * (H_ratio - 1), pixel * (V_ratio - 1)), Point(pixel * H_ratio, pixel * V_ratio),
            Scalar(0, 200, 0), FILLED);
    rectangle(image, Point(pixel * (H_ratio - 1), pixel * (V_ratio - 1)), Point(pixel * H_ratio, pixel * V_ratio), 
            Scalar(0, 0, 0), 2, LINE_8);
}
