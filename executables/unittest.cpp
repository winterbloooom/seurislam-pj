//
// Created by 717lumos on 22. 6. 16.
//
#include <gtest/gtest.h>
#include "system/slam_assembly.h"

class AssemblyTest : public ::testing::Test {
public:
  void SetUp() override;
  
  proslam::ParameterCollection* parameters;
  // void app_main();
};

void AssemblyTest::SetUp()
{
  cv::setUseOptimized(true);
  parameters = new proslam::ParameterCollection();
  parameters->command_line_parameters->configuration_file_name = "/root/catkin_ws/src/srrg_proslam/configurations/configuration_kitti.yaml";
  // parameters->command_line_parameters->option_use_gui = true;
  parameters->parseFromFile(parameters->command_line_parameters->configuration_file_name);
}

// void AssemblyTest::app_main()
// {
//   proslam::SLAMAssembly slam_system(parameters);
//   std::shared_ptr<std::thread> slam_thread = nullptr;
// }

// TEST_F(AssemblyTest, ParseParam)
// {
//   ASSERT_NO_THROW(parameters->parseFromFile(parameters->command_line_parameters->configuration_file_name));
// }

// TEST_F(AssemblyTest, CameraLoad)
// {
//   proslam::SLAMAssembly slam_system(parameters);
//   ASSERT_NO_THROW(slam_system.loadCamerasFromMessageFile());
// }

TEST_F(AssemblyTest, PlaybackTest)
{
  proslam::SLAMAssembly slam_system(parameters);
  std::shared_ptr<std::thread> slam_thread = nullptr;
  
  slam_system.loadCamerasFromMessageFile();

  cv::setNumThreads(0);

  // slam_system.playbackMessageFileOnce();

  ASSERT_NO_THROW(slam_system.playbackMessageFileOnce());
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}