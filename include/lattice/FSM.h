#ifndef _LATTICE_FSM_
#define _LATTICE_FSM_

#include <lattice/FSMState.h>
#include <lattice/FSMTransition.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <iosfwd>

namespace lattice {

  class FSM {
    std::map<size_t, FSMState> _states;
    std::map<size_t, FSMTransition> _transitions;
    size_t _currentState;
    size_t _numStates;

  public:
    FSM();
    FSM( const FSM& other );
    FSM& operator=( const FSM& rhs );
    ~FSM();

    // running FSM
    void reset();
    void applyTransition( bool nextSymbol );
    bool isInAcceptState();
    size_t readState();

    bool buildFSMFromFile( const std::string& filename );

  protected:
    // building FSM
    void addState( size_t stateID, bool acceptState );
    void addTransition( size_t fromState, size_t next0, size_t next1 );

    // validation and optimization
    bool validFSM();
    size_t hopcroftOptimization();
    
    std::map<size_t, FSMState> states() const { return _states; }
    std::map<size_t, FSMTransition> transitions() const { return _transitions; }
    size_t currentState() const { return _currentState; }
    size_t numStates() const { return _numStates; }
  };

}

#endif
