//
//  RecipeDetailViewController.hpp
//  Recipes
//
//  Created by apple on 6/25/16.
//
//

#ifndef RecipeDetailViewController_hpp
#define RecipeDetailViewController_hpp

#include <stdio.h>
#include <iostream>
#include "CrossApp.h"
#include "RecipeInfo.h"
#include "AppMacros.h"
USING_NS_CC;

class RecipeDetailViewController: public CAViewController,CATableViewDelegate,CATableViewDataSource
{
    
public:
    CC_SYNTHESIZE_PASS_BY_REF2(RecipeInfo*,m_RecipeInfo,RecipeInfo);
    CC_SYNTHESIZE_PASS_BY_REF2(bool,m_showRightButton,ShowRightButton);
//    CREATE_FUNC(RecipeDetailViewController);
    
    RecipeDetailViewController(RecipeInfo*& pRecipeInfo);
    RecipeDetailViewController();
    
    virtual ~RecipeDetailViewController();
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
    
    void viewDidAppear();
    
    void setRightButtonState(bool isSelect);
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
private:
    void initRecipeTableView();
    void onClickRightButtuon(CAControl* btn,DPoint point);
public:


};

#endif /* RecipeDetailViewController_hpp */
