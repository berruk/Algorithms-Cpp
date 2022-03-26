/*
*
*   STATE MACHINE LIBRARY
*     @author: github/berruk
*
*
*/


#include "cpplist.h"
#include "state.h"

#ifndef _STATEMACHINE_H
#define _STATEMACHINE_H


/*
 * Represents a State Machine
 * state_list : List of states 
 * current_state : index of current state of machine
 */
class StateMachine{
    
    public:
    
    List<class State*> state_list;
    int current_state = -1;

    StateMachine();
    ~StateMachine();

    State* addState(void (*)());
    bool transition_to(State*);
  
    friend void err(int, int);
    	
};

StateMachine::StateMachine(){
  state_list = *(new List<State*>);
};

StateMachine::~StateMachine(){};

/*
 * Adds a new state to the machine.
 * @param
 * func_ptr: function executed at the state
 * @return
 * s: pointer to new state
 */
State* StateMachine::addState(void(*func_ptr)()){

    State* s = new State();

    s->state_function = func_ptr;
    state_list.push_back(s);
    s->index = state_list.size()-1;

    if(current_state==-1) current_state = 0;

    return s;

}

/*
 * Error function for impossible transitions
 */
void err(int src, int dest){

    std::cout << "Transition from State " << src <<
    "to State " << dest << "unavailable" << std::endl;

}


/*
 * Transition to another state.
 * @param
 * to_trans: pointer to state
 * @return
 * bool: transition occurs or not
 */
bool StateMachine::transition_to(State* to_trans){

    int i = to_trans->index;

    if(i < state_list.size()){

        if(state_list[current_state]->eval_transition(to_trans))
            current_state = i;

        state_list[current_state]->state_function();
        return true;

    }

    err(current_state,i);
    return false;
}

#endif