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

// TEST_F(AssemblyTest, PlaybackTest)
// {
//   proslam::SLAMAssembly slam_system(parameters);
//   std::shared_ptr<std::thread> slam_thread = nullptr;
  
//   slam_system.loadCamerasFromMessageFile();

//   cv::setNumThreads(0);

//   ASSERT_NO_THROW(slam_system.playbackMessageFileOnce());
// }

/////////////////////////////////////////////////////////////////////////////////
class FeatureTest : public ::testing::Test {
public:
  void SetUp() override;
  
  proslam::ParameterCollection* parameters;
  // void app_main();
};

void FeatureTest::SetUp()
{
  cv::setUseOptimized(true);

  // params setting
  parameters = new proslam::ParameterCollection();
  parameters->command_line_parameters->configuration_file_name = "~/catkin_ws/src/srrg_proslam/configurations/configuration_kitti.yaml";
  parameters->command_line_parameters->dataset_file_name = "00.txt";
  parameters->command_line_parameters->option_use_gui = false;
  parameters->parseFromFile(parameters->command_line_parameters->configuration_file_name);
}

TEST_F(FeatureTest, ORBTest)
{
/*
* base_framepoint_generator.cpp - void  BaseFramePointGenerator::configure()  -> feature 선택 구현부
* slam_assembly.cpp - void SLAMAssembly::_createStereoTracker(Camera* camera_left_, Camera* camera_right_) -> 위 함수 호출 부분
*                     void SLAMAssembly::loadCameras(Camera* camera_left_, Camera* camera_right_) -> 위 함수 호출 부분
*/
  proslam::SLAMAssembly slam_system(parameters);
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