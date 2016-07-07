#include "SearchViewController.h"
//#include "BookIntroductionViewController.h"
#include "RootWindow.h"
#include "GlobalFunction.h"
//#include "AppMacros.h"
#include "AppMacros.h"
//#include "SearchResultViewController.h"


CSearchViewController::CSearchViewController() :
m_pTextField(NULL),
m_pListView(NULL),
m_pRecord(NULL)
{	
	GetLocalSearchRecord();
}

CSearchViewController::~CSearchViewController()
{
}

void CSearchViewController::viewDidLoad()
{
	DRect winRect = this->getView()->getBounds();

	m_pTextField = CATextField::createWithLayout(DLayout(DHorizontalLayout_L_R(V(20), V(120)), DVerticalLayout_T_H(V(30), V(100))));
	m_pTextField->setPlaceHolderText(UTF8("输入菜名/原料名"));
	m_pTextField->setDelegate(this);
	//m_pTextField->becomeFirstResponder();
	m_pTextField->setMarginLeft(20);
	m_pTextField->setFontSize(FONT11);
	m_pTextField->setReturnType(CATextField::Search);
	
	CAButton *pSearch = CAButton::createWithLayout(DLayout(DHorizontalLayout_R_W(V(20), V(120)), DVerticalLayout_T_H(V(30), V(100))), CAButtonTypeRoundedRect);
	pSearch->setTitleForState(CAControlStateAll, UTF8("搜索"));
	pSearch->setTitleColorForState(CAControlStateAll, CAColor_white);
	pSearch->addTarget(this, CAControl_selector(CSearchViewController::ClickSearchBtn), CAControlEventTouchUpInSide);
	pSearch->setBackgroundViewForState(CAControlStateNormal, CAImageView::createWithImage(CAImage::create("image/search_bg.png")));
	pSearch->setBackgroundViewForState(CAControlStateHighlighted, CAImageView::createWithImage(CAImage::create("image/search_pushed.png")));
	
	m_pRecord = CAView::createWithLayout(DLayout(DHorizontalLayout_L_R(V(20), V(20)), DVerticalLayout_T_H(V(160), V(150))));
	CALabel *pLabel = CALabel::createWithLayout(DLayout(DHorizontalLayout_L_R(V(30), V(170)), DVerticalLayout_T_H(0, V(149))));
	pLabel->setText(UTF8("暂无记录"));
	pLabel->setTextAlignment(CATextAlignmentLeft);
	pLabel->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
//	pLabel->setFontName("msyh.ttf");
	pLabel->setFontSize(FONT12);
	pLabel->setColor(ccc4(42, 42, 42, 255));
	pLabel->setTextTag("label");
	m_pRecord->addSubview(pLabel);
    
    
    
CAButton *pClearRecord = CAButton::createWithLayout(DLayout(DHorizontalLayout_R_W(V(20), V(150)), DVerticalLayout_T_H(V(0), V(149))), CAButtonTypeCustom);
    pClearRecord->setTitleFontSize(FONT12);
    pClearRecord->setTitleForState(CAControlStateAll, UTF8("清除记录"));
    pClearRecord->setTitleColorForState(CAControlStateAll, CAColor_black);
    pClearRecord->addTarget(this, CAControl_selector(CSearchViewController::ClickClearRecordBtn), CAControlEventTouchUpInSide);
    pClearRecord->setTextTag("clearButton");
    m_pRecord->addSubview(pClearRecord);
    
//    pSearch->setBackgroundViewForState(CAControlStateNormal, CAImageView::createWithImage(CAImage::create("image/search_bg.png")));
//    pSearch->setBackgroundViewForState(CAControlStateHighlighted, CAImageView::createWithImage(CAImage::create("image/search_pushed.png")));
    
    
    
    
	CAView *pLine = CAView::createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_B_H(0,V(1))));
	pLine->setColor(ccc4(213, 213, 213, 255));
	pLine->setTextTag("line");
	m_pRecord->addSubview(pLine);
	m_pRecord->setColor(ccc4(240, 240, 240, 255));

	m_pListView = CAListView::createWithLayout(DLayout(DHorizontalLayout_L_R(V(20), V(20)), DVerticalLayout_T_B(V(310), 0)));
	m_pListView->setListViewDataSource(this);
	m_pListView->setListViewDelegate(this);
	m_pListView->setAllowsSelection(true);
	m_pListView->setSeparatorColor(ccc4(213, 213, 213, 255));
	m_pListView->setSeparatorViewHeight(1);
	m_pListView->setBackgroundColor(ccc4(240, 240, 240, 255));	

	this->getView()->addSubview(m_pTextField);
	this->getView()->addSubview(pSearch);
	this->getView()->addSubview(m_pRecord);
	this->getView()->addSubview(m_pListView);
	this->getView()->setColor(ccc4(240, 240, 240, 255));
	CAViewController::viewDidLoad();
}

void CSearchViewController::ClickClearRecordBtn(CAControl *pControl, DPoint point)
{
    std::string xml = CGlobalFunction::GetProfilePath();
    if(CCFileUtils::sharedFileUtils()->isFileExist(xml))
    {
        if(remove(xml.c_str())==0)
        {
            m_textMap.clear();
            m_pListView->reloadData();
            UpdateRecordView();
        }
    }
}

void CSearchViewController::viewDidUnload()
{

}

bool CSearchViewController::onTextFieldInsertText(CATextField * sender, const char * insText, int nLen, int nPosition)
{
	return false;
}

bool CSearchViewController::onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen, int nPosition)
{
	return false;
}

void CSearchListViewCell::normalListViewCell()
{
	CC_RETURN_IF(m_pBackgroundView == NULL);
	m_pBackgroundView->setColor(ccc4(240, 240, 240, 0));
}

void CSearchListViewCell::highlightedListViewCell()
{
	CAListViewCell::highlightedListViewCell();
}

void CSearchListViewCell::selectedListViewCell()
{
	CC_RETURN_IF(m_pBackgroundView == NULL);
	m_pBackgroundView->setColor(ccc4(240, 240, 240, 0));
}

CSearchListViewCell* CSearchListViewCell::create(const std::string& reuseIdentifier)
{
	CSearchListViewCell* cell = new CSearchListViewCell();
	if (cell && cell->initWithReuseIdentifier(reuseIdentifier))
	{
		cell->autorelease();
		return cell;
	}
	CC_SAFE_DELETE(cell);
	return NULL;
}


void CSearchViewController::ClickSearchBtn(CAControl *pControl, DPoint point)
{
	std::string text = m_pTextField->getText();
	if (text.empty())
	{
		return;
	}
	AddTextToMap(text);
	SaveSearchRecord(text);
    
    RootWindow::getInstance()->refreshRecipeListBySearchKey(text);
}

void CSearchViewController::viewDidAppear()
{
	CAApplication::getApplication()->setStatusBarStyle(CAStatusBarStyleLightContent);
	CALabel *pTitle = new CALabel();
	pTitle->init();
	pTitle->autorelease();
	pTitle->setText(UTF8("搜索"));
	pTitle->setColor(CAColor_white);
	pTitle->setFontSize(FONT8);
	pTitle->setFontName("msyh.ttf");
	pTitle->setTextAlignment(CATextAlignmentCenter);
	pTitle->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	CANavigationBarItem *pNavItem = CANavigationBarItem::create(UTF8("搜索"));
	pNavItem->setTitleView(pTitle);
    this->setNavigationBarItem(pNavItem);


//	RootWindow::getInstance()->getRootNavigationController()->setNavigationBarBackgroundColor(ccc4(57, 183, 234, 255));
	m_pTextField->setText("");
	UpdateRecordView();
	m_pListView->reloadData();
}

void CSearchViewController::textFieldShouldReturn(CATextField *sender)
{
	ClickSearchBtn(NULL, DPoint());	
}

unsigned int CSearchViewController::numberOfIndex(CAListView *listView)
{
	return m_textMap.size();
}

unsigned int CSearchViewController::listViewHeightForIndex(CAListView *listView, unsigned int index)
{
	return V(150);
}

CAListViewCell* CSearchViewController::listViewCellAtIndex(CAListView *listView, const DSize& cellSize, unsigned int index)
{
	CALabel *pText = NULL;
	CAListViewCell* cell = listView->dequeueReusableCellWithIdentifier("cell");
	if (!cell)
	{
		cell = CSearchListViewCell::create("cell");
		pText = CALabel::createWithLayout(DLayout(DHorizontalLayout_L_R(V(50), V(50)), DVerticalLayoutFill));
//		pText->setFontName("msyh.ttf");
		pText->setColor(ccc4(122, 122, 122, 255));
		pText->setTextTag("pText");
		pText->setFontSize(FONT11);
		pText->setTextAlignment(CATextAlignmentLeft);
		pText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		pText->setNumberOfLine(1);
		cell->addSubview(pText);
	}
	pText = (CALabel*)cell->getSubviewByTextTag("pText");
	if (pText)
	{
		pText->setText(GetValue(index));
	}
	cell->setBackgroundView(CAView::createWithColor(ccc4(240, 240, 240, 255)));
	return cell;
}

void CSearchViewController::listViewWillDisplayCellAtIndex(CAListView* table, CAListViewCell* cell, unsigned int index)
{

}

void CSearchViewController::listViewDidSelectCellAtIndex(CAListView *listView, unsigned int index)
{
	std::string text = GetValue(index);
	m_pTextField->setText(text);
//	NovelRequestParaInfo novelInfo;
//	novelInfo.wd = text;
//	CSearchResultViewController *pController = CSearchResultViewController::GetNewSearchResultViewController();
//	pController->SetBarItemInfo();
//	RootWindow::getInstance()->getRootNavigationController()->pushViewController(pController, true);
//	pController->SetInfo(novelInfo);
}

void CSearchViewController::listViewDidDeselectCellAtIndex(CAListView *listView, unsigned int index)
{
	
}

std::string CSearchViewController::GetValue(int index)
{
	std::string text;
	if (m_textMap.find(index) != m_textMap.end())
	{
		text = m_textMap.at(index);
	}
	return text;
}

void CSearchViewController::GetLocalSearchRecord()
{
	std::string xml = CGlobalFunction::GetProfilePath();
	tinyxml2::XMLDocument *pDocument = new tinyxml2::XMLDocument();
	if (!pDocument)
	{
		return ;
	}
	unsigned long size = 0;
	unsigned char * data = CCFileUtils::sharedFileUtils()->getFileData(xml.c_str(), "rb", &size);
	pDocument->Parse((const char *)data);
	tinyxml2::XMLElement *pRootElement = pDocument->RootElement();
	if (pRootElement)
	{
		tinyxml2::XMLElement *pBookElement = pRootElement->FirstChildElement("book");
		if (pBookElement)
		{
			std::string str = "search";
			tinyxml2::XMLElement *pBookSearchElement = pBookElement->FirstChildElement();
			while (pBookSearchElement)
			{
				if (str.compare(pBookSearchElement->Name()) == 0)
				{
					tinyxml2::XMLElement *pBookItem = pBookSearchElement->FirstChildElement();
					for (int i = 0; pBookItem; i++)
					{
						m_textMap[i] = pBookItem->Name();
						pBookItem = pBookItem->NextSiblingElement();
					}
					break;
				}
				pBookSearchElement = pBookSearchElement->NextSiblingElement();
			}			
		}		
	}	
	delete pDocument;
	pDocument = NULL;
}

void CSearchViewController::SaveSearchRecord(std::string text)
{
	std::string xml = CGlobalFunction::GetProfilePath();
	tinyxml2::XMLDocument *pDocument = new tinyxml2::XMLDocument();
	if (!pDocument)
	{
		return;
	}
	unsigned long size = 0;
	unsigned char * data = CCFileUtils::sharedFileUtils()->getFileData(xml.c_str(), "rb", &size);
	pDocument->Parse((const char *)data);
	tinyxml2::XMLElement *pRootElement = pDocument->RootElement();
	if (pRootElement)
	{
		tinyxml2::XMLElement *pBookElement = pRootElement->FirstChildElement();
		if (pBookElement)
		{
			bool findBook = false;
			while (pBookElement)
			{
				std::string book = "book";
				if (book.compare(pBookElement->Name()) == 0)
				{
					findBook = true;
					std::string str = "search";
					tinyxml2::XMLElement *pBookSearchElement = pBookElement->FirstChildElement();
					if (pBookSearchElement)
					{
						bool findSearch = false;
						bool findText = false;
						while (pBookSearchElement)
						{
							if (str.compare(pBookSearchElement->Name()) == 0)
							{
								findSearch = true;
								tinyxml2::XMLElement *pBookItem = pBookSearchElement->FirstChildElement();
								for (int i = 0; pBookItem; i++)
								{
									if (text.compare(pBookItem->Name()) == 0)
									{
										findText = true;
										break;
									}
									pBookItem = pBookItem->NextSiblingElement();
								}
								if (findText)
								{
									break;
								}
								else
								{
									pBookItem = pDocument->NewElement(text.c_str());
									pBookSearchElement->LinkEndChild(pBookItem);
									break;
								}
							}
							pBookSearchElement = pBookSearchElement->NextSiblingElement();
						}
						if (!findSearch)
						{
							pBookSearchElement = pDocument->NewElement("search");
							pBookElement->LinkEndChild(pBookSearchElement);
							tinyxml2::XMLElement *pBookItem = pDocument->NewElement(text.c_str());
							pBookSearchElement->LinkEndChild(pBookItem);
							break;
						}
						else
						{
							break;
						}
					}
					else
					{
						pBookSearchElement = pDocument->NewElement("search");
						pBookElement->LinkEndChild(pBookSearchElement);
						tinyxml2::XMLElement *pBookItem = pDocument->NewElement(text.c_str());
						pBookSearchElement->LinkEndChild(pBookItem);
						break;
					}
				}
			}
			if (!findBook)
			{
				tinyxml2::XMLElement *pBookElement = pDocument->NewElement("book");
				pRootElement->LinkEndChild(pBookElement);
				tinyxml2::XMLElement *pBookSearchElement = pDocument->NewElement("search");
				pBookElement->LinkEndChild(pBookSearchElement);
				tinyxml2::XMLElement *pBookItem = pDocument->NewElement(text.c_str());
				pBookSearchElement->LinkEndChild(pBookItem);
			}			
		}
		else
		{
			tinyxml2::XMLElement *pBookElement = pDocument->NewElement("book");
			pRootElement->LinkEndChild(pBookElement);
			tinyxml2::XMLElement *pBookSearchElement = pDocument->NewElement("search");
			pBookElement->LinkEndChild(pBookSearchElement);
			tinyxml2::XMLElement *pBookItem = pDocument->NewElement(text.c_str());
			pBookSearchElement->LinkEndChild(pBookItem);
		}
	}
	else
	{
		pRootElement = pDocument->NewElement("profile");
		pDocument->LinkEndChild(pRootElement);
		tinyxml2::XMLElement *pBookElement = pDocument->NewElement("book");
		pRootElement->LinkEndChild(pBookElement);
		tinyxml2::XMLElement *pBookSearchElement = pDocument->NewElement("search");
		pBookElement->LinkEndChild(pBookSearchElement);
		tinyxml2::XMLElement *pBookItem = pDocument->NewElement(text.c_str());
		pBookSearchElement->LinkEndChild(pBookItem);
	}
	pDocument->SaveFile(xml.c_str());
	delete pDocument;
	pDocument = NULL;
}

void CSearchViewController::AddTextToMap(std::string text)
{
	bool find = false;
	std::map<int, std::string>::iterator it = m_textMap.begin();
	for (; it != m_textMap.end(); it++)
	{
		if (it->second.compare(text) == 0)
		{
			find = true;
			break;
		}
	}
	if (!find)
	{
		m_textMap[m_textMap.size()] = text;
	}
}

void CSearchViewController::UpdateRecordView()
{
	if (m_pRecord)
	{
		CALabel *pLabel = (CALabel*)m_pRecord->getSubviewByTextTag("label");
		CAView *pLine = m_pRecord->getSubviewByTextTag("line");
        CAButton *pClearButton = (CAButton *)m_pRecord->getSubviewByTextTag("clearButton");
		if (pLabel && pLine)
		{
			if (m_textMap.size() == 0)
			{
				pLabel->setText(UTF8("暂无记录"));
				pLine->setVisible(false);
                pClearButton->setVisible(false);
			}
			else
			{
				pLabel->setText(UTF8("搜索记录"));
				pLine->setVisible(true);
                pClearButton->setVisible(true);
			}
		}		
	}
}
