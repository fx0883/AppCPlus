//
//  FSDataManager.cpp
//  SharpMessage
//
//  Created by 冯璇 on 15/5/2.
//
//

#include "FSDataManager.h"




FSDataManager::FSDataManager()
{
    m_RecipeManager = FSRecipeManager::create();
    m_RecipeManager->retain();
}

FSDataManager::~FSDataManager()
{
    m_RecipeManager->release();

    CCLog("~FSDataManager");
}