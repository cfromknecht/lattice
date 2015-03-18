#ifndef _ENCODED_BLOCK_H_
#define _ENCODED_BLOCK_H_

#include <lattice/PolyRingMatrix.h>

#include <memory>

namespace lattice {

  class EncodedBlock {
  public:
    PolyRingMatrixPtr encodedBit;
    PolyRingMatrixPtr encodedTerminalToken;
    PolyRingMatrixPtr encodedRejectToken;
    PolyRingMatrixPtr encodedAcceptToken;
    PolyRingMatrixPtr initToken;
    PolyRingMatrixPtr B;

    EncodedBlock();
    EncodedBlock( const EncodedBlock& other );
    ~EncodedBlock() {}
  };

  typedef std::unique_ptr<EncodedBlock> EncodedBlockPtr;

} // namespace lattice

#endif

