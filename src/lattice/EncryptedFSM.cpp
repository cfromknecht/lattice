#include <lattice/EncryptedFSM.h>

#include <vector>
#include <map>

namespace lattice {

  EncryptedFSM::EncryptedFSM( size_t lambda, size_t k, const FSM& fsm) :
      _secretKey{new EncryptedFSMSecretKey(lambda, k)} {
    this->preProcess( fsm );
  }

  void EncryptedFSM::preProcess( const FSM& fsm ) {
    auto states = fsm.states();
    auto transitions = fsm.transitions();

    std::map<size_t, PolyRingMatrix*> stateSecretKeys;
    for ( size_t stateID = 1; stateID < states.numStates(); ++stateID ) {
      stateSecretKeys[stateID] = new PolyRingMatrix{1, 1, 
    }

    for ( size_t stateID = 0; stateID < states.numStates(); ++stateID ) {
      auto transition = transitions[stateID];
      if ( stateID != 0 ) {

      }
    }
  }

} // namespace lattice

