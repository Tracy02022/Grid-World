

#include <stdio.h>

#include "MDP.h"


/*Compute a Q-value for a given state and its action
  Input: state variable s; action (go to East/North/West/South), the corresponding interger value for each action is defined in the "MDP.h" Macros definition on the top
  Output: you need to update the corresponding q_values of the input state variable s
 */
void MDP::computeQValue(State &s, const int action)
{
	/*store each direction value after computation*/
	float q1;
	float q2;
	float q3;
	/*each direction coresponding Q value*/
	if (action == ACTION_EAST)
	{
		/*face the wall situation*/
		if (s.location.x == 0 && s.location.y == 1)
		{
			q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[0][0].state_value);
			q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[2][0].state_value);
			/*compute convergence*/
			if (cur_convergence < abs(s.q_values[0] - (q2 + q1 + q3)))
				cur_convergence = abs(s.q_values[0] - (q2 + q1 + q3));
			s.q_values[0] = q2 + q1 + q3;
		}
		else
		{
			if (s.location.y == 2)
			{
				/*go south*/
				q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			}
			else
			{
				if ((s.location.y  == 0) && (s.location.x == 1))
				{
					/*face the wall situation*/
					q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
				}
				else
				{
					/*go south*/
					q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y + 1][s.location.x].state_value);
				}
			}
			if (s.location.x == 3)
			{
				/*face the wall situation*/
				q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			}
			else
			{
				if (s.location.y == 1 && s.location.x == 0)
				{
					/*face the wall situation with EAST action*/
					q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
				}
				else
				{
					/*take EAST action*/
					q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x + 1].state_value);
				}
			}
			if (s.location.y == 0)
			{
				/*go north*/
				q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			}
			else
			{
				if (s.location.y == 2 && s.location.x == 1)
				{
					/*face the wall situation*/
					q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
				}
				else
				{
					/*go north*/
					q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y - 1][s.location.x].state_value);
				}
			}
			/*compute convergence*/
			if (cur_convergence < abs(s.q_values[0] - (q2 + q1 + q3)))
				cur_convergence = abs(s.q_values[0] - (q2 + q1 + q3));
			s.q_values[0] = q2 + q1 + q3;
		}
	}
	else if (action == ACTION_WEST)
	{
		/*face the wall situation*/
		if (s.location.x == 2 && s.location.y == 1)
		{
			q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y - 1][s.location.x].state_value);
			q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y + 1][s.location.x].state_value);
			/*compute convergence*/
			if (cur_convergence < abs(s.q_values[2] - (q2 + q1 + q3)))
				cur_convergence = abs(s.q_values[2] - (q2 + q1 + q3));
			s.q_values[2] = q2 + q1 + q3;
		}
		else
		{
			/*go south*/
			if (s.location.y == 2)
			{
				q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			}
			else
			{
				/*face the wall situation*/
				if (s.location.y == 0 && s.location.x == 1)
				{
					q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
				}
				else
				{
					q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y + 1][s.location.x].state_value);
				}
			}
			/*go west*/
			if (s.location.x == 0)
			{
				q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			}
			else
			{
				if (s.location.y == 1 && s.location.x == 2)
				{
					/*face the wall situation with take WEST action*/
					q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
				}
				else
				{
					q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x - 1].state_value);
				}
			}
			/*go north*/
			if (s.location.y == 0)
			{
				q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			}
			else
			{
				if (s.location.y == 2 && s.location.x == 1)
				{
					/*face the wall situation*/
					q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
				}
				else
				{
					q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y - 1][s.location.x].state_value);
				}
			}
			/*computer convergence*/
			if (cur_convergence < abs(s.q_values[2] - (q2 + q1 + q3)))
				cur_convergence = abs(s.q_values[2] - (q2 + q1 + q3));
			s.q_values[2] = q2 + q1 + q3;
		
		}
	}

	else if (action == ACTION_NORTH)
	{
		/*face the wall situation*/
		if (s.location.x == 1 && s.location.y == 2)
		{
			q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y ][s.location.x- 1].state_value);
			q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y ][s.location.x+ 1].state_value);
			/*computer convergence*/
			if (cur_convergence < abs(s.q_values[3] - (q2 + q1 + q3)))
				cur_convergence = abs(s.q_values[3] - (q2 + q1 + q3));
			s.q_values[3] = q2 + q1 + q3;
		}
		else
		{
			/*go west*/
			if (s.location.x == 0)
			{
				q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			}
			else
			{
				/*face the wall situation with take WEST action*/
				if (s.location.y == 1 && s.location.x == 2)
				{
					q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
				}
				else
				{
					q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x - 1].state_value);
				}
			}
			/*go north*/
			if (s.location.y == 0)
			{
				q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			}
			else
			{
				if (s.location.y == 2 && s.location.x == 1)
				{
					/*face the wall situation*/
					q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
				}
				else
				{
					q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y - 1][s.location.x].state_value);
				}
			}
			/*face the wall go EAST*/
			if (s.location.x == 3)
			{
				q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			}
			else
			{
				if (s.location.y == 1 && s.location.x == 0)
				{
					q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
				}
				else
				{
					q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x + 1].state_value);
				}
			}
			/*computer convergence*/
			if (cur_convergence < abs(s.q_values[3] - (q2 + q1 + q3)))
				cur_convergence = abs(s.q_values[3] - (q2 + q1 + q3));
			s.q_values[3] = q2 + q1 + q3;
			
		}
	}

	else
	{
		/*go SOUTH with facing wall situation*/
		if (s.location.x == 1 && s.location.y == 0)
		{
			q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x - 1].state_value);
			q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x + 1].state_value);
			/*computer convergence*/
			if (cur_convergence < abs(s.q_values[1] - (q2 + q1 + q3)))
				cur_convergence = abs(s.q_values[1] - (q2 + q1 + q3));
			s.q_values[1] = q2 + q1 + q3;
		}
		else
		{
			/*go WEST*/
			if (s.location.x == 0)
			{
				q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			}
			else
			{
				if (s.location.y == 1 && s.location.x == 2)
				{
					q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
				}
				else
				{
					q1 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x - 1].state_value);
				}
			}
			/*go SOUTH*/
			if (s.location.y == 2)
			{
				q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			}
			else
			{
				if (s.location.y == 0 && s.location.x == 1)
				{
					q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
				}
				else
				{
					q2 = TRANSITION_SUCCEED*(ACTION_REWARD + GAMMA*states[s.location.y + 1][s.location.x].state_value);
				}
			}
			/*go EAST*/
			if (s.location.x == 3)
			{
				q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
			}
			else
			{
				if (s.location.y == 1 && s.location.x == 0)
				{
					q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x].state_value);
				}
				else
				{
					q3 = TRANSITION_FAIL*0.5*(ACTION_REWARD + GAMMA*states[s.location.y][s.location.x + 1].state_value);
				}
			}
			/*computer convergence*/
			if (cur_convergence < abs(s.q_values[1] - (q2 + q1 + q3)))
				cur_convergence = abs(s.q_values[1] - (q2 + q1 + q3));
			s.q_values[1] = q2 + q1 + q3;
		}
	}
}


/*There is no return value, actually you need to use the computing result to update the state values of all the states defined as data member "State states[3][4]". Of course, you don't need to update the wall state: states[1][1], the diamond state: states[0][3], and pitfall state: states[1][3] */
void MDP::valueIteration()
{
	/*first set the variable to be 0*/
	cur_convergence = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((i == 1 && j == 1) || (i == 0 && j == 3) || (i == 1&&j == 3))
				continue;
			else
			{
				/*computer every single state with forth actions*/
				computeQValue(states[i][j], ACTION_EAST);
				computeQValue(states[i][j], ACTION_SOUTH);
				computeQValue(states[i][j], ACTION_WEST);
				computeQValue(states[i][j], ACTION_NORTH);

			}
		}
	}
	/*set value for all the states by choosing MAX(Qvalue)*/
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((i == 1 && j == 1) || (i == 0 && j == 3) || (i == 1 && j == 3))
				continue;
			else
			{
				states[i][j].state_value = max(max(max(states[i][j].q_values[0], states[i][j].q_values[1]), states[i][j].q_values[2]), states[i][j].q_values[3]);	
			}
		}
	}
}



MDP::MDP()
{
    /*Initialize all the state with 0.0 state_value and 0.0 Q_values*/
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            states[y][x].location.x = x; //specify the location for this state
            states[y][x].location.y = y;
            
            states[y][x].state_value = 0.0; //define the state value
            states[y][x].q_values[0] = 0.0; //define the Q value
            states[y][x].q_values[1] = 0.0;
            states[y][x].q_values[2] = 0.0;
            states[y][x].q_values[3] = 0.0;
        }
    }
    
    /* Reset the values for the two special states: diamonds (0, 3), pitfall (1, 3). Actually there are no Q-values for these two states as these two states represents the final state of the game. Similarly, for the wall (1, 1), it does not have any state value or Q values. So make sure not to update these three states during your program*/
    states[0][3].state_value = 1.0;
    states[1][3].state_value = -1.0;
    
    
    
    /*Set the current convergence to a big number initially*/
    cur_convergence = 100; //the reason this value is set to a big value is to ensure 
    
    
}


MDP::~MDP()
{
    
}

/*Reset the current computed state and Q values*/
void MDP::resetData()
{
    /*Initialize all the state with 0.0 state_value and 0.0 Q_values*/
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            states[y][x].location.x = x; //specify the location for this state
            states[y][x].location.y = y;
            
            states[y][x].state_value = 0.0; //define the state value
            states[y][x].q_values[0] = 0.0; //define the Q value
            states[y][x].q_values[1] = 0.0;
            states[y][x].q_values[2] = 0.0;
            states[y][x].q_values[3] = 0.0;
        }
    }
    
    /* Reset the values for the two special states: diamonds (0, 3), pitfall (1, 3). Actually there are no Q-values for these two states as these two states represents the final state of the game. Similarly, for the wall (1, 1), it does not have any state value or Q values. So make sure not to update these three states during your program*/
    states[0][3].state_value = 1.0;
    states[1][3].state_value = -1.0;
    
    
    
    /*Set the current convergence to a big number initially*/
    cur_convergence = 0; //the reason this value is set to a big value is to ensure
    
    
}
