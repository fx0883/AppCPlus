//
//  MenuViewController.cpp
//  Test
//
//  Created by renhongguang on 15/4/3.
//
//

#include "MenuViewController.h"
#include "CDWebViewController.h"
#include "GlobalFunction.h"
//#include "CDUIShowAutoCollectionView.h"

MenuViewController::MenuViewController()
{
    CANotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(MenuViewController::changeStatusBarOrientation), CAApplicationDidChangeStatusBarOrientationNotification, NULL);
}

MenuViewController::~MenuViewController()
{
    CANotificationCenter::sharedNotificationCenter()->removeObserver(this, CAApplicationDidChangeStatusBarOrientationNotification);
}

void MenuViewController::initData()
{
    int intMemuCount = getArrayLen(menuList);
    for (int i = 0; i<intMemuCount; i++) {
        m_CanExpandMenu.insert(make_pair(i,false));
    }
    

    
}

bool MenuViewController::init()
{
    return true;
}

void MenuViewController::viewDidLoad()
{
    //Modify by fx
    initData();
    this->getView()->setColor(CAColor_clear);
    
    DLayout tableViewLayout;
    DLayout logoLayout;
//    const CAInterfaceOrientation& orientation = CAApplication::getApplication()->getStatusBarOrientation();
//    if (orientation == CAInterfaceOrientationLandscape)
    {
        tableViewLayout = DLayout(DHorizontalLayout_L_R(30, 10), DVerticalLayout_B_H(0, AppHeight*3/4));
        logoLayout = DLayout(DHorizontalLayout_W_C(AppHeight/8, 0.5), DVerticalLayout_T_H((AppHeight/8)-(AppHeight/16), AppHeight/8));
    }
//    else
//    {
//        tableViewLayout = DLayout(DHorizontalLayoutFill, DVerticalLayout_T_B(450, 0));
//        logoLayout = DLayout(DHorizontalLayout_W_C(261, 0.5), DVerticalLayout_T_H(120, 258));
//    }
    
    CAView *topViewLine = CAView::createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_B_H(AppHeight*3/4,1)), CAColor_white);
    
    this->getView()->addSubview(topViewLine);
    
//    CAView *topView = CAView::createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_T_H(0, AppHeight/4)), MenuTopViewColor);
//    
//    this->getView()->addSubview(topView);
    CALabel* appNameLabel = CALabel::createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_T_H((AppHeight/4)-(AppHeight/16), AppHeight/16)));
    appNameLabel->setTextAlignment(CATextAlignmentCenter);
    appNameLabel->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    appNameLabel->setFontSize(32);
    appNameLabel->setColor(CAColor_black);
    appNameLabel->setTag(109);
    appNameLabel->setText("孕妇营养食谱A+");
    this->getView()->addSubview(appNameLabel);
    
    
    tableView = CATableView::createWithLayout(tableViewLayout);
//    tableView->setLayout(tableViewLayout);
    tableView->setAllowsSelection(true);
    tableView->setTableViewDelegate(this);
    tableView->setTableViewDataSource(this);
    tableView->setBackgroundColor(CAColor_clear);
    tableView->setSeparatorColor(ccc4(255, 255, 255,100));
//    tableView->setShowsScrollIndicators(true);
    tableView->setScrollEnabled(true);

    this->getView()->addSubview(tableView);
    
    m_pLogo = CAImageView::createWithImage(CAImage::create("image/logo.png"));
    m_pLogo->setLayout(logoLayout);
    this->getView()->addSubview(m_pLogo);
//    topView->addSubview(m_pLogo);
    
    
}

void MenuViewController::viewDidUnload()
{

}

void MenuViewController::changeStatusBarOrientation(CAObject* obj)
{
    const CAInterfaceOrientation& orientation = CAApplication::getApplication()->getStatusBarOrientation();
    
    DLayout tableViewLayout;
    DLayout logoLayout;
    if (orientation == CAInterfaceOrientationLandscape)
    {
        tableViewLayout = DLayout(DHorizontalLayoutFill, DVerticalLayout_B_H(0, 400));
        logoLayout = DLayout(DHorizontalLayout_W_C(261, 0.5), DVerticalLayout_T_H(120, 258));
    }
    else
    {
        tableViewLayout = DLayout(DHorizontalLayoutFill, DVerticalLayout_T_B(450, 0));
        logoLayout = DLayout(DHorizontalLayout_W_C(261, 0.5), DVerticalLayout_T_H(120, 258));
    }
    
    tableView->setLayout(tableViewLayout);
    m_pLogo->setLayout(logoLayout);
}

void MenuViewController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    RootWindow::getInstance()->dismissModalViewController(true);
    
    if(getArrayNumber(menuList[section])>1 && row == 0)
    {
        if (m_CanExpandMenu[section])
        {
            m_CanExpandMenu[section]  = false;
        }
        else
        {
            m_CanExpandMenu[section]  = true;
        }
        
        this->tableView->reloadData();
        

    }
    else
    {
        switch (section) {
            case 0:
            {
                int intMonth  = row;
                RootWindow::getInstance()->refreshRecipeListByMonth(intMonth);
                RootWindow::getInstance()->getDrawerController()->hideLeftViewController(true);
                break;
            }
            case 1:
            {
                int intMonth  = row+3;
                RootWindow::getInstance()->refreshRecipeListByMonth(intMonth);
                RootWindow::getInstance()->getDrawerController()->hideLeftViewController(true);
                break;
            }
            case 2:
                
            {
                int intMonth  = row+6;
                RootWindow::getInstance()->refreshRecipeListByMonth(intMonth);
                RootWindow::getInstance()->getDrawerController()->hideLeftViewController(true);
                break;
            }
            case 3:
                
            {
                string strType = unicode_to_utf8(menuList[section][row]);
                RootWindow::getInstance()->refreshRecipeListByType(strType);
                RootWindow::getInstance()->getDrawerController()->hideLeftViewController(true);
                break;
            }
                
            case 4:
                
            {
 
                RootWindow::getInstance()->refreshRecipeListforFavorite();
                RootWindow::getInstance()->getDrawerController()->hideLeftViewController(true);
                break;
            }
                
            default:
                break;
        }
    }
    
    
}




CATableViewCell* MenuViewController::tableCellAtIndex(CATableView* table, const DSize& cellSize, unsigned int section, unsigned int row)
{
    CATableViewCell* cell = table->dequeueReusableCellWithIdentifier("CrossApp");
    if (cell == NULL)
    {
        cell = CATableViewCell::create("CrossApp");
        cell->setBackgroundView(NULL);
        CALabel* test = CALabel::createWithLayout(DLayout(DHorizontalLayout_L_R(70, 0), DVerticalLayoutFill));
        test->setTextAlignment(CATextAlignmentLeft);
        test->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
        test->setFontSize(40);
		test->setColor(MenuTextColor);
        test->setTag(100);
        cell->addSubview(test);
        
        CAView *leftFlagView = CAView::createWithLayout(DLayout(DHorizontalLayout_L_W(50, 10), DVerticalLayout_H_C(10, 0.5)), CAColor_red);
        leftFlagView->setTag(102);
        cell->addSubview(leftFlagView);
        
//        CAImageView* arrow = CAImageView::createWithLayout(DLayout(DHorizontalLayout_R_W(0, 64), DVerticalLayout_T_H(20, 64)));
//        arrow->setTag(101);
//        cell->addSubview(arrow);
    }
	CALabel* test = (CALabel*)cell->getSubviewByTag(100);
    
    std::string strText;

    strText = unicode_to_utf8(menuList[section][row]);
    
	test->setText(strText);// menuList[row]);
    
    
    
//    CAImageView* arrow = (CAImageView*)cell->getSubviewByTag(101);
    CAView* leftview = (CAView*)cell->getSubviewByTag(102);
    if(getArrayNumber(menuList[section])>1 && row == 0)
    {
//        arrow->setImage(CAImage::create("source_material/cell_btn_right.png"));
        
   
        leftview->setVisible(true);
        
    }
    else
    {
//        arrow->setImage(NULL);
        leftview->setVisible(false);
    }

    
    return cell;
}

unsigned int MenuViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    unsigned int intCount = 1;
    if(m_CanExpandMenu[section])
    {
        
    
        intCount = getArrayNumber(menuList[section]);
    }
    
    return intCount;
}

unsigned int MenuViewController::numberOfSections(CATableView *table)
{
    return getArrayLen(menuList);
}

unsigned int MenuViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    return 100;
}
