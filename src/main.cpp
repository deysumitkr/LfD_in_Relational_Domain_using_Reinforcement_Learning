#include <iostream>
#include <fstream>
#include <exception>
#include <opencv2/opencv.hpp>

#include "cvui.h"
#include "objects.hpp"
#include "scene_generator.h"
#include "externalDefinitions.h"

/*
 * Types that may be checked with this system
 * 1) single object trajectory replication
 * 2) relational multi-object relational task completion
 */

#define CONTROL_WINDOW_NAME "Controls"
#define furnacePath "~/Documents/projects/tilde"
#define SAVED_DEMONSTRATIONS_PATH "../furnace/Demonstrations/"
#define UTILS_PATH "../furnace/Utils/"
#define SNAPSHOT_DIR "../furnace/Models/snapShots/"
#define PREDICTION_PATH "../furnace/Models/predict/"
//#define ACE_ILP_PATH "/home/sumit/Downloads/softwares/ACE-ilProlog-1.2.20/linux/"
//#define PROLOG_COMMAND "prolog"

cv::Mat CONTROL_BACKGROUND = cv::Mat(250, 600, CV_8UC3, cv::Scalar(49, 52, 49));

/**
 * @note Returning a pointer which was declared and defined within the function might lead to unexpected behaviour or a crash
 * @return time in format 2012-05-06.21:47:59
 */
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

/**
 * @brief Execute shell/bash commands and return std-out
 * @param cmd A valid shell/bash command
 * @return std-out after execution of the command
 */
std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}


void showText(std::string msg){
    std::string cmd = "zenity  --info --text=\""+ msg +"\"";
    exec(cmd.c_str());
}

std::string getText(std::string title, std::string message){
    std::string cmd = "zenity  --title  \""+ title +"\" --entry --text \"" + message + "\"";
    std::string str = exec(cmd.c_str());
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}

void addLogs(std::string log){
    std::string logFilePath = "../furnace/Logs/log";
    std::fstream outFile;
    outFile.open(logFilePath, std::ios::out | std::ios::app);
    outFile << log << "\n";
}


void tryFunc(){

    st::scene_generator scn(cv::Mat(720, 1280, CV_8UC3, cv::Scalar(0)));
    st::objects::params p;

    cv::namedWindow(CONTROL_WINDOW_NAME);
    cvui::init(CONTROL_WINDOW_NAME);

    /**
     * @brief examples for directly adding independent object with custom properties from within code
    p.circle_params.radius = 40;
    scn.addObject(1,st::objects::CIRCLE, cv::Point(400, 60), p, cv::Scalar(0, 0, 200), "red_Ball");

    p.quad_params.height = 70; p.quad_params.width=250;
    scn.addObject(2,st::objects::RECTANGLE, cv::Point(140, 370), p, cv::Scalar(0, 180, 250), "orange_Bar");

    p.quad_params.height=10; p.quad_params.width=10;
    scn.addObject(3,st::objects::RECTANGLE, cv::Point(200, 150), p, cv::Scalar(240, 80, 20), "blue_sq");
    */

    cv::namedWindow("scene1");
    scn.activateWindow("scene1");

    std::cout << "#objects in scn1: " << scn.getAllObjects().size() << std::endl;
    bool loop = true;
    while(loop){
        cv::imshow("scene1", scn.getScene());
        char c = (char)cv::waitKey(30);
        if(c == 27) loop = false;

        CONTROL_BACKGROUND =  cv::Scalar(49, 52, 49);

        try {

            if (cvui::button(CONTROL_BACKGROUND, 50, 50, (scn.isRecording())?"Stop Recording Actions":"Start Recording Actions")) {
                if(scn.isRecording()) {
                    scn.stopRecording();
                    showText("Recording Stopped:\nMultiple demonstrations may be given under same task name.");
                }
                else{
                    std::string fname, tname;
                    tname = getText("Enter Task Name", "Multiple demonstrations may belong to same task name.");
                    fname = getText("Enter File Name", "Name of this particular demonstration. Same file name within same task will be over-written.");
                    exec(("cd " + std::string(SAVED_DEMONSTRATIONS_PATH) + "; mkdir " + tname).c_str());
                    scn.startRecording(SAVED_DEMONSTRATIONS_PATH + tname + "/" + fname, tname);
                    showText("Recording Started:\nAll changes made in the scene will be recorded still the recording is stopped.");
                }
            }

            if (cvui::button(CONTROL_BACKGROUND, 50, 150, "Train Model")) {
                std::cout << exec(("cd " + std::string(UTILS_PATH) + ";python fileSystem.py --savedTasks").c_str()) << std::endl;
                //std::cout << "Enter the task name you wish to train from the above list (case-sensitive)? ";

                std::string trainTaskName = getText("Enter Task Name:", exec(("cd " + std::string(UTILS_PATH) + ";python fileSystem.py --savedTasks").c_str()));
                showText("Training will start now. Time required to train a model depends on the amount of data in the demonstration(s).");

                std::string logs;
                logs = exec(("cd " + std::string(UTILS_PATH) + ";python modelsFormat.py "+trainTaskName).c_str()) ;
                logs += exec(("cd " + std::string(UTILS_PATH) + ";sh try.sh "+trainTaskName+ " "+ ACE_ILP_PATH).c_str());
                logs += exec(("cd " + std::string(UTILS_PATH) + ";python makeTemplate.py "+trainTaskName).c_str());
                addLogs(logs);
                showText("Training Finished:\nThe trainings details can be found in furnace/Logs/log file.");
            }

            if (cvui::button(CONTROL_BACKGROUND, 250, 150, "Predict for Current State")) {
                std::string state = scn.getCurrentState();
                if(state.length() > 5) {
                    std::string cmd, taskName;
                    taskName = getText("Enter Task Name:", exec(("cd " + std::string(UTILS_PATH) + ";python fileSystem.py --savedTasks").c_str()));
                    cmd = "cd " + std::string(UTILS_PATH) + "; python predict.py -t "+ taskName +" -s \"" + state + "\" -p " + PROLOG_COMMAND;
                    std::string qsaOut = exec(cmd.c_str());
                    cmd += " --object";
                    std::string objID = exec(cmd.c_str());
                    objID.erase(std::remove_if(objID.begin(), objID.end(), isspace), objID.end());
                    int recommendedObjectID =  int(std::stod(objID)+0.5);

                    std::string info = "Q(s,a): " + qsaOut + "\n" + "Recommended Object to move:\nObjectID: " + std::to_string(recommendedObjectID) + " -> (" + objID + ")";
                    showText(info);
                }
                else { showText( "State is empty!"); }
            }


            if (cvui::button(CONTROL_BACKGROUND, 250, 100, "Generate Heat Map")) {
                std::string state = scn.getCurrentState();
                if(state.length() > 5) {
                    std::string cmd, taskName;
                    taskName = getText("Enter Task Name:", exec(("cd " + std::string(UTILS_PATH) + ";python fileSystem.py --savedTasks").c_str()));
                    showText("It might take a lot of time to evalute Q-values at every position in the image.\nHave Patience!");
                    cmd = "cd " + std::string(UTILS_PATH) + "; python predict.py -t "+ taskName +" -s \"" + state + "\" -p" + PROLOG_COMMAND;
                    std::string qsaOut = exec(cmd.c_str());
                    cmd += " --object --heatMap";
                    std::string objID = exec(cmd.c_str());
                    objID.erase(std::remove_if(objID.begin(), objID.end(), isspace), objID.end());
                    int recommendedObjectID =  int(std::stod(objID)+0.5);

                    std::string info = "Q(s,a): " + qsaOut + "\n" + "Recommended Object to move:\nObjectID: " + std::to_string(recommendedObjectID) + " -> (" + objID + ")";
                    showText(info);
                }
                else { showText( "State is empty!"); }
            }

            if (cvui::button(CONTROL_BACKGROUND, 50, 100, "Save Current State")) {
                std::string state = scn.getCurrentState();
                if(state.length() > 5) {
                    std::string fileName = getText("Enter file name to save as..:", "Avoid file extension");
                    cv::imwrite(SNAPSHOT_DIR + fileName + ".png", scn.getScene());
                }
                else { showText( "State is empty!"); }
            }

        }
        catch(...){
            showText("Something undesirable happened.\nBut you can anyway continue!");
        }

        if (cvui::button(CONTROL_BACKGROUND, 250, 50, "Show Current State")) {
            std::string state = scn.getCurrentState();
            if(state.length() > 5) {
                std::string cmd, taskName;
                showText(state);
            }
            else { showText( "State is empty!"); }
        }

        if (cvui::button(CONTROL_BACKGROUND, 0, 0, "Exit")) {
            showText( "The demonstrations and trained models will remain saved.\n Tot Ziens!");
            loop = false;
        }

        cvui::update();
        cv::imshow(CONTROL_WINDOW_NAME, CONTROL_BACKGROUND);

        /*
        switch(c){

            case 32:
                if(scn.isRecording()) scn.stopRecording();
                else{
                    std::string fname, tname;
                    std::cout << "FileName: "; std::cin >> fname;
                    std::cout << "TaskName: "; std::cin >> tname;
                    exec(("cd " + std::string(SAVED_DEMONSTRATIONS_PATH) + "; mkdir " + tname).c_str());
                    scn.startRecording(SAVED_DEMONSTRATIONS_PATH + tname + "/" + fname, tname);
                }
                break;

            case 'p': case 'P': // for play / predict
                {
                    std::string state = scn.getCurrentState();
                    if(state.length() > 5) {
                        std::string cmd, taskName;
                        //cmd = "cd " + std::string(furnacePath) + std::string("; python makeTemplate.py \"") + state + "\"";
                        std::cout << "TaskName: "; std::cin >> taskName;
                        cmd = "cd " + std::string(UTILS_PATH) + "; python predict.py -t "+ taskName +" -s \"" + state + "\" -p " + PROLOG_COMMAND;
                        std::cout << exec(cmd.c_str()) << std::endl;
                        cmd += " --object";
                        std::cout << exec(cmd.c_str()) << std::endl;
                    }
                    else { std::cout << "State is empty." << std::endl; }
                }
                break;

            case 't': case 'T':
                {
                    std::cout << exec(("cd " + std::string(UTILS_PATH) + ";python fileSystem.py --savedTasks").c_str()) << std::endl;
                    std::cout << "Enter the task name you wish to train from the above list (case-sensitive)? ";
                    std::string trainTaskName; std::cin >> trainTaskName;
                    std::cout << exec(("cd " + std::string(UTILS_PATH) + ";python modelsFormat.py "+trainTaskName).c_str()) << std::endl;
                    std::cout << exec(("cd " + std::string(UTILS_PATH) + ";sh try.sh "+trainTaskName+ " "+ ACE_ILP_PATH).c_str()) << std::endl;
                    std::cout << exec(("cd " + std::string(UTILS_PATH) + ";python makeTemplate.py "+trainTaskName).c_str()) << std::endl;
                }
                break;

            case 'z': case 'Z':
                {
                    //
                }
                break;

            default: break;
        }
        */

    }

    cv::destroyAllWindows();

}

int main(int argc, char* argv[]){
    tryFunc();

    return 0;
}