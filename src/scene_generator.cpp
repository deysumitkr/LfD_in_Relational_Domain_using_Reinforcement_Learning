//
// Created by sumit on 14/7/17.
//

#include <memory>
#include "scene_generator.h"

bool st::scene_generator::LButtonDown = false;

st::scene_generator::scene_generator(int width, int height, cv::Scalar backgroundColor) { scene_generator(cv::Mat(height, width, CV_8UC3, backgroundColor)); }
st::scene_generator::scene_generator(cv::Mat background) {
    mBackground = background;
    mRecorder = new Recorder();
}

cv::Mat st::scene_generator::getScene() {
    cv::Mat scene = mBackground.clone();

    for (int i=0; i<zIndex.size(); i++){
        objectsByID[zIndex[i]].obj->draw(scene);
        if(showObjectCenters) cv::circle(scene, objectsByID[zIndex[i]].obj->center(),2,cv::Scalar(250, 170, 0), 1);
    }

    if(showLastTrajectoryPath)
    for (int i=0; i<trajectory.size(); i++){
        cv::circle(scene, trajectory[i], 2, cv::Scalar(0, 250, 0), -1);
    }

    if(inAction && trajectory.size() > 0) objectsByID[inActID].obj->drawOutline(scene, trajectory.back());

    return scene;
}

std::string st::scene_generator::getCurrentState() {
    std::string state = "\n";
    for(std::map<int, st::objectDB>::iterator it = objectsByID.begin(); it!= objectsByID.end(); it++){
        state += "objectID(" + std::to_string(it->first) + ").\n";
        state += "shape(" + std::to_string(it->first) +  ", " + std::to_string(it->second.type) + ").\n";
        state += "color(" + std::to_string(it->first) +  ", "
                   + std::to_string(int(it->second.obj->color()[2])) + ", "
                   + std::to_string(int(it->second.obj->color()[1])) + ", "
                   + std::to_string(int(it->second.obj->color()[0])) + ").\n";
        state += "size(" + std::to_string(it->first) +  ", " + std::to_string(it->second.obj->getBoundingBox().width) +  ", " + std::to_string(it->second.obj->getBoundingBox().height) + ").\n";
        state += "position(" + std::to_string(it->first) +  ", " + std::to_string(it->second.obj->center().x) +  ", " + std::to_string(it->second.obj->center().y) + ").\n";
    }
    return state;
}



void st::scene_generator::startRecording(std::string filename, std::string taskName) {
    trajectory.clear();

    mRecorder->setFileName(filename);
    mRecorder->setTaskName(taskName);
    mRecorder->startRecording(objectsByID);

    std::cout << "Recording..." << std::endl;
}

void st::scene_generator::stopRecording() {
    mRecorder->stopRecording();
    std::cout << "Recording Stopped!!" << std::endl;
}

void st::scene_generator::addObject(int id, int objectType, cv::Point center, st::objects::params objectParams, cv::Scalar color, std::string objectName) {
    st::objectDB ob;
    ob.ID = id;
    ob.name = objectName;
    ob.type = objectType;
    ob.prop = objectParams;

    switch (objectType){
        case st::objects::CIRCLE:
            ob.obj = (st::objects*) new st::circle(id, center, objectParams.circle_params.radius, color);
            break;

        case st::objects::RECTANGLE:
            ob.obj = (st::objects*) new st::rectangle(id, center, objectParams.quad_params.width, objectParams.quad_params.height, color);
            break;

        default:
            return;
    }

    objectsByID[id] = ob;
    objectsByName[objectName] = ob;
    zIndex.push_back(id);
}

void st::scene_generator::spawnObject(int objectType) {

    int id=1; while(std::find(zIndex.begin(), zIndex.end(), id) != zIndex.end()){ id++; }
    cv::Point center = cv::Point(mBackground.cols/2, mBackground.rows/2);
    st::objects::params p;
    cv::Scalar color = cv::Scalar(223, 223, 223);
    std::string objectName = "";

    switch (objectType){
        case st::objects::CIRCLE:
            p.circle_params.radius = 40;
            break;

        case st::objects::RECTANGLE:
            p.quad_params.width = 150; p.quad_params.height = 50;
            break;

        default: return;
    }

    addObject(id, objectType, center, p, color, objectName);
}

void st::scene_generator::getSpawnObjectWindow(std::string winName){
    iconBg = cv::Mat(100, 150, CV_8UC3, cv::Scalar(220,220,220));
    cv::Mat iconSeparator = cv::Mat(2, iconBg.cols, CV_8UC3, cv::Scalar(230,120,0));

    cv::Mat quadIcon = iconBg.clone();
    cv::Rect r = cv::Rect(int(0.1*iconBg.cols), iconBg.rows/4, int(0.8*iconBg.cols), iconBg.rows/2);
    cv::rectangle(quadIcon, r, cv::Scalar(220, 120, 20), -1);

    cv::Mat circleIcon = iconBg.clone();
    cv::circle(circleIcon, cv::Point(iconBg.cols/2,iconBg.rows/2), int(0.8*iconBg.rows/2), cv::Scalar(20, 50, 180), -1);


    cv::vconcat(quadIcon, iconSeparator, iconPanel);
    cv::vconcat(iconPanel, circleIcon, iconPanel);

    cv::namedWindow(winName, cv::WINDOW_NORMAL);
    cv::imshow(winName, iconPanel);

    cv::setMouseCallback(winName, st::scene_generator::spawnObjectsCallBackFunction, this);

}

void st::scene_generator::activateWindow(std::string windowName) {
    cv::setMouseCallback(windowName, st::scene_generator::callBackFunction, this);
    std::string spawnWindow = "Spawn in " + windowName;
    getSpawnObjectWindow(spawnWindow);
}

st::objectDB st::scene_generator::getObjectByID(int id) { return objectsByID[id]; }

std::map<int, st::objectDB> st::scene_generator::getAllObjects() { return objectsByID; }


void st::scene_generator::initNewAction(cv::Point pt) {
    for(int i=(int)zIndex.size()-1; i>=0; i--){
        if(objectsByID[zIndex[i]].obj->isWithinObject(pt)){

            inAction = true;
            inActID = zIndex[i];

            cv::Point center = objectsByID[inActID].obj->center();
            offSet.x = center.x - pt.x;
            offSet.y = center.y - pt.y;

            trajectory.clear();
            trajectory.push_back(center);

            zIndex.erase(zIndex.begin()+i);
            zIndex.push_back(inActID);

            return;
        }
    }
}

void st::scene_generator::endAction(cv::Point pt) {
    trajectory.push_back(cv::Point(pt.x + offSet.x, pt.y + offSet.y));
    cv::Point p0 = trajectory[0];
    int dx = pt.x - p0.x;
    int dy = pt.y - p0.y;

    cv::Point c0 = objectsByID[inActID].obj->center();
    objectsByID[inActID].obj->setCenter(cv::Point(c0.x+dx+offSet.x, c0.y+dy+offSet.y));
    inAction = false;

    if(mRecorder->isRecording()) mRecorder->saveTrajectory(inActID, trajectory);
    std::cout << "Trajectory Length: " << trajectory.size() << std::endl;
}

void st::scene_generator::replicate(cv::Point pt) {
    int id = getObjectAtLocation(pt);
    if(id != -1){
        st::objects::params p;
        switch(objectsByID[id].obj->type()){
            case st::objects::CIRCLE:
                p.circle_params.radius = static_cast<circle*>(objectsByID[id].obj)->radius();
                break;

            case st::objects::RECTANGLE:
                p.quad_params.width = static_cast<rectangle*>(objectsByID[id].obj)->mWidth;
                p.quad_params.height = static_cast<rectangle*>(objectsByID[id].obj)->mHeight;
                break;
            default: return;
        }

        int newId=1; while(std::find(zIndex.begin(), zIndex.end(), newId) != zIndex.end()){ newId++; }
        cv::Point center = cv::Point(mBackground.cols/2, mBackground.rows/2);

        addObject(newId, objectsByID[id].obj->type(), center, p, objectsByID[id].obj->color(), "");
    }
}

void st::scene_generator::cleanUp(cv::Point pt) {
    int id = getObjectAtLocation(pt);
    if(id == -1) { trajectory.clear(); }
    else {
        objectsByID.erase(objectsByID.find(id));
        zIndex.erase(std::remove(zIndex.begin(), zIndex.end(), id), zIndex.end());
    }
}


void st::scene_generator::controlPanelAction(cv::Point pt) {
    int id = getObjectAtLocation(pt);
    if(id != -1){
        std::string winName = "Controls for object ID: "+std::to_string(id);
        cv::namedWindow(winName, cv::WINDOW_NORMAL);
        objectsByID[id].obj->showControls(winName);
    }
}


double st::scene_generator::euclideanDistance(cv::Point p1, cv::Point p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}


/**
 * @brief static mouse callBack function to receive mouse events
 * @param event
 * @param x
 * @param y
 * @param flags
 * @param userdata Instance of the class - scene_generator is required
 */
void st::scene_generator::callBackFunction(int event, int x, int y, int flags, void *userdata) {
    st::scene_generator* scn = (st::scene_generator*)userdata;
    switch(event){
        case cv::EVENT_LBUTTONDOWN:
            if(!scn->inAction && !LButtonDown){ scn->initNewAction(cv::Point(x, y)); }
            LButtonDown = true;
            break;

        case cv::EVENT_LBUTTONUP:
            if(scn->inAction) { scn->endAction(cv::Point(x,y)); }
            LButtonDown = false;
            break;

        case cv::EVENT_LBUTTONDBLCLK:
            scn->replicate(cv::Point(x,y));
            break;

        case cv::EVENT_RBUTTONUP:
            scn->controlPanelAction(cv::Point(x,y));
            break;

        case cv::EVENT_MBUTTONUP:
            scn->cleanUp(cv::Point(x,y));
            break;

        case cv::EVENT_MOUSEMOVE:
            if(scn->inAction) {
                if(scn->trajectory.size() == 0) scn->trajectory.push_back(cv::Point(x + scn->offSet.x, y + scn->offSet.y));
                else if(scn->euclideanDistance(scn->trajectory.back(), cv::Point(x + scn->offSet.x, y + scn->offSet.y)) > scn->distanceResolution) scn->trajectory.push_back(cv::Point(x + scn->offSet.x, y + scn->offSet.y));
            }
            break;

        default:;
    }
}

void st::scene_generator::spawnObjectsCallBackFunction(int event, int x, int y, int flags, void *userdata) {
    st::scene_generator* scn = (st::scene_generator*)userdata;
    switch(event){
        case cv::EVENT_LBUTTONUP:
            if(y < scn->iconPanel.rows/2){ scn->spawnObject(st::objects::RECTANGLE); }
            else scn->spawnObject(st::objects::CIRCLE);
            break;
        default:;
    }
}

int st::scene_generator::getObjectAtLocation(cv::Point pt) {
    for(int i=(int)zIndex.size()-1; i>=0; i--){
        if(objectsByID[zIndex[i]].obj->isWithinObject(pt)){
            return zIndex[i];
        }
    }
    return -1;
}














