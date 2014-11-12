//////////////////////////////////////////////////////////////////////
// File name : BasicFsmT.h
// Purpose : To define simple FSM implementation base class. 
//            This class to be inherited
//            by any class which would like to implement FSM
///////////////////////////////////////////////////////////////////////
#ifndef _BasicFsmT_h
#define _BasicFsmT_h

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include<stdio.h>

using namespace std;

class BasicFsm;
class onlyFunPtr
{
	virtual int func (BasicFsm* pFSM, string event, int info)
	{
		cout<<"onlyFunPtr::func -> I must not be called, error!!!!\n";
	}
};

class BasicFsm
{
 public :
    BasicFsm(); // Default Constructor, //TODO: I think its not required and I can remove it
    BasicFsm(string initialState);
    virtual ~BasicFsm();

    // StateMachine Method prototype, this type of function pointer will be given by all apps by calling AddStateEventMethod(....)
    typedef int (*pFsmMethodT) (BasicFsm* pFSM, string event, int info);
	
	typedef int (onlyFunPtr::*pFsmMethodT2) (BasicFsm* pFSM, string event, int info);

	//Add a state to be handled by the fsm
    virtual int AddState(string state);
	
	//Store the address of Method/function to be called for the specified state and event 
    virtual int AddStateEventMethod(string state, string event, pFsmMethodT);
	
	//Get the current state of the fsm
    virtual string GetState();

	//Calls the Method specified for the specified state event, it will get current state and then will call function for currentState+event.
    virtual int Fsm(string event, int info);

	//Change fsm state to the specified state(it should be a valid state i.e. stored in vector m_statesVec).
    virtual int TransitionToState(string state);
	
	//set fsm processed event to the specified event(it should be a valid event i.e. stored in vector m_eventsVec).
    virtual int SetPreviousEvent(string event); 


 protected :

    vector<string> m_statesVec; // all valid states list in the  fsm
    vector<string> m_eventsVec; // all valid events list in the  fsm
    string m_fsmStateStr;      // current state of the state fsm
    string m_fsmPrevEventStr;  // the last event processed by the fsm 
    string m_fsmPrevStateStr;  // the previous state of fsm 

    // the key is state and event strings concatanated together
     map<string, pFsmMethodT> m_stateEventToMethodMap;
	 map<string, pFsmMethodT2> m_stateEventToMethodMap2;


};

#endif // _BasicFsmT_h
////////////// End File  : BasicFsmT.h  ///////////////////////////////
