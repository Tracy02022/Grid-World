//
//  VisualDisplay.h
//  AI_GridWorld
//

#ifndef AI_GridWorld_VisualDisplay_h
#define AI_GridWorld_VisualDisplay_h


#endif

#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/gpu/gpu.hpp>
#include "MDP.h"

#define ratio 1.0 //determine the size of the image
#define margin_left 25 //the pixels start for putting text number on the square
#define margin_bottom 10

#define NUM_BUTTON 100
using namespace std;
using namespace cv;
using namespace gpu;

/* Square Unit on the Grid World, which represents a state*/
struct Square{
    
    Point cen_pos; //the center position of the cell
    Point q_pos[4]; //the four positions to put the number for Q value in E S W N order
    float state_value; //the number will be put in the center, which is V(s)
    float q_value[4]; //the number will be put in the four corner, which is Q(s, a, s'), in E S W N order
    Point arrow_pos; //the position that the left/right/top/bottom
};


/*Buttons*/
struct Button{
    Mat org_img; //store the original image that has no click
    Mat hov_img; //store the image when the mouse hove on top of it
    Mat clk_img; //store the image when the mouse is clicking on it.
    int status; //store the status of the button that 0 - shows original image, 1 - shows hover image, 2 - shows clicked image
    Point top_let; //the position of top left corner of the image
    Point bot_rgh; //the position of bottom right corner of the image
    
};

struct GoButton : Button{
    Mat org_img_2; //as the go button is special that there are go and pause pattern on the button
    Mat hov_img_2;
    Mat clk_img_2;
    int type; //2 - go is on; 1- paus is on
};


/*The main GUI class showing the grid world map*/
class VisualDisplay{
public:
    MDP mdp; //the markov decision process class used to compute the values
    Mat gridworld_img; //the main image will display in the window
    Mat arrow_imgs[4]; //the arrow images
    Mat arrow_masks[4]; //the mask image for the arrow
    Mat org_gridworld[2]; //the original image loaded from file
    
    int square_length; //the size of each square in pixels
    Point grid_size; //the x and y of this point represent the grid area size
    Square square[3][4]; //3x4 squares on the image
    
    
    /*Control Data*/
    int center_num_sign; //control data: show the state value in the center of each square
                 //decide whether the Q value is displayed: 1 - state value; 0 - Q value
    int policy_sign; //0- not draw the arrow; 1 - draw the arrow
    int idx; //the global index about number of iterations

    /*Workflow control image*/
    Button button[NUM_BUTTON]; //the buttons
    GoButton go_btn; //go button for running the algorithm in a batch
    
public:
    VisualDisplay();
    ~VisualDisplay();
    void loadImages();
    void run();
    void painContainer();
    void paintButtons(); //this is called by paintContainer
    
    void refreshData(); //retrieve new data from the MDP
    
    
    /*Button Check*/
    void buttonHoverCheck(int x, int y);
    void buttonClickCheck(int x, int y);
    
    /*Button Callback Functions*/
    void onNext();
    void onReset();
    void onGo();
};


