//
//  FSRecipeManager.hpp
//  Recipes
//
//  Created by apple on 6/19/16.
//
//

#ifndef FSRecipeManager_h
#define FSRecipeManager_h
#include <stdio.h>
#include "CrossApp.h"
#include "CrossAppExt.h"
#include "AppMacros.h"
#include <string.h>
#include "RecipeInfo.h"
#include <vector>
#include "CDData.h"

using namespace std;

//class sqlite3;
class SqliteCursor
{
    int m_nPos;
    std::list<std::vector<std::string>*> m_listvecData;
    std::vector<std::vector<std::string>*> m_vecvecData;
    std::vector<std::string> m_vecTitle;
public:
    SqliteCursor()
    {
        m_nPos = 0;
    }
    ~SqliteCursor()
    {
        for ( std::list<std::vector<std::string>*>::iterator it = m_listvecData.begin() ; it != m_listvecData.end() ; it ++ )
            delete (*it);
    }
    void AddRowData( int n_column, char ** column_value, char ** column_name )
    {
        if ( m_listvecData.size() == 0 )
        {
            m_vecTitle.resize( n_column );
            for ( int i = 0 ; i < n_column ; i ++ ) m_vecTitle[i] = column_name[i];
        }
        std::vector<std::string>* vec = new std::vector<std::string>();
        vec->resize( n_column );
        for ( int i = 0 ; i < n_column ; i ++ ) if ( column_value[i] != NULL ) (*vec)[i] = column_value[i];
        m_listvecData.push_back( vec );
    }
    void MakeData()
    {
        if ( m_vecvecData.size() != m_listvecData.size() )
        {
            m_vecvecData.resize( m_listvecData.size() );
            int i = 0;
            for ( std::list<std::vector<std::string>*>::iterator it = m_listvecData.begin() ; it != m_listvecData.end() ; it ++ , i ++ )
                m_vecvecData[i] = (*it);
        }
    }
    int GetRowCount()
    {
        return (int)m_listvecData.size();
    }
    int GetColumnCount()
    {
        return (int)m_vecTitle.size();
    }
    std::vector<std::string> &GetCurRow()
    {
        return (*m_vecvecData[m_nPos]);
    }
    const char* GetData( int column )
    {
        MakeData();
        std::vector<std::string> &row = GetCurRow();
        if ( column < 0 || column >= (int)row.size() ) return "";
        return row[column].c_str();
    }
    const char* GetColumData( int column )
    {
        if ( column < 0 || column >= (int)m_vecTitle.size() ) return "";
        return m_vecTitle[column].c_str();
    }
    int GetPos()
    {
        return m_nPos;
    }
    bool SetPos( int pos )
    {
        if ( GetRowCount() == 0 ) return false;
        MakeData();
        if ( pos < 0 ) pos = 0;
        else if ( pos > GetRowCount() - 1 ) pos = GetRowCount() - 1;
        m_nPos = pos;
        return true;
    }
};


typedef CAMap<std::string,CAVector<RecipeInfo*>*> KEYSTRINGMAP;
class FSRecipeManager:public CAObject
{
//protected:
//    CAMap<std::string,CAVector<CAObject*>> m_recipesMap;
//    
//public:
//    inline CAMap<std::string,CAVector<CAObject*>>& getRecipesMap()
//    {
//        return m_recipesMap;
//    };
    
public:
//    CAMap<std::string,CAVector<CAObject>> m_recipesMap;
    CC_SYNTHESIZE_PASS_BY_REF2(KEYSTRINGMAP,m_recipesMap,RecipesMap)
public:
    CREATE_FUNC(FSRecipeManager)
    
public:
    bool init();
    FSRecipeManager();
    virtual ~FSRecipeManager();
public:
//    CAVector<RecipeInfo*>*& loadRecipesForMonth(int intMonth);
    
    void loadRecipesForMonth(int intMonth,CAVector<RecipeInfo*>*& pVectorRecipe);
    
    void searchRecipesForKey(string strSearchKey,CAVector<RecipeInfo*>*& pVectorRecipe);
    
    void loadRecipesForType(string strType,CAVector<RecipeInfo*>*& pVectorRecipe);
    
    void loadFavorite(CAVector<RecipeInfo*>*& pVectorRecipe);

public:
    std::vector<int> vfavoriteRecipes;
    std::string favoriteRecipeStr;
    void loadfavoriteRecipes();
    void savefavoriteRecipes();
    bool isFavorite(int recipeId);
    void addfavoriteRecipe(int recipeId);
    void removefavoriteRecipe(int recipeId);
    void savefavoriteRecipes(CAVector<RecipeInfo*>*& pVectorRecipe);
    
    
protected:
    sqlite3 *_sqlite3;
    SqliteCursor* SqliteQurey( sqlite3 *pSql , std::string sql );
    static int QueryResult( void * para, int n_column, char ** column_value, char ** column_name )
    {
        ((SqliteCursor*)para)->AddRowData(n_column , column_value , column_name );
        return 0;
    }
};


#endif /* FSRecipeManager_hpp */
