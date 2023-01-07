#pragma once
#ifndef BASEINFO_H
#define BASEINFO_H

#define  RECYLE "废纸篓"

class BaseInfo
{
public:
    enum OperationType
    {
       AddNode,
       AddNodeGroup,
       DeleteNode,
       MoveNode,
    };

    enum NodeType
    {
        Child,
        Parent,
    };
};

#endif // BASEINFO_H
