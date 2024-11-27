//
// Created by Vincent Lin on 11/27/24.
//

#include "../include/capture/webcam_capture.h"
#include <gtest/gtest.h>
#include <opencv2/core.hpp>

class WebcamCaptureTest : public ::testing::Test {
protected:
    WebcamCapture* webcam;

    void SetUp() override {
        webcam = new WebcamCapture(0);
    }

    void TearDown() override {
        delete webcam;
    }
};

// Webcam works
TEST_F(WebcamCaptureTest, ConstructorOpensWebcam){
    EXPECT_TRUE(webcam->isOpen()) << "Webcam should be opened successfully.";
}

// Captures frame
TEST_F(WebcamCaptureTest, CaptureFrame){
    ASSERT_TRUE(webcam->isOpen()) << "Webcam must be opened successfully";

    bool res = webcam->captureFrame();
    EXPECT_TRUE(res) << "CaptureFrame should return successfully";
    EXPECT_FALSE(webcam->getFrame().empty()) << "Captured Frame should not be empty";
}

// Frame has valid dimensions
TEST_F(WebcamCaptureTest, GetFrameContent) {
    ASSERT_TRUE(webcam->isOpen()) << "Webcam must be opened successfully";

    webcam->captureFrame();
    const cv::Mat& frame = webcam->getFrame();
    EXPECT_GT(frame.cols, 0) << "CF should have a valid width";
    EXPECT_GT(frame.rows, 0) << "CF should have a valid height";
}

// Released webcam
TEST_F(WebcamCaptureTest, ReleaseWebcam){
    ASSERT_TRUE(webcam->isOpen()) << "Webcam must be open";

    webcam->release();
    EXPECT_FALSE(webcam->isOpen()) << "Webcam should not be on after release";
}

// Invalid device index
TEST_F(WebcamCaptureTest, InvalidDeviceIndex) {
    WebcamCapture invWeb(-1);
    EXPECT_FALSE(invWeb.isOpen()) << "Webcam should not open";
}

// Web release twice
TEST_F(WebcamCaptureTest, DoubleRelease){
    ASSERT_TRUE(webcam->isOpen()) << "Webcam must be opened successfully";

    webcam->release();
    EXPECT_NO_THROW(webcam->release()) << "Webcam should not throw except with double release";
    EXPECT_FALSE(webcam->isOpen()) << "Webcam should not be open";
}