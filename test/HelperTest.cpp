#include <lattice/Helper.hpp>

#include <gtest/gtest.h>

TEST( HelperTest, makeUnique ) {
  // create new pointer to 42
  auto sizePtr = lattice::make_unique<size_t>( 42 );

  // test that pointer is not null and that value is set to 42
  ASSERT_NE( nullptr, sizePtr );
  ASSERT_EQ( size_t(42), *sizePtr );

  // move ownership to new unique_ptr
  auto newSizePtr = std::move( sizePtr );

  // test that old pointer is null
  ASSERT_EQ( nullptr, sizePtr );

  // test that new pointer is not null, and that value is still 42
  ASSERT_NE( nullptr, newSizePtr );
  ASSERT_EQ( size_t(42), *newSizePtr );
}
