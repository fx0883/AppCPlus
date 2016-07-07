//
//  FSloadResBase.h
//  SharpMessage
//
//  Created by 冯璇 on 15/4/29.
//
//

#ifndef __SharpMessage__FSloadResBase__
#define __SharpMessage__FSloadResBase__

#include <stdio.h>
#include <string>
#include "CrossApp.h"
#include "AppMacros.h"
#include "CrossAppExt.h"
using namespace std;
class FSloadResBase:public CAObject
{
//public:
//    static FSloadResBase* sharedFSloadRes();
//    static FSloadResBase *m_sharedFSloadRes;
protected:
    sqlite3 *_sqlite3;
public:
    ~FSloadResBase();
    
public:
//    CC_SYNTHESIZE_PASS_BY_REF(string, m_dbName, DBName)
public:

    virtual bool init();
};
#endif /* defined(__SharpMessage__FSloadResBase__) */
