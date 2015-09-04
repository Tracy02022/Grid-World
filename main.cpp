

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "VisualDisplay.h"

using namespace std;
using namespace cv;


int main(int argc, const char * argv[]) {
    
    VisualDisplay display;
    display.loadImages();
    display.run();
    
    
    return 0;
}
