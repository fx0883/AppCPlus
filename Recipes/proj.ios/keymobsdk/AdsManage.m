//
//  AdsMoGoManage.m
//  DYMReader
//
//  Created by apple on 3/25/16.
//  Copyright © 2016 Dong Yiming. All rights reserved.
//

#import "AdsManage.h"
#import "AdsManage+Specific.h"
//#import "DYMBookUtility.h"
#import <KeymobAd/KeymobAd.h>
//#import "AdListener.h"



@interface AdsManage()
{
    Boolean _isFirstShow;
    
}
@end

@implementation AdsManage

+(instancetype)sharedManager {
    static AdsManage *instance;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [AdsManage new];
    });
    
    return instance;
}


- (instancetype)init
{
    self = [super init];
    if (self) {
        _isFirstShow = YES;
        _needToShowedInterstitial = YES;
        [self initAd];
    }
    return self;
}


-(void) configAdFromKeymobService{
    [[AdManager sharedInstance] configWithKeymobService:self.adsId isTesting:NO];//if you are debugging ,set auto cache no
}
-(void) configAdFromFile{
    NSError* error;
    NSString* file= [[NSBundle mainBundle] pathForResource:@"ads" ofType:@"json"];
    NSString *textFileContents =[NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:&error];
    NSLog(@"---------%@",textFileContents);
    [[AdManager sharedInstance] configWithJSON:textFileContents];
}

-(void)initAd
{
    
    [AdManager sharedInstance].controller=[AdsManage topMostVC];
    [AdManager sharedInstance].listener=self;
    [self configAdFromKeymobService];
    //[self configAdFromFile];
    [[AdManager sharedInstance] loadInterstitial];
}

-(void)initSplash
{


}

- (void)initInterstitialIns{
 
    
}





-(void)showInterstitial
{
//    if([[AdManager sharedInstance] isInterstitialReady]){
//        [[AdManager sharedInstance] showInterstitialWithController:[DYMBookUtility topMostVC]];
//    }
    if(_needToShowedInterstitial == NO)
    {
        return;
    }
    
    if([[AdManager sharedInstance] isInterstitialReady]){
        [[AdManager sharedInstance] showInterstitialWithController:[AdsManage topMostVC]];
    }else{
        [[AdManager sharedInstance] loadInterstitial];
    }
}

+(UIViewController *)topMostVC {
    
    UIViewController *topVC = [UIApplication sharedApplication].keyWindow.rootViewController;
    while (topVC.presentedViewController) {
        topVC = topVC.presentedViewController;
    }
    
    return topVC;
}

-(void)setupTopBanner:(UIView*)pView
{


}

-(void)setupBottomBanner:(UIViewController*)pVC
{
    CGRect rx = pVC.view.bounds;
//    
//    int intX = 0;
//    int intY = 519;
    
//    [[AdManager sharedInstance] showBannerABS:KM_SIZE_TYPE_BANNER atX:0 atY:400 withController:pVC];
    
//    [[AdManager sharedInstance] showRelationBanner:BANNER_SIZE_BANNER atPosition:BANNER_POSITIONS_BOTTOM_CENTER withOffY:80];
    
//    [AdManager sharedInstance] showRelationBanner:<#(int)#> atPosition:<#(int)#> withOffY:<#(int)#> withController:<#(UIViewController *)#>
    
    
    if([[UIScreen mainScreen] bounds].size.height > 480)
    {
    [[AdManager sharedInstance] showRelationBanner:KM_SIZE_TYPE_BANNER atPosition:KM_BANNER_POSITIONS_BOTTOM_CENTER withOffY:0 withController:pVC];
    }
    
//        [[AdManager sharedInstance] showBannerABS:KM_SIZE_TYPE_BANNER atX:intX atY:intY withController:pVC];
    
}







#pragma mark- IAdEventListener

- (void)onLoadedSuccess:(int) adtype withAdapter:(id<IPlatform>)adapter andData:(id)error{
    if(KM_AD_TYPES_INTERSTITIAL==adtype && _isFirstShow){
        _isFirstShow = NO;
           [[AdsManage sharedManager] showInterstitial];
        }
    NSLog(@"onLoadedSuccess %@  %d",[adapter platformName],adtype);
}
- (void)onLoadedFail:(int) adtype withAdapter:(id<IPlatform>)adapter andData:(id)error{
    
//    if(KM_AD_TYPES_INTERSTITIAL==adtype){
//        
//        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
//            //            [AdManager sharedInstance].controller=[DYMBookUtility topMostVC];
//            [[AdManager sharedInstance] loadInterstitial];
//        });
//        
//    }
    NSLog(@"onLoadedFail %@ %@ %d",error,[adapter platformName],adtype);
}
- (void)onAdOpened:(int) adtype withAdapter:(id<IPlatform>)adapter andData:(id)error{
    NSLog(@"onAdOpened %@ %@ %d",error,[adapter platformName],adtype);
}
- (void)onAdClosed:(int) adtype withAdapter:(id<IPlatform>)adapter andData:(id)error{
    if(KM_AD_TYPES_INTERSTITIAL==adtype){
        
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
//            [AdManager sharedInstance].controller=[DYMBookUtility topMostVC];
            [[AdManager sharedInstance] loadInterstitial];
        });

    }

    NSLog(@"onAdClosed %@ %@ %d",error,[adapter platformName],adtype);
}
- (void)onAdClicked:(int) adtype withAdapter:(id<IPlatform>)adapter andData:(id)error{
    NSLog(@"onAdClicked %@ %@ %d",error,[adapter platformName],adtype);
}
- (void)onOtherEvent:(int) adtype withAdapter:(id<IPlatform>)adapter andData:(id)error eventName:(NSString*)_eventName{
    NSLog(@"onOtherEvent %@ %@ %d",error,[adapter platformName],adtype);
    
    if([_eventName  isEqual: @"initKeymobFail"])
    {
        [self configAdFromFile];
//        [[AdManager sharedInstance] loadInterstitial];
    }
    else if([_eventName  isEqual: @"initKeymobSuccess"])
    {
//         [[AdManager sharedInstance] loadInterstitial];
    }
    
}





@end
