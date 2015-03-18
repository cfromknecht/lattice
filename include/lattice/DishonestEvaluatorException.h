#ifndef _LATTICE_DISHONEST_EVALUATOR_EXCEPTION_H_
#define _LATTICE_DISHONEST_EVALUATOR_EXCEPTION_H_

#include <sstream>
#include <stdexcept>
#include <string>

namespace lattice {

  /**
   * Exception to be thrown when a StreamingEvaluator returns an invalid proof.
   * Signals that the evaluator's authenticity may need reconsidering.
   *
   * @param tag size_t - the tag indicating which stream's evaluator is
   * dishonest.
   */
  class DishonestEvaluatorException: public std::runtime_error {
  private:
    size_t _tag;
    
    DishonestEvaluatorException() = delete;

  public:
    DishonestEvaluatorException( size_t tag );

    virtual const char* what() const throw () {
      std::stringstream ss;
      ss << "[DishonestEvaluatorException]: The StreamingEvaluator for tag " 
         << _tag << " returned an invalid proof and may not be honest.";
      return ss.str().c_str();
    }
  };

} // namespace lattice 

#endif 

