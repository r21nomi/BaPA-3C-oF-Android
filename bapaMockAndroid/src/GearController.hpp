//
// Created by 新家 亮太 on 2016/08/14.
//

#ifndef BAPAMOCKANDROID_GEARCONTROLLER_H
#define BAPAMOCKANDROID_GEARCONTROLLER_H

#include "ofMain.h"
#include "Gear.hpp"

class GearController {
    public:
        GearController();
        void setItems(vector<Item*> items);
        void update(float accelX, float accelY);

    private:
        void initRotateItems();
        bool isContain(int id);
        int getPosition(int id);
        int rotateType;
        vector<Gear*> gears;
        vector<int> rotatingIds;
        int rotateItemCount;
        int startTime;
};

#endif //BAPAMOCKANDROID_GEARCONTROLLER_H
