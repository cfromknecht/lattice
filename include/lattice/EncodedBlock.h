#ifndef _ENCODED_BLOCK_H_
#define _ENCODED_BLOCK_H_

#include <lattice/PolyRingMatrix.h>

#include <memory>
#include <stdexcept>
#include <string>

namespace lattice {

  class EncodedBlock {
  private:
    PolyRingMatrix* _encodedBit;
    PolyRingMatrix* _encodedTerminalToken;
    PolyRingMatrix* _encodedRejectToken;
    PolyRingMatrix* _encodedAcceptToken;
    PolyRingMatrix* _initToken;
    PolyRingMatrix* _B;

    std::string _marshalledData;
    bool _needsMarshalling = true;

  public:
    EncodedBlock();
    EncodedBlock( const EncodedBlock& other );
    EncodedBlock& operator=( const EncodedBlock& rhs );
    ~EncodedBlock() {}

    std::string marshal();
    void unmarshal( const std::string& rawData );

    PolyRingMatrix* getEncodedBit() const { 
      if ( !_encodedBit )
        throw std::logic_error{"[EncodedBlock]: encoded bit accessed before being set"};
      return new PolyRingMatrix{*_encodedBit};
    }

    PolyRingMatrix* getEncodedTerminalToken() const { 
      if ( !_encodedTerminalToken )
        throw std::logic_error{"[EncodedBlock]: encoded terminal token accessed before being set"};
      return new PolyRingMatrix{*_encodedTerminalToken};
    }

    PolyRingMatrix* getEncodedRejectToken() const { 
      if ( !_encodedRejectToken )
        throw std::logic_error{"[EncodedBlock]: encoded reject token  accessed before being set"};
      return new PolyRingMatrix{*_encodedRejectToken};
    }

    PolyRingMatrix* getEncodedAcceptToken() const { 
      if ( !_encodedAcceptToken )
        throw std::logic_error{"[EncodedBlock]: encoded accept token accessed before being set"};
      return new PolyRingMatrix{*_encodedAcceptToken};
    }

    PolyRingMatrix* getInitToken() const { 
      if ( !_initToken )
        throw std::logic_error{"[EncodedBlock]: init token accessed before being set"};
      return new PolyRingMatrix{*_initToken};
    }

    PolyRingMatrix* getB() const { 
      if ( !_B )
        throw std::logic_error{"[EncodedBlock]: B matrix accessed before being set"};
      return new PolyRingMatrix{*_B};
    }

    void setEncodedBit( PolyRingMatrix* encodedBit );
    void setEncodedTerminalToken( PolyRingMatrix* encodedTerminalToken );
    void setEncodedRejectToken( PolyRingMatrix* encodedRejectToken );
    void setEncodedAcceptToken( PolyRingMatrix* encodedAcceptToken );
    void setInitToken( PolyRingMatrix* initToken );
    void setB( PolyRingMatrix* B );
  };

  typedef std::unique_ptr<EncodedBlock> EncodedBlockPtr;

} // namespace lattice

#endif

