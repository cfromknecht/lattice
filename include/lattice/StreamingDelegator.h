#ifndef _STREAMING_DELEGATOR_H_
#define _STREAMING_DELEGATOR_H_

#include <lattice/DishonestEvaluatorException.h>
#include <lattice/EncodedFSM.h>
#include <lattice/Helper.hpp>

#include <exception>
#include <map>
#include <sstream>
#include <string>

namespace lattice {

  /**
   * @class StreamingDelegator
   * 
   * Manages the delegation of computation for a specified FSM.  Each
   * StreamingDelegator is responsible for delegating a single function.
   * Multiple data streams can be multiplexed and sent to different evaluators.
   */

  class StreamingDelegator {
  private:

    // FSM encoded with error-correcting transitions and states
    EncodedFSM _encodedFSM;
    // Stores all open data streams to be processed and verified
    std::map<size_t, std::string> _ipAddresses{};

    bool sendBlock( std::string ipAddress, EncodedBlockPtr& encodedBlock );

    /*
    bool writeBlock( Poco::Net::HTTPClientSession& session,
        Poco::Net::HTTPRequest& request, 
        Poco::Net::HTTPResponse&, 
        EncodedBlockPtr& encodedBlock );
    */

    StreamingDelegator() = delete;

  public:

    /**
     * @param lambda size_t - the number of bits of security for the encrypted
     * computation.
     *
     * @param k size_t - log 2 of the modulus for polynomial coefficients
     * @param fsm FSM& - an FSM defining the function to be delegated.
     */
    StreamingDelegator( size_t lambda, size_t k, const FSM& fsm );

    /**
     * Creates a new Stream and appends it to the _streams vector.
     * 
     * @param ipAddress std::string& - IPv4 or IPv6 address string of evaluator
     *
     * @return size_t - the tag referring to the newly created stream
     */
    size_t openStream( const std::string& ipAddress );

    /**
     * Encodes a single bit x for the stream corresponding to the tag.
     *
     * @param tag size_t - tag indicating which stream to append the encrypted
     * bit.
     * @param x bool - the bit to be encrypted.
     * @param isLastBit bool - set to true when x is the last bit of the stream 
     * to be encrypted.
     */
    void encode( size_t tag, bool x, bool isLastBit );

    /**
     * Encodes a string to the stream corresponding to the tag.
     *
     * @param tag size_t - tag indicating which stream to append the encrypted
     * string.
     * @param string std::string& - the bytes to append to the stream
     * @param isLastString bool - indicates whether this is the last string to 
     * be appended
     */
    void encode( size_t tag, const std::string& string, bool isLastString );

    /**
     * Requests the verification and proof from the evaluating entity and
     * returns the result of the computation.
     *
     * @param tag size_t - the tag indicating which stream to evaluate.
     *
     * @return bool - true indicates that the computation was executed honestly 
     * and ended in an accept state.  false indicates that the computation was
     * executed honestly and resulted in a reject state.
     *
     * @throws DishonestEvaluatorException - indicates that neither the accept 
     * or reject proof is returned, client should reconsider the authenticity of
     * the evaluator.
     */
    bool verify( size_t tag );

    void evaluate( size_t tag ) { _encodedFSM.evaluate( tag ); }

    size_t sizeOfTransitions() const { return _encodedFSM.toStringTransitions().length(); }
    size_t sizeOfPublicKey() const { return _encodedFSM.toStringPublicKey().length(); }
    size_t sizeOfSecretKey() const { return _encodedFSM.toStringSecretKey().length(); }
  };

  typedef std::unique_ptr<StreamingDelegator> StreamingDelegatorPtr;

} // namespace lattice

#endif

