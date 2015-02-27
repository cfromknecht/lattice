#ifndef _STREAMING_DELEGATOR_H_
#define _STREAMING_DELEGATOR_H_

#include <exception>
#include <string>
#include <stringstream>
#include <vector>

namespace lattice {

  class StreamingDelegator {
  private:

    // FSM encoded with error-correcting transitions and states
    const EncryptedFSM& _encryptedFSM;
    // Stores all open data streams to be processed and verified
    const std::vector<Stream> _streams{};

    StreamingDelegator() = delete;

  public:

    /**
     * @param lambda size_t - the number of bits of security for the encrypted
     * computation.
     *
     * @param k size_t - log 2 of the modulus for polynomial coefficients
     *
     * @param fsm FSM& - an FSM defining the function to be delegated.
     */
    StreamingDelegator( size_t lambda, size_t k, const FSM& fsm );

    /**
     * Creates a new Stream and appends it to the _streams vector.
     *
     * @return size_t - the tag referring to the newly created stream
     */
    size_t openStream();

    /**
     * Encodes a single bit x for the stream corresponding to tag.
     *
     * @param tag size_t - tag indicating which stream to append the encrypted
     * bit.
     *
     * @param x bool - the bit to be encrypted.
     *
     * @param isLastBit bool - set to true when x is the last bit of the stream 
     * to be encrypted.
     */
    void encode( size_t tag, bool x, bool isLastBit );

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
  };

  /**
   * Exception to be thrown when a StreamingEvaluator returns an invalid proof.
   * Signals that the evaluator's authenticity may need reconsidering.
   *
   * @param tag size_t - the tag indicating which stream's evaluator is
   * dishonest.
   */
  class DishonestEvaluatorException: public std::runtime_error {
  private:
    const size_t _tag;
    DishonestEvaluatorException() = delete;

  public:
    DishonestEvaluatorException( size_t tag ) : _tag{tag} {}

    virtual char const* what() const throw() {
      std::stringstream ss;
      ss << "The StreamingEvaluator for tag " << _tag << " returned an invalid"
            << " proof and may not be honest.";
      return ss.str();
    }
  };

} // namespace lattice

#endif

