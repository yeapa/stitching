#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <cstring>
#include <iostream>
using namespace std;
struct Message
{
public:
    long int m_msgType;
    char  pPara[4147200];
    unsigned int m_length;
    Message(unsigned int length=4147200,long int msg_type=1)
    {
        m_msgType=msg_type;
        m_length=length;
        // cout<<"long int size :"<<sizeof(msg_type)<<endl;
    }
};
#endif
