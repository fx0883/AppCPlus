//#include "CommonHttpManager.h"

#ifndef CDData_h
#define CDData_h

#include "AppMacros.h"

#define _T(x) L##x
#define CHAR    wchar_t


//导航条颜色
#define NavColor ccc4(243,122,142,255)
#define SectionTitleColor ccc4(245,191,186,255)
#define MenuTextColor ccc4(114,78,56,255)
#define MenuTopViewColor ccc4(255,189,184,255)
#define FAVORITERECIPEKEY "FavoriteRecipeKey"

//孕期子菜单
static const CHAR* menuList[5][6] =
{
    {_T("孕早期食谱"),_T("怀孕第一个月"), _T("怀孕第二个月"),_T("怀孕第三个月")},
    {_T("孕中期食谱"),_T("怀孕第四个月"), _T("怀孕第五个月"),_T("怀孕第六个月")},
    {_T("孕晚期食谱"),_T("怀孕第七个月"), _T("怀孕第八个月"), _T("怀孕第九个月"), _T("怀孕第十个月")},
    {_T("功能性食谱"),_T("缓解孕吐食谱"), _T("补血食谱"), _T("孕妇补维生素食谱"), _T("优生食谱")},
    {_T("我的收藏")}
};


static const CHAR* recipeDetailStep[3] =
{
    _T("用料"), _T("制作步骤"), _T("小提示")
};





//static const CHAR* menuTitle[4] =
//{
//	_T("分类"), _T("新闻"), _T("图片"), _T("我的")
//};
//
//static const CHAR* newsTitle[5] =
//{
//	_T("头条"), _T("娱乐"), _T("社会"), _T("汽车"), _T("科技")
//};
//
//static const CHAR* imageTitle[4] =
//{
//	_T("八卦"), _T("服饰"), _T("美体"), _T("彩妆")
//};
//
//static const char* menuTag[5] =
//{
//	"__all__", "news_entertainment", "news_society", "news_car", "news_tech"
//};
//
//static const char* imageTag[4] =
//{
//	"gossip", "style", "body", "beauty"
//};
//
//static const CHAR* aboutMenuTag[12] =
//{
//	_T("新用户做任务，赢大奖"),
//    _T("礼品中心"),
//    _T("离线下载"),
//    _T("夜间模式"),
//    _T("头条推送"),
//    _T("仅wifi下载图片"),
//    _T("正文字号"),
//    _T("清除缓存"),
//    _T("检查更新"),
//    _T("评分"),
//    _T("反馈"),
//    _T("关于")
//};
//
//static const char* iconTag[30] =
//{
//    "image/AlertView.png",
//    "image/button.png",
//    "image/SegmentedControl.png",
//    
//    "image/ImageView.png",
//    "image/Scale9ImageView.png",
//    "image/indicatorView.png",
//    
//    "image/Progress.png",
//    "image/slider.png",
//    "image/Switch.png",
//    
//    "image/Stepper.png",
//    "image/Label.png",
//    "image/TextField.png",
//    
//    "image/TextView.png",
//    "image/TabBar.png",
//    "image/PageView.png",
//    
//    "image/ScrollView.png",
//    "image/CollectionView.png",
//    "image/CollectionView.png",
//    
//    "image/CollectionView.png",
//    "image/CollectionView.png",
//    "image/ListView.png",
//    
//    "image/TableView.png",
//    "image/PickerView.png",
//    "image/WebView.png",
//    
//    "image/GifView.png",
//    "image/FlashView.png",
//    "image/Video.png",
//    
//    "image/RenderImage.png",
//    "image/Video.png",
//    "image/CollectionView.png",
//    
//};

#endif
