//
//  FSDataManager.h
//  SharpMessage
//
//  Created by 冯璇 on 15/5/2.
//
//

#ifndef __SharpMessage__FSDataManager__
#define __SharpMessage__FSDataManager__

#include <stdio.h>
#include "AppMacros.h"
#include "CrossApp.h"
#include <string>

using namespace std;

#include "FSRecipeManager.h"

class FSReadSetting:public CAObject
{
    public:
        string bgImage;
        string fontColor;
};

class FSDataManager:public CAObject
{
    SINGLETON(FSDataManager)
    CC_SYNTHESIZE_PASS_BY_REF2(FSRecipeManager*, m_RecipeManager, RecipeManager)
    

};

#endif /* defined(__SharpMessage__FSDataManager__) */
