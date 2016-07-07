#ifndef __Global_Function_H__
#define __Global_Function_H__


#include <ctype.h>
#include "CrossApp.h"
#include "FSUtil.h"
using namespace CrossApp;




#define AppWidth (CAApplication::getApplication()->getWinSize().width)
#define AppHeight (CAApplication::getApplication()->getWinSize().height)

class CGlobalFunction
{
public:
//	static HttpUrlInfo GetHttpUrlInfoByType(HttpUrlNovelRequestType urlType, NovelRequestParaInfo novelInfo);
	static std::string GetSignValue(const std::string srcValue);
	//static float GetWidth(float width){ return width / 1080 * AppWidth; }
	//static float GetHeight(float height){ return height / 1920 * AppHeight; }
	static bool IsChinese(std::string src, int index);
	static std::string GetProfilePath();
    
    //modify by fx
    //遍历文件夹
    static std::vector<std::string> getFilePathAtVec(std::string filePath);
    
    static int copyFile(const char *SourceFile,const char *NewFile);
    
    static int copyFileAndroid(const char *SourceFile,const char *NewFile);
    
    static vector<string> stringSplit( string str, string pattern);
    
    static vector<int> stringSplitInt( string str, string pattern);
    
    static string vectorToString(vector<string>& vec,string pattern);
    
    static string vectorToString(vector<int>& vec,string pattern);
    
public:
    //Round(1.234,2) = 1.23
    //Round(1.234,0) = 1.0
    //Round(123.4,-1) = 120.0
    static double Round(double dVal, short iPlaces);
    
    
    static int multiple(short iPlaces);

    
    static double roundEx(double dVal, short iPlaces);

    static wchar_t * MBCS2Unicode(wchar_t * buff, const char * str);

    static char * Unicode2MBCS(char * buff, const wchar_t * str);

    static wstring str2wstr(string str);

    static string wstr2str(wstring wstr);
    
    static int wputs(wstring wstr);
    
    static int wputs(const wchar_t * wstr);
    
    //第一种替换字符串的方法用replace()
    
    static void string_replace(string&s1,const string&s2,const string&s3);

    //第二种替换字符串的方法用erase()和insert()
    static void string_replace_2(string&s1,const string&s2,const string&s3);

    
    
    static vector<string> split( string str, string pattern);

    

};

#endif 
