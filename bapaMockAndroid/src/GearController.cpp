//
// Created by 新家 亮太 on 2016/08/14.
//

#include "GearController.hpp"

GearController::GearController() {
    // no-op
}

void GearController::setItems(vector<Item*> items) {
    gears.clear();

    for (Item *item : items) {
        Gear* gear = dynamic_cast<Gear*>(item);
        if (gear) {
            gears.push_back(gear);
        }
    }

    rotateType = 0;
    initRotateItems();
}

void GearController::update(float accelX, float accelY) {
    if (ofGetElapsedTimeMillis() - startTime > 5 * 1000) {
        initRotateItems();
    }

    int count = 0;
    for (Gear *gear : gears) {
        if (ABS(accelX) > 0.4 || ABS(accelY) > 0.4) {
            gear->update(accelX, accelY);

        } else if (isContain(count)) {
            gear->update();

            if (gear->hasFinishRotate()) {
                // Remove from vector.
                int position = getPosition(count);
                rotatingIds.erase(rotatingIds.begin() + position);
            }

            if (gear->getAngle() > 300) {
                int position = getPosition(count);
                int id = rotatingIds[position];
                int nextId = id + rotateItemCount;
                if (nextId > gears.size() - 1) {
                    nextId = nextId - gears.size();
                }
                if (getPosition(nextId) < 0) {
                    // Add next id if vector has not the id.
                    rotatingIds.push_back(nextId);
                }
            }
        }
        count++;
    }
}

void GearController::initRotateItems() {
    rotatingIds.clear();

    for (int i = 0; i < gears.size(); i++) {
        switch (rotateType) {
            case 0:
                if (i < 9) {
                    rotatingIds.push_back(i);
                }
                break;

            case 1:
                if (i % 5 == 0) {
                    rotatingIds.push_back(i);
                }
                break;

            case 2:
                rotatingIds.push_back(i);
                break;

            default:
                continue;
        }
        gears[i]->reset();
    }
    rotateType++;
    if (rotateType > 2) {
        rotateType = 0;
    }
    rotateItemCount = rotatingIds.size();
    startTime = ofGetElapsedTimeMillis();
}

bool GearController::isContain(int id) {
    return std::find(rotatingIds.begin(), rotatingIds.end(), id) != rotatingIds.end();
}

int GearController::getPosition(int targetId) {
    for (int i = 0, len = rotatingIds.size(); i < len; i++) {
        int id = rotatingIds[i];

        if (id == targetId) {
            return i;
        }
    }
    return -1;
}
