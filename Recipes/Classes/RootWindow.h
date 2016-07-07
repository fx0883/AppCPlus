

#ifndef __HelloCpp__RootWindow__
#define __HelloCpp__RootWindow__

#include <iostream>
#include "CrossApp.h"
#include "CDData.h"
#include "RecipeListViewController.h"
#include "RecipeInfo.h"
#include "SearchViewController.h"
USING_NS_CC;

class RootWindow: public CAWindow, public CAKeypadDelegate
{
    
public:

    static RootWindow* getInstance();
    
    RootWindow();
    
    virtual ~RootWindow();
    
    virtual bool init();
    virtual void draw();
    CC_SYNTHESIZE_READONLY(CANavigationController*, m_pRootNavigationController, RootNavigationController);
    CC_SYNTHESIZE_READONLY(CADrawerController*, m_pRootDrawerController, DrawerController);
    
    CC_SYNTHESIZE_READONLY(RecipeListViewController*, m_recipelistviewcontroller, RecipeListViewController);
    
    void initUIView();
//    void intNewsView();
    
    virtual void keyBackClicked();
    void buttonCallBack(CAControl* btn,DPoint point);
    void buttonSearch(CAControl* btn,DPoint point);

    
public:
    //Modify by Fx
    void refreshRecipeListByMonth(int intMonth);
    void refreshRecipeListBySearchKey(string& strSearchKey);
    void refreshRecipeListByType(string& strType);
    void refreshRecipeListforFavorite();
    void showRecipeDetail(RecipeInfo*& pRecipeInfo);
    void showRecipeDetail(RecipeInfo*& pRecipeInfo,bool isCanFav);
    
    void closeSearchView();
    
public:
    void alertCallBack(int btnIndex);
    
private:
//    CSearchViewController* pSearchViewController;
    
};


#endif /* defined(__HelloCpp__ViewController__) */
