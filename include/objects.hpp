//
// Created by sumit on 11/7/17.
//

#ifndef SHOW_TASK_OBJECTS_H
#define SHOW_TASK_OBJECTS_H

#include <opencv2/opencv.hpp>
//#include "allStructures.h"

namespace st {
    //static std::vector<int> registeredIDs;

    struct customColor{
        int red, blue, green;
    };



    class objects {

    private:
        int mID;
        int mType;
        cv::Scalar mColor;
        cv::Point mCenter;

    protected:
        customColor myColor;
        void setID(const int id) { mID = id; }
        void setType(const int type) { mType = type; }


    public:

        enum {
            RECTANGLE,
            CIRCLE
        };

        union params {

            struct circle {
                int radius;
            } circle_params;

            struct quad {
                int width, height;
            } quad_params;

        };




        // Read
        const int ID() { return mID; }
        const int type() { return mType; }
        const cv::Scalar color() { return mColor; }
        const cv::Point center() { return mCenter; }

        virtual cv::Rect getBoundingBox() = 0;
        virtual bool isWithinObject(cv::Point) = 0 ;
        virtual void drawOutline(cv::Mat, cv::Point center) = 0;
        virtual void paramsControl(std::string windowName) = 0;
        void showControls(std::string windowName) {
            cv::createTrackbar("Red", windowName, &this->myColor.red, 255, this->colorCallbackFunction, this);
            cv::createTrackbar("Green", windowName, &this->myColor.green, 255, this->colorCallbackFunction, this);
            cv::createTrackbar("Blue", windowName, &this->myColor.blue, 255, this->colorCallbackFunction, this);
            paramsControl(windowName);
        };

        // Write
        void setCenter(const cv::Point pt) { mCenter = pt; }
        void updateColor(){ mColor = cv::Scalar(myColor.blue, myColor.green, myColor.red); }
        void setColor(const cv::Scalar color) {
            myColor.red = int(color[2]);
            myColor.green = int(color[1]);
            myColor.blue = int(color[0]);
            mColor = color;
        }


        // Globals
        virtual void draw(cv::Mat) = 0;
        //const static std::vector<int> allIDs() { return st::registeredIDs; }
        //bool isRegisteredID(int id) { return std::find(st::registeredIDs.begin(), st::registeredIDs.end(), id) != st::registeredIDs.end(); }

        static void colorCallbackFunction(int val, void *data){ ((st::objects*)data)->updateColor(); }
    };

    struct objectDB {
        int ID;
        std::string name;
        int type;
        st::objects::params prop;
        st::objects* obj;
    };

}

#endif //SHOW_TASK_OBJECTS_H
