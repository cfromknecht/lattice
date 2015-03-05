#include <lattice/EncodedBlock.h>

#include <memory>


namespace lattice {

  EncodedBlock::EncodedBlock( const EncodedBlock& other ) :
      encodedBit{new PolyRingMatrix{*other.encodedBit}},
      encodedTerminalToken{new PolyRingMatrix{*other.encodedTerminalToken}},
      encodedRejectToken{new PolyRingMatrix{*other.encodedRejectToken}},
      encodedAcceptToken{new PolyRingMatrix{*other.encodedAcceptToken}},
      initToken{new PolyRingMatrix{*other.initToken}},
      B{new PolyRingMatrix{*other.B}} {}

} // namespace lattice

