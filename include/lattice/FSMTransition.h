#ifndef _LATTICE_FSM_TRANSITION_
#define _LATTICE_FSM_TRANSITION_

#include <cstdlib>

namespace lattice {

  class FSMTransition {
    size_t _nextStateFor0;
    size_t _nextStateFor1;

  public:
    FSMTransition();
    FSMTransition( size_t next0, size_t next1 );
    FSMTransition( const FSMTransition& other );
    FSMTransition& operator=( const FSMTransition& other );
    ~FSMTransition();

    size_t nextStateForSymbol( bool nextSymbol ) const;

    size_t nextStateFor0() const { return _nextStateFor0; }
    size_t nextStateFor1() const { return _nextStateFor1; }
  };

}

#endif

