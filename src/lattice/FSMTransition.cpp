#include <lattice/FSMTransition.h>

namespace lattice {

  FSMTransition::FSMTransition() : _nextStateFor0{0}, _nextStateFor1{0} {}

  /**
   * Instantiates an FSMTransition given the two possible subsequent states
   * @param size_t next0 - next state if symbol is 0
   * @param size_t next1 - next state if symbol is 1
   */
  FSMTransition::FSMTransition( size_t next0, size_t next1 ) : 
    _nextStateFor0{next0}, _nextStateFor1{next1} {}

  /**
   * Instantiates an FSMTransition given an existing FSMTransition
   * @param FSMTransition other - the FSMTransition to be copied
   */
  FSMTransition::FSMTransition( const FSMTransition& other ) : 
    _nextStateFor0{other.nextStateFor0()}, 
    _nextStateFor1{other.nextStateFor1()} {}

  /**
   * Sets an existing FSMTransition to be identical to an existing FSMTransition
   * @param FSMTransition rhs - the FSMTransition to be copied
   */
  FSMTransition& FSMTransition::operator=( const FSMTransition& rhs ) {
    if ( this != &rhs ) {
      _nextStateFor0 = rhs.nextStateFor0();
      _nextStateFor1 = rhs.nextStateFor1();
    }
    return *this;
  }

  /**
   * Destroys an FSMTransition, stubbed in case we add pointer member variables
   */
  FSMTransition::~FSMTransition() {}

  /**
   * Returns the subsequent state given a binary input symbol
   * @param bool nextSymbol - next symbol of the bit stream
   * @return - the stateID of the next 
   */
  size_t FSMTransition::nextStateForSymbol( bool nextSymbol ) const {
    return nextSymbol == 0 ? _nextStateFor0 : _nextStateFor1;
  }
  
}

