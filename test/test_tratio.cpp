#include "tratio.h"

#include <gtest.h>

TEST(TRatio, can_create_ratio_without_parameters)
{
  // Arrange & Act & Assert
  ASSERT_NO_THROW(TRatio r);
}

TEST(TRatio, can_create_ratio_with_parameter)
{
  // Arrange & Act
  TRatio r(4);

  // Assert
  EXPECT_EQ(4, r.GetNumerator());
}

TEST(TRatio, can_create_ratio_with_another_parameter)
{
  // Arrange & Act
  TRatio r(100500);

  // Assert
  EXPECT_EQ(100500, r.GetNumerator());
}

TEST(TRatio, can_get_denominator)
{
  // Arrange & Act
  TRatio r(1, 3);

  // Assert
  EXPECT_EQ(3, r.GetDenominator());
}

TEST(TRatio, throws_on_zero_denominator)
{
  // Arrange & Act & Assert
  ASSERT_ANY_THROW(TRatio r(1, 0));
}

TEST(TRatio, default_value_is_one)
{
  // Arrange & Act
  TRatio r;

  // Assert
  EXPECT_EQ(1, r.GetNumerator());
  EXPECT_EQ(1, r.GetDenominator());
}
