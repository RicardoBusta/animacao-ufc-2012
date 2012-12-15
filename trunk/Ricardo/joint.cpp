#include "joint.h"

Joint::Joint()
{
}

void Joint::draw()
{
    for(int i=0;i<child.size();i++){
        child[i]->draw();
    }
    object->draw();
}
