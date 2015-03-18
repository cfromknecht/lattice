#include <lattice/DishonestEvaluatorException.h>

namespace lattice {

  DishonestEvaluatorException::DishonestEvaluatorException( size_t tag ) :
      std::runtime_error{"[DishonestEvaluatorException]"},
      _tag( tag ) {}

} // namespace lattice

