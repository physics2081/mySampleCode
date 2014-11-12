//////////////////////////////////////////////////////////////////////
// Developer: Nitin
// File name : BasicFsmTest.cpp
// Purpose : To test implementation of FSM by BasicFsmT Class.
//          This includes BasicFsmT as public base class to implement a
//          sample Telephone state machine.
// 
///////////////////////////////////////////////////////////////////////

#include "BasicFsmT.h"
#include <algorithm> // for std::find( ) etc.
#include <iostream>
#include <sstream>
#include <stdexcept>


///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
/////// Test Functions for BasicFsm Class ////////////////////

namespace TelephoneEnumsT
{

// List of Valid Sate in the Stmc
const string S_Idle = "S_Idle";
const string S_DIGIT_COLLECTION = "S_DigitCollection";
const string S_ESTABLISHING = "S_Establishing";
const string S_RINGING_OG = "S_RingingOG";
const string S_RINGING_IC = "S_RingingIC";
const string S_CALL_ESTABLISHED = "S_Established";
const string S_CALL_FE_TERMINATED  = "S_FETerminated";


// List of Valid Events in the Stmc
const string E_ONHOOK = "E_Onhook";
const string E_OFFOOK = "E_Offhook";
const string E_DIGIT_COLLECT = "E_DigitCollect";
const string E_DIGIT_COLLECT_COMPLETE = "E_DigitCollectComplete";
const string E_OG_RING = "E_OGRing";
const string E_REMOTE_ANSWER = "E_RemoteAnswer";
const string E_IC_RING = "E_ICRing";
const string E_TIMEOUT = "E_Timeout";

}; // end namespace declaration

class Telephone : public BasicFsm
{
private :
    string digitsCollected;
    string myNumber;
    time_t  call_st_time;
    time_t  call_end_time;


public :
    Telephone();
    Telephone(string myNumber);
    ~Telephone();
    void DispDigitsCollected()
    {
        cout << "Digits collected so far = " << digitsCollected << endl;
    }

    friend int OffHookAtIdle(BasicFsm* pFsm, string event, int info);
    friend int DigitCollect(BasicFsm* pFsm, string event, int info);
    friend int DigitCollectComplete(BasicFsm* pFsm, string event, int info);
    friend int TimeoutAtDigitCollection(BasicFsm* pFsm, string event, int info);
    friend int OffHookAtEstablished(BasicFsm* pFsm, string event, int info);
    /// This state-event processing list of functions are not complete

    void InitFsm(); // This will init the fsm functions => will add State,Event,Method => It will tell that for which state,event pair which function should be called
}; // end of Telephone class declaration

using namespace std;
using namespace TelephoneEnumsT;

Telephone::Telephone()
{
    digitsCollected.clear();
    myNumber.clear();
    call_st_time = 0; 
    call_end_time = 0;
}

Telephone::Telephone(string myNumber)
{
    digitsCollected.clear();
    myNumber.assign(myNumber);
    call_st_time = 0; 
    call_end_time = 0;
}

Telephone::~Telephone()
{

}

int OffHookAtIdle(BasicFsm* pFsm, string event, int info)
{
    stringstream logMsg;

  try {
    Telephone* pPhone = static_cast <Telephone*> (pFsm);
    logMsg << "In Function OffHookAtIdle() " << " At State "
           << pFsm->GetState() << " For Event " << event << endl;

        cout << logMsg.str() << endl;
    
	// Do the required Processing here

    pPhone->digitsCollected.clear();

    // Do state transition and do some book keeping
    pPhone->TransitionToState(TelephoneEnumsT::S_DIGIT_COLLECTION);
    pPhone->SetPreviousEvent(event);
  } // end try
  catch (exception& Error) {
    stringstream logErr;
    logErr << "Exception at OffHookAtIdle(), Error : " << Error.what();

  }
    return(0);
}

int DigitCollect(BasicFsm* pFsm, string event, int info)
{
    stringstream logMsg;

  try 
  {
    Telephone* pPhone = static_cast <Telephone*> (pFsm);
    logMsg << "In Function DigitCollect() " << " At State "
           << pFsm->GetState() << " For Event " << event 
           << " adding digit to dialed number " << info << endl;

        cout << logMsg.str() << endl;

    // Do the required Processing here

    char cinfo[8];
    sprintf(cinfo,"%d",info);
    pPhone->digitsCollected.append((const char *) (&cinfo), (size_t)(1));

    // Do state transition and do some book keeping
    pPhone->SetPreviousEvent(event);
  } // end try
  catch (exception& Error) {
    stringstream logErr;
    logErr << "Exception at DigitCollect(), Error : " << Error.what();

  }
    return(0);
}

int DigitCollectComplete(BasicFsm* pFsm, string event, int info)
{
    // Do the required Processing
    return(0);
}

int TimeoutAtDigitCollection(BasicFsm* pFsm, string event, int info)
{
    // Do the required Processing
    return(0);
}

int OffHookAtEstablished(BasicFsm* pFsm, string event, int info)
{

    // Do the required Processing
    return(0);
}

void  Telephone::InitFsm()
{
    AddStateEventMethod(TelephoneEnumsT::S_Idle, 
                        TelephoneEnumsT::E_OFFOOK, 
                        &(OffHookAtIdle));

    AddStateEventMethod(TelephoneEnumsT::S_DIGIT_COLLECTION, 
                        TelephoneEnumsT::E_DIGIT_COLLECT, 
                        &(DigitCollect));

    // Add State - Event functions so forth...
}

int main()
{

    int fsmStatus; 
    Telephone myPhone1("1112223333");
    myPhone1.InitFsm();

    // Test some event handlers
    myPhone1.TransitionToState(S_Idle);
    fsmStatus = myPhone1.Fsm(E_OFFOOK, 0);
    fsmStatus = myPhone1.Fsm(E_DIGIT_COLLECT, 9);

    Telephone myPhone2("2223331234");
    myPhone2.InitFsm();

    // Test some event handlers
    myPhone2.TransitionToState(S_Idle);
    fsmStatus = myPhone2.Fsm(E_OFFOOK, 1);
    fsmStatus = myPhone2.Fsm(E_DIGIT_COLLECT, 2);

    myPhone1.DispDigitsCollected();
    myPhone2.DispDigitsCollected();

    // Authors comment: try to modify the base class, which can still be
    // inherited by any FSM implementing classes
    // where you just need to do Telephone::InitFsm();
    // instead of doing myPhone1.InitFsm(); and myPhone2.InitFsm(); ...

}
/////// End File : BasicFsmTest.cpp  //////////////////////////////////////////
