#ifndef _LATTICE_FSM_STATE_
#define _LATTICE_FSM_STATE_

#include <cstdlib>

namespace lattice {

  class FSMState {
    size_t _stateID;
    bool _acceptState;

  public:
    FSMState();
    FSMState( size_t stateID, bool acceptState );
    FSMState( const FSMState& other );
    FSMState& operator=( const FSMState& rhs );
    ~FSMState();

    bool acceptState() const { return _acceptState; }
    size_t stateID() const { return _stateID; }
  };

}

#endif

