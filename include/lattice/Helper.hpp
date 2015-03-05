#ifndef _LATTICE_HELPER_H_
#define _LATTICE_HELPER_H_

#include <memory>

namespace lattice {

  template<typename T, typename ...Args>
  std::unique_ptr<T> make_unique( Args&& ...args ) {
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
  }

  constexpr size_t operator "" _z ( unsigned long long n ) {
    return n;
  }

} // namespace lattice

#endif

