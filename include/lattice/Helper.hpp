#ifndef _LATTICE_HELPER_H_
#define _LATTICE_HELPER_H_

#include <iostream>
#include <memory>

namespace lattice {

  template<typename T, typename ...Args>
  std::unique_ptr<T> make_unique( Args&& ...args ) {
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
  }

  constexpr size_t operator "" _z ( unsigned long long n ) {
    return n;
  }

  static inline void log( const std::string& message ) {
    std::cout << message << std::endl;
  }

} // namespace lattice

#endif

