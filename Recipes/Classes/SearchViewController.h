#pragma once
#ifndef __SearchViewController__
#define __SearchViewController__

#include "CrossApp.h"

USING_NS_CC;


class CSearchListViewCell : public CAListViewCell
{
public:
	static CSearchListViewCell* create(const std::string& reuseIdentifier);
protected:
	virtual void normalListViewCell();
	virtual void highlightedListViewCell();
	virtual void selectedListViewCell();
};


//搜索类
class CSearchViewController :
	public CAViewController,
	public CATextFieldDelegate,
	public CAListViewDataSource,
	public CAListViewDelegate
{
public:
	CSearchViewController();
	~CSearchViewController();
public:
	//listview回调接口
	virtual unsigned int numberOfIndex(CAListView *listView);
	virtual unsigned int listViewHeightForIndex(CAListView *listView, unsigned int index);
	virtual CAListViewCell* listViewCellAtIndex(CAListView *listView, const DSize& cellSize, unsigned int index);
	virtual void listViewWillDisplayCellAtIndex(CAListView* table, CAListViewCell* cell, unsigned int index);
	virtual void listViewDidSelectCellAtIndex(CAListView *listView, unsigned int index);
	virtual void listViewDidDeselectCellAtIndex(CAListView *listView, unsigned int index);
public:
	bool onTextFieldInsertText(CATextField * sender, const char * insText, int nLen, int nPosition);	
	bool onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen, int nPosition);	
public:
	virtual void viewDidLoad();
	virtual void viewDidUnload();
	virtual void viewDidAppear();
	virtual void textFieldShouldReturn(CATextField *sender);

public:
	void ClickSearchBtn(CAControl *pControl, DPoint point);//点击搜索按钮
    void ClickClearRecordBtn(CAControl *pControl, DPoint point);//点击搜索按钮
	std::string GetValue(int index);//获取点击cell中的文字值
	void GetLocalSearchRecord();//获取本地搜索记录
	void SaveSearchRecord(std::string text);//保存本地搜索记录
	void AddTextToMap(std::string text);//添加数据到内存
	void UpdateRecordView();//更新搜索记录
private:
	CATextField *m_pTextField;
	CAListView *m_pListView;
	CAView *m_pRecord;
	std::map<int, std::string> m_textMap;
};


#endif