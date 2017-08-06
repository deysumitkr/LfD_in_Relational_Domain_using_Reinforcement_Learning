//
// Created by sumit on 23/7/17.
//

#ifndef SHOW_TASK_ALLSTRUCTURES_H
#define SHOW_TASK_ALLSTRUCTURES_H

namespace st {

    struct trajectory {
        int id;
        std::vector<cv::Point> points;
    };

    struct task {
        std::vector<st::objectDB> allObjects;
        std::map<int, cv::Point> initPositions;
        std::vector<trajectory> actions;
    };
}

#endif //SHOW_TASK_ALLSTRUCTURES_H
