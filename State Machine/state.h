/*
*
*   STATE LIBRARY
*     @author: github/berruk
*
*
*/

#include "cpplist.h"

#ifndef STATE_H
#define STATE_H

/*
 * Represents a transition between two states
 * event_function : function occuring with the transition
 * to_transition : index of destined transition
 */
struct Transition{

  void (*event_function)();
  int to_transition;

};

/*
 * Represents a state in the State Machine.
 * transitions: List of pointer to possible transitions
 * index: index of state
 * state_function: pointer to states function
 */
class State{
    
    public:
    State();
    ~State();

    void add_transition(void (*event_function)(), State* to_transition);
    bool eval_transition(State* to_transition);
    
    List<struct Transition*> transitions;   
	  int index;
    void (*state_function)();

    

};


State::State(){

  transitions = *(new List<struct Transition*>);

};

State::~State(){};

/*
 * Adds a transition struct to the transitions List of the state
 * @param
 * event_function: address of transition function
 * to_transition: destined state
 */
void State::add_transition(void (*event_function)(), State* to_trans){

  struct Transition* tr = new Transition{
      event_function, 
      to_trans->index
      };

  transitions.push_back(tr);

}


/*
 * Evaluates if a transition is possible or not.
 * @param
 * to_trans: state to transition
 * @return
 * bool: transition occurs or not
 */

bool State::eval_transition(State* to_trans){
  

  for(int i=0; i<transitions.size(); i++)

      if(transitions[i]->to_transition == to_trans->index){
        
        transitions[i]->event_function();
        return true;

      }

    
  return false;

}

#endif