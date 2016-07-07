//
//  RecipeDetailViewController.cpp
//  Recipes
//
//  Created by apple on 6/25/16.
//
//

#include "RecipeDetailViewController.h"
#include "RecipeDetail1Cell.h"
#include "RecipeDetail2Cell.h"
#include "RootWindow.h"
#include "AppMacros.h"
#include "FSDataManager.h"
RecipeDetailViewController::RecipeDetailViewController()
:p_TableView(NULL)
,m_showRightButton(false)
{
    //m_recipeData = FSDataManager::GetInstance().getRecipeManager()->loadRecipesForMonth(1);
}

RecipeDetailViewController::RecipeDetailViewController(RecipeInfo*& pRecipeInfo)
:p_TableView(NULL)
{
    m_RecipeInfo = pRecipeInfo;
}


RecipeDetailViewController::~RecipeDetailViewController()
{
    
}


void RecipeDetailViewController::viewDidLoad()
{

    initRecipeTableView();
    
    if(m_showRightButton)
    {
    CABarButtonItem* rightButton = CABarButtonItem::create("", CAImage::create("image/unfavor-icon.png"), CAImage::create("image/favor-icon.png"));
    
    rightButton->setTarget(this, CAControl_selector(RecipeDetailViewController::onClickRightButtuon));
    CANavigationBarItem* curNavItem = this->getNavigationBarItem();
    curNavItem->addRightButtonItem(rightButton);
    this->setNavigationBarItem(curNavItem);
    }
    
}

void RecipeDetailViewController::viewDidAppear()
{
    bool isfavorite = FSDataManager::GetInstance().getRecipeManager()->isFavorite(m_RecipeInfo->getID());
//    if(isfavorite)
//    {
//        
//    }
//    else
//    {
//        
//    }
    this->setRightButtonState(isfavorite);
}

//bool a=false;
void RecipeDetailViewController::onClickRightButtuon(CAControl* btn,DPoint point)
{
//    CANavigationBarItem* curNavItem = this->getNavigationBarItem();
//    CABarButtonItem* rightButton =   dynamic_cast<CABarButtonItem*>(curNavItem->getRightButtonItems().at(0));
//    if(rightButton!=NULL)
//    {
//        if(a)
//        {
//            rightButton->setImage(CAImage::create("image/unfavor-icon.png"));
//        }
//        else
//        {
//            rightButton->setImage(CAImage::create("image/favor-icon.png"));
//        }
//        a=!a;
//
//    }
//    this->setNavigationBarItem(curNavItem);
    
    bool isfavorite = FSDataManager::GetInstance().getRecipeManager()->isFavorite(m_RecipeInfo->getID());
    if(!isfavorite)
    {
        FSDataManager::GetInstance().getRecipeManager()->addfavoriteRecipe(m_RecipeInfo->getID());
    }
    else
    {
        FSDataManager::GetInstance().getRecipeManager()->removefavoriteRecipe(m_RecipeInfo->getID());
    }
    this->setRightButtonState(!isfavorite);
    FSDataManager::GetInstance().getRecipeManager()->savefavoriteRecipes();
}

void RecipeDetailViewController::setRightButtonState(bool isSelect)
{
    CANavigationBarItem* curNavItem = this->getNavigationBarItem();
    CABarButtonItem* rightButton =   dynamic_cast<CABarButtonItem*>(curNavItem->getRightButtonItems().at(0));
    if(rightButton!=NULL)
    {
        if(isSelect)
        {
            rightButton->setImage(CAImage::create("image/favor-icon.png"));
        }
        else
        {
            rightButton->setImage(CAImage::create("image/unfavor-icon.png"));
        }
    }
    this->setNavigationBarItem(curNavItem);
}

void RecipeDetailViewController::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

void RecipeDetailViewController::initRecipeTableView()
{
    
    if (p_TableView!=NULL)
    {
        this->getView()->removeSubview(p_TableView);
        p_TableView = NULL;
    }
    
    p_TableView= CATableView::createWithLayout(DLayoutFill);
    p_TableView->setTableViewDataSource(this);
    p_TableView->setTableViewDelegate(this);
    //    p_TableView->setScrollViewDelegate(this);
    p_TableView->setSeparatorColor(CAColor_clear);
    p_TableView->setAllowsSelection(false);
    this->getView()->addSubview(p_TableView);

}



void RecipeDetailViewController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    //    CDWebViewController* _webController = new CDWebViewController();
    //    _webController->init();
    //    _webController->setTitle(" ");
    //
    //    _webController->autorelease();
    //    RootWindow::getInstance()->getDrawerController()->hideLeftViewController(true);
    //    RootWindow::getInstance()->getRootNavigationController()->pushViewController(_webController, true);
    //    _webController->initWebView(m_msg[row].m_url);
}

void RecipeDetailViewController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
}

CATableViewCell* RecipeDetailViewController::tableCellAtIndex(CATableView* table, const DSize& cellSize, unsigned int section, unsigned int row)
{
    
//    RecipesTableCell* cell = dynamic_cast<RecipesTableCell*>(table->dequeueReusableCellWithIdentifier("CrossApp"));
//    if (cell == NULL)
//    {
//        cell = RecipesTableCell::create("RecipeListCell");
//    }
//    cell->setModel(*m_recipeData->at(row));
//    
//    return cell;
   CATableViewCell *cell;
   if(section == 0)
   {
       cell = table->dequeueReusableCellWithIdentifier("RecipeCell1");
       if(cell == NULL)
       {
           cell = RecipeDetail1Cell::create("RecipeCell1");
       }
       dynamic_cast<RecipeDetail1Cell*>(cell)->setModel(*m_RecipeInfo);
       
   }
   else if(section == 1 || section == 3)
   {
       cell = table->dequeueReusableCellWithIdentifier("RecipeCell2");
       if(cell == NULL)
       {
           cell = CATableViewCell::create("RecipeCell2");
           CALabel *label = CALabel::createWithLayout(DLayout(DHorizontalLayout_L_R(10, 10), DVerticalLayoutFill));
           label->setColor(CAColor_black);
           label->setTextAlignment(CATextAlignmentLeft);
           //    theDesc->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
           label->setFontSize(28);
           label->setTag(102);
           label->setColor(CAColor_gray);
           label->setLineSpacing(0);
           cell->getContentView()->addSubview(label);
           
           if(section == 1)
           {
               label->setText(m_RecipeInfo->getIngredients());
           }
           else if(section == 3)
           {
               label->setText(m_RecipeInfo->getPrompt());
           }
           
           CCLOG("%f",hee);

       }
//       dynamic_cast<RecipeDetail1Cell*>(cell)->setModel(*m_RecipeInfo);

   }
   else if(section == 2)
   {
       cell = table->dequeueReusableCellWithIdentifier("RecipeCellStep");
       if(cell == NULL)
       {
           cell = RecipeDetail2Cell::create("RecipeCellStep");
       }
       dynamic_cast<RecipeDetail2Cell*>(cell)->setString(m_RecipeInfo->getStepList().at(row));
   }

    
    return cell;
}





void RecipeDetailViewController::tableViewWillDisplayCellAtIndex(CATableView* table, CATableViewCell* cell, unsigned int section, unsigned int row)
{
    /*
     if (cell != NULL)
     {
     temp_time+=0.02f;
     CAViewAnimation::beginAnimations("", NULL);
     CAViewAnimation::setAnimationDuration(temp_time);
     CAViewAnimation::setAnimationDidStopSelector(this,CAViewAnimation0_selector(CDNewsViewController::tempCallBack));
     CAViewAnimation::commitAnimations();
     
     cell->getContentView()->setScale(0.8f);
     cell->getContentView()->setRotationY(-180);
     
     CAViewAnimation::beginAnimations("", NULL);
     CAViewAnimation::setAnimationDuration(0.3f);
     CAViewAnimation::setAnimationDelay(temp_time);
     cell->getContentView()->setScale(1.0f);
     cell->getContentView()->setRotationY(0);
     //执行动画
     CAViewAnimation::commitAnimations();
     }
     */
}

//void RecipeListViewController::tempCallBack()
//{
//    temp_time-=0.02f;
//}

unsigned int RecipeDetailViewController::numberOfSections(CATableView *table)
{
    return 4;
}

unsigned int RecipeDetailViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    //    FSDataManager::GetInstance().getRecipeManager()->loadRecipesForMonth(1,m_recipeData);
    
    unsigned int rowCount = 1;
    if(section == 2)
    {
        rowCount = (unsigned int)m_RecipeInfo->getStepList().size();
    }
    
    return rowCount;
    
}

unsigned int RecipeDetailViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    unsigned int rowHeight = 100;
    
    if(section == 0)
    {
        float fwinWidth = CAApplication::getApplication()->getWinSize().width;
        rowHeight = fwinWidth*3/4;
//        rowHeight += 120;
    }
    else if(section == 1)
    {
        rowHeight = CAImage::getStringHeight("", 28, m_RecipeInfo->getIngredients(), CAApplication::getApplication()->getWinSize().width-20);
        rowHeight += 5;

        
    }
    else if(section == 2)
    {
//        rowHeight = 150;
        
        rowHeight = CAImage::getStringHeight("", 28, m_RecipeInfo->getStepList().at(row)
                                             , CAApplication::getApplication()->getWinSize().width-20);
        if(rowHeight <= 145)
        {
            rowHeight = 150;
        }
        else
        {
            rowHeight += 5;
        }
        
    }
    else if(section == 3)
    {
        rowHeight = CAImage::getStringHeight("", 28, m_RecipeInfo->getPrompt(), CAApplication::getApplication()->getWinSize().width-20);
        rowHeight += 20;
    }
    
    return rowHeight;
}




CAView* RecipeDetailViewController::tableViewSectionViewForHeaderInSection(CATableView* table, const DSize& viewSize, unsigned int section)
{
    std::string head = "";
    if(section == 0)
    {
        if(m_RecipeInfo->getMonth()>0)
        {
            char strTitle[48];
            sprintf(strTitle, "第%d个月",m_RecipeInfo->getMonth());
            head = strTitle;
        }
        else
        {
            head = UTF8("功能性食谱");
        }
  
        
    }
    if(section>0)
    {
        head = unicode_to_utf8(recipeDetailStep[section-1]);
    }

    CAView* view = CAView::createWithColor(SectionTitleColor);
     float fwinWidth = CAApplication::getApplication()->getWinSize().width;
    DSize _size = viewSize;
    CALabel* header = CALabel::createWithLayout(DLayout(DHorizontalLayout_L_W(20,fwinWidth/2), DVerticalLayoutFill));
    header->setText(head);
    header->setFontSize(30);
    header->setColor(CAColor_white);
    header->setTextAlignment(CATextAlignmentLeft);
    header->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    view->addSubview(header);
    
    
    if(section == 2 || section == 0)
    {
    CALabel* headerRight = CALabel::createWithLayout(DLayout(DHorizontalLayout_R_W(20,fwinWidth/2), DVerticalLayoutFill));
        char rightText[48];
        sprintf(rightText, "共%lu步",m_RecipeInfo->getStepList().size());
    if(section == 2)
        headerRight->setText(rightText);
    if(section==0)
        headerRight->setText(m_RecipeInfo->getType());
    headerRight->setFontSize(30);
    headerRight->setColor(CAColor_white);
    headerRight->setTextAlignment(CATextAlignmentRight);
    headerRight->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    view->addSubview(headerRight);
    }
    
    return view;
}



unsigned int RecipeDetailViewController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
    unsigned int headerHeight = 100;
    
    if(section == 0)
    {
        headerHeight = 60;
    }
    else
    {
        headerHeight = 60;
    }
    
    return headerHeight;

}
