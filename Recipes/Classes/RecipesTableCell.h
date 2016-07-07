//
//  RecipesTableCell.hpp
//  Recipes
//
//  Created by apple on 6/20/16.
//
//

#ifndef RecipesTableCell_h
#define RecipesTableCell_h

#include <stdio.h>
#include "CrossApp.h"
#include "RecipeInfo.h"
//#include "FSDeleteTableCell.h"
#include "FSCheckBoxTableCell.h"
#include "AppMacros.h"
class RecipesTableCell : public FSCheckBoxTableCell
{
public:
    RecipesTableCell();
    virtual ~RecipesTableCell();
    static RecipesTableCell* create(const std::string& identifier);
    virtual void highlightedTableViewCell();
    virtual void selectedTableViewCell();
public:
    virtual bool initWithReuseIdentifier(const std::string& reuseIdentifier);
    void setModel(RecipeInfo *cellmodel);
    
    
    virtual void clickCheckBoxButton(CAControl* btn,DPoint point);
    
public:
//    void longPress(CAControl* btn,DPoint point);
//    CAObject *pControlStateTarget;
    FSControlState clickCheckBox;
private:
    CALabel* theTitle;
    CALabel* theDesc;
    CALabel* theMonth;
    CAImageView* theImage;
    
    RecipeInfo *m_RecipeInfo;
    
//public:
//    virtual bool ccTouchBegan(CATouch *pTouch, CAEvent *pEvent);
//    
//    virtual void ccTouchMoved(CATouch *pTouch, CAEvent *pEvent);
//    
//    virtual void ccTouchEnded(CATouch *pTouch, CAEvent *pEvent);
//    
//    virtual void ccTouchCancelled(CATouch *pTouch, CAEvent *pEvent);
//    
//        CC_PROPERTY_IS(bool, m_bTouchMoved, TouchMoved);
};


#endif /* RecipesTableCell_hpp */
