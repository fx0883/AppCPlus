#import "AppController.h"
#import "AppDelegate.h"
#import "RootViewController.h"
#import "AdsManage.h"
#import "iRate.h"

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// CrossApp application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    // Init the EAGLView

    // Use RootViewController manage EAGLView 
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = NO;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden:NO];
    
    CrossApp::CCApplication::sharedApplication()->run();
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [AdsManage sharedManager];
    });
    [self setupIRate];
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    CrossApp::CAApplication::getApplication()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    CrossApp::CAApplication::getApplication()->resume();
    
    int64_t intdelta = 0;
    
#ifdef DEBUG
    
    intdelta = (int64_t)(3 * NSEC_PER_USEC);
    
#else
    
    intdelta = (int64_t)(3 * NSEC_PER_SEC);
    
#endif
    
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, intdelta), dispatch_get_main_queue(), ^{
            [[AdsManage sharedManager] showInterstitial];
        });
        

}
#pragma mark - iRate
-(void)setupIRate {
    ///
    [iRate sharedInstance].messageTitle = NSLocalizedString(@"求5星好评", nil);
    [iRate sharedInstance].message = NSLocalizedString(@"🌟您似乎很喜欢这个应用哦！\n为了让更多朋友能知道我们，能否花几秒钟给一个5星好评呢？💖谢谢咯~", nil);
    [iRate sharedInstance].updateMessage = NSLocalizedString(@"🌟我们的应用更新了哦！\n为了让更多朋友能知道我们，能否花几秒钟给一个5星好评呢？💖谢谢咯~", nil);
    [iRate sharedInstance].cancelButtonLabel = NSLocalizedString(@"算了，没功夫", nil);
    [iRate sharedInstance].remindButtonLabel = NSLocalizedString(@"额，容朕再想想", nil);
    [iRate sharedInstance].rateButtonLabel = NSLocalizedString(@"好啊，赏你个5星", nil);
    [iRate sharedInstance].useUIAlertControllerIfAvailable = YES;
    [iRate sharedInstance].previewMode = NO;
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    CrossApp::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    CrossApp::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}


@end
