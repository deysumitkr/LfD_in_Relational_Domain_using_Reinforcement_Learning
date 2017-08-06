//
// Created by sumit on 13/7/17.
//

#ifndef SHOW_TASK_QUADS_H
#define SHOW_TASK_QUADS_H

#include "objects.hpp"

namespace st {
    class rectangle : public objects {
    public:
        int mWidth, mHeight;
        cv::Point topLeft;

        rectangle(int ID, cv::Point center, int width, int height, cv::Scalar color);
        rectangle(int ID, cv::Rect rect, cv::Scalar color);

        virtual bool isWithinObject(cv::Point);
        virtual cv::Rect getBoundingBox();
        virtual void draw(cv::Mat);
        void drawOutline(cv::Mat, cv::Point center);
        void paramsControl(std::string windowName);
    };
}

#endif //SHOW_TASK_QUADS_H
