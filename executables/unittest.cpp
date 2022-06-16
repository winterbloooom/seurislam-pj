//
// Created by 717lumos on 22. 6. 16.
//
#include <gtest/gtest.h>
#include "system/slam_assembly.h"

class AssemblyTest : public ::testing::Test {
public:
  // AssemblyTest();
  proslam::ParameterCollection* parameters = new proslam::ParameterCollection();
  // proslam::SLAMAssembly slam_system = proslam::SLAMAssembly(parameters);
  // proslam::ParameterCollection* parameters;
  // proslam::SLAMAssembly slam_system;
  void set_config();
  void start_system();
  std::shared_ptr<std::thread> slam_thread = nullptr;
  
};

// AssemblyTest::AssemblyTest()
// {
//   // proslam::ParameterCollection* parameters = new proslam::ParameterCollection();
//   // proslam::SLAMAssembly slam_system = proslam::SLAMAssembly(parameters);
//   void set_config();
//   // void start_system();
// }

void AssemblyTest::set_config()
{
  parameters->command_line_parameters->configuration_file_name = "/root/catkin_ws/src/srrg_proslam/configurations/configuration_kitti.yaml";
  parameters->parseFromFile(parameters->command_line_parameters->configuration_file_name);
  parameters->command_line_parameters->option_use_gui = true;
}

void AssemblyTest::start_system()
{
  proslam::SLAMAssembly slam_system(parameters);
  slam_system.loadCamerasFromMessageFile();
}

TEST_F(AssemblyTest, GetConfigFile)
{
  set_config();
  ASSERT_NO_THROW(start_system());

  // ASSERT_NO_THROW(parameters->parseFromFile(parameters->command_line_parameters->configuration_file_name));
}

// TEST(Test_Name_Major, Test_Name_Minor)
// {
//   constexpr bool evaluation = true;
//   EXPECT_EQ(evaluation, true);
// }

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}