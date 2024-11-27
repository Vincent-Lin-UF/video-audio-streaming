//
// Created by Vincent Lin on 11/27/24.
//

#include "capture/webcam_capture.h"
#include <iostream>

WebcamCapture::WebcamCapture(int deviceIndex) : deviceIndex_(deviceIndex), videoCapture_(deviceIndex) {
    if(!videoCapture_.isOpened()) {
        std::cerr << "Error: Unable to open webcam (Device Index:" << deviceIndex << ")\n";
    }
}

WebcamCapture::~WebcamCapture(){
    release();
}

bool WebcamCapture::isOpen() const {
    return videoCapture_.isOpened();
}

bool WebcamCapture::captureFrame() {
    if(!videoCapture_.isOpened()){
        std::cerr << "Error: webcam is not open \n";
        return false;
    }

    if(!videoCapture_.read(frame_)){
        std::cerr << "Error: unable to read frame\n";
        return false;
    }
    return true;
}

const cv::Mat& WebcamCapture::getFrame() const {
    return frame_;
}

void WebcamCapture::release() {
    if(videoCapture_.isOpened()){
        videoCapture_.release();
    }
}
