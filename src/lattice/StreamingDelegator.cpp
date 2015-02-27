#include <lattice/StreamingDelegator.h>

#include <string>
#include <vector>

namespace lattice {

  StreamingDelegator::StreamingDelegator( size_t lambda, size_t k, 
      const FSM& fsm ) : _encryptedFSM{new EncryptedFSM(lambda, k, fsm)} {}

  size_t StreamingDelegator::openStream() {
    return 0
  }

  void StreamingDelegator::encode( size_t tag, bool x, bool isLastBit ) {
    
  }

  bool StreamingDelegator::verify( size_t tag ) {
    return true;
  }

} // namespace lattice

