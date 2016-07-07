//
//  Util.h
//  SharpMessage
//
//  Created by apple on 6/24/15.
//
//

#ifndef __FS__Util__
#define __FS__Util__

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>

#include <wchar.h>


#include <fstream>


using namespace std;
////Round(1.234,2) = 1.23
////Round(1.234,0) = 1.0
////Round(123.4,-1) = 120.0
//double Round(double dVal, short iPlaces) {
//    double dRetval;
//    double dMod = 0.0000001;
//    if (dVal<0.0) dMod=-0.0000001;
//    dRetval=dVal;
//    dRetval+=(5.0/pow(10.0,iPlaces+1.0));
//    dRetval*=pow(10.0,iPlaces);
//    dRetval=floor(dRetval+dMod);
//    dRetval/=pow(10.0,iPlaces);
//    return(dRetval);
//};
//
//
//int multiple(short iPlaces)
//{
//    int sum = 1;
//    for (int i=1; i<=iPlaces; i++) {
//        sum = sum*10;
//    }
//    return sum;
//};
//
//double roundEx(double dVal, short iPlaces) {
//    double retDouble = Round(dVal,iPlaces);
//    int sum = multiple(iPlaces);
//    int retInt = (int)sum*retDouble;
//    retDouble = (double)retInt/sum;
//    return retDouble;
//};
//
//
//
//wchar_t * MBCS2Unicode(wchar_t * buff, const char * str)
//
//{
//    
//    wchar_t * wp = buff;
//    
//    char * p = (char *)str;
//    
//    while(*p)
//        
//    {
//        
//        if(*p & 0x80)
//            
//        {
//            
//            *wp = *(wchar_t *)p;
//            
//            p++;
//            
//        }
//        
//        else{
//            
//            *wp = (wchar_t) *p;
//            
//        }
//        
//        wp++;
//        
//        p++;
//        
//    }
//    
//    *wp = 0x0000;
//    
//    return buff;
//    
//};
//
//
//
//char * Unicode2MBCS(char * buff, const wchar_t * str)
//
//{
//    
//    wchar_t * wp = (wchar_t *)str;
//    
//    char * p = buff, * tmp;
//    
//    while(*wp){
//        
//        tmp = (char *)wp;
//        
//        if(*wp & 0xFF00){
//            
//            *p = *tmp;
//            
//            p++;tmp++;
//            
//            *p = *tmp;
//            
//            p++;
//            
//        }
//        
//        else{
//            
//            *p = *tmp;
//            
//            p++;
//            
//        }
//        
//        wp++;
//        
//    }
//    
//    *p = 0x00;
//    
//    return buff;
//    
//};
//
//
//
//wstring str2wstr(string str)
//
//{
//    
//    size_t len = str.size();
//    
//    wchar_t * b = (wchar_t *)malloc((len+1)*sizeof(wchar_t));
//    
//    MBCS2Unicode(b,str.c_str());
//    
//    wstring r(b);
//    
//    free(b);
//    
//    return r;
//    
//};
//
//
//
//string wstr2str(wstring wstr)
//
//{
//    
//    size_t len = wstr.size();
//    
//    char * b = (char *)malloc((2*len+1)*sizeof(char));
//    
//    Unicode2MBCS(b,wstr.c_str());
//    
//    string r(b);
//    
//    free(b);
//    
//    return r;
//    
//};
//
//
//
//int wputs(wstring wstr)
//
//{
//    
//    wputs(wstr.c_str());
//    
//    return 0;
//    
//};
//
//
//
//int wputs(const wchar_t * wstr)
//
//{
//    
//    int len = wcslen(wstr);
//    
//    char * buff = (char *)malloc((len * 2 + 1)*sizeof(char));
//    
//    Unicode2MBCS(buff,wstr);
//    
//    printf("%s",buff);
//    
//    free(buff);
//    
//    return 0;
//    
//};
//
//
////第一种替换字符串的方法用replace()
//
//void string_replace(string&s1,const string&s2,const string&s3)
//{
//    string::size_type pos=0;
//    string::size_type a=s2.size();
//    string::size_type b=s3.size();
//    while((pos=s1.find(s2,pos))!=string::npos)
//    {
//        s1.replace(pos,a,s3);
//        pos+=b;
//    }
//};
//
////第二种替换字符串的方法用erase()和insert()
//
//void string_replace_2(string&s1,const string&s2,const string&s3)
//{
//    string::size_type pos=0;
//    string::size_type a=s2.size();
//    string::size_type b=s3.size();
//    while((pos=s1.find(s2,pos))!=string::npos)
//    {
//        s1.erase(pos,a);
//        s1.insert(pos,s3);
//        pos+=b;
//    }
//};
//
//
//vector<string> split( string str, string pattern)
//{
//    vector<string> ret;
//    if(pattern.empty()) return ret;
//    size_t start=0,index=str.find_first_of(pattern,0);
//    while(index!=str.npos)
//    {
//        if(start!=index)
//            ret.push_back(str.substr(start,index-start));
//        start=index+1;
//        index=str.find_first_of(pattern,start);
//    }
//    if(!str.substr(start).empty())
//        ret.push_back(str.substr(start));
//    return ret;
//};
//




#endif
