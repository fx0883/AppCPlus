

#include "RootWindow.h"
//#include "FirstViewController.h"
#include "MenuViewController.h"
#include "RecipeListViewController.h"
#include "RecipeDetailViewController.h"
#include "CDData.h"
//#include "SearchViewController.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

static RootWindow* _window = NULL;

RootWindow* RootWindow::getInstance()
{
    if (_window == NULL)
    {
        _window = new RootWindow();
        _window->init();
        _window->autorelease();
    }
    return _window;
    
}

RootWindow::RootWindow()
:m_pRootNavigationController(NULL)
,m_pRootDrawerController(NULL)
,m_recipelistviewcontroller(NULL)
//,pSearchViewController(NULL)
{
    CAApplication::getApplication()->getKeypadDispatcher()->addDelegate(this);
}

RootWindow::~RootWindow()
{
    CAApplication::getApplication()->getKeypadDispatcher()->removeDelegate(this);
}

bool RootWindow::init()
{
//    if (!CAWindow::init())
//    {
//        return false;
//    }
//    
//    FirstViewController* _viewController = new FirstViewController();
//    _viewController->init();
//    this->setRootViewController(_viewController);
//    _viewController->release();
//    
//    return true;
    
    if (!CAWindow::init())
    {
        return false;
    }
    
    CAApplication::getApplication()->setNotificationView(CAView::createWithFrame(this->getBounds(), CAColor_green));
    
    this->initUIView();
    
    MenuViewController* _menuview = MenuViewController::create();

    
    CADrawerController* drawer = new CADrawerController();
    drawer->initWithController(_menuview, m_pRootNavigationController);
    drawer->setBackgroundImage(CAImage::create("image/bg.jpg"));

    drawer->setEffect3D(false);
    
    this->setRootViewController(drawer);
//    drawer->showLeftViewController(true);
    drawer->autorelease();
    
    m_pRootDrawerController = drawer;

    CAApplication::getApplication()->setNotificationView(NULL);
    
    return true;
}


void RootWindow::draw()
{
    
}

void RootWindow::initUIView()
{
    do
    {
        CAViewController* viewController = m_pRootNavigationController ? m_pRootNavigationController->getViewControllerAtIndex(0) : NULL;
        
        CC_BREAK_IF(dynamic_cast<RecipeListViewController*>(viewController));
        
//        FirstViewController* tabBarController = new FirstViewController();
//        tabBarController->init();
//        tabBarController->autorelease();
        m_recipelistviewcontroller  = RecipeListViewController::create();
     //   recipelistviewcontroller->autorelease();
        CANavigationBarItem* temp_nav = CANavigationBarItem::create(UTF8("怀孕期间吃什么"));
        CABarButtonItem* item = CABarButtonItem::create("", CAImage::create("image/ic_category_list.png"), NULL);
        item->setTarget(this, CAControl_selector(RootWindow::buttonCallBack));
        
        
        CABarButtonItem *rightButton = CABarButtonItem::create("", CAImage::create("image/search.png"), CAImage::create("image/search.png"));
        rightButton->setTarget(this, CAControl_selector(RootWindow::buttonSearch));
        temp_nav->addRightButtonItem(rightButton);
        temp_nav->addLeftButtonItem(item);
        m_recipelistviewcontroller->setNavigationBarItem(temp_nav);
        
        temp_nav->retain();
        
        if (m_pRootNavigationController)
        {
            m_pRootNavigationController->replaceViewController(m_recipelistviewcontroller, false);
        }
        else
        {
            m_pRootNavigationController = new CANavigationController();
            m_pRootNavigationController->initWithRootViewController(m_recipelistviewcontroller);
//            m_pRootNavigationController->setNavigationBarBackgroundImage(CAImage::create("image/navbg.jpg"));
            m_pRootNavigationController->setNavigationBarBackgroundColor(NavColor);
        }
        

        
    }
    while (0);
    
    if (m_pRootDrawerController)
    {
        m_pRootDrawerController->hideLeftViewController(true);
    }
    
    CAApplication::getApplication()->setStatusBarStyle(CAStatusBarStyleLightContent);
}

void RootWindow::buttonCallBack(CAControl* btn,DPoint point)
{
    this->getDrawerController()->showLeftViewController(true);
}

void RootWindow::buttonSearch(CAControl* btn,DPoint point)
{

    CSearchViewController *pSearchViewController = new CSearchViewController();
    

    pSearchViewController->init();
    pSearchViewController->autorelease();

    
    m_pRootNavigationController->pushViewController(pSearchViewController, true);
}


void RootWindow::keyBackClicked()
{
    CC_RETURN_IF(CAAlertView::hideWithDisplayed());
    
    if (this->getModalViewController())
    {
        this->dismissModalViewController(true);
    }
    else if (this->getDrawerController()->isShowLeftViewController())
    {
        this->getDrawerController()->hideLeftViewController(true);
    }
    else if (this->getRootNavigationController()->getViewControllerCount() > 1)
    {
        this->getRootNavigationController()->popViewControllerAnimated(true);
    }
    else
    {
        CAAlertView *pAlertView = CAAlertView::createWithText("", UTF8("你确定要退出？"), UTF8("确定"), UTF8("取消"), NULL);
        pAlertView->setTarget(this, CAAlertView_selector(RootWindow::alertCallBack));
        pAlertView->show();
//        CAApplication::getApplication()->end();
    }
}

void RootWindow::alertCallBack(int btnIndex)
{
    if (btnIndex == 0)
    {
        CAApplication::getApplication()->end();
    }
}

void RootWindow::refreshRecipeListByMonth(int intMonth)
{
    this->getRecipeListViewController()->refreshDataByMonth(intMonth);
}

void RootWindow::refreshRecipeListBySearchKey(string& strSearchKey)
{
//    this->getRootNavigationController()->popViewControllerAnimated(false);
    this->getRecipeListViewController()->refreshDataforSearchKey(strSearchKey);
    
    
    CAScheduler::schedule(schedule_selector(RootWindow::closeSearchView), this, 1, 0, 1);
    
}


void RootWindow::refreshRecipeListByType(string& strType)
{
    //    this->getRootNavigationController()->popViewControllerAnimated(false);
    this->getRecipeListViewController()->refreshDataforType(strType);

}


void RootWindow::refreshRecipeListforFavorite()
{
    this->getRecipeListViewController()->refreshRecipeListforFavorite();
}


void RootWindow::closeSearchView()
{
    this->getRootNavigationController()->popViewControllerAnimated(false);
    
    CAScheduler::unschedule(schedule_selector(RootWindow::closeSearchView), this);
}



void RootWindow::showRecipeDetail(RecipeInfo*& pRecipeInfo)
{
//    RecipeDetailViewController* pRecipeDetailViewController = new RecipeDetailViewController(pRecipeInfo);
//    pRecipeDetailViewController->init();
//    pRecipeDetailViewController->autorelease();
//    CANavigationBarItem* temp_nav = CANavigationBarItem::create(pRecipeInfo->getName());
//    pRecipeDetailViewController->setNavigationBarItem(temp_nav);
//    this->getRootNavigationController()->pushViewController(pRecipeDetailViewController, true);
    this->showRecipeDetail(pRecipeInfo, true);
}

void RootWindow::showRecipeDetail(RecipeInfo*& pRecipeInfo,bool isCanFav)
{
    RecipeDetailViewController* pRecipeDetailViewController = new RecipeDetailViewController(pRecipeInfo);
    pRecipeDetailViewController->setShowRightButton(isCanFav);
    pRecipeDetailViewController->init();
    pRecipeDetailViewController->autorelease();
    CANavigationBarItem* temp_nav = CANavigationBarItem::create(pRecipeInfo->getName());
    pRecipeDetailViewController->setNavigationBarItem(temp_nav);
    this->getRootNavigationController()->pushViewController(pRecipeDetailViewController, true);
}






