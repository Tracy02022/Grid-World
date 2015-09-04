//
//  MDP.h
//  AI_GridWorld
//


#ifndef AI_GridWorld_MDP_h
#define AI_GridWorld_MDP_h


#endif

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define ACTION_EAST 0
#define ACTION_SOUTH 1
#define ACTION_WEST 2
#define ACTION_NORTH 3

#define TRANSITION_SUCCEED 0.8 //The probability that by taking action A, it moves to the expected destination state S'. Here the state S' represents the new state that the action A aims to move to.

#define TRANSITION_FAIL 0.2 //he probability that by taking action A, it moves to an unexpected destination state S'. For example, by taking action East, you may moves to the neighboring direction North or South. So the probability of going to North or South is 0.1. We assume the two directions evenly split the value of TRANSITION_FAIL 0.2

#define GAMMA 0.9 //the discount factor

#define ACTION_REWARD -0.1 //The instantaneous for taking each action (we assume the four actions (N/E/W/S) has the same reward)

#define CONVERGENCE 0.0000001 
//#define CONVERGENCE 0.0000001 //The threshold for convergence to determine a stop sign

using namespace cv;


//A structure defines a state variable
struct State{
    Point location; //the 2D location of this state, e.g. (0, 0), (0, 2), (2, 3)...
                    //the location defines the ID for the state
    float state_value;
    float q_values[4]; //four possible values in four directions, these four values have the same order as the action defined above: q_values[0] corresponds to action East; q_values[1] corresponds to action South; q_values[2] corresponds to action West; q_values[3] corresponds to action North
};


class MDP {
 
public:
    MDP();
    ~MDP();
    
    State states[3][4]; //the main variables that define the state for each cell in the gridwall. Actually, there are three state varibles that you do not need to update their state values and Q values: states[1][1], states[0][3], states[1][3], which represent the wall, diamond reward, and pitfall. 
    
    
    
    
    
    void computeQValue(State &s, const int action);// Compute the Q value for a given state and its action
    
    
    void valueIteration(); //The main function to compute the state value for each state by computing four different Q-values and use the maximum one as the state value.
    
    void resetData(); //clear the Q-values and state values of all the states to zero. Meanwhile, the cur_convergence is set to a big value.
    
    
    float cur_convergence; //represent the current convergence status. Actually, it represents the biggest Q-value change of all the Q -values of all the state in the current iteration
    
    
    
};