//
//  RecipeInfo.hpp
//  Recipes
//
//  Created by apple on 6/19/16.
//
//

#ifndef RecipeInfo_h
#define RecipeInfo_h

#include <stdio.h>
#include "Crossapp.h"


#include <stdio.h>
#include "CrossApp.h"
#include <string>
#include <vector>

using namespace::std;

class RecipeInfo:public CAObject
{
public:
    CC_SYNTHESIZE_PASS_BY_REF(int, m_id, ID)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_name, Name)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_ingredients, Ingredients)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_steps, Steps)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_prompt, Prompt)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_photo, Photo)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_suberPhoto, SuberPhoto)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_type, Type)
    CC_SYNTHESIZE_PASS_BY_REF(int, m_month, Month)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_suberName, SuberName)
    CC_SYNTHESIZE_PASS_BY_REF(vector<string>, m_steplist, StepList)
    CC_SYNTHESIZE_PASS_BY_REF(bool, m_bIsChecked, IsChecked)
public:
    RecipeInfo();
    ~RecipeInfo();
    
};

#endif /* RecipeInfo_hpp */
