//
// Created by 717lumos on 22. 6. 16.
//
#include <gtest/gtest.h>

TEST(Test_Name_Major, Test_Name_Minor)
{
  constexpr bool evaluation = true;
  EXPECT_EQ(evaluation, true);
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}