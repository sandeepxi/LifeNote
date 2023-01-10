#pragma once
#ifndef BASEINFO_H
#define BASEINFO_H

#define  RECYLE "废纸篓"
#define  STARTFLAG "夯"
//这个方案得再思考下，有挺多坑的，文件的名称要不要变成 “夯xxx.html”目前删除文件有错误

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
