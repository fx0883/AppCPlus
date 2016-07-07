//
//  RecipesTableCell.cpp
//  Recipes
//
//  Created by apple on 6/20/16.
//
//

#include "RecipesTableCell.h"
RecipesTableCell::RecipesTableCell()
:theTitle(NULL),
theDesc(NULL),
theImage(NULL),
theMonth(NULL),
clickCheckBox(NULL),
m_RecipeInfo(NULL)
{
    this->setAllowsSelected(false);
}

RecipesTableCell::~RecipesTableCell()
{
    
}

RecipesTableCell* RecipesTableCell::create(const std::string& identifier)
{
    CCLog("RecipesTableCell");
    RecipesTableCell* tableViewCell = new RecipesTableCell();
    if(tableViewCell&&tableViewCell->initWithReuseIdentifier(identifier))
    {
        tableViewCell->autorelease();
        return tableViewCell;
    }
    CC_SAFE_DELETE(tableViewCell);
    return NULL;
}

void RecipesTableCell::highlightedTableViewCell()
{
    this->setBackgroundView(CAView::createWithColor(ccc4(0, 0, 0, 64)));
}

void RecipesTableCell::selectedTableViewCell()
{
    this->setBackgroundView(CAView::createWithColor(ccc4(0, 0, 0, 64)));
}

bool RecipesTableCell::initWithReuseIdentifier(const std::string& reuseIdentifier)
{
    if (!FSCheckBoxTableCell::initWithReuseIdentifier(reuseIdentifier))
    {
        return false;
    }
    
    
    this->theImage = CAImageView::createWithLayout(DLayout(DHorizontalLayout_L_W(20, 200), DVerticalLayout_T_B(20, 20)));
    

    theImage->setTag(101);
    theImage->setImageViewScaleType(CAImageViewScaleTypeFitImageCrop);
    
    this->getLeftContentView()->addSubview(theImage);
//    this->getContentView()->addSubview(theImage);

    theTitle = CALabel::createWithLayout(DLayout(DHorizontalLayout_L_R(240, 150), DVerticalLayout_T_H(20, 40)));
    theTitle->setColor(CAColor_black);
    theTitle->setTextAlignment(CATextAlignmentLeft);
    theTitle->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    theTitle->setFontSize(32);
    theTitle->setTag(100);
//    this->getContentView()->addSubview(theTitle);
    this->getLeftContentView()->addSubview(theTitle);
    theDesc = CALabel::createWithLayout(DLayout(DHorizontalLayout_L_R(240, 20), DVerticalLayout_T_B(65, 10)));
    theDesc->setColor(CAColor_black);
    theDesc->setTextAlignment(CATextAlignmentLeft);
    theDesc->setFontSize(24);
    theDesc->setTag(102);
    theDesc->setColor(CAColor_gray);
    theDesc->setLineSpacing(-10);
//    this->getContentView()->addSubview(theDesc);
        this->getLeftContentView()->addSubview(theDesc);
    
    //theMonth
    theMonth = CALabel::createWithLayout(DLayout(DHorizontalLayout_R_W(20, 125), DVerticalLayout_T_H(20, 40)));
    theMonth->setColor(CAColor_black);
    theMonth->setTextAlignment(CATextAlignmentRight);
    theMonth->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    theMonth->setFontSize(24);
    theMonth->setTag(103);
    theMonth->setColor(CAColor_gray);
    theMonth->setLineSpacing(10);
//    this->getContentView()->addSubview(theMonth);
    this->getLeftContentView()->addSubview(theMonth);
    

    
//    this->showRightButton(true);
    return true;
}






void RecipesTableCell::setModel(RecipeInfo *cellmodel)
{
//    theImage->setImage(CAImage::create("image/HelloWorld.png"));
//    theImage->setUrl(cellmodel.m_imageUrl);
//    theTitle->setText(cellmodel.m_title);
//    theDesc->setText(cellmodel.m_desc);
    
    char imagePath[64];
    sprintf(imagePath, "recipesImage/%s",cellmodel->getPhoto().c_str());
    theImage->setImage(CAImage::create(imagePath));
    theTitle->setText(cellmodel->getName());
    theDesc->setText(cellmodel->getPrompt());
    
    if(cellmodel->getMonth()>0)
    {
        char chrMonth[24];
        sprintf(chrMonth, "第%d个月",cellmodel->getMonth());
        theMonth->setText(chrMonth);
    }
    else
    {
        theMonth->setText(UTF8("功能性食谱"));
    }
    
    m_RecipeInfo = cellmodel;
    
}

void RecipesTableCell::clickCheckBoxButton(CAControl* btn,DPoint point)
{
    
    if(m_RecipeInfo)
    {
        m_RecipeInfo->setIsChecked(btn->getControlState() == CAControlStateSelected);
    }
    
    if(clickCheckBox)
    {
        clickCheckBox(btn->getControlState());
        
    }

}
