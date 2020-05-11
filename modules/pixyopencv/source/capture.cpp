//
// Created by 日熊悠太 on 2020/05/09.
//

#include "capture.hpp"

namespace {

int demosaic(uint16_t width, uint16_t height, const uint8_t *bayerImage, uint32_t *image)
{
    uint32_t x, y, xx, yy, r, g, b;
    uint8_t *pixel0, *pixel;

    for (y=0; y<height; y++)
    {
        yy = y;
        if (yy==0)
            yy++;
        else if (yy==height-1)
            yy--;
        pixel0 = (uint8_t *)bayerImage + yy*width;
        for (x=0; x<width; x++, image++)
        {
            xx = x;
            if (xx==0)
                xx++;
            else if (xx==width-1)
                xx--;
            pixel = pixel0 + xx;
            if (yy&1)
            {
                if (xx&1)
                {
                    r = *pixel;
                    g = (*(pixel-1)+*(pixel+1)+*(pixel+width)+*(pixel-width))>>2;
                    b = (*(pixel-width-1)+*(pixel-width+1)+*(pixel+width-1)+*(pixel+width+1))>>2;
                }
                else
                {
                    r = (*(pixel-1)+*(pixel+1))>>1;
                    g = *pixel;
                    b = (*(pixel-width)+*(pixel+width))>>1;
                }
            }
            else
            {
                if (xx&1)
                {
                    r = (*(pixel-width)+*(pixel+width))>>1;
                    g = *pixel;
                    b = (*(pixel-1)+*(pixel+1))>>1;
                }
                else
                {
                    r = (*(pixel-width-1)+*(pixel-width+1)+*(pixel+width-1)+*(pixel+width+1))>>2;
                    g = (*(pixel-1)+*(pixel+1)+*(pixel+width)+*(pixel-width))>>2;
                    b = *pixel;
                }
            }
            *image = (b<<16) | (g<<8) | r;
        }
    }
}

}

namespace cv {
namespace pixy {

PixyCapture::PixyCapture(uint32_t pixy_init_arg)
{
    pixy.init(pixy_init_arg);
}

bool PixyCapture::read(cv::Mat &frame)
{
    pixy.m_link.stop();
    uint8_t *bayerFrame;
    uint32_t rgbFrame[PIXY2_RAW_FRAME_WIDTH*PIXY2_RAW_FRAME_HEIGHT];
    pixy.m_link.getRawFrame(&bayerFrame);
    demosaic(PIXY2_RAW_FRAME_WIDTH, PIXY2_RAW_FRAME_HEIGHT, bayerFrame, rgbFrame);
    pixy.m_link.resume();

    frame = cv::Mat3b(cv::Size(PIXY2_RAW_FRAME_WIDTH, PIXY2_RAW_FRAME_HEIGHT));
    uint8_t* data = frame.data;

    for (int y = 0; y < PIXY2_RAW_FRAME_HEIGHT; y++) {
        for (int x = 0; x < PIXY2_RAW_FRAME_WIDTH; x++) {
            uint8_t b = (rgbFrame[y * PIXY2_RAW_FRAME_WIDTH + x] >> 16) & 0xff;
            *data = b;
            data++;
            uint8_t g = (rgbFrame[y * PIXY2_RAW_FRAME_WIDTH + x] >> 8) & 0xff;
            *data = g;
            data++;
            uint8_t r = rgbFrame[y * PIXY2_RAW_FRAME_WIDTH + x] & 0xff;
            *data = r;
            data++;
        }
    }

    return true;
}

}
}
