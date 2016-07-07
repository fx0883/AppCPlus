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

class FSCheckBoxTableCell : public CATableViewCell
{
public:
    FSCheckBoxTableCell();
    virtual ~FSCheckBoxTableCell();
//    static FSDeleteTableCell* create(const std::string& identifier);
//    virtual void highlightedTableViewCell();
//    virtual void selectedTableViewCell();
public:
    virtual bool initWithReuseIdentifier(const std::string& reuseIdentifier);

    virtual void clickCheckBoxButton(CAControl* btn,DPoint point);
    
    void endAction();
    
public:
    //    void longPress(CAControl* btn,DPoint point);
    
    
    CC_SYNTHESIZE_PASS_BY_REF2(CAView*, m_LeftContentView, LeftContentView)
    CC_SYNTHESIZE_PASS_BY_REF2(CAView*, m_RightContentView, RightContentView)
private:
//    CALabel* theTitle;
//    CALabel* theDesc;
//    CALabel* theMonth;
//    CAImageView* theImage;
    
    CAButton* m_rightButton;
//    void updateViewFrame();
//    void begin();
    
protected:
    float m_fDivision;
    
    float m_fCurrDivision;
    
    int m_fOffX;
    
public:
    DLayout m_LeftLayout[2];
    DLayout m_RightLayout[2];
    
    void showRightButton(bool bIsShow);
    
    bool isChecked();
    
    void setRightButtonChecked(bool bIsChecked);
    
};

#endif /* FSDeleteTableCell_hpp */
