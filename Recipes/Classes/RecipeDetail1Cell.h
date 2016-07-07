//
//  RecipeDetail1Cell.hpp
//  Recipes
//
//  Created by apple on 6/25/16.
//
//

#ifndef RecipeDetail1Cell_hpp
#define RecipeDetail1Cell_hpp

#include <stdio.h>
#include "CrossApp.h"
#include "RecipeInfo.h"
class RecipeDetail1Cell : public CATableViewCell
{
public:
    RecipeDetail1Cell();
    virtual ~RecipeDetail1Cell();
    static RecipeDetail1Cell* create(const std::string& identifier);
//    virtual void highlightedTableViewCell();
//    virtual void selectedTableViewCell();
public:
    virtual bool initWithReuseIdentifier(const std::string& reuseIdentifier);
    void setModel(const RecipeInfo& cellmodel);
private:
    CALabel* theTitle;
    CALabel* theCategory;
    CALabel* theMonth;
    CAImageView* theImage;
};

#endif /* RecipeDetail1Cell_hpp */
