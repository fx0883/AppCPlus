//
//  RecipeListViewController.cpp
//  Recipes
//
//  Created by apple on 6/20/16.
//
//

#include "RecipeListViewController.h"

#include "RecipesTableCell.h"
#include "FSDataManager.h"
#include "RootWindow.h"
#include "GlobalFunction.h"


//静态数据成员的定义和初始化
RecipeListViewController* RecipeListViewController::curRecipeListViewController = NULL;
RecipeListViewController::RecipeListViewController()
:p_TableView(NULL)
,m_recipeData(NULL)
,m_strSectionTitle("")
,m_editNavBar(NULL)
,m_editFinishNavBar(NULL)
,m_bottomViewHight(0)
,m_editModel(false)
,m_editView(false)

{
    //m_recipeData = FSDataManager::GetInstance().getRecipeManager()->loadRecipesForMonth(1);
    curRecipeListViewController = this;
}

RecipeListViewController::~RecipeListViewController()
{
 
}

void RecipeListViewController::refreshRecipeTable()
{
    loadDataforMonth(1);
    p_TableView->reloadData();
}



void RecipeListViewController::viewDidLoad()
{
    this->setNavigationBarItem(this->getNavigationBarItem());
    m_curNavBar = this->getNavigationBarItem();
  //  searchBarButton = (CABarButtonItem*)m_curNavBar->getRightButtonItems().at(0);

    
    loadDataforMonth(1);
    initViewLayout();
    
    initRecipeTableView();
    initEditBottomView();
    
//    setToEditView(true);

}

void RecipeListViewController::refreshDataByMonth(int intMonth)
{
    loadDataforMonth(intMonth);
    this->setToEditView(false);
    this->setToEditModel(false);
//    p_TableView->reloadData();
}



void RecipeListViewController::refreshDataforSearchKey(string& strSearchKey)
{
 
    FSDataManager::GetInstance().getRecipeManager()->searchRecipesForKey(strSearchKey, m_recipeData);
//    CCLog("=================>refreshDataforSearchKey11111111");
 
    
    char chrSectionTitle[200];
    sprintf(chrSectionTitle, "%s共搜索到%zu条结果",strSearchKey.c_str(),m_recipeData->size());
    m_strSectionTitle = chrSectionTitle;
    
    this->setToEditView(false);
    this->setToEditModel(false);
//    p_TableView->reloadData();
}


void RecipeListViewController::refreshDataforType(string& strType)
{
    
    FSDataManager::GetInstance().getRecipeManager()->loadRecipesForType(strType, m_recipeData);
    //    CCLog("=================>refreshDataforSearchKey11111111");
    m_strSectionTitle = strType;
    
    this->setToEditView(false);
    this->setToEditModel(false);
    //    p_TableView->reloadData();
}




void RecipeListViewController::refreshRecipeListforFavorite()
{
    FSDataManager::GetInstance().getRecipeManager()->loadFavorite(m_recipeData);
    //    CCLog("=================>refreshDataforSearchKey11111111");

    m_strSectionTitle = "我的收藏";
    
    //    CCLog("=================>refreshDataforSearchKey222222222");
    this->setToEditView(true);
    this->setToEditModel(false);
}

void RecipeListViewController::loadDataforMonth(int intMonth)
{
    FSDataManager::GetInstance().getRecipeManager()->loadRecipesForMonth(intMonth,m_recipeData);
    
    char chrSectionTitle[48];
    sprintf(chrSectionTitle, "第%d个月的营养食谱",intMonth);
    m_strSectionTitle = chrSectionTitle;
    
    
//    this->setToEditView(false);
//    this->setToEditModel(false);
}





void RecipeListViewController::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

void RecipeListViewController::initRecipeTableView()
{

    if (p_TableView!=NULL)
    {
        this->getView()->removeSubview(p_TableView);
        p_TableView = NULL;
    }
    
    p_TableView= CATableView::createWithLayout(m_tabelViewLayout[0]);
    p_TableView->setTableViewDataSource(this);
    p_TableView->setTableViewDelegate(this);

    p_TableView->setAllowsSelection(true);
    this->getView()->addSubview(p_TableView);

}

void RecipeListViewController::initViewLayout()
{
    m_tabelViewLayout[0].horizontal = DHorizontalLayoutFill;
    m_tabelViewLayout[0].vertical = DVerticalLayoutFill;
    
    m_bottomViewHight = AppHeight/10;
    m_tabelViewLayout[1].horizontal = DHorizontalLayoutFill;
    m_tabelViewLayout[1].vertical = DVerticalLayout_T_B(0, m_bottomViewHight);
    
    
    m_bottomViewLayout[0].horizontal = DHorizontalLayoutFill;
    m_bottomViewLayout[0].vertical = DVerticalLayout_B_H(-m_bottomViewHight, m_bottomViewHight);
    
    m_bottomViewLayout[1].horizontal = DHorizontalLayoutFill;
    m_bottomViewLayout[1].vertical = DVerticalLayout_B_H(0, m_bottomViewHight);
}



void RecipeListViewController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{

//    CATableViewCell* cellForRowAtIndexPath(unsigned int section, unsigned int row);
    if(m_editModel)
    {
        return;
    }
    
    
    RecipeInfo* pRecipe  = m_recipeData->at(row);
    RootWindow::getInstance()->showRecipeDetail(pRecipe,!m_editView);
    
}

void RecipeListViewController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
}

CATableViewCell* RecipeListViewController::tableCellAtIndex(CATableView* table, const DSize& cellSize, unsigned int section, unsigned int row)
{
    
//    CCLog("=================>tableCellAtIndex");
    RecipesTableCell* cell = dynamic_cast<RecipesTableCell*>(table->dequeueReusableCellWithIdentifier("RecipeListCell"));
    if (cell == NULL)
    {
        cell = RecipesTableCell::create("RecipeListCell");
    }
    cell->setModel(m_recipeData->at(row));
    cell->showRightButton(m_editModel);
    
    if(m_editModel)
    {
        cell->setRightButtonChecked(m_recipeData->at(row)->getIsChecked());
    }
    cell->clickCheckBox =&RecipeListViewController::onClickedCellButton;
    return cell;
    
}

void RecipeListViewController::tableViewWillDisplayCellAtIndex(CATableView* table, CATableViewCell* cell, unsigned int section, unsigned int row)
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

unsigned int RecipeListViewController::numberOfSections(CATableView *table)
{
    return 1;
}

unsigned int RecipeListViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
//    FSDataManager::GetInstance().getRecipeManager()->loadRecipesForMonth(1,m_recipeData);
    return (unsigned int)m_recipeData->size();
}

unsigned int RecipeListViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    return 200;
}


CAView* RecipeListViewController::tableViewSectionViewForHeaderInSection(CATableView* table, const DSize& viewSize, unsigned int section)
{
    std::string head = m_strSectionTitle;
    CAView* view = CAView::createWithColor(SectionTitleColor);
    
    DSize _size = viewSize;
    CALabel* header = CALabel::createWithLayout(DLayout(DHorizontalLayout_L_R(0,0), DVerticalLayoutFill));
    header->setText(head);
    header->setFontSize(30);
    header->setColor(CAColor_white);
    header->setTextAlignment(CATextAlignmentCenter);
    header->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    view->addSubview(header);
    
    return view;
}

unsigned int RecipeListViewController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
    
    return 60;
}


void RecipeListViewController::onClickedCellButton(CAControlState state)
{
    curRecipeListViewController->changeSeletedButtonText();
}

void RecipeListViewController::setToEditView(bool isEditView)
{
    m_editView = isEditView;
    if(isEditView)
    {

        if(m_editNavBar == NULL)
        {
            
            m_editNavBar = CANavigationBarItem::create(this->getNavigationBarItem()->getTitle());
            
            editBarButton = CABarButtonItem::create("编辑", NULL, NULL);
            editBarButton->setTarget(this, CAControl_selector(RecipeListViewController::buttonEdit));
            m_editNavBar->addRightButtonItem(editBarButton);
            
            
            CABarButtonItem* leftButton = CABarButtonItem::create("", CAImage::create("image/ic_category_list.png"), NULL);
            leftButton->setTarget(this, CAControl_selector(RecipeListViewController::onEditleftButtonClick));
            m_editNavBar->addLeftButtonItem(leftButton);
            
            m_editNavBar->retain();
        }

        this->setNavigationBarItem(m_editNavBar);
    }
    else
    {
        this->setNavigationBarItem(m_curNavBar);
    }
}

void RecipeListViewController::setToEditModel(bool isEditModel)
{
    if(isEditModel)
    {
        //控制下方选择view
        CAViewAnimation::beginAnimations("", NULL);
        CAViewAnimation::setAnimationDuration(0.1f);
        p_TableView->setLayout(m_tabelViewLayout[1]);
        m_EditBottomView->setLayout(m_bottomViewLayout[1]);
        CAViewAnimation::commitAnimations();
    }
    else
    {
        CAViewAnimation::beginAnimations("", NULL);
        CAViewAnimation::setAnimationDuration(0.1f);
        p_TableView->setLayout(m_tabelViewLayout[0]);
        m_EditBottomView->setLayout(m_bottomViewLayout[0]);
        CAViewAnimation::commitAnimations();
    }
    
    m_editModel = isEditModel;
        p_TableView->reloadData();
}

void RecipeListViewController::onEditleftButtonClick(CAControl* btn,DPoint point)
{
    RootWindow::getInstance()->getDrawerController()->showLeftViewController(true);
}

void RecipeListViewController::buttonEdit(CAControl* btn,DPoint point)
{
    
    if(m_editFinishNavBar == NULL)
    {
        
        m_editFinishNavBar = CANavigationBarItem::create(this->getNavigationBarItem()->getTitle());
        
        CABarButtonItem *finishBarButton = CABarButtonItem::create("完成", NULL, NULL);
        finishBarButton->setTarget(this, CAControl_selector(RecipeListViewController::onClickFinishButton));
        //            editBarButton->autorelease();
        m_editFinishNavBar->addRightButtonItem(finishBarButton);
        
        
        m_editFinishNavBar->retain();
        
        
    }
    this->setNavigationBarItem(m_editFinishNavBar);
    
    this->setToEditModel(true);

}

void RecipeListViewController::onClickFinishButton(CAControl* btn,DPoint point)
{
    setToEditModel(false);
    setToEditView(true);
}

void RecipeListViewController::showEditBottomView(bool isShow)
{

}
void RecipeListViewController::initEditBottomView()
{
    m_EditBottomView = CAView::createWithLayout(m_bottomViewLayout[0]);
    this->getView()->addSubview(m_EditBottomView);
    
    CAView* horizontallineview = CAView::createWithLayout(DLayout(DHorizontalLayout_L_R(1, 1), DVerticalLayout_T_H(1, 1)), CAColor_gray);
    m_EditBottomView->addSubview(horizontallineview);
    
    selectAllButton = CAButton::createWithLayout(DLayout(DHorizontalLayout_L_W(0, AppWidth/2 - 2), DVerticalLayoutFill), CAButtonTypeCustom);
    selectAllButton->setTitleFontSize(FONT3);
    selectAllButton->setTitleForState(CAControlState::CAControlStateAll, "全选");
    selectAllButton->addTarget(this, CAControl_selector(RecipeListViewController::onClickSelectAllButton), CAControlEvents::CAControlEventTouchUpInSide);
    m_EditBottomView->addSubview(selectAllButton);
    
    
    
    CAView* verticalLineView = CAView::createWithLayout(DLayout(DHorizontalLayout_L_W(AppWidth/2, 1), DVerticalLayout_T_B(5, 5)), CAColor_gray);
    m_EditBottomView->addSubview(verticalLineView);
    
    CAButton *rightButton = CAButton::createWithLayout(DLayout(DHorizontalLayout_R_W(0, AppWidth/2 - 2), DVerticalLayoutFill), CAButtonTypeCustom);
    rightButton->setTitleFontSize(FONT3);
    rightButton->setTitleForState(CAControlState::CAControlStateAll, "删除");
        rightButton->addTarget(this, CAControl_selector(RecipeListViewController::onClickDeleteButton), CAControlEvents::CAControlEventTouchUpInSide);
    m_EditBottomView->addSubview(rightButton);
}


void RecipeListViewController::onClickSelectAllButton(CAControl* btn,DPoint point)
{
    CAButton *curBtn = (CAButton*)btn;
    if(isSelectedAll())
    {
        setAllCheckBoxState(false);
        curBtn->setTitleForState(CAControlState::CAControlStateAll, "全选");
    }
    else
    {
        setAllCheckBoxState(true);
        curBtn->setTitleForState(CAControlState::CAControlStateAll, "全不选");
    }
    p_TableView->reloadData();
}


void RecipeListViewController::changeSeletedButtonText()
{

    if(!isSelectedAll())
    {
        selectAllButton->setTitleForState(CAControlState::CAControlStateAll, "全选");
    }
    else
    {
        selectAllButton->setTitleForState(CAControlState::CAControlStateAll, "全不选");
    }
    p_TableView->reloadData();
}



void RecipeListViewController::onClickDeleteButton(CAControl* btn,DPoint point)
{
//    vector<int>::iterator it;
//    
//    for(it=vfavoriteRecipes.begin();it!=vfavoriteRecipes.end();)
//    {
//        if(*it == recipeId)
//        {
//            it=vfavoriteRecipes.erase(it);    //删除元素，返回值指向已删除元素的下一个位置
//        }
//        
//        else
//        {
//            ++it;    //指向下一个位置
//        }
    vector<RecipeInfo*>::iterator it;
    
    
    
    for(int i=m_recipeData->size()-1; i>=0; i--)
    {
        RecipeInfo* item = m_recipeData->at(i);
        if(item->getIsChecked())
        {
            m_recipeData->erase(i);
        }
    }
    
    FSDataManager::GetInstance().getRecipeManager()->savefavoriteRecipes(m_recipeData);
    
    
    p_TableView->reloadData();
}

void RecipeListViewController::setAllCheckBoxState(bool isChecked)
{
    for(size_t i = 0;i<m_recipeData->size();i++)
    {
        RecipeInfo *item = m_recipeData->at(i);
        item->setIsChecked(isChecked);
    }
}

bool RecipeListViewController::isSelectedAll()
{
    bool ret=true;
    if(m_recipeData->size() == 0)
    {
        ret = false;
        return ret;
    }
    
    
        for(size_t i = 0;i<m_recipeData->size();i++)
        {
            RecipeInfo *item = m_recipeData->at(i);
            if(!item->getIsChecked())
            {
                ret = false;
                break;
            }
        }
    
    
    return ret;
}



