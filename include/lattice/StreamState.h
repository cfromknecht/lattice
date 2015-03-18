#ifndef _STREAM_STATE_
#define _STREAM_STATE_

#include <lattice/Helper.hpp>
#include <lattice/PolyRingMatrix.h>

#include <memory>

namespace lattice {

  class StreamState {
  private:
    StreamState() = delete;

  public:
    PolyRingMatrixPtr prevToken;
    PolyRingMatrixPtr r0;
    PolyRingMatrixPtr r1;
    bool isInitialUse;

    StreamState( bool isInitialUse_ );
    StreamState( const StreamState& other );
    ~StreamState() {}

    StreamState& operator=( const StreamState& other );
    StreamState& operator=( StreamState& other);

  };

  typedef std::unique_ptr<StreamState> StreamStatePtr;

} // namespace  lattice

#endif

