//
//  TDInvFileUtils.h
//  SharpMessage
//
//  Created by apple on 15/8/20.
//
//

#ifndef __SharpMessage__TDInvFileUtils__
#define __SharpMessage__TDInvFileUtils__

//
//  TDInvFileUtils.h
//  MyCocoa2DTest
//
//  Created by 韦 柱全 on 13-2-27.
//
//



#include <iostream>
#include "CrossApp.h"
USING_NS_CC;
using namespace std;

/** 负责操作文件储存和读取
 */

class TDInvFileUtils {
public:
    /** 读取本地文件，返回数据 */
    static string getFileByName(string pFileName);
    
    /** 储存内容到文件 */
    static bool saveFile(char* pContent,string pFileName);
    
    static bool saveFile(unsigned char *pContent, string pFileName, int length);
    
};



#endif /* defined(__SharpMessage__TDInvFileUtils__) */
