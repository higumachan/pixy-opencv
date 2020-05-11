//
// Created by 日熊悠太 on 2020/05/09.
//

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "pixyopencv/capture.hpp"

int main() {
    cv::Mat frame;
    cv::pixy::PixyCapture cap;

    while (true) {
        cap.read(frame);
        cv::imshow("frame", frame);
        cv::waitKey(100);
    }
}
