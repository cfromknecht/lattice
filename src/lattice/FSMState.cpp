#include <lattice/FSMState.h>

namespace lattice {

  FSMState::FSMState() : _stateID{0}, _acceptState{false} {}

  /**
   * FSMState Constructor
   * @param size_t stateID - unique identifier for state
   * @param bool acceptState - is this state an accept state
   */
  FSMState::FSMState( size_t stateID_, bool acceptState_ ) : _stateID{stateID_}, 
    _acceptState{acceptState_} {}

  /**
   * Instantiates a new FSMState using an existing FSMState
   * @param other - the FSMState to be copied
   */
  FSMState::FSMState( const FSMState& other ) : _stateID{other.stateID()}, 
    _acceptState{other.acceptState()} {}

  /**
   * Sets an existing FSMState to be identical to an existing FSMState
   * @param rhs - the FSMState to be copied
   * @return - the new FSMState
   */
  FSMState& FSMState::operator=( const FSMState& rhs ) {
    if ( this != &rhs ) {
      _stateID = rhs.stateID();
      _acceptState = rhs.acceptState();
    }
    return *this;
  }

  /**
   * Deconstrutor, no pointers so nothing to do
   */
   FSMState::~FSMState() {}

}

