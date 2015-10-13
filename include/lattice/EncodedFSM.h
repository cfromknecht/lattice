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
#include <string>
#include <vector>

namespace lattice {

  class EncodedFSM {
  private:

    std::vector<PolyRingMatrixPtr> _transitions{};
    std::vector<PolyRingMatrixPtr> _acceptTransitions{};
    std::vector<PolyRingMatrixPtr> _rejectTransitions{};
    std::map<size_t, StreamStatePtr> _streamStates{};
    EncodedFSMSecretKeyPtr _secretKeyPtr;
    size_t _currentTag;

    EncodedFSM() = delete;

    void preProcess( const FSM& fsm );
  public:

    EncodedFSM( size_t lambda, size_t k, const FSM& fsm );

    size_t openStream();
    EncodedBlockPtr encode( size_t tag, bool x, bool isLastBit );

    StreamStatePtr streamStateForTag( size_t tag );

    std::string toString() const;
    std::string toStringPublicKey() const;
    std::string toStringSecretKey() const;
    std::string toStringTransitions() const;

    void evaluate( size_t tag );
  };
 
} // namespace lattice

#endif

