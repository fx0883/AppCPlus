//
//  RecipeListViewController.hpp
//  Recipes
//
//  Created by apple on 6/20/16.
//
//

#ifndef RecipeListViewController_hpp
#define RecipeListViewController_hpp

#include <stdio.h>
#include <iostream>
#include "CrossApp.h"
#include "RecipeInfo.h"
USING_NS_CC;

class RecipeListViewController: public CAViewController,CATableViewDelegate,CATableViewDataSource
{
    
public:
    CREATE_FUNC(RecipeListViewController);
    RecipeListViewController();
    
    virtual ~RecipeListViewController();
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
protected:
        CATableView* p_TableView;
    
public:
    virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual void tableViewWillDisplayCellAtIndex(CATableView* table, CATableViewCell* cell, unsigned int section, unsigned int row);
    virtual CATableViewCell* tableCellAtIndex(CATableView* table, const DSize& cellSize, unsigned int section, unsigned int row);
    virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
    virtual unsigned int numberOfSections(CATableView *table);
    virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    
    virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, const DSize& viewSize, unsigned int section);
    
    unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section);
    
//    virtual void scrollViewHeaderBeginRefreshing(CAScrollView* view);
//    virtual void scrollViewFooterBeginRefreshing(CAScrollView* view);
    
//    virtual void pageViewDidSelectPageAtIndex(CAPageView* pageView, unsigned int index, const DPoint& point);
    
//    virtual void pageViewDidBeginTurning(CAPageView* pageView);
//    virtual void pageViewDidEndTurning(CAPageView* pageView);
    
    void buttonEdit(CAControl* btn,DPoint point);
    void onClickFinishButton(CAControl* btn,DPoint point);
    void onEditleftButtonClick(CAControl* btn,DPoint point);
    
    void showEditBottomView(bool isShow);
    void initEditBottomView();
private:
    void initRecipeTableView();
    void loadDataforMonth(int intMonth);

    void refreshRecipeTable();
    CAVector<RecipeInfo*>* m_recipeData;
    
    CANavigationBarItem *m_curNavBar;
    CABarButtonItem *searchBarButton;
    CABarButtonItem *editBarButton;
    CANavigationBarItem *m_editNavBar;
    CANavigationBarItem *m_editFinishNavBar;
    
    CAView* m_EditBottomView;
    
    bool m_editModel;
    bool m_editView;
    
private:
    DLayout m_tabelViewLayout[2];
    DLayout m_bottomViewLayout[2];
    void initViewLayout();
    
    float m_bottomViewHight;
    
    bool isSelectedAll();
    void setAllCheckBoxState(bool isChecked);
    void changeSeletedButtonText();
    CAButton *selectAllButton;
public:
    void refreshDataByMonth(int intMonth);
    void refreshDataforSearchKey(string& strSearchKey);
    void refreshDataforType(string& strType);
    void refreshRecipeListforFavorite();
    std::string m_strSectionTitle;
    
    
    static void onClickedCellButton(CAControlState state);
    
    
    static RecipeListViewController* curRecipeListViewController;
    
    void setToEditView(bool isEditView);
    void setToEditModel(bool isEditModel);

    
    void onClickSelectAllButton(CAControl* btn,DPoint point);
    void onClickDeleteButton(CAControl* btn,DPoint point);
    
};
#endif /* RecipeListViewController_hpp */
