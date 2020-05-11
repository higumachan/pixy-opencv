//
// Created by 日熊悠太 on 2020/05/09.
//

#ifndef PIXY_OPENCV_CAPTURE_HPP
#define PIXY_OPENCV_CAPTURE_HPP

#include <opencv2/core.hpp>
#include <libpixyusb2.h>

namespace cv {
namespace pixy {

class PixyCapture {
public:
    PixyCapture(uint32_t pixy_init_arg=PIXY_DEFAULT_ARGVAL);
    bool read(cv::Mat &frame);

private:
    Pixy2 pixy;

};

}
}

#endif //PIXY_OPENCV_CAPTURE_HPP
