//
// Created by Vincent Lin on 11/27/24.
//

#ifndef VIDEO_AUDIO_STREAMING_WEBCAM_CAPTURE_H
#define VIDEO_AUDIO_STREAMING_WEBCAM_CAPTURE_H

#include <opencv2/opencv.hpp>
#include <string>

class WebcamCapture {
public:
    explicit WebcamCapture(int deviceIndex = 0);
    ~WebcamCapture();

    bool isOpen() const;
    bool captureFrame();
    const cv::Mat& getFrame() const;
    void release();

private:
    int deviceIndex_;
    cv::VideoCapture videoCapture_;
    cv::Mat frame_;
};

#endif //VIDEO_AUDIO_STREAMING_WEBCAM_CAPTURE_H
