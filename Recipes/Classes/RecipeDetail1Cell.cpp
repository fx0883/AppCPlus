//
//  RecipeDetail1Cell.cpp
//  Recipes
//
//  Created by apple on 6/25/16.
//
//

#include "RecipeDetail1Cell.h"
RecipeDetail1Cell::RecipeDetail1Cell()
:theTitle(NULL),
theCategory(NULL),
theImage(NULL),
theMonth(NULL)
{
    this->setAllowsSelected(false);
}

RecipeDetail1Cell::~RecipeDetail1Cell()
{
    
}

RecipeDetail1Cell* RecipeDetail1Cell::create(const std::string& identifier)
{
    CCLog("RecipesTableCell");
    RecipeDetail1Cell* tableViewCell = new RecipeDetail1Cell();
    if(tableViewCell&&tableViewCell->initWithReuseIdentifier(identifier))
    {
        tableViewCell->autorelease();
        return tableViewCell;
    }
    CC_SAFE_DELETE(tableViewCell);
    return NULL;
}



bool RecipeDetail1Cell::initWithReuseIdentifier(const std::string& reuseIdentifier)
{
    if (!CATableViewCell::initWithReuseIdentifier(reuseIdentifier))
    {
        return false;
    }
    
    float fwinWidth = CAApplication::getApplication()->getWinSize().width;
    int imageHeight = fwinWidth*2/4;
    
//    theImage = CAImageView::createWithLayout(DLayout(DHorizontalLayout_L_R(0, 0), DVerticalLayout_T_H(0, imageHeight)));
    
    theImage = CAImageView::createWithLayout(DLayoutFill);
    theImage->setTag(101);
    theImage->setImageViewScaleType(CAImageViewScaleTypeFitImageCrop);

    this->getContentView()->addSubview(theImage);
    //
//    theTitle = CALabel::createWithLayout(DLayout(DHorizontalLayout_L_R(0, 0), DVerticalLayout_T_H(imageHeight+10, 60)));
//    theTitle->setColor(CAColor_black);
//    theTitle->setTextAlignment(CATextAlignmentCenter);
//    theTitle->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
//    theTitle->setFontSize(32);
//    theTitle->setTag(100);
//    this->getContentView()->addSubview(theTitle);
//    
//    
//    
//    theCategory = CALabel::createWithLayout(DLayout(DHorizontalLayout_L_W(0, fwinWidth/2), DVerticalLayout_T_H(imageHeight+70, 40)));
//    theCategory->setColor(CAColor_black);
//    theCategory->setTextAlignment(CATextAlignmentCenter);
//    theCategory->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
//    theCategory->setFontSize(24);
//    theCategory->setTag(102);
//    theCategory->setColor(CAColor_gray);
////    theCategory->setLineSpacing(-10);
//    this->getContentView()->addSubview(theCategory);
//    
//    
//    //theMonth
//    theMonth = CALabel::createWithLayout(DLayout(DHorizontalLayout_R_W(0, fwinWidth/2), DVerticalLayout_T_H(imageHeight+70, 40)));
//    theMonth->setColor(CAColor_black);
//    theMonth->setTextAlignment(CATextAlignmentCenter);
//    theMonth->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
//    theMonth->setFontSize(24);
//    theMonth->setTag(103);
//    theMonth->setColor(CAColor_gray);
//    theMonth->setLineSpacing(10);
//    this->getContentView()->addSubview(theMonth);
    
    return true;
}

void RecipeDetail1Cell::setModel(const RecipeInfo &cellmodel)
{
    //    theImage->setImage(CAImage::create("image/HelloWorld.png"));
    //    theImage->setUrl(cellmodel.m_imageUrl);
    //    theTitle->setText(cellmodel.m_title);
    //    theDesc->setText(cellmodel.m_desc);
    
    char imagePath[64];
    sprintf(imagePath, "recipesImage/%s",cellmodel.getPhoto().c_str());
    theImage->setImage(CAImage::create(imagePath));
//    theTitle->setText(cellmodel.getName());
//    theCategory->setText(cellmodel.getType());
    
//    char chrMonth[24];
//    sprintf(chrMonth, "第%d个月",cellmodel.getMonth());
//    theMonth->setText(chrMonth);
    
    
    
}