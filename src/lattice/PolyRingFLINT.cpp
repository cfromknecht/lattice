#include <lattice/PolyRingFLINT.h>

namespace lattice {

  PolyRingFLINT PolyRingFLINT::operator+( const PolyRingFLINT& rhs ) const {
    auto lhs = new PolyRingFLINT{*this};
    lhs->addAssign( rhs );
    return *lhs;
  }

  PolyRingFLINT PolyRingFLINT::operator-( const PolyRingFLINT& rhs ) const {
    auto lhs = new PolyRingFLINT{*this};
    lhs->subtractAssign( rhs );
    return *lhs;
  }

  PolyRingFLINT PolyRingFLINT::operator*( const PolyRingFLINT& rhs ) const {
    auto lhs = new PolyRingFLINT{*this};
    lhs->multiplyAssign( rhs );
    return *lhs;
  }

  void PolyRingFLINT::assign( const PolyRingBase& rhs ) {
    assignParameters( rhs );
    assignRingParameters( dynamic_cast<const PolyRingFLINT&>( rhs ) );
  }

  void PolyRingFLINT::addAssign( const PolyRingBase& rhs ) {
    assignParameters( rhs );
    assignRingParameters( dynamic_cast<const PolyRingFLINT&>( rhs ) );
  }

  void PolyRingFLINT::subtractAssign( const PolyRingBase& rhs ) {
    assignParameters( rhs );
    assignRingParameters( dynamic_cast<const PolyRingFLINT&>( rhs ) );
  }

  void PolyRingFLINT::multiplyAssign( const PolyRingBase& rhs ) {
    assignParameters( rhs );
    assignRingParameters( dynamic_cast<const PolyRingFLINT&>( rhs ) );
  }

}

