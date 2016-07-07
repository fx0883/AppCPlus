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


//������
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
	//listview�ص��ӿ�
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
	void ClickSearchBtn(CAControl *pControl, DPoint point);//���������ť
    void ClickClearRecordBtn(CAControl *pControl, DPoint point);//���������ť
	std::string GetValue(int index);//��ȡ���cell�е�����ֵ
	void GetLocalSearchRecord();//��ȡ����������¼
	void SaveSearchRecord(std::string text);//���汾��������¼
	void AddTextToMap(std::string text);//������ݵ��ڴ�
	void UpdateRecordView();//����������¼
private:
	CATextField *m_pTextField;
	CAListView *m_pListView;
	CAView *m_pRecord;
	std::map<int, std::string> m_textMap;
};


#endif