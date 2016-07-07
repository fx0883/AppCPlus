//
//  FSContext.h
//  SharpMessage
//
//  Created by 冯璇 on 15/5/2.
//
//

#ifndef __SharpMessage__FSContext__
#define __SharpMessage__FSContext__

#include <stdio.h>
#include "CrossApp.h"

#include "AppMacros.h"

class FSContext:CAObject
{
    SINGLETON(FSContext)

public:
    string getDbPath();


    
};

#endif /* defined(__SharpMessage__FSContext__) */
