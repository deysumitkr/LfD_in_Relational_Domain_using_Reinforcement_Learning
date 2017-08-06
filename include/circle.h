//
// Created by sumit on 12/7/17.
//

#ifndef SHOW_TASK_CIRCLE_H
#define SHOW_TASK_CIRCLE_H

#include "objects.hpp"

namespace st {
    class circle : public objects {
    protected:
        int mRadius;
    public:
        int radius() { return mRadius; }

        circle(int ID, cv::Point center, int radius, cv::Scalar color);

        virtual bool isWithinObject(cv::Point);
        virtual cv::Rect getBoundingBox();
        virtual void draw(cv::Mat);
        void drawOutline(cv::Mat, cv::Point center);
        void paramsControl(std::string windowName);
    };
}

#endif //SHOW_TASK_CIRCLE_H
