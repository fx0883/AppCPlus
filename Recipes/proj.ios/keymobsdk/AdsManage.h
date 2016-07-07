//
//  AdsMoGoManage.h
//  DYMReader
//
//  Created by apple on 3/25/16.
//  Copyright © 2016 Dong Yiming. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <KeymobAd/KeymobAd.h>

@protocol AdManageAppId <NSObject>

-(NSString *)adsId;
@end


@interface AdsManage : NSObject<IAdEventListener>

@property (nonatomic, assign) BOOL                          needToShowedInterstitial;

+(instancetype)sharedManager;

-(void)showInterstitial;

-(void)setupTopBanner:(UIView*)pView;

-(void)setupBottomBanner:(UIViewController*)pVC;

+(UIViewController *)topMostVC;

//-(void)initAd;
//
//-(void)initInterstitialIns;

@end
