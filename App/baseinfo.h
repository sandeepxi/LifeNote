#pragma once
#ifndef BASEINFO_H
#define BASEINFO_H

#define  RECYLE "废纸篓"
//xml-node 开头不能用数字，否则报错。使用START_FLAG加在n标题前面，如“蚌2022年计划”来作为替代
#define  START_FLAG "蚌"
#define  ATTRIBUTE_NOTETYPE "nodetype"
#define  ATTRIBUTE_STARTFLAG "isStartWithDigit"


class BaseInfo
{
public:
    enum OperationType
    {
       AddNode,
       AddNodeGroup,
       DeleteNode,
       MoveNode,
       RenameNode,
    };

    enum NodeType
    {
        Child,
        Parent,
    };
};

#endif // BASEINFO_H
