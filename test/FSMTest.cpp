#include <lattice/FSM.h>

#include <gtest/gtest.h>

#include <cstdlib>

TEST( FSMTest, initialization ) {
  auto fsm = lattice::FSM( "fsm/fsm-a.in" );

  ASSERT_TRUE( fsm.validFSM() );
  ASSERT_EQ( fsm.numStates(), size_t(16) );
}
