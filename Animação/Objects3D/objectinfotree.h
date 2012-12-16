#ifndef OBJECTINFOTREE_H
#define OBJECTINFOTREE_H

#include <QString>
#include <vector>

class ObjectInfoTree{
public:
    ObjectInfoTree();

    QString test;

    std::vector<ObjectInfoTree*> child;
};

#endif // OBJECTINFOTREE_H
