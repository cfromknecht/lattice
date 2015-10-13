#ifndef _STREAM_STATE_
#define _STREAM_STATE_

#include <lattice/Helper.hpp>
#include <lattice/PolyRingMatrix.h>

#include <cassert>
#include <memory>

namespace lattice {

  class StreamState {
  private:
    PolyRingMatrix* _prevToken;
    PolyRingMatrix* _r0;
    PolyRingMatrix* _r1;
    bool _isInitialUse;

    StreamState() = delete;

  public:
    StreamState( bool isInitialUse );
    StreamState( const StreamState& other );
    ~StreamState() {}

    StreamState& operator=( const StreamState& other );
    StreamState& operator=( StreamState& other);

    bool isInitialUse() const { return _isInitialUse; }

    PolyRingMatrix prevToken() const { 
      assert( _prevToken != nullptr );
      return PolyRingMatrix( *_prevToken ); 
    }
      
    PolyRingMatrix r0() const { 
      assert( _r0 != nullptr );
      return PolyRingMatrix( *_r0 ); 
    }
      
    PolyRingMatrix r1() const { 
      assert( _r1 != nullptr );
      return PolyRingMatrix( *_r1 ); 
    }


    void setPrevToken( const PolyRingMatrix& newPrevToken );
    void setR0( const PolyRingMatrix& newR0 );
    void setR1( const PolyRingMatrix& newR1 );
  };

  typedef std::unique_ptr<StreamState> StreamStatePtr;

} // namespace  lattice

#endif

