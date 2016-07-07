//
//  FSDeleteTableCell.cpp
//  Recipes
//
//  Created by apple on 6/28/16.
//
//

#include "FSCheckBoxTableCell.h"
#include "GlobalFunction.h"
//#include "stdlib.h"

FSCheckBoxTableCell::FSCheckBoxTableCell()
:m_fCurrDivision(0)

{
//    this->setAllowsSelected(false);
}

FSCheckBoxTableCell::~FSCheckBoxTableCell()
{
    
}







bool FSCheckBoxTableCell::initWithReuseIdentifier(const std::string& reuseIdentifier)
{
    if (!CATableViewCell::initWithReuseIdentifier(reuseIdentifier))
    {
        return false;
    }
    
//    m_fDivision = this->getContentView()->getBounds().size.width - AppWidth/3;
    m_fDivision = AppWidth/4;
    m_fCurrDivision = m_fDivision;
    //AppWidth
    m_LeftLayout[0].horizontal.left = 0;
    m_LeftLayout[0].horizontal.width = AppWidth;
    m_LeftLayout[0].vertical = DVerticalLayoutFill;
    
    m_LeftLayout[1].horizontal.left = 0;
    m_LeftLayout[1].horizontal.width = AppWidth - m_fDivision;
    m_LeftLayout[1].vertical = DVerticalLayoutFill;

    m_RightLayout[0].horizontal.right = -m_fDivision;
    m_RightLayout[0].horizontal.width = m_fDivision;
    m_RightLayout[0].vertical = DVerticalLayoutFill;
    
    m_RightLayout[1].horizontal.right = 0;
    m_RightLayout[1].horizontal.width = m_fDivision;
    m_RightLayout[1].vertical = DVerticalLayoutFill;
    
    
//    m_LeftLayout[0].horizontal.left = 0;
//    m_LeftLayout[0].horizontal.right = 0;
//    m_LeftLayout[0].vertical = DVerticalLayoutFill;
//    
//    m_LeftLayout[1].horizontal.left = 0;
//    m_LeftLayout[1].horizontal.right = m_fDivision;
//    m_LeftLayout[1].vertical = DVerticalLayoutFill;
//    
//    m_RightLayout[0].horizontal.right = -m_fDivision;
//    m_RightLayout[0].horizontal.left = AppWidth;
//    m_RightLayout[0].vertical = DVerticalLayoutFill;
//    
//    m_RightLayout[1].horizontal.right = 0;
//    m_RightLayout[1].horizontal.left = AppWidth - m_fDivision;
//    m_RightLayout[1].vertical = DVerticalLayoutFill;
    
    
    
    m_LeftContentView = CAView::createWithLayout(m_LeftLayout[0]);
    this->getContentView()->addSubview(m_LeftContentView);
    
    
    m_RightContentView = CAView::createWithLayout(m_RightLayout[0]);
    this->getContentView()->addSubview(m_RightContentView);
    
//    CAButtonTypeSquareRect
//    m_rightButton = CAButton::createWithLayout(DLayoutZero, CAButtonType::CAButtonTypeCustom);
    
//    m_rightButton =CAButton::createWithCenter(m_RightContentView->getBounds(), CAButtonType::CAButtonTypeCustom);
    
    m_rightButton = CAButton::createWithLayout(DLayout(DHorizontalLayout_L_R(5, 5), DVerticalLayout_T_B(5, 5)), CAButtonType::CAButtonTypeCustom);
    
    
//    m_rightButton->setTitleFontSize(FONT3);
//    m_rightButton->setTitleColorForState(CAControlState::CAControlStateAll, CAColor_blue);
//    m_rightButton->setColor(CAColor_red);
//    m_rightButton->setTitleForState(CAControlStateAll, "Delete");
    m_rightButton->setAllowsSelected(true);
    m_rightButton->setImageForState(CAControlState::CAControlStateNormal, CAImage::create("image/unchecked_checkbox.png"));
    m_rightButton->setImageForState(CAControlState::CAControlStateSelected, CAImage::create("image/checked_checkbox.png"));
    m_rightButton->setImageSize(DSize(48,48));
//    m_RightContentView->setZOrder(1000);
//    m_rightButton->setZOrder(100);
    m_rightButton->addTarget(this,CAControl_selector(FSCheckBoxTableCell::clickCheckBoxButton),CAControlEventTouchUpInSide);
    m_RightContentView->addSubview(m_rightButton);
    
    
    
    
    
    return true;
}

void FSCheckBoxTableCell::clickCheckBoxButton(CAControl* btn,DPoint point)
{
    
}

//void FSCheckBoxTableCell::selectedTableViewCell()
//{
//
//}


//void FSCheckBoxTableCell::updateViewFrame()
//{
//    DPoint point[2] =
//    {
//        DPoint(m_fCurrDivision - m_fDivision, 0),
//        DPoint(m_fCurrDivision, 0)
//    };
//    
////    if (m_bEffect3D)
////    {
////        float scale0 = 0.5f + 0.5f * m_fCurrDivision / m_fDivision;
////        float scale1 = 1.0f - powf(m_fCurrDivision / m_fDivision, 2) * 0.2f;
////        
////        m_pContainer[0]->setAlpha(m_fCurrDivision / m_fDivision);
////        m_pContainer[0]->setScale(scale0);
////        m_pContainer[1]->setScale(scale1);
////        point[0].x = (m_fCurrDivision - m_fDivision) / 3;
////    }
////    else
////    {
////        m_pContainer[0]->setScale(1);
////        m_pContainer[1]->setScale(1);
////    }
////    
//    DLayout layout[2];
//    layout[0] = m_LeftLayout[0];
//    layout[0].horizontal.left =  point[0].x;
//    
//    
//    
//    layout[1] = m_RightLayout[1];
//    layout[1].horizontal.right = - point[1].x;
//    
////    layout[0].horizontal.left = m_fCurrDivision;
////
////    layout[1] = m_rHideLayout[1];
////    layout[1].horizontal.left = point[1].x;
////    layout[1].horizontal.right = -point[1].x;
////    
////    for (int i=0; i<2; i++)
////    {
////        m_pContainer[i]->setLayout(layout[i]);
////    }
//    
//    m_LeftContentView->setLayout(layout[0]);
//    m_rightButton->setLayout(layout[1]);
//    
//}


void FSCheckBoxTableCell::showRightButton(bool bIsShow)
{
    if(bIsShow)
    {
        CAViewAnimation::beginAnimations("", NULL);
        CAViewAnimation::setAnimationDuration(0.1f);
        m_LeftContentView->setLayout(m_LeftLayout[1]);
        m_RightContentView->setLayout(m_RightLayout[1]);
        
        CAViewAnimation::setAnimationDidStopSelector(this, CAViewAnimation0_selector(FSCheckBoxTableCell::endAction));
        CAViewAnimation::commitAnimations();
        
//        m_fCurrDivision = 0;
    }
    else
    {
        CAViewAnimation::beginAnimations("", NULL);
        CAViewAnimation::setAnimationDuration(0.1f);
        m_LeftContentView->setLayout(m_LeftLayout[0]);
        m_RightContentView->setLayout(m_RightLayout[0]);

        CAViewAnimation::commitAnimations();
        
//        m_fCurrDivision = m_fDivision;
    }
    
//    this->setTouchEnabled(true);
}


void FSCheckBoxTableCell::endAction()
{

    
}

bool FSCheckBoxTableCell::isChecked()
{
    return m_rightButton->getControlState() == CAControlState::CAControlStateSelected;
}

void FSCheckBoxTableCell::setRightButtonChecked(bool bIsChecked)
{
    if(bIsChecked)
    {
        m_rightButton->setControlState(CAControlState::CAControlStateSelected);
    }
    else
    {
        m_rightButton->setControlState(CAControlState::CAControlStateNormal);
    }
}

