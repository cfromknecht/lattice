#include <lattice/StreamingDelegator.h>

#include <string>
#include <map>

namespace lattice {

  StreamingDelegator::StreamingDelegator( size_t lambda, size_t k, 
      const FSM& fsm ) : 
      _encryptedFSM{new EncryptedFSM(lambda, k, fsm)} {}

  size_t StreamingDelegator::openStream( const std::string ipAddress ) {
    auto newTag = _encryptedFSM.openStream();
    _ipAddresses[newTag] = ipAddress;
    return newTag;
  }

  void StreamingDelegator::encode( size_t tag, bool x, bool isLastBit ) {
    auto encodedBlock = _encryptedFSM.encode( tag, x, isLastBit );
    auto ipAddress = _ipAddresses[tag];
    // TODO send block to ipAddress
  }

  bool StreamingDelegator::verify( size_t tag ) {
    auto ipAddress = _ipAddresses[tag];

    // TODO retrieve computation

    auto proof;
    auto prevState = _previousStates[tag];

    if ( prevState.r0 == proof ) {
      return false;
    } else if ( prevState.r1 == proof ) {
      return true;
    } else {
      throw DishonestEvaluatorException{tag};
    }
  }

} // namespace lattice

