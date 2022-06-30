//
// Created by 717lumos on 22. 6. 16.
//
#include <gtest/gtest.h>
#include "system/slam_assembly.h"
#include "types/camera.h"

class AssemblyTest : public ::testing::Test {
public:
  void SetUp() override;
  
  proslam::ParameterCollection* parameters;
  proslam::SLAMAssembly slam_system;
  
};

void AssemblyTest::SetUp()
{
  cv::setUseOptimized(true);
  parameters = new proslam::ParameterCollection();
  parameters->command_line_parameters->configuration_file_name = "/root/catkin_ws/src/srrg_proslam/configurations/configuration_kitti.yaml";
  parameters->parseFromFile(parameters->command_line_parameters->configuration_file_name);

  slam_system.setSLAMAssembly(parameters);
}

//// Parsing Parameter file
// TEST_F(AssemblyTest, ParseParam)
// {
//   ASSERT_NO_THROW(parameters->parseFromFile(parameters->command_line_parameters->configuration_file_name));
// }

//// Load Camera Info
TEST_F(AssemblyTest, CameraLoad)
{
  ASSERT_NO_THROW(slam_system.loadCamerasFromMessageFile());
}

//// Playback Messagefile for one frame
TEST_F(AssemblyTest, PlaybackTest)
{
  std::shared_ptr<std::thread> slam_thread = nullptr;
  
  slam_system.loadCamerasFromMessageFile();

  cv::setNumThreads(0);

  ASSERT_NO_THROW(slam_system.playbackMessageFileOnce());
}

/////////////////////////////////////////////////////////////////////////////////
// class FeatureTest : public ::testing::Test {
// public:
//   void SetUp() override;
  
//   proslam::ParameterCollection* parameters;
//   // void app_main();
// };

// void FeatureTest::SetUp()
// {
//   cv::setUseOptimized(true);

//   // params setting
//   parameters = new proslam::ParameterCollection();
//   parameters->command_line_parameters->configuration_file_name = "~/catkin_ws/src/srrg_proslam/configurations/configuration_kitti.yaml";
//   parameters->command_line_parameters->dataset_file_name = "00.txt";
//   parameters->command_line_parameters->option_use_gui = false;
//   parameters->parseFromFile(parameters->command_line_parameters->configuration_file_name);
// }

TEST_F(AssemblyTest, ORBTest)
{
  slam_system.loadCamerasFromMessageFile();
  proslam::Camera* camera_left_ = slam_system.getCameraLeft();
  proslam::Camera* camera_right_ = slam_system.getCameraRight();

  camera_left_->setCameraMatrix(camera_left_->projectionMatrix().block<3,3>(0,0));
  camera_right_->setCameraMatrix(camera_left_->cameraMatrix());

  proslam::StereoFramePointGenerator* framepoint_generator = new proslam::StereoFramePointGenerator(parameters->stereo_framepoint_generator_parameters);
  framepoint_generator->setCameraLeft(camera_left_);
  framepoint_generator->setCameraRight(camera_right_);
  ASSERT_NO_THROW(framepoint_generator->configure());
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
