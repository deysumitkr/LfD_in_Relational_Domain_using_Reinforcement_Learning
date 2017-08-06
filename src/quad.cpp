//
// Created by sumit on 13/7/17.
//

#include "quad.h"

st::rectangle::rectangle(int ID, cv::Rect rect, cv::Scalar color) : topLeft(cv::Point(rect.x, rect.y)), mWidth(rect.width), mHeight(rect.height) {
    setID(ID);
    setType(st::objects::RECTANGLE);
    setCenter(cv::Point(rect.x + rect.width/2, rect.y + rect.height/2));
    setColor(color);
}

st::rectangle::rectangle(int ID, cv::Point center, int width, int height, cv::Scalar color)
        : rectangle(ID, cv::Rect(center.x - (width/2), center.y - (height/2), width, height), color){}


bool st::rectangle::isWithinObject(cv::Point pt) {
    cv::Point mCenter = center();
    cv::Point topLeft = cv::Point(mCenter.x - mWidth/2, mCenter.y - mHeight/2);
    if(pt.x >= topLeft.x && pt.x <= topLeft.x+mWidth){
        return pt.y >= topLeft.y && pt.y <= topLeft.y+mHeight;
    }
    return false;
}

cv::Rect st::rectangle::getBoundingBox() {
    cv::Point mCenter = center();
    cv::Point topLeft = cv::Point(mCenter.x - mWidth/2, mCenter.y - mHeight/2);

    return cv::Rect(topLeft.x, topLeft.y, mWidth, mHeight);
}

void st::rectangle::draw(cv::Mat canvas) {
    cv::rectangle(canvas, getBoundingBox(), color(), -1);
}

void st::rectangle::drawOutline(cv::Mat canvas, cv::Point center) {
    cv::Rect r = cv::Rect(center.x - mWidth/2, center.y - mHeight/2, mWidth, mHeight);
    cv::rectangle(canvas, r, color(), 2);
}

void st::rectangle::paramsControl(std::string windowName) {
    cv::createTrackbar("Width", windowName, &this->mWidth, 255);
    cv::createTrackbar("Height", windowName, &this->mHeight, 255);
}
