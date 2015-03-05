#ifndef _ENCODED_FSM_H_
#define _ENCODED_FSM_H_

#include <lattice/EncodedBlock.h>
#include <lattice/EncodedFSMSecretKey.h>
#include <lattice/FSM.h>
#include <lattice/GTrapdoor.h>
#include <lattice/Helper.hpp>
#include <lattice/PolyRingMatrix.h>
#include <lattice/StreamState.h>

#include <map>
#include <memory>
#include <vector>

namespace lattice {

  class EncodedFSM {
  private:

    std::vector<PolyRingMatrix> _transitions{};
    std::vector<PolyRingMatrix> _acceptTransitions{};
    std::vector<PolyRingMatrix> _rejectTransitions{};
    std::map<size_t, StreamState> _streamStates{};
    EncodedFSMSecretKeyPtr _secretKeyPtr;
    size_t _currentTag = 0;

    EncodedFSM() = delete;

    void preProcess( const FSM& fsm );
  public:

    EncodedFSM( size_t lambda, size_t k, const FSM& fsm );

    size_t openStream();
    EncodedBlockPtr encode( size_t tag, bool x, bool isLastBit );
  };
 
} // namespace lattice

#endif

