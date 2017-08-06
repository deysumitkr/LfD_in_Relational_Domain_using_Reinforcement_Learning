//
// Created by sumit on 14/7/17.
//

#ifndef SHOW_TASK_SCENE_GENERATOR_H
#define SHOW_TASK_SCENE_GENERATOR_H

#include <opencv2/opencv.hpp>
#include "objects.hpp"
#include "circle.h"
#include "quad.h"
//#include "allStructures.h"
#include "recorder.h"

namespace st {



    class scene_generator {
    private:
        cv::Mat mScene;
        cv::Mat mBackground;

        cv::Mat iconBg;
        cv::Mat iconPanel;

        Recorder* mRecorder;

        std::map<int, objectDB> objectsByID;
        std::map<std::string, objectDB> objectsByName;
        std::vector<int> zIndex;

        void controlPanelAction(cv::Point);
        int getObjectAtLocation(cv::Point);


    public:

        scene_generator(int width, int height, cv::Scalar backgroundColor=cv::Scalar(0));
        scene_generator(cv::Mat background);
        void addObject(int id, int objectType, cv::Point center, st::objects::params objectParams, cv::Scalar color = cv::Scalar(255,255,255), std::string objectName = "");
        //void addObjects(std::vector<int> ids, std::vector<int> objectTypes, std::vector<st::objects::params> objectParams, std::vector<std::string> objectNames);

        st::objectDB getObjectByID(int);
        void activateWindow(std::string); // must be called after the window is created
        cv::Mat getScene();
        std::map<int, st::objectDB> getAllObjects();

        static void callBackFunction(int event, int x, int y, int flags, void* userdata);
        static void spawnObjectsCallBackFunction(int event, int x, int y, int flags, void* userdata);

        // actions
        bool inAction = false;
        int inActID = -1;
        cv::Point offSet;
        std::vector<cv::Point> trajectory;

        void initNewAction(cv::Point);
        void endAction(cv::Point);

        void startRecording(std::string FileName, std::string TaskName);
        void stopRecording();
        bool isRecording(){ return mRecorder->isRecording(); }
        std::string getCurrentState();

        // globals
        static bool LButtonDown;
        double distanceResolution = 20;
        bool showLastTrajectoryPath = true;
        bool showObjectCenters = true;
        double euclideanDistance(cv::Point, cv::Point);

        void getSpawnObjectWindow(std::string);
        void spawnObject(int objectType);

        void replicate(cv::Point);
        void cleanUp(cv::Point);

        ~scene_generator(){
            delete(mRecorder);
        };
    };


}


#endif //SHOW_TASK_SCENE_GENERATOR_H
