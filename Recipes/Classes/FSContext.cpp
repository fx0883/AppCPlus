//
//  FSContext.cpp
//  SharpMessage
//
//  Created by 冯璇 on 15/5/2.
//
//

#include "FSContext.h"
//#include "FSUtil.h"
#include "GlobalFunction.h"

FSContext::FSContext()
{
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    
//#else  
//    char writeableDbPath[256];
//    sprintf(writeableDbPath, "%s%s",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(),DBName);
//    
//          CCLog("=================>11");
//    
//          CCLog("=================>%s",writeableDbPath);
//    if(!CCFileUtils::sharedFileUtils()->isFileExist(writeableDbPath))
//    {
//        string strDBName(DBName);
//        vector<string> dbDirVector = CGlobalFunction::stringSplit(strDBName, "/");
//        
//        //        std::vector<int> vect;
//        for(int i = 0; i < dbDirVector.size()-1; i++) {
//            std::cout<<dbDirVector[i]<<std::endl;
//            
//            char writeableDBdir[256];
//            sprintf(writeableDBdir, "%s%s",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(),dbDirVector[i].c_str());
//            if(!CCFileUtils::sharedFileUtils()->isFileExist(writeableDbPath))
//            {
//                CCFileUtils::sharedFileUtils()->createDirectory(writeableDBdir);
//            }
//            
//        }
//        
//        
//        string strDBPath = string(DBName);
//        strDBPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(strDBPath);
//        
//        CGlobalFunction::copyFile(strDBPath.c_str(), writeableDbPath);
//        
//        
//    }
//#endif
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#else
    char writeableDbPath[256];
    sprintf(writeableDbPath, "%s%s",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(),DBNameAndroid);
    
    CCLog("=================>11");
    
    CCLog("=================>%s",writeableDbPath);
    if(!CCFileUtils::sharedFileUtils()->isFileExist(writeableDbPath))
    {
//        string strDBName(DBName);
//        vector<string> dbDirVector = CGlobalFunction::stringSplit(strDBName, "/");
//        
//        //        std::vector<int> vect;
//        for(int i = 0; i < dbDirVector.size()-1; i++) {
//            std::cout<<dbDirVector[i]<<std::endl;
//            
//            char writeableDBdir[256];
//            sprintf(writeableDBdir, "%s%s",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(),dbDirVector[i].c_str());
//            if(!CCFileUtils::sharedFileUtils()->isFileExist(writeableDbPath))
//            {
//                CCFileUtils::sharedFileUtils()->createDirectory(writeableDBdir);
//            }
//            
//        }
        
        
        string strDBPath = string(DBName);
        strDBPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(strDBPath);
        
//        int retCopy = CGlobalFunction::copyFile(strDBPath.c_str(), writeableDbPath);
        
        CGlobalFunction::copyFileAndroid(strDBPath.c_str(), writeableDbPath);
        
     //    CCLog("retCopy %d",retCopy);
        
    }
#endif
    
    
}



FSContext::~FSContext()
{

}

string FSContext::getDbPath()
{
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    string strDBPath = string(DBName);
//    strDBPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(strDBPath);
//    CCLog("dbNewsPath = %s",strDBPath.c_str());
//
//    return strDBPath;
//#else
//    
//    string strDBPath = CCFileUtils::sharedFileUtils()->getWritablePath() + string(DBName);
//    CCLog("dbNewsPath = %s",strDBPath.c_str());
//    return strDBPath;
//
//#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    string strDBPath = string(DBName);
    strDBPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(strDBPath);
    CCLog("dbNewsPath = %s",strDBPath.c_str());
    
    return strDBPath;
#else
    
    string strDBPath = CCFileUtils::sharedFileUtils()->getWritablePath() + string(DBNameAndroid);
    CCLog("android DB Path = %s",strDBPath.c_str());
    return strDBPath;
    
#endif
    


}