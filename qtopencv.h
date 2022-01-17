#ifndef QTOPENCV_H
#define QTOPENCV_H
#include"opencv2/opencv.hpp"
#include"opencv2/highgui.hpp"
#include<QImage>

class QtOpencv
{
public:
    QtOpencv();
    static QImage cvMat2QImage(const cv::Mat& mat);
    static cv::Mat qImageToMat(QImage image);

};

#endif // QTOPENCV_H
