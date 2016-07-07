#include "GlobalFunction.h"
#include <stdlib.h>

#include <dirent.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>

#include <wchar.h>


#include <fstream>
#include "FSUtil.h"




std::string CGlobalFunction::GetSignValue(const std::string srcValue)
{
	std::string signValue, tempValue;
	//std::string src = utf8_to_url_string(srcValue.c_str());
	MD5 md5(srcValue);
	tempValue = md5.md5();
	for (int i = 0; i < tempValue.size(); i++)
	{
		signValue += tolower(tempValue.at(i));
	}
	return signValue;
}

bool CGlobalFunction::IsChinese(std::string src, int index)
{
	char ch = src.substr(index, 1).at(0);
	if (ch >= 0 && ch < 128)
	{
		return false;
	}
	return true;
}

std::string CGlobalFunction::GetProfilePath()
{
	std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath().append("profile.xml");
	return filePath;
}

std::vector<std::string> CGlobalFunction::getFilePathAtVec(std::string filePath)
{
    std::vector<std::string> path_vec;
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    int i=0;
    
    if((dp=opendir(filePath.c_str()))==NULL)
    {
        CCLog("cannot open %s===========>",filePath.c_str());
        //  fprintf(stderr,cannot open %s,filePath.c_str());
        exit(1);
    }
    chdir(filePath.c_str());
    
    while((entry=readdir(dp))!=NULL&&i<255)
    {
        stat(entry->d_name,&statbuf);
        if(!S_ISREG(statbuf.st_mode))
            continue;
        //   path_vec.push_back(StringUtils::format(%s,entry->d_name));
        CCLog("open %s===========>",entry->d_name);
        path_vec.push_back(string(entry->d_name));
        
        
    }
    return path_vec;
}

int CGlobalFunction::copyFileAndroid(const char *SourceFile,const char *NewFile)
{
    
//    auto data =  FileUtils::getInstance()->getDataFromFile(filePath);
//    
//    //second - save it:
//    string dbPath = FileUtils::getInstance()->getWritablePath() + path;
//    
//    FILE* dest = fopen(dbPath.c_str(), "wb");
//    fwrite(data.getBytes(), 1, data.getSize(), dest);
//    fclose(dest);

    
    unsigned long pSize = 0;
    unsigned char* pData = CCFileUtils::sharedFileUtils()->getFileData(SourceFile, "rb", &pSize);
    
    //second - save it:
//    string dbPath = FileUtils::getInstance()->getWritablePath() + path;
    
    FILE* dest = fopen(NewFile, "wb");
    fwrite(pData, 1, pSize, dest);
    fclose(dest);
    return 1;
}

int CGlobalFunction::copyFile(const char *SourceFile,const char *NewFile)
{
    ifstream in;
    ofstream out;
    in.open(SourceFile,ios::binary);//打开源文件
    if(in.fail())//打开源文件失败
    {
        CCLog("Error 1: Fail to open the source file.");
        in.close();
        out.close();
        return 0;
    }
    out.open(NewFile,ios::binary);//创建目标文件
    if(out.fail())//创建文件失败
    {
        CCLog("Error 2: Fail to create the new file.");
        out.close();
        in.close();
        return 0;
    }
    else//复制文件
    {
        out<<in.rdbuf();
        out.close();
        in.close();
        return 1;
    }
    return 0;
};

vector<string> CGlobalFunction::stringSplit( string str, string pattern)
{
    vector<string> ret;
    if(pattern.empty()) return ret;
    size_t start=0,index=str.find_first_of(pattern,0);
    while(index!=str.npos)
    {
        if(start!=index)
            ret.push_back(str.substr(start,index-start));
        start=index+1;
        index=str.find_first_of(pattern,start);
    }
    if(!str.substr(start).empty())
        ret.push_back(str.substr(start));
    return ret;
};
vector<int> CGlobalFunction::stringSplitInt( string str, string pattern)
{
    vector<int> ret;
    if(pattern.empty()) return ret;
    size_t start=0,index=str.find_first_of(pattern,0);
    while(index!=str.npos)
    {
        if(start!=index)
            ret.push_back(atoi(str.substr(start,index-start).c_str()));
        start=index+1;
        index=str.find_first_of(pattern,start);
    }
    if(!str.substr(start).empty())
        ret.push_back(atoi(str.substr(start).c_str()));
    return ret;
}

string CGlobalFunction::vectorToString(vector<string>& vec,string pattern)
{
    string retStr="";
    for (size_t i =0; i < vec.size(); i ++) {
        
        string strItem = vec[i];
        
        retStr = retStr + strItem;
        if(i<vec.size() - 1)
        {
            retStr = retStr + pattern;
        }
    }
    return retStr;
    
}

string CGlobalFunction::vectorToString(vector<int>& vec,string pattern)
{
    string retStr="";
    for (size_t i =0; i < vec.size(); i ++) {
        
        char strItem[20];
        sprintf(strItem, "%d",vec[i]);
        
        retStr = retStr + strItem;
        if(i<vec.size() - 1)
        {
            retStr = retStr + pattern;
        }
    }
    return retStr;
}


//Round(1.234,2) = 1.23
//Round(1.234,0) = 1.0
//Round(123.4,-1) = 120.0
double CGlobalFunction::Round(double dVal, short iPlaces) {
    double dRetval;
    double dMod = 0.0000001;
    if (dVal<0.0) dMod=-0.0000001;
    dRetval=dVal;
    dRetval+=(5.0/pow(10.0,iPlaces+1.0));
    dRetval*=pow(10.0,iPlaces);
    dRetval=floor(dRetval+dMod);
    dRetval/=pow(10.0,iPlaces);
    return(dRetval);
};


int CGlobalFunction::multiple(short iPlaces)
{
    int sum = 1;
    for (int i=1; i<=iPlaces; i++) {
        sum = sum*10;
    }
    return sum;
};

double CGlobalFunction::roundEx(double dVal, short iPlaces) {
    double retDouble = Round(dVal,iPlaces);
    int sum = multiple(iPlaces);
    int retInt = (int)sum*retDouble;
    retDouble = (double)retInt/sum;
    return retDouble;
};



wchar_t * CGlobalFunction::MBCS2Unicode(wchar_t * buff, const char * str)

{
    
    wchar_t * wp = buff;
    
    char * p = (char *)str;
    
    while(*p)
        
    {
        
        if(*p & 0x80)
            
        {
            
            *wp = *(wchar_t *)p;
            
            p++;
            
        }
        
        else{
            
            *wp = (wchar_t) *p;
            
        }
        
        wp++;
        
        p++;
        
    }
    
    *wp = 0x0000;
    
    return buff;
    
};



char* CGlobalFunction::Unicode2MBCS(char * buff, const wchar_t * str)

{
    
    wchar_t * wp = (wchar_t *)str;
    
    char * p = buff, * tmp;
    
    while(*wp){
        
        tmp = (char *)wp;
        
        if(*wp & 0xFF00){
            
            *p = *tmp;
            
            p++;tmp++;
            
            *p = *tmp;
            
            p++;
            
        }
        
        else{
            
            *p = *tmp;
            
            p++;
            
        }
        
        wp++;
        
    }
    
    *p = 0x00;
    
    return buff;
    
};



wstring CGlobalFunction::str2wstr(string str)

{
    
    size_t len = str.size();
    
    wchar_t * b = (wchar_t *)malloc((len+1)*sizeof(wchar_t));
    
    MBCS2Unicode(b,str.c_str());
    
    wstring r(b);
    
    free(b);
    
    return r;
    
};



string CGlobalFunction::wstr2str(wstring wstr)

{
    
    size_t len = wstr.size();
    
    char * b = (char *)malloc((2*len+1)*sizeof(char));
    
    Unicode2MBCS(b,wstr.c_str());
    
    string r(b);
    
    free(b);
    
    return r;
    
};



int CGlobalFunction::wputs(wstring wstr)

{
    
    wputs(wstr.c_str());
    
    return 0;
    
};



int CGlobalFunction::wputs(const wchar_t * wstr)

{
    
    int len = wcslen(wstr);
    
    char * buff = (char *)malloc((len * 2 + 1)*sizeof(char));
    
    Unicode2MBCS(buff,wstr);
    
    printf("%s",buff);
    
    free(buff);
    
    return 0;
    
};


//第一种替换字符串的方法用replace()

void CGlobalFunction::string_replace(string&s1,const string&s2,const string&s3)
{
    string::size_type pos=0;
    string::size_type a=s2.size();
    string::size_type b=s3.size();
    while((pos=s1.find(s2,pos))!=string::npos)
    {
        s1.replace(pos,a,s3);
        pos+=b;
    }
};

//第二种替换字符串的方法用erase()和insert()

void CGlobalFunction::string_replace_2(string&s1,const string&s2,const string&s3)
{
    string::size_type pos=0;
    string::size_type a=s2.size();
    string::size_type b=s3.size();
    while((pos=s1.find(s2,pos))!=string::npos)
    {
        s1.erase(pos,a);
        s1.insert(pos,s3);
        pos+=b;
    }
};


vector<string> CGlobalFunction::split( string str, string pattern)
{
    vector<string> ret;
    if(pattern.empty()) return ret;
    size_t start=0,index=str.find_first_of(pattern,0);
    while(index!=str.npos)
    {
        if(start!=index)
            ret.push_back(str.substr(start,index-start));
        start=index+1;
        index=str.find_first_of(pattern,start);
    }
    if(!str.substr(start).empty())
        ret.push_back(str.substr(start));
    return ret;
};




