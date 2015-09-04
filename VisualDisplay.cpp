

#include "VisualDisplay.h"

void onMouse( int event, int x, int y, int flags, void* param )
{
    VisualDisplay* vd = (VisualDisplay*) param;
    
    
    switch( event )
    {
        case CV_EVENT_LBUTTONDOWN:
            printf("(%d, %d)\n", x, y);
            vd->buttonClickCheck(x, y);
            break;
            
        case CV_EVENT_RBUTTONDOWN:
            break;
        case CV_EVENT_LBUTTONUP:
            
            break;
            
            
        case CV_EVENT_RBUTTONUP:
            
            break;
            
        case CV_EVENT_MOUSEMOVE:
            vd->buttonHoverCheck(x, y);
            break;
    }
    
}

void VisualDisplay::buttonHoverCheck(int x, int y)
{
    for(int i = 0; i < 6; i++)
    {
        if(i < 2) /*Radio Button Use*/
        {
            if(button[i].status != 2)
            {
                if(button[i].top_let.x < x && x < button[i].bot_rgh.x && button[i].top_let.y < y && y < button[i].bot_rgh.y)
                {
                    button[i].status = 1;
                }
                else
                {
                    button[i].status = 0;
                }
            }
        }
        else if(i == 2 || i == 3 ) /*For checkbox use (random selection of domain value*/
        {
            
        }
        else/*Next, Reset Button use*/
        {
            if(button[i].top_let.x < x && x < button[i].bot_rgh.x && button[i].top_let.y < y && y < button[i].bot_rgh.y)
            {
                button[i].status = 1;
            }
            else
            {
                button[i].status = 0;
            }
            
        }
    }
    
    if(go_btn.top_let.x < x && x < go_btn.bot_rgh.x && go_btn.top_let.y < y && y < go_btn.bot_rgh.y)
    {
        go_btn.status = 1;
    }
    else
    {
        go_btn.status = 0;
    }
    
}

void VisualDisplay::buttonClickCheck(int x, int y)
{
    /* For option buttion (radio)*/
    for(int i = 0; i < 2; i++)
    {
        if(button[i].status == 1)
        {
            button[i].status = 2;
            
            /*Set the rest option button to 0*/
            for(int j = 0; j < 2; j++)
            {
                if(j != i)
                {
                    button[j].status = 0;
                }
            }
            
            
            /*Reset the Go Button*/
            go_btn.type = 1; //initially it is in ready to go state.
        }
        
    }
    
    /* For check box use*/
    //Q or state value
    if(button[2].top_let.x < x && x < button[2].bot_rgh.x && button[2].top_let.y - 4 * ratio <= y && y <= button[2].bot_rgh.y)
    {
        printf("top_lef: %d, bot_right: %d\n", button[2].top_let.y, button[2].bot_rgh.y);
        button[2].status = (button[2].status == 0)? 2 : 0;
        if(button[2].status == 2)
        {
            center_num_sign = 0;
        }
        else{
            center_num_sign = 1;
        }
    }
    //show the policy
    else if(button[3].top_let.x < x && x < button[3].bot_rgh.x && button[3].top_let.y - 4 * ratio <= y && y < button[3].bot_rgh.y)
    {
        button[3].status = (button[3].status == 0)? 2 : 0;
        if(button[3].status == 2)
        {
            policy_sign = 1;
        }
        else{
            policy_sign = 0;
        }
    }
    
    
    /* For controlling buttons: next, reset */
    for(int i = 4; i < (6); i++)
    {
        
        if(button[i].status == 1)
        {
            button[i].status = 2;
            if(i == 4)
            {
                
                onNext();
            }
            if(i == 5)
            {
                onReset();
            }
        }
    }
    
    /* For the go button */
    if(go_btn.status == 1 || go_btn.status == 2)
    {
        go_btn.status = 2;
        go_btn.type = (go_btn.type == 1)?2:1;
        onGo();
    }
}

void VisualDisplay::onReset()
{
    mdp.resetData();
    idx = 0;
    
}

void VisualDisplay::onNext()
{
    if(idx < 100)
    {
        mdp.valueIteration();
        idx++;
    }
}

void VisualDisplay::onGo()
{
    if(idx < 100 && mdp.cur_convergence > CONVERGENCE)
    {
        mdp.valueIteration();
        idx++;
    }
    cv::waitKey(100);
}

VisualDisplay::VisualDisplay()
{
    cv::namedWindow("Grid World");
    setMouseCallback("Grid World", onMouse, this);
    
    /*The pixel position for each row (the top boundary)*/
    int row_pixel[3] = {8, 156, 304};
    
    /*The pixel position for each column (the left boundary)*/
    int col_pixel[4] = {14, 161, 307, 452};
    
    square_length = 144 * ratio; //pixel size of each square
    for(int i = 0; i < 3; i++)
        row_pixel[i] *= ratio;
    for(int i = 0; i < 4; i++)
        col_pixel[i] *= ratio;
    
    /*The grid world area of the image (left and bottom boundary*/
    grid_size.x = 620 * ratio;
    grid_size.y = 460 * ratio;
    
    /*initialize all the squares: number positions, state value, Q value*/
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            if((y == 0 && x == 3) || (y == 1 && x == 3) || (y == 1 && x == 1))
                continue;
                
            //Center
            square[y][x].cen_pos.y = row_pixel[y] + square_length / 2.0 + margin_bottom * ratio;
            square[y][x].cen_pos.x = col_pixel[x] + square_length / 2.0 - margin_left * ratio;
            
            
            //East
            square[y][x].q_pos[0].y = row_pixel[y] + square_length / 2.0 + margin_bottom * ratio;
            square[y][x].q_pos[0].x = col_pixel[x] + square_length * 6.8 / 9.0 - margin_left * ratio;
            
            
            //South
            square[y][x].q_pos[1].y = row_pixel[y] + square_length * 5.0 / 6.0 + margin_bottom * ratio;
            square[y][x].q_pos[1].x = col_pixel[x] + square_length / 2.0 - margin_left * ratio;
            
            
            //West
            square[y][x].q_pos[2].y = row_pixel[y] + square_length / 2.0 + margin_bottom * ratio;
            square[y][x].q_pos[2].x = col_pixel[x] + square_length * 1.0 / 5.0 - margin_left * ratio;
            
            
            //North
            square[y][x].q_pos[3].y = row_pixel[y] + square_length * 1.0 / 6.0 + margin_bottom * ratio;
            square[y][x].q_pos[3].x = col_pixel[x] + square_length / 2.0 - margin_left * ratio;

            
            //Arrow position
            square[y][x].arrow_pos.x = col_pixel[x];
            square[y][x].arrow_pos.y = col_pixel[y];
            
            
            square[y][x].state_value = 0.00f;
            
            for(int i = 0; i < 4; i++)
                square[y][x].q_value[i] = 0.0f;
        }
    }
    
    
    
    /*initialize the control data*/
    center_num_sign = 1;
    idx = 0; //initiall set it to zero
    policy_sign = 0; //initially not draw the arrow
    
    
    /*Initiate the button status*/
    for(int i = 1; i < 6; i++)
    {
        button[i].status = 0;
    }
    button[0].status = 2;
    go_btn.type = 1; //initially it is in ready to go state.}
}

VisualDisplay::~VisualDisplay(void)
{
}



/* Draw the buttons on the canvas */
void VisualDisplay::paintButtons()
{
    
    /*Render the buttons*/
    for(int i = 2; i < 6; i++)
    {
        if(button[i].status == 0) //render ordinary image
        {
            {
                button[i].org_img.copyTo(gridworld_img(cv::Range(button[i].top_let.y, button[i].bot_rgh.y), cv::Range(button[i].top_let.x, button[i].bot_rgh.x)));
            }
        }
        else if(button[i].status == 1) //render the hover image
        {
            button[i].hov_img.copyTo(gridworld_img(cv::Range(button[i].top_let.y, button[i].bot_rgh.y), cv::Range(button[i].top_let.x, button[i].bot_rgh.x)));
        }
        else //render selected image
        {
            button[i].clk_img.copyTo(gridworld_img(cv::Range(button[i].top_let.y, button[i].bot_rgh.y), cv::Range(button[i].top_let.x, button[i].bot_rgh.x)));
        }
    }
    
    if(go_btn.status == 0 && go_btn.type ==1)
    {
        go_btn.org_img.copyTo(gridworld_img(cv::Range(go_btn.top_let.y, go_btn.bot_rgh.y), cv::Range(go_btn.top_let.x, go_btn.bot_rgh.x)));
    }
     if(go_btn.status == 1 && go_btn.type ==1)
    {
        go_btn.hov_img.copyTo(gridworld_img(cv::Range(go_btn.top_let.y, go_btn.bot_rgh.y), cv::Range(go_btn.top_let.x, go_btn.bot_rgh.x)));
    }
    else if(go_btn.status == 2 && go_btn.type == 2)
    {
        go_btn.clk_img.copyTo(gridworld_img(cv::Range(go_btn.top_let.y, go_btn.bot_rgh.y), cv::Range(go_btn.top_let.x, go_btn.bot_rgh.x)));
    }
    else if(go_btn.status == 0 && go_btn.type == 2)
    {
        go_btn.org_img_2.copyTo(gridworld_img(cv::Range(go_btn.top_let.y, go_btn.bot_rgh.y), cv::Range(go_btn.top_let.x, go_btn.bot_rgh.x)));
    }
    else if(go_btn.status == 1 && go_btn.type == 2)
    {
        go_btn.hov_img_2.copyTo(gridworld_img(cv::Range(go_btn.top_let.y, go_btn.bot_rgh.y), cv::Range(go_btn.top_let.x, go_btn.bot_rgh.x)));
    }
    else if(go_btn.status == 2 && go_btn.type == 1)
    {
        go_btn.clk_img_2.copyTo(gridworld_img(cv::Range(go_btn.top_let.y, go_btn.bot_rgh.y), cv::Range(go_btn.top_let.x, go_btn.bot_rgh.x)));
    }
    
    
    /*Render the labels*/
   // cv::putText(gridworld_img, "Game Mode", Point(button[0].top_let.x + 30 * ratio, button[0].top_let.y + 14 * ratio), FONT_HERSHEY_COMPLEX_SMALL, 0.75 * ratio, Scalar(50, 50, 50), 1, CV_AA);
    cv::putText(gridworld_img, "MDP Process", Point(button[1].top_let.x - 10 * ratio, button[1].top_let.y - 5 * ratio), FONT_HERSHEY_COMPLEX_SMALL, 0.85 * ratio, Scalar(50, 50, 50), 1, CV_AA);
    cv::putText(gridworld_img, "Show Q-values", Point(button[2].top_let.x + 30 * ratio, button[2].top_let.y + 14 * ratio), FONT_HERSHEY_COMPLEX_SMALL, 0.7 * ratio, Scalar(50, 50, 50), 1, CV_AA);
    cv::putText(gridworld_img, "Show Policy", Point(button[3].top_let.x + 30 * ratio, button[3].top_let.y + 14 * ratio), FONT_HERSHEY_COMPLEX_SMALL, 0.7 * ratio, Scalar(50, 50, 50), 1, CV_AA);

    /*Render the iteration label*/
    char iteration_text[200];
    sprintf(iteration_text, "Iterations: %d", idx);
    cv::putText(gridworld_img, iteration_text, Point(grid_size.x / 2.0 - 50 * ratio, grid_size.y + 15 * ratio), FONT_HERSHEY_COMPLEX_SMALL, 0.7 * ratio, Scalar(50, 50, 50), 1, CV_AA);
}

void VisualDisplay::painContainer()
{
    /*Initially render the gridworld from the original image*/
    if(center_num_sign == 1)
        org_gridworld[0].copyTo(gridworld_img);
    else
        org_gridworld[1].copyTo(gridworld_img);
    
    
    /*Draw the state value or Q value on the image*/
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            char num_char[20];
            
            
            //Draw the arrows on the image
            if(policy_sign == 1)
            {
                if(!((y == 0 && x == 3) || (y == 1 && x == 1) || (y == 1 && x == 3)))
                {
                    int max_idx = 0; //store the index with maximum value
                    float max_val = -1000.0f; //store the maximum value
                    
                    for(int i = 0; i < 4; i++)
                    {
                        if(square[y][x].q_value[i] > max_val)
                        {
                            max_idx = i;
                            max_val = square[y][x].q_value[i];
                            
                        }
                    }
                    
                    if(square[y][x].q_value[0] == square[y][x].q_value[1] && square[y][x].q_value[1] == square[y][x].q_value[2] && square[y][x].q_value[2] == square[y][x].q_value[3])
                        max_idx = 0;
                   
                    
                    arrow_imgs[max_idx].copyTo(gridworld_img(cv::Range(square[y][x].arrow_pos.y, square[y][x].arrow_pos.y + square_length), cv::Range(square[y][x].arrow_pos.x, square[y][x].arrow_pos.x + square_length)), arrow_masks[max_idx]);
                }
            }
            
            
            //draw state value
            if(center_num_sign == 1)
            {
                sprintf(num_char, "%.4f", square[y][x].state_value);
                cv::putText(gridworld_img, num_char, square[y][x].cen_pos, FONT_HERSHEY_DUPLEX , 0.5 * ratio, Scalar(0, 0, 0), 1, CV_AA);
            }
            else //draw Q value
            {
                
                for(int i = 0; i < 4; i++)
                {
                    sprintf(num_char, "%.4f", square[y][x].q_value[i]);
                    cv::putText(gridworld_img, num_char, square[y][x].q_pos[i], FONT_HERSHEY_DUPLEX , 0.40 * ratio, Scalar(0, 0, 0), 1, CV_AA);
                }
            }
            
        }
    }
    
    
    
    
    /* draw the buttons */
    paintButtons();
}

void VisualDisplay::loadImages()
{
    org_gridworld[0] = imread("imgs/GridWorld.jpg");
    org_gridworld[1] = imread("imgs/GridWorld_cross.jpg");
    cv::resize(org_gridworld[0], org_gridworld[0], cv::Size(org_gridworld[0].cols * ratio, org_gridworld[0].rows * ratio));
    cv::resize(org_gridworld[1], org_gridworld[1], cv::Size(org_gridworld[1].cols * ratio, org_gridworld[1].rows * ratio));

    
    /*Load the button images*/
    button[0].org_img = imread("imgs/radio_button.png"); //button  0 (Gaming Mode)
    button[0].hov_img = imread("imgs/radio_hover.png");
    button[0].clk_img = imread("imgs/radio_select.png");
    resize(button[0].org_img, button[0].org_img, Size(20 * ratio, 20 * ratio));
    resize(button[0].hov_img, button[0].hov_img, Size(20 * ratio, 20 * ratio));
    resize(button[0].clk_img, button[0].clk_img, Size(20 * ratio, 20 * ratio));
    button[0].top_let.x = grid_size.x + 5 * ratio;
    button[0].top_let.y = grid_size.y * .10;
    button[0].bot_rgh.x = button[0].top_let.x + button[0].org_img.cols;
    button[0].bot_rgh.y = button[0].top_let.y + button[0].org_img.rows;
    
    
    button[0].org_img.copyTo(button[1].org_img); //button 1 (MDP Mode)
    button[0].hov_img.copyTo(button[1].hov_img);
    button[0].clk_img.copyTo(button[1].clk_img);
    button[1].top_let.x = grid_size.x + 5 * ratio;
    button[1].top_let.y = grid_size.y * .20;
    button[1].bot_rgh.x = button[1].top_let.x + button[1].org_img.cols;
    button[1].bot_rgh.y = button[1].top_let.y + button[1].org_img.rows;
    
    
    
    
    button[2].org_img = imread("imgs/checkbox_unchecked.png"); //show the Q value
    button[2].hov_img = imread("imgs/checkbox_unchecked.png");
    button[2].clk_img = imread("imgs/checkbox_checked.png");
    resize(button[2].org_img, button[2].org_img, Size(18 * ratio, 18 * ratio));
    resize(button[2].hov_img, button[2].hov_img, Size(18 * ratio, 18 * ratio));
    resize(button[2].clk_img, button[2].clk_img, Size(18 * ratio, 18 * ratio));
    button[2].top_let.x = grid_size.x + 25 * ratio; //render the check button
    button[2].top_let.y = grid_size.y * .28;
    button[2].bot_rgh.x = button[2].top_let.x + button[2].org_img.cols;
    button[2].bot_rgh.y = button[2].top_let.y + button[2].org_img.rows;
    
    
    button[3].org_img = imread("imgs/checkbox_unchecked.png"); //show the policy
    button[3].hov_img = imread("imgs/checkbox_unchecked.png");
    button[3].clk_img = imread("imgs/checkbox_checked.png");
    resize(button[3].org_img, button[3].org_img, Size(18 * ratio, 18 * ratio));
    resize(button[3].hov_img, button[3].hov_img, Size(18 * ratio, 18 * ratio));
    resize(button[3].clk_img, button[3].clk_img, Size(18 * ratio, 18 * ratio));
    button[3].top_let.x = grid_size.x + 25 * ratio; //render the check button
    button[3].top_let.y = grid_size.y * .36;
    button[3].bot_rgh.x = button[3].top_let.x + button[3].org_img.cols;
    button[3].bot_rgh.y = button[3].top_let.y + button[3].org_img.rows;
    

    
    button[4].org_img = imread("imgs/next.png"); //next button (move one step forward)
    button[4].hov_img = imread("imgs/next_hover.png");
    button[4].clk_img = imread("imgs/next.png");
    resize(button[4].org_img, button[4].org_img, Size(70 * ratio, 35 * ratio));
    resize(button[4].hov_img, button[4].hov_img, Size(70 * ratio, 35 * ratio));
    resize(button[4].clk_img, button[4].clk_img, Size(70 * ratio, 35 * ratio));
    button[4].top_let.x = grid_size.x; //render the next button
    button[4].top_let.y = grid_size.y * .46;
    button[4].bot_rgh.x = button[4].top_let.x + button[4].org_img.cols;
    button[4].bot_rgh.y = button[4].top_let.y + button[4].org_img.rows;
    
    button[5].org_img = imread("imgs/reset.png"); //reset button  (clear all the Q values and state values to 0)
    button[5].hov_img = imread("imgs/reset_hover.png");
    button[5].clk_img = imread("imgs/reset.png");
    resize(button[5].org_img, button[5].org_img, Size(70 * ratio, 35 * ratio));
    resize(button[5].hov_img, button[5].hov_img, Size(70 * ratio, 35 * ratio));
    resize(button[5].clk_img, button[5].clk_img, Size(70 * ratio, 35 * ratio));
    button[5].top_let.x = grid_size.x + 100 * ratio; //render the next button
    button[5].top_let.y = grid_size.y * .46;
    button[5].bot_rgh.x = button[5].top_let.x + button[5].org_img.cols;
    button[5].bot_rgh.y = button[5].top_let.y + button[5].org_img.rows;
    
    
    go_btn.org_img = imread("imgs/go.png"); //next button 0 (move one step forward)
    go_btn.hov_img = imread("imgs/go_hover.png");
    go_btn.clk_img = imread("imgs/pause_hover.png");
    resize(go_btn.org_img, go_btn.org_img, Size(80 * ratio, 80 * ratio));
    resize(go_btn.hov_img, go_btn.hov_img, Size(80 * ratio, 80 * ratio));
    resize(go_btn.clk_img, go_btn.clk_img, Size(80 * ratio, 80 * ratio));
    go_btn.org_img_2 = imread("imgs/pause.png"); //next button 0 (move one step forward)
    go_btn.hov_img_2 = imread("imgs/pause_hover.png");
    go_btn.clk_img_2 = imread("imgs/go_hover.png");
    resize(go_btn.org_img_2, go_btn.org_img_2, Size(80 * ratio, 80 * ratio));
    resize(go_btn.hov_img_2, go_btn.hov_img_2, Size(80 * ratio, 80 * ratio));
    resize(go_btn.clk_img_2, go_btn.clk_img_2, Size(80 * ratio, 80 * ratio));
    go_btn.top_let.x = grid_size.x + 50 * ratio; //render the next button
    go_btn.top_let.y = grid_size.y * .60;
    go_btn.bot_rgh.x = go_btn.top_let.x + go_btn.org_img.cols;
    go_btn.bot_rgh.y = go_btn.top_let.y + go_btn.org_img.rows;
    
    
    arrow_imgs[ACTION_EAST] = imread("imgs/east.png");
    arrow_masks[ACTION_EAST] = imread("imgs/east_mask.png", 0);
    resize(arrow_imgs[ACTION_EAST], arrow_imgs[ACTION_EAST], Size(square_length, square_length));
    resize(arrow_masks[ACTION_EAST], arrow_masks[ACTION_EAST], Size(square_length, square_length));
    
    
    arrow_imgs[ACTION_WEST] = imread("imgs/west.png");
    arrow_masks[ACTION_WEST] = imread("imgs/west_mask.png", 0);
    resize(arrow_imgs[ACTION_WEST], arrow_imgs[ACTION_WEST], Size(square_length, square_length));
    resize(arrow_masks[ACTION_WEST], arrow_masks[ACTION_WEST], Size(square_length, square_length));
  
    
    arrow_imgs[ACTION_NORTH] = imread("imgs/north.png");
    arrow_masks[ACTION_NORTH] = imread("imgs/north_mask.png", 0);
    resize(arrow_imgs[ACTION_NORTH], arrow_imgs[ACTION_NORTH], Size(square_length, square_length));
    resize(arrow_masks[ACTION_NORTH], arrow_masks[ACTION_NORTH], Size(square_length, square_length));
    
    
    arrow_imgs[ACTION_SOUTH] = imread("imgs/south.png");
    arrow_masks[ACTION_SOUTH] = imread("imgs/south_mask.png", 0);
    resize(arrow_imgs[ACTION_SOUTH], arrow_imgs[ACTION_SOUTH], Size(square_length, square_length));
    resize(arrow_masks[ACTION_SOUTH], arrow_masks[ACTION_SOUTH], Size(square_length, square_length));

}

void VisualDisplay::run()
{
    while(1)
    {
        /*In every interation, refresh the data from CSP first*/
        refreshData();
        
        /* Paint the GUI */
        painContainer();
        
        /*Control Button Refreshing*/
        for(int i = 4; i < 6; i++)
        {
            if(button[i].status == 2)
            {
                waitKey(20);
                button[i].status = 1;
            }
        }
        
        /*For the Go Button*/
        if(go_btn.type == 2)
        {
            onGo();
        }
        if(idx >= 100 || mdp.cur_convergence < CONVERGENCE)
        {
            go_btn.type = 1;
        }
        
        imshow("Grid World", gridworld_img);
        
        char c = cv::waitKey(1);
        
        if(c == 27)
            break;
        if(c == 'c')
        {
            center_num_sign = (center_num_sign == 0) ? 1 : 0;
            
        }
    }
}


/* Transfer the data from MDP object to the VisualDisplay class*/
void VisualDisplay::refreshData()
{
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            square[y][x].state_value = mdp.states[y][x].state_value;
            
            for(int i = 0; i < 4; i++)
            {
                square[y][x].q_value[i] = mdp.states[y][x].q_values[i];
            }
        }
    }
}
