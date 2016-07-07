//
//  RecipeDetail1Cell.cpp
//  Recipes
//
//  Created by apple on 6/25/16.
//
//

#include "RecipeDetail2Cell.h"
RecipeDetail2Cell::RecipeDetail2Cell()
:theContent(NULL),
theLineView(NULL)
{
    this->setAllowsSelected(false);
}

RecipeDetail2Cell::~RecipeDetail2Cell()
{
    
}

RecipeDetail2Cell* RecipeDetail2Cell::create(const std::string& identifier)
{
    CCLog("RecipesTableCell");
    RecipeDetail2Cell* tableViewCell = new RecipeDetail2Cell();
    if(tableViewCell&&tableViewCell->initWithReuseIdentifier(identifier))
    {
        tableViewCell->autorelease();
        return tableViewCell;
    }
    CC_SAFE_DELETE(tableViewCell);
    return NULL;
}



bool RecipeDetail2Cell::initWithReuseIdentifier(const std::string& reuseIdentifier)
{
    if (!CATableViewCell::initWithReuseIdentifier(reuseIdentifier))
    {
        return false;
    }
    
    float fwinWidth = CAApplication::getApplication()->getWinSize().width;
    

    //
    theContent = CALabel::createWithLayout(DLayout(DHorizontalLayout_L_R(10, 10), DVerticalLayout_T_B(10, 10)));
    theContent->setColor(CAColor_gray);
    theContent->setTextAlignment(CATextAlignmentLeft);
    theContent->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    theContent->setFontSize(28);
    theContent->setTag(100);
    this->getContentView()->addSubview(theContent);
    
    
    theLineView = CAView::createWithColor(CAColor_gray);
    theLineView->setLayout(DLayout(DHorizontalLayout_L_R(2, 2), DVerticalLayout_B_H(2, 1)));
    this->getContentView()->addSubview(theLineView);
    
//    theCategory = CALabel::createWithLayout(DLayout(DHorizontalLayout_L_W(0, fwinWidth/2), DVerticalLayout_T_H(260, 40)));
//    theCategory->setColor(CAColor_black);
//    theCategory->setTextAlignment(CATextAlignmentLeft);
//    //    theDesc->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
//    theCategory->setFontSize(24);
//    theCategory->setTag(102);
//    theCategory->setColor(CAColor_gray);
//    //    theCategory->setLineSpacing(-10);
//    this->getContentView()->addSubview(theCategory);
//    
//    
//    //theMonth
//    theMonth = CALabel::createWithLayout(DLayout(DHorizontalLayout_R_W(0, fwinWidth/2), DVerticalLayout_T_H(260, 40)));
//    theMonth->setColor(CAColor_black);
//    theMonth->setTextAlignment(CATextAlignmentRight);
//    theMonth->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
//    theMonth->setFontSize(24);
//    theMonth->setTag(103);
//    theMonth->setColor(CAColor_gray);
//    theMonth->setLineSpacing(10);
//    this->getContentView()->addSubview(theMonth);
    
    return true;
}

void RecipeDetail2Cell::setString(const string& strText)
{
    theContent->setText(strText);
}