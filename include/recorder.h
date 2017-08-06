//
// Created by sumit on 23/7/17.
//

#ifndef SHOW_TASK_RECORDER_H
#define SHOW_TASK_RECORDER_H

#include <fstream>
#include "objects.hpp"
//#include "scene_generator.h"

class Recorder {

private:
    bool mRecording = false;
    std::string mFileName;
    std::string mTaskName;
    std::map<int, st::objectDB> mObjectsByID;

    void initialize(){
        std::fstream outFile;

        outFile.open(mFileName, std::ios::out | std::ios::app);
        outFile << mTaskName << "\n";

        outFile << "\nHeader:\n";
        for(std::map<int, st::objectDB>::iterator it = mObjectsByID.begin(); it!= mObjectsByID.end(); it++){
            outFile << "objectID(" + std::to_string(it->first) + ").\n";
            outFile << "shape(" + std::to_string(it->first) +  ", " + std::to_string(it->second.type) + ").\n";
            outFile << "color(" + std::to_string(it->first) +  ", "
                       + std::to_string(int(it->second.obj->color()[2])) + ", "
                       + std::to_string(int(it->second.obj->color()[1])) + ", "
                       + std::to_string(int(it->second.obj->color()[0])) + ").\n";
            outFile << "size(" + std::to_string(it->first) +  ", " + std::to_string(it->second.obj->getBoundingBox().width) +  ", " + std::to_string(it->second.obj->getBoundingBox().height) + ").\n";
        }

        outFile << "\nInitial State:\n";
        for(std::map<int, st::objectDB>::iterator it = mObjectsByID.begin(); it!= mObjectsByID.end(); it++){
            outFile << "position(" + std::to_string(it->first) +  ", " + std::to_string(it->second.obj->center().x) +  ", " + std::to_string(it->second.obj->center().y) + ").\n";
        }

        outFile << "\nTrajectories:\n";
        outFile.close();
    }

public:
    Recorder() {};
    Recorder(std::string fileName, std::string taskName) : mFileName(fileName), mTaskName(taskName) {}

    void setFileName(std::string fileName) { mFileName = fileName; }
    void setTaskName(std::string taskName) { mTaskName = taskName; }

    bool startRecording(std::map<int, st::objectDB> objectsByID){
        if(mRecording) return false;
        mRecording = true;
        mObjectsByID = objectsByID;
        initialize();
        return true;
    }

    bool stopRecording(){
        if(!mRecording) return false;
        mRecording = false;
        return true;
    }

    void saveTrajectory(int id, std::vector<cv::Point> trajectory){
        std::fstream outFile;
        outFile.open(mFileName, std::ios::app);
        outFile << "#\n";
        for (int i=0; i<trajectory.size(); i++){
            outFile << "move(" + std::to_string(id) +  ", " + std::to_string(trajectory[i].x) +  ", " + std::to_string(trajectory[i].y) + ").\n";
        }
        outFile.close();
    }

    bool isRecording() { return mRecording; }

};

#endif //SHOW_TASK_RECORDER_H