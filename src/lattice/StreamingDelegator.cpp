#include <lattice/StreamingDelegator.h>

#include <lattice/DishonestEvaluatorException.h>
#include <lattice/EncodedFSM.h>
#include <lattice/Helper.hpp>

#include <exception>
#include <map>
#include <sstream>
#include <string>

namespace lattice {

  StreamingDelegator::StreamingDelegator( size_t lambda, size_t k, 
      const FSM& fsm ) : 
    _encodedFSM(lambda, k, fsm) {}

  size_t StreamingDelegator::openStream( const std::string& ipAddress ) {
    // create stream and record ip address
    auto newTag = _encodedFSM.openStream();
    _ipAddresses[newTag] = ipAddress;

    return newTag;
  }

  void StreamingDelegator::encode( size_t tag, bool x, bool isLastBit ) {
    auto encodedBlock = _encodedFSM.encode( tag, x, isLastBit );
    auto ipAddress = _ipAddresses[tag];
    this->sendBlock( ipAddress, encodedBlock );
  }

  void StreamingDelegator::encode( size_t tag, const std::string& input, bool
      isLastString ) {
    auto inputLength = input.size();
    for ( size_t i = 0; i < inputLength; ++i ) {
      for ( size_t j = 7; j < 8; --j ) {
        std::cout << "." << std::flush;
        bool nextSymbol = (input[i] >> j) & 1;
        if ( !isLastString ) {
          this->encode( tag, nextSymbol, false );
        } else {
          auto isLastBit = (i == inputLength-1) && (j == 0);
          if ( isLastBit ) std::cout << std::endl;
          this->encode( tag, nextSymbol, isLastBit );
        }
      }
    }
  }

  bool StreamingDelegator::verify( size_t tag ) {
    auto ipAddress = _ipAddresses[tag];

    // TODO retrieve computation
//    std::cout << "[StreamingDelegator]: creating fake proof ..." << std::endl;
    auto proof = make_unique<PolyRingMatrix>( 1, 1, 256, 8 );
//    std::cout << "[StreamingDelegator]: getting previous state ..." << std::endl;
    auto prevState = _encodedFSM.streamStateForTag( tag );

    // if proof equals r0 or r1, evaluation was honest.  Otherwise we should not
    // trust the evaluator
    if ( prevState->r0() == *proof ) {
      return false;
    } else if ( prevState->r1() == *proof ) {
      return true;
    } else {
      throw DishonestEvaluatorException{tag};
    }
  }

  bool StreamingDelegator::sendBlock( std::string, EncodedBlockPtr& ) {
    /*
    std::string ipAddress;
    size_t port;

    std::istringstream buffer{fullAddress};
    buffer >> ipAddress >> port;

    std::cout << "ip: " << ipAddress << " port: " << port << std::endl;

    auto uriString = ipAddress.append( "/" );

    // create HTTP POST Request
    auto uri = Poco::URI(uriString);

    Poco::Net::HTTPClientSession session;
    session.setHost( uri.getHost() );
    session.setPort( uri.getPort() );

    Poco::Net::HTTPRequest request;
    request.setMethod( Poco::Net::HTTPRequest::HTTP_POST );
    request.setURI( uriString );
    request.setVersion( Poco::Net::HTTPMessage::HTTP_1_1 );

    Poco::Net::HTTPResponse response;

    // send block to StremingEvaluator, logs to std err on failure
    if ( !writeBlock( session, request, response, encodedBlock ) ) {
      std::cerr << "[StreamingDelegator]: Failed to send block" << std::endl;
      return false;
    }
    */
    return true;
  }

  /*
  bool StreamingDelegator::writeBlock( Poco::Net::HTTPClientSession& session,
      Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response, 
      EncodedBlockPtr& encodedBlock ) {
    // set request's content length
    std::string requestBody = encodedBlock->marshal();
    request.setContentLength( requestBody.length() );

    // send request and write data
    std::ostream& outputStream = session.sendRequest( request );
    outputStream << requestBody;

    // write request to std out
    request.write(std::cout);

    // receive input and write to std out
    std::istream& inputStream = session.receiveResponse( response );
    std::cout << inputStream.rdbuf() << std::endl;

    return true;
  }
  */

} // namespace lattice

