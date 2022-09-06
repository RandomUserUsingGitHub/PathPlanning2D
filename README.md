# Implementation of the a* algorithm alongside ucs and greedy algorithm
The a* algorithm is an algorithm used to find the best route in a subset of a graph. This algorithm is related to ucs, greedy algorithm and dynamic programming. It helps determine how to reach a target path in an efficient manner. Essentially, this algorithm can be used for pathfinding and finding the best solution to a problem.

In general, the a* algorithm is considered more efficient than ucs and greedy algorithm. However, there are situations where ucs and greedy algorithm are more efficient than the a* algorithm. For instance, if you are only looking for a short path from one node to another, the a* algorithm may not be as efficient as an initialized UC tree. However, for long paths or paths that lead to many nodes, the A*, greedy or random search algorithms may be more efficient.


## Results


![Alt Text](https://media3.giphy.com/media/CkhGkcb1cQ2fxyghjg/giphy.gif?cid=790b7611a5476e1cf37b84460a8e69136cb22c71bf294449&rid=giphy.gif&ct=g)


## Options

![Alt Text](https://i.ibb.co/qsGsCQp/Screenshot-from-2022-09-06-12-01-44.png)

a* mode . . . . . . . . . . . . . . press **1**\
ucs mode . . . . . . . . . . . . . press **2**\
greedy mode . . . . . . . . . .press **3**\
remove walls . . . . . . . . . .press **w**\
allow  diagonal . . . . . . . . .press **d**\
exit the app . . . . . . . . . . . press **q**


* Total length from agent to goal, gets calculated (only if there is a possible route)
* Total time taken by the execution of the selected algorithm gets calculated
* You can also set the output ratio and size from the code on Visual.h
## Installation

You need to have **g++** and **opencv** installed on your **linux** system in order to run the program

**g++**
```bash
  sudo apt update
  sudo apt install g++
```
**Packages**
* cmake :
```bash
  sudo apt update
  sudo apt-get install build-essential cmake
```
* Packages required to import or record image files in a particular format :
```bash
  sudo apt-get install libjpeg-dev libtiff5-dev libpng-dev
```
* The Video4Linux package includes device drivers and APIs to support real-time video capture on Linux :
```bash
  sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libxvidcore-dev libx264-dev libxine2-dev
```
* The Video4Linux package includes device drivers and APIs to support real-time video capture on Linux :
```bash
  sudo apt-get install libv4l-dev v4l-utils
```
* GStreamer is a library for streaming video :
```bash
  sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev 
```
* OpenCV can window itself using the highgui module to show images or videos :
```bash
  sudo apt-get install libgtk2.0-dev
```
* Library required to support OpenGL :
```bash
  sudo apt-get install mesa-utils libgl1-mesa-dri libgtkgl2.0-dev libgtkglext1-dev  
```
* Libraries used for OpenCV optimization :
```bash
  sudo apt-get install libatlas-base-dev gfortran libeigen3-dev
```
**openCv**
* Follow these steps :
```bash
    wget -O opencv.zip https://github.com/opencv/opencv/archive/4.2.0.zip
    unzip opencv_contrib.zip
    wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.2.0.zip
    unzip opencv_contrib.zip
    cd opencv-4.0.1/
    mkdir build
    cd build
```
* Set the opencv compilation :
```bash
  cmake -D CMAKE_BUILD_TYPE=RELEASE \
  -D CMAKE_INSTALL_PREFIX=/usr/local \
  -D WITH_TBB=OFF \
  -D WITH_IPP=OFF \
  -D WITH_1394=OFF \
  -D BUILD_WITH_DEBUG_INFO=OFF \
  -D BUILD_DOCS=OFF \
  -D INSTALL_C_EXAMPLES=ON \
  -D INSTALL_PYTHON_EXAMPLES=ON \
  -D BUILD_EXAMPLES=OFF \
  -D BUILD_TESTS=OFF \
  -D BUILD_PERF_TESTS=OFF \
  -D WITH_QT=OFF \
  -D WITH_GTK=ON \
  -D WITH_OPENGL=ON \
  -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-4.2.0/modules \
  -D WITH_V4L=ON  \
  -D WITH_FFMPEG=ON \
  -D WITH_XINE=ON \
  -D BUILD_NEW_PYTHON_SUPPORT=ON \
  -D OPENCV_GENERATE_PKGCONFIG=ON ../
```
* This can take a long time :
```bash
  make
```
* Installing the compilation output :
```bash
  sudo make install
```