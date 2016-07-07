//
//  FSDeleteTableCell.hpp
//  Recipes
//
//  Created by apple on 6/28/16.
//
//

#ifndef FSDeleteTableCell_hpp
#define FSDeleteTableCell_hpp

#include <stdio.h>

#include <stdio.h>
#include "CrossApp.h"
#include "AppMacros.h"

class FSDeleteTableCell : public CATableViewCell
{
public:
    FSDeleteTableCell();
    virtual ~FSDeleteTableCell();
//    static FSDeleteTableCell* create(const std::string& identifier);
    virtual void highlightedTableViewCell();
    virtual void selectedTableViewCell();
public:
    virtual bool initWithReuseIdentifier(const std::string& reuseIdentifier);

    virtual void clickRightButton(CAControl* btn,DPoint point);
    
public:
    //    void longPress(CAControl* btn,DPoint point);
    
    
    CC_SYNTHESIZE_PASS_BY_REF2(CAView*, m_LeftContentView, LeftContentView)
private:
//    CALabel* theTitle;
//    CALabel* theDesc;
//    CALabel* theMonth;
//    CAImageView* theImage;
    
    CAButton* m_rightButton;
    void updateViewFrame();
    void begin();
    
protected:
    float m_fDivision;
    
    float m_fCurrDivision;
    
    int m_fOffX;
    
public:
    virtual bool ccTouchBegan(CATouch *pTouch, CAEvent *pEvent);
    
    virtual void ccTouchMoved(CATouch *pTouch, CAEvent *pEvent);
    
    virtual void ccTouchEnded(CATouch *pTouch, CAEvent *pEvent);
    
    virtual void ccTouchCancelled(CATouch *pTouch, CAEvent *pEvent);
    
    CC_PROPERTY_IS(bool, m_bTouchMoved, TouchMoved);
    
    DLayout m_LeftLayout[2];
    DLayout m_RightLayout[2];
    
    void showRightButton(bool bIsShow);
    
    
//    bool m_bShowRight;
    
};

#endif /* FSDeleteTableCell_hpp */
