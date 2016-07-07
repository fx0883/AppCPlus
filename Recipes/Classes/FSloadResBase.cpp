//
//  FSloadResBase.cpp
//  SharpMessage
//
//  Created by 冯璇 on 15/4/29.
//
//

#include "FSloadResBase.h"

//FSloadResBase* FSloadResBase::m_sharedFSloadRes = NULL;
//
//FSloadResBase* FSloadResBase::sharedFSloadRes()
//{
//    return m_sharedFSloadRes;
//}

bool FSloadResBase::init()
{
    _sqlite3 = NULL;
//    this->setDBName(DBNAME);
    return true;
}

FSloadResBase::~FSloadResBase()
{
    if (_sqlite3) {
        sqlite3_close(_sqlite3);
    }
}
