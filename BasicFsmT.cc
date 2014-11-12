//////////////////////////////////////////////////////////////////////
// Developer : Nitin
// File name : BasicFsmT.cpp
// Purpose : To define BasicFsmT Class methods. This class to be inherited
//            by any class which would like to implement FSM
///////////////////////////////////////////////////////////////////////
#include "BasicFsmT.h"
#include <algorithm> // for std::find( ) etc.
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <stdlib.h>

//TODO: I think default constructor(below) is not required.
/// Description : Default Constructor, called by derrived classes object
/// @param[in] 
/// @returns 
BasicFsm::BasicFsm()
{
    m_statesVec.clear();
    m_eventsVec.clear();
    m_fsmStateStr.clear();
    m_fsmPrevEventStr.clear();
    m_fsmPrevStateStr.clear();
    m_stateEventToMethodMap.clear();
}

/// Description : Constructor, with initial state to setup.
///             Need expicit call by derrived classes constructor.
/// @param[in] 
/// @returns 
BasicFsm::BasicFsm(string initialState)
{
    m_statesVec.clear();
    m_eventsVec.clear();
    m_fsmStateStr.clear();
    m_fsmPrevEventStr.clear();
    m_fsmPrevStateStr.clear();
    m_stateEventToMethodMap.clear();

    m_statesVec.push_back(initialState);
    m_fsmStateStr = initialState;
}

/// Description : Destructor, this can be overrided by derrived class's destructor
///               No special cleanup is needed.. 
/// @param[in] 
/// @returns 
BasicFsm::~BasicFsm()
{
//TODO: write here clean up code which will free all memory(if allocated at run time)
}

/// Description : Add a state to be handled by the fsm
///     
/// @param[in] : state to be handled by the fsm
/// @returns 
int BasicFsm::AddState(string state)
{
    vector<string>::iterator itr;
    itr = find(m_statesVec.begin(), m_statesVec.end(), state);
    if (itr == m_statesVec.end())
    { 
      m_statesVec.push_back(state);
    }
    // else state is already available
}

/// Description : Store the address of Method/function to be called
///    for the specified state and event 
/// @param[in] : state - at which the specified Method is applicable.
/// @param[in] : event - for which the specified Method is applicable.
/// @param[in] : pFunc - Address of the Method to be called for the
///                      specified state and event. 
/// @returns 
int BasicFsm::AddStateEventMethod(string state, string event, pFsmMethodT pFunc)
{
    string stateNEvent;

    vector<string>::iterator itr;
    itr = find(m_statesVec.begin(), m_statesVec.end(), state);
    if (itr == m_statesVec.end())
    { 
      m_statesVec.push_back(state);
    }
    // else state is already available

    itr = find(m_eventsVec.begin(), m_eventsVec.end(), state);
    if (itr == m_eventsVec.end())
    { 
      m_eventsVec.push_back(event);
    }
    // else state is already available

    // Add the function pointer to be called for the specified state-event pair
    stateNEvent = state + event;
    m_stateEventToMethodMap[stateNEvent] = pFunc;

}

/// Description : Get the current state of the fsm
/// @param[in] : 
/// @returns 
string BasicFsm::GetState()
{
    return (m_fsmStateStr);
}

/// Description :  Change fsm state to the specified state.
/// @param[in] 
/// @returns 
int BasicFsm::TransitionToState(string state) 
{
    vector<string>::iterator itr;
    itr = find(m_statesVec.begin(), m_statesVec.end(), state);
    if (itr != m_statesVec.end())
    { // transition to state is a valid state
      m_fsmPrevStateStr = m_fsmStateStr;
      m_fsmStateStr = state; 
    }
    // else transition to state is not valid 

}

/// Description :  set fsm processed event to the specified event.
/// @param[in] 
/// @returns 
int BasicFsm::SetPreviousEvent(string event) 
{
    vector<string>::iterator itr;
    itr = find(m_eventsVec.begin(), m_eventsVec.end(), event);
    if (itr != m_eventsVec.end())
    { // transition to event is a valid event
      m_fsmPrevEventStr = event;
    }
    // else event is not valid 

}

/// Description :  Calls the Method specified for the specified state
///                event
/// @param[in] event - The event to be processed 
/// @param[in] info  - Additional info needed for the method to process. 
/// @returns   -1    - If specfied state or event is in valid, or
///                    no fsm function is defined for that state+event pair.  
int  BasicFsm::Fsm(string event, int info)
{
    pFsmMethodT pFunc;
    int retStatus;
    string state, stateNEvent;

  try 
  {
    state = GetState();
    stateNEvent = state + event;
    map<string, pFsmMethodT>::iterator itr = m_stateEventToMethodMap.find(stateNEvent);

    // validate state, event and event handler
    if (itr == m_stateEventToMethodMap.end())
    {
        return(-1);
    }
    pFunc = itr->second; // get pointer to the function to be executed.
    // retStatus = (this->*(pFunc))(this, event, info); 
    retStatus = (*(pFunc))(this, event, info); 

    SetPreviousEvent(event); 
    return(retStatus);

  } // end try
  catch(exception& Error) {
    stringstream logErr;
    logErr << "Exception at BasicFsm::fsm, Error : " << Error.what();
  } 

}
/////////// End File : BasicFsmT.cpp ////////////////////////////////
