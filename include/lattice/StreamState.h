#ifndef _STREAM_STATE_
#define _STREAM_STATE_

namespace lattice {

  class StreamState {
  private:
    StreamState() = delete;
  public:

    PolyRingMatrixPtr prevToken;
    PolyRingMatrixPtr r0;
    PolyRingMatrixPtr r1;
    bool isInitialUse;

    StreamState( bool isInitialUse );
    StreamState( const StreamState& other );
    ~StreamState() {}

    StreamState& operator=( const StreamState& other );
    StreamState& operator=( StreamState& other);

  };

} // namespace  lattice

#endif

