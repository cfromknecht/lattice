#include <lattice/EncodedBlock.h>

#include <memory>
#include <stdexcept>
#include <string>

namespace lattice {

  EncodedBlock::EncodedBlock() :
      _encodedBit(nullptr), 
      _encodedTerminalToken(nullptr),
      _encodedRejectToken(nullptr),
      _encodedAcceptToken(nullptr),
      _initToken(nullptr),
      _B(nullptr),
      _marshalledData(),
      _needsMarshalling(true) {}

  EncodedBlock::EncodedBlock( const EncodedBlock& other ) :
      _encodedBit(other.getEncodedBit()),
      _encodedTerminalToken(other.getEncodedTerminalToken()),
      _encodedRejectToken(other.getEncodedRejectToken()),
      _encodedAcceptToken(other.getEncodedAcceptToken()),
      _initToken(other.getInitToken()),
      _B(other.getB()),
      _marshalledData(),
      _needsMarshalling(true) {}

  EncodedBlock& EncodedBlock::operator=( const EncodedBlock& rhs ) {
    if ( this != &rhs ) {
      _encodedBit = rhs.getEncodedBit();
      _encodedTerminalToken = rhs.getEncodedTerminalToken();
      _encodedRejectToken = rhs.getEncodedRejectToken();
      _encodedAcceptToken = rhs.getEncodedAcceptToken();
      _initToken = rhs.getInitToken();
      _B = rhs.getB();
      _marshalledData = "";
      _needsMarshalling = true;
    }

    return *this;
  }

  std::string EncodedBlock::marshal() {
    // used cached marshal if its still valid
    if ( !_needsMarshalling ) return _marshalledData;

    // TODO(cfromknecht) build marshalled string
    std::string testData{"test block"};
    _marshalledData = testData;
    _needsMarshalling = false;

    return _marshalledData;
  }

  void EncodedBlock::unmarshal( const std::string& ) {
    // TODO(cfromknecht) parse data
  }


  void EncodedBlock::setEncodedBit( PolyRingMatrix* encodedBit ) {
    _encodedBit = encodedBit;
    _needsMarshalling = true;
  }

  void EncodedBlock::setEncodedTerminalToken( PolyRingMatrix* encodedTerminalToken ) {
    _encodedTerminalToken = encodedTerminalToken;
    _needsMarshalling = true;
  }

  void EncodedBlock::setEncodedRejectToken( PolyRingMatrix* encodedRejectToken ) {
    _encodedRejectToken = encodedRejectToken;
    _needsMarshalling = true;
  }

  void EncodedBlock::setEncodedAcceptToken( PolyRingMatrix* encodedAcceptToken ) {
    _encodedAcceptToken = encodedAcceptToken;
    _needsMarshalling = true;
  }

  void EncodedBlock::setInitToken( PolyRingMatrix* initToken ) {
    _initToken = initToken;
    _needsMarshalling = true;
  }

  void EncodedBlock::setB( PolyRingMatrix* B ) {
    _B = B;
    _needsMarshalling = true;
  }

} // namespace lattice

