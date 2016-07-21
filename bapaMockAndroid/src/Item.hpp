//
// Created by 新家 亮太 on 2016/07/17.
//

#ifndef BAPAMOCKANDROID_ITEM_H
#define BAPAMOCKANDROID_ITEM_H

class Item {
    public:
        virtual void update(float x, float y, float velocityX, float velocityY) = 0;
        virtual void draw() = 0;
        virtual ofPoint getLocation() = 0;
};

#endif //BAPAMOCKANDROID_ITEM_H
