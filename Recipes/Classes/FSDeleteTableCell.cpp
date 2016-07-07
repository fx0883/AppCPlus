//
//  FSDeleteTableCell.cpp
//  Recipes
//
//  Created by apple on 6/28/16.
//
//

#include "FSDeleteTableCell.h"
#include "GlobalFunction.h"
//#include "stdlib.h"

FSDeleteTableCell::FSDeleteTableCell()
:m_fCurrDivision(0)

{
//    this->setAllowsSelected(false);
}

FSDeleteTableCell::~FSDeleteTableCell()
{
    
}



void FSDeleteTableCell::highlightedTableViewCell()
{
    this->setBackgroundView(CAView::createWithColor(ccc4(0, 0, 0, 64)));
}



bool FSDeleteTableCell::initWithReuseIdentifier(const std::string& reuseIdentifier)
{
    if (!CATableViewCell::initWithReuseIdentifier(reuseIdentifier))
    {
        return false;
    }
    
//    m_fDivision = this->getContentView()->getBounds().size.width - AppWidth/3;
    m_fDivision = AppWidth/3;
    m_fCurrDivision = m_fDivision;
    //AppWidth
    m_LeftLayout[0].horizontal.left = 0;
    m_LeftLayout[0].horizontal.width = AppWidth;
    m_LeftLayout[0].vertical = DVerticalLayoutFill;
    
    m_LeftLayout[1].horizontal.left = -m_fDivision;
    m_LeftLayout[1].horizontal.width = AppWidth;
    m_LeftLayout[1].vertical = DVerticalLayoutFill;

    m_RightLayout[0].horizontal.right = -m_fDivision;
    m_RightLayout[0].horizontal.width = m_fDivision;
    m_RightLayout[0].vertical = DVerticalLayoutFill;
    
    m_RightLayout[1].horizontal.right = 0;
    m_RightLayout[1].horizontal.width = m_fDivision;
    m_RightLayout[1].vertical = DVerticalLayoutFill;
    
    
    m_LeftContentView = CAView::createWithLayout(m_LeftLayout[0]);
    this->getContentView()->addSubview(m_LeftContentView);
    
    m_rightButton = CAButton::createWithLayout(m_RightLayout[0], CAButtonTypeSquareRect);
    m_rightButton->setTitleFontSize(FONT3);
    m_rightButton->setTitleColorForState(CAControlState::CAControlStateAll, CAColor_blue);
    m_rightButton->setColor(CAColor_red);
    m_rightButton->setTitleForState(CAControlStateAll, "Delete");
    
    m_rightButton->addTarget(this,CAControl_selector(FSDeleteTableCell::clickRightButton),CAControlEventTouchUpInSide);
    this->getContentView()->addSubview(m_rightButton);

    
    
    
    
    return true;
}

void FSDeleteTableCell::selectedTableViewCell()
{

}

bool FSDeleteTableCell::ccTouchBegan(CATouch *pTouch, CAEvent *pEvent)
{
    return m_vTouches.size() == 1;
}

void FSDeleteTableCell::updateViewFrame()
{
    DPoint point[2] =
    {
        DPoint(m_fCurrDivision - m_fDivision, 0),
        DPoint(m_fCurrDivision, 0)
    };
    
//    if (m_bEffect3D)
//    {
//        float scale0 = 0.5f + 0.5f * m_fCurrDivision / m_fDivision;
//        float scale1 = 1.0f - powf(m_fCurrDivision / m_fDivision, 2) * 0.2f;
//        
//        m_pContainer[0]->setAlpha(m_fCurrDivision / m_fDivision);
//        m_pContainer[0]->setScale(scale0);
//        m_pContainer[1]->setScale(scale1);
//        point[0].x = (m_fCurrDivision - m_fDivision) / 3;
//    }
//    else
//    {
//        m_pContainer[0]->setScale(1);
//        m_pContainer[1]->setScale(1);
//    }
//    
    DLayout layout[2];
    layout[0] = m_LeftLayout[0];
    layout[0].horizontal.left =  point[0].x;
    
    
    
    layout[1] = m_RightLayout[1];
    layout[1].horizontal.right = - point[1].x;
    
//    layout[0].horizontal.left = m_fCurrDivision;
//
//    layout[1] = m_rHideLayout[1];
//    layout[1].horizontal.left = point[1].x;
//    layout[1].horizontal.right = -point[1].x;
//    
//    for (int i=0; i<2; i++)
//    {
//        m_pContainer[i]->setLayout(layout[i]);
//    }
    
    m_LeftContentView->setLayout(layout[0]);
    m_rightButton->setLayout(layout[1]);
    
}

void FSDeleteTableCell::begin()
{
    this->setTouchEnabled(false);
}

void FSDeleteTableCell::ccTouchMoved(CATouch *pTouch, CAEvent *pEvent)
{
    CC_RETURN_IF(m_bTouchMoved == false);
    float offDis = pTouch->getLocation().x - pTouch->getPreviousLocation().x;
        m_fCurrDivision += offDis;
        m_fCurrDivision = MIN(m_fCurrDivision, m_fDivision);
        m_fCurrDivision = MAX(m_fCurrDivision, 0);
    
    
//    float offDisY = pTouch->getLocation().y - pTouch->getPreviousLocation().y;
//    if(std::abs((int)offDisY) > FLT_EPSILON && std::abs((int)offDis) < FLT_EPSILON)
//    {
//        m_bShowRight = false;
//        this->begin();
//    }
//    else
//    {
//        this->begin();
//        this->updateViewFrame();
//    }
    
    this->begin();
    this->updateViewFrame();
    
    m_fOffX = offDis;
    
    
    CCLog("m_fOffX =====> %d",m_fOffX);
}

void FSDeleteTableCell::ccTouchEnded(CATouch *pTouch, CAEvent *pEvent)
{
    
    if (std::abs(m_fOffX) > FLT_EPSILON)
    {
        if (m_fOffX > 0)
        {

            this->showRightButton(false);
        }
        else
        {

             this->showRightButton(true);
        }
    }
    else
    {
        if (m_fCurrDivision > m_fDivision / 2)
        {
             this->showRightButton(false);
        }
        else
        {
            this->showRightButton(true);
        }
    }
    
    m_fOffX = 0;

}

void FSDeleteTableCell::showRightButton(bool bIsShow)
{
    if(bIsShow)
    {
        CAViewAnimation::beginAnimations("", NULL);
        CAViewAnimation::setAnimationDuration(0.1f);
         m_LeftContentView->setLayout(m_LeftLayout[1]);
        m_rightButton->setLayout(m_RightLayout[1]);
        CAViewAnimation::commitAnimations();
        
        m_fCurrDivision = 0;
    }
    else
    {
        CAViewAnimation::beginAnimations("", NULL);
        CAViewAnimation::setAnimationDuration(0.1f);
        m_LeftContentView->setLayout(m_LeftLayout[0]);
        m_rightButton->setLayout(m_RightLayout[0]);
        CAViewAnimation::commitAnimations();
        
        m_fCurrDivision = m_fDivision;
    }
    
    this->setTouchEnabled(true);
}

void FSDeleteTableCell::ccTouchCancelled(CATouch *pTouch, CAEvent *pEvent)
{
    this->ccTouchEnded(pTouch, pEvent);
}

void FSDeleteTableCell::setTouchMoved(bool var)
{
    m_bTouchMoved = var;
    this->setPriorityScroll(var);
}

bool FSDeleteTableCell::isTouchMoved()
{
    return m_bTouchMoved;
}

void FSDeleteTableCell::clickRightButton(CAControl* btn,DPoint point)
{

}
