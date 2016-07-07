//
//  FSRecipeManager.cpp
//  Recipes
//
//  Created by apple on 6/19/16.
//
//

#include "FSRecipeManager.h"
#include "FSContext.h"

#include "GlobalFunction.h"

//

bool FSRecipeManager::init()
{
    
    bool bRet = true;

    return bRet;
}
FSRecipeManager::FSRecipeManager()
:_sqlite3(NULL)
{
//    loadRecipesForMonth(1);
}


FSRecipeManager::~FSRecipeManager()
{
    CCLog("~FSRecipeManager");
}


void FSRecipeManager::loadRecipesForType(string strType,CAVector<RecipeInfo*>*& pVectorRecipe)
{
    //    return;
    if(this->getRecipesMap().contains(strType))
    {
        pVectorRecipe = this->getRecipesMap().getValue(strType);
        return;
    }
    else
    {
        pVectorRecipe = new CAVector<RecipeInfo*>();
        
    }
    
    int ret = 0;
    //    CCLog("fullPath = %s",DBPATH);
    
    ret = sqlite3_open(FSContext::GetInstance().getDbPath().c_str(), &_sqlite3);
    //查询结果
    char **re;
    //行、列
    int r,c;
    
    char strSql[256];
    sprintf(strSql, "select * from recipe where type = '%s'",strType.c_str());
    
    //    sprintf(strSql, "select * from CB_WomanRecipe where month = %d",2);
    
    CCLog("strSql = %s",strSql);
    
    sqlite3_get_table(_sqlite3,strSql,&re,&r,&c,NULL);
    CCLog("=================> count = %d",r);
    for(int i=1;i<=r;i++)
    {
        //        CCLog("=================>12");
        RecipeInfo *recipeinfo = new RecipeInfo();
        int id = atoi(re[i*c+0]);
        recipeinfo->setID(id);
        recipeinfo->setName(re[i*c+1]);
        
        string strIngredients(re[i*c+2]);
        CGlobalFunction::string_replace(strIngredients,"<br>","\r\n");
        recipeinfo->setIngredients(strIngredients);
        //        recipeinfo->setSteps(re[i*c+3]);
        
        string strSteps(re[i*c+3]);
        recipeinfo->setSteps(strSteps);
        recipeinfo->setStepList(CGlobalFunction::split(strSteps,"<br>"));
        
        
        string strPrompt(re[i*c+4]);
        CGlobalFunction::string_replace(strPrompt,"<br>","\r\n");
        recipeinfo->setPrompt(strPrompt);
        
        
        
        recipeinfo->setPhoto(re[i*c+5]);
        recipeinfo->setSuberPhoto(re[i*c+6]);
        recipeinfo->setType(re[i*c+7]);
        
        recipeinfo->setMonth(std::atoi(re[i*c+8]));
        
        recipeinfo->setSuberName(re[i*c+9]);
        
        
        pVectorRecipe->pushBack(recipeinfo);
    }
    this->getRecipesMap().insert(strType, pVectorRecipe);
    
    
    sqlite3_free_table(re);
    sqlite3_close(_sqlite3);
    
}























void FSRecipeManager::searchRecipesForKey(string strSearchKey,CAVector<RecipeInfo*>*& pVectorRecipe)
{
//    return;
    if(this->getRecipesMap().contains(strSearchKey))
    {
        pVectorRecipe = this->getRecipesMap().getValue(strSearchKey);
        return;
    }
    else
    {
        pVectorRecipe = new CAVector<RecipeInfo*>();
        
    }
    
    int ret = 0;
    //    CCLog("fullPath = %s",DBPATH);
    
    ret = sqlite3_open(FSContext::GetInstance().getDbPath().c_str(), &_sqlite3);
    //查询结果
    char **re;
    //行、列
    int r,c;
    
    char strSql[256];
    sprintf(strSql, "select * from recipe where name like '%%%s%%' or ingredients like '%%%s%%'",strSearchKey.c_str(),strSearchKey.c_str());
    
//    sprintf(strSql, "select * from CB_WomanRecipe where month = %d",2);
    
    CCLog("strSql = %s",strSql);
    
    sqlite3_get_table(_sqlite3,strSql,&re,&r,&c,NULL);
    CCLog("=================> count = %d",r);
    for(int i=1;i<=r;i++)
    {
//        CCLog("=================>12");
        RecipeInfo *recipeinfo = new RecipeInfo();
        int id = atoi(re[i*c+0]);
        recipeinfo->setID(id);
        recipeinfo->setName(re[i*c+1]);
        
        string strIngredients(re[i*c+2]);
        CGlobalFunction::string_replace(strIngredients,"<br>","\r\n");
        recipeinfo->setIngredients(strIngredients);
//        recipeinfo->setSteps(re[i*c+3]);
        
        string strSteps(re[i*c+3]);
        recipeinfo->setSteps(strSteps);
        recipeinfo->setStepList(CGlobalFunction::split(strSteps,"<br>"));
        
        
        string strPrompt(re[i*c+4]);
        CGlobalFunction::string_replace(strPrompt,"<br>","\r\n");
        recipeinfo->setPrompt(strPrompt);
        
        
        
        recipeinfo->setPhoto(re[i*c+5]);
        recipeinfo->setSuberPhoto(re[i*c+6]);
        recipeinfo->setType(re[i*c+7]);

        recipeinfo->setMonth(std::atoi(re[i*c+8]));

        recipeinfo->setSuberName(re[i*c+9]);
        
        
        pVectorRecipe->pushBack(recipeinfo);
    }
    this->getRecipesMap().insert(strSearchKey, pVectorRecipe);
    
    
    sqlite3_free_table(re);
    sqlite3_close(_sqlite3);

}


void FSRecipeManager::loadFavorite(CAVector<RecipeInfo*>*& pVectorRecipe)
{
    pVectorRecipe = new CAVector<RecipeInfo*>();
    
    int ret = 0;
    //    CCLog("fullPath = %s",DBPATH);
    ret = sqlite3_open(FSContext::GetInstance().getDbPath().c_str(), &_sqlite3);
    //查询结果
    char **re;
    //行、列
    int r,c;
    
    char strSql[256];
    sprintf(strSql, "select * from recipe where id in (%s)",favoriteRecipeStr.c_str());
    
    //    sprintf(strSql, "select * from CB_WomanRecipe where month = %d",2);
    
    CCLog("strSql = %s",strSql);
    
    sqlite3_get_table(_sqlite3,strSql,&re,&r,&c,NULL);
    CCLog("=================> count = %d",r);
    for(int i=1;i<=r;i++)
    {
        //        CCLog("=================>12");
        RecipeInfo *recipeinfo = new RecipeInfo();
        int id = atoi(re[i*c+0]);
        recipeinfo->setID(id);
        recipeinfo->setName(re[i*c+1]);
        
        string strIngredients(re[i*c+2]);
        CGlobalFunction::string_replace(strIngredients,"<br>","\r\n");
        recipeinfo->setIngredients(strIngredients);
        //        recipeinfo->setSteps(re[i*c+3]);
        
        string strSteps(re[i*c+3]);
        recipeinfo->setSteps(strSteps);
        recipeinfo->setStepList(CGlobalFunction::split(strSteps,"<br>"));
        
        
        string strPrompt(re[i*c+4]);
        CGlobalFunction::string_replace(strPrompt,"<br>","\r\n");
        recipeinfo->setPrompt(strPrompt);
        
        
        
        recipeinfo->setPhoto(re[i*c+5]);
        recipeinfo->setSuberPhoto(re[i*c+6]);
        recipeinfo->setType(re[i*c+7]);
        
        recipeinfo->setMonth(std::atoi(re[i*c+8]));
        
        recipeinfo->setSuberName(re[i*c+9]);
        
        
        pVectorRecipe->pushBack(recipeinfo);
    }
    sqlite3_free_table(re);
    sqlite3_close(_sqlite3);
}




void FSRecipeManager::loadRecipesForMonth(int intMonth,CAVector<RecipeInfo*>*& pVectorRecipe)
{
    
    
    char strMonth[8];
    int length = sprintf(strMonth, "%d", intMonth);
    

    if(this->getRecipesMap().contains(strMonth))
    {
        pVectorRecipe = this->getRecipesMap().getValue(strMonth);
        return;
    }
    else
    {
        pVectorRecipe = new CAVector<RecipeInfo*>();
        
    }
    
    int ret = 0;
    //    CCLog("fullPath = %s",DBPATH);
        CCLog("=================>11");
    ret = sqlite3_open(FSContext::GetInstance().getDbPath().c_str(), &_sqlite3);
    
        CCLog("=================>12");
    
           CCLog("=================> ret = %d",ret);
    //查询结果
    char **re;
    //行、列
    int r,c;
    
    char strSql[100];
    sprintf(strSql, "select * from recipe where month = %d",intMonth);
    
    CCLog("%s",strSql);
    
    int intGetTable=sqlite3_get_table(_sqlite3,strSql,&re,&r,&c,NULL);
//    sqlite3_get_table(_sqlite3,"select * from CB_WomanRecipe",&re,&r,&c,NULL);
    
    CCLog("intGetTable %d",intGetTable);
    CCLog("count %d",r);
    
    for(int i=1;i<=r;i++)
    {
        RecipeInfo *recipeinfo = new RecipeInfo();
        int id = atoi(re[i*c+0]);
        recipeinfo->setID(id);
        recipeinfo->setName(re[i*c+1]);
        
        string strIngredients(re[i*c+2]);
        CGlobalFunction::string_replace(strIngredients,"<br>","\r\n");
        recipeinfo->setIngredients(strIngredients);
//        recipeinfo->setSteps(re[i*c+3]);
        
        string strSteps(re[i*c+3]);
        recipeinfo->setSteps(strSteps);
        recipeinfo->setStepList(CGlobalFunction::split(strSteps,"<br>"));
        
        
        string strPrompt(re[i*c+4]);
        CGlobalFunction::string_replace(strPrompt,"<br>","\r\n");
        recipeinfo->setPrompt(strPrompt);
        
        
        
        recipeinfo->setPhoto(re[i*c+5]);
        recipeinfo->setSuberPhoto(re[i*c+6]);
        recipeinfo->setType(re[i*c+7]);
        recipeinfo->setMonth(intMonth);
        recipeinfo->setSuberName(re[i*c+9]);
        

        pVectorRecipe->pushBack(recipeinfo);
    }
    CCLog("=================>3");
    this->getRecipesMap().insert(strMonth, pVectorRecipe);
    
    CCLog("=================>4");
    sqlite3_free_table(re);
    sqlite3_close(_sqlite3);
    return ;
}


void FSRecipeManager::loadfavoriteRecipes()
{
    favoriteRecipeStr = CAUserDefault::sharedUserDefault()->getStringForKey(FAVORITERECIPEKEY);
    if(favoriteRecipeStr != "")
    {
        vfavoriteRecipes = CGlobalFunction::stringSplitInt(favoriteRecipeStr,",");
    }
    
}

void FSRecipeManager::savefavoriteRecipes(CAVector<RecipeInfo*>*& pVectorRecipe)
{
    favoriteRecipeStr="";
    for (size_t i =0; i < pVectorRecipe->size(); i ++) {
        
        char strItem[20];
        
        sprintf(strItem, "%d",pVectorRecipe->at(i)->getID() );
        
        favoriteRecipeStr = favoriteRecipeStr + strItem;
        if(i<pVectorRecipe->size() - 1)
        {
            favoriteRecipeStr = favoriteRecipeStr + ",";
        }
    }
    vfavoriteRecipes = CGlobalFunction::stringSplitInt(favoriteRecipeStr,",");
    savefavoriteRecipes();
}

void FSRecipeManager::savefavoriteRecipes()
{
    favoriteRecipeStr = CGlobalFunction::vectorToString(vfavoriteRecipes, ",");
    CAUserDefault::sharedUserDefault()->setStringForKey(FAVORITERECIPEKEY, favoriteRecipeStr);
}

bool FSRecipeManager::isFavorite(int recipeId)
{
    vector<int>::iterator it;

    
    it=find(vfavoriteRecipes.begin(),vfavoriteRecipes.end(),recipeId);
    
    bool ret = false;
    if (it!=vfavoriteRecipes.end())
    {
        //vec中存在value值
        ret = true;
    }
    else
    {
        //vec中不存在value值
        ret = false;
    }
    
    return ret;
}

void FSRecipeManager::addfavoriteRecipe(int recipeId)
{
    if(!isFavorite(recipeId))
    {
        vfavoriteRecipes.push_back(recipeId);
    }
}

void FSRecipeManager::removefavoriteRecipe(int recipeId)
{
//    for(size_t i = 0;i<vfavoriteRecipes.size();i++)
//    {
//        if(recipeId==vfavoriteRecipes[i])
//        {
//            vfavoriteRecipes
//        }
//    }
    
    vector<int>::iterator it;

for(it=vfavoriteRecipes.begin();it!=vfavoriteRecipes.end();)
{
if(*it == recipeId)
{
    it=vfavoriteRecipes.erase(it);    //删除元素，返回值指向已删除元素的下一个位置
}

else
{
    ++it;    //指向下一个位置
}


    
}
}
