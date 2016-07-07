//
//  RecipeDetail1Cell.hpp
//  Recipes
//
//  Created by apple on 6/25/16.
//
//

#ifndef RecipeDetail2Cell_hpp
#define RecipeDetail2Cell_hpp

#include <stdio.h>
#include "CrossApp.h"
//#include "RecipeInfo.h"
class RecipeDetail2Cell : public CATableViewCell
{
public:
    RecipeDetail2Cell();
    virtual ~RecipeDetail2Cell();
    static RecipeDetail2Cell* create(const std::string& identifier);
    //    virtual void highlightedTableViewCell();
    //    virtual void selectedTableViewCell();
public:
    virtual bool initWithReuseIdentifier(const std::string& reuseIdentifier);
//    void setModel(const RecipeInfo& cellmodel);
    void setString(const string& strText);
private:
    CALabel* theContent;
    CAView* theLineView;
};

#endif /* RecipeDetail1Cell_hpp */
