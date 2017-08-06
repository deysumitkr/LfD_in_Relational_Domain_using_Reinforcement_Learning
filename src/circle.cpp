//
// Created by sumit on 12/7/17.
//

#include "circle.h"

st::circle::circle(int ID, cv::Point center, int radius, cv::Scalar color) {
    setID(ID);
    setType(st::objects::CIRCLE);
    setCenter(center);
    setColor(color);
    this->mRadius = radius;
}

bool st::circle::isWithinObject(cv::Point pt) {
    cv::Point mCenter = center();
    return std::sqrt(std::pow(mCenter.y-pt.y, 2) + std::pow(mCenter.x-pt.x, 2)) <= mRadius;
}

cv::Rect st::circle::getBoundingBox() {
    cv::Point mCenter = center();
    return cv::Rect(mCenter.x-mRadius, mCenter.y-mRadius, mRadius*2, mRadius*2);
}

void st::circle::draw(cv::Mat canvas) {
    cv::circle(canvas, center(), radius(), color(), -1);
}

void st::circle::drawOutline(cv::Mat canvas, cv::Point center) {
    cv::circle(canvas, center, mRadius, color(), 2);
}

void st::circle::paramsControl(std::string windowName) {
    cv::createTrackbar("Radius", windowName, &this->mRadius, 255);
}

