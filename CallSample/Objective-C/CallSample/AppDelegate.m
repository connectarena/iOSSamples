//
//  AppDelegate.m
//  CallSample
//
//  Created by Kiran Vangara on 11/01/15.
//  Copyright © 2015-2018, Connect Arena Private Limited. All rights reserved.
//

#import "AppDelegate.h"
#import <PushKit/PushKit.h>
#import <AVFoundation/AVFoundation.h>
#import <AWSS3/AWSS3TransferUtility.h>

#import "CallManager.h"
#import "LoginViewController.h"
@import UserNotifications;
@import VoxSDK;

@interface AppDelegate ()<PKPushRegistryDelegate, UNUserNotificationCenterDelegate>

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
	UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
	[center removeAllDeliveredNotifications];

    // initialize core modules
    [[CSClient sharedInstance] initialize];
	
	// initialize call manager
	[CallManager sharedInstance];
	
    [[UINavigationBar appearance] setTintColor:[UIColor colorWithRed:249.0/255.0 green:249.0/255.0 blue:249.0/255.0 alpha:1.0]];
	
    [[UITabBar appearance] setTintColor:[UIColor colorWithRed:0.0/255.0 green:150.0/255.0 blue:136.0/255.0 alpha:1.0]];
    [[UITabBar appearance] setAlpha:1.0];
    
    UIPageControl *pageControl = [UIPageControl appearance];
    pageControl.pageIndicatorTintColor = [UIColor lightGrayColor];
    pageControl.currentPageIndicatorTintColor = [UIColor colorWithRed:0.0/255.0 green:150.0/255.0 blue:136.0/255.0 alpha:1.0];
    //pageControl.backgroundColor = [UIColor blueColor];
	
//    [[UIBarButtonItem appearanceWhenContainedIn: [UISearchBar class], nil] setTintColor:[UIColor blackColor]];
    
    
    [[UIBarButtonItem appearanceWhenContainedInInstancesOfClasses:@[[UISearchBar class]]] setTintColor:[UIColor blackColor]];

	// Ask permission for user notifications
	
	UNAuthorizationOptions options = UNAuthorizationOptionAlert + UNAuthorizationOptionSound + UNAuthorizationOptionBadge;
	
	[center requestAuthorizationWithOptions:options
						  completionHandler:^(BOOL granted, NSError * _Nullable error) {
							  if (!granted) {
								  NSLog(@"UserNotification permission not granted");
							  }
						  }];
	
	PKPushRegistry *pushRegistry = [[PKPushRegistry alloc]
									initWithQueue:dispatch_get_main_queue()];
	pushRegistry.delegate = self;
	pushRegistry.desiredPushTypes = [NSSet setWithObject:PKPushTypeVoIP];
	
    [self registerForRemoteNotification];
    
    if ([CSSettings getAutoSignin] == false){
        [self moveToLoginScreen];
    } else {
        [self moveToHomeViewController];
    }
	
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
	
	// Clear notifications
	UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
	[center removeAllDeliveredNotifications];
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.

}

//-(BOOL)application:(UIApplication *)application continueUserActivity:(nonnull NSUserActivity *)userActivity restorationHandler:(nonnull void (^)(NSArray * _Nullable))restorationHandler {
//    
//    NSLog(@"%s %@", __PRETTY_FUNCTION__, userActivity);
//    
//    return TRUE;
//}

- (BOOL)application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void (^)(NSArray<id<UIUserActivityRestoring>> * _Nullable))restorationHandler {
    
    NSLog(@"%s %@", __PRETTY_FUNCTION__, userActivity);
    
    return TRUE;
    
}

- (void)application:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)(void))completionHandler {

    [AWSS3TransferUtility interceptApplication:application
           handleEventsForBackgroundURLSession:identifier
                             completionHandler:completionHandler];
}

#pragma mark - Push Notification callback
- (void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings {
    [application registerForRemoteNotifications];
}

#define SYSTEM_VERSION_GRATERTHAN_OR_EQUALTO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)

-(void) registerForRemoteNotification {
    
    UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
    center.delegate = self;
    [center requestAuthorizationWithOptions:(UNAuthorizationOptionSound | UNAuthorizationOptionAlert | UNAuthorizationOptionBadge) completionHandler:^(BOOL granted, NSError * _Nullable error){
        if(!error){
            dispatch_async(dispatch_get_main_queue(), ^{
                [[UIApplication sharedApplication] registerForRemoteNotifications];
            });
        }
        else {
            NSLog(@"UserNotification registration error : %@", error.localizedDescription);
        }
    }];
}

//Called when a notification is delivered to a foreground app.
-(void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions options))completionHandler{
    NSLog(@"User Info : %@",notification.request.content.userInfo);
    completionHandler(UNAuthorizationOptionSound | UNAuthorizationOptionAlert | UNAuthorizationOptionBadge);
}

//Called to let your app know which action was selected by the user for a given notification.
- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void(^)(void))completionHandler {
	NSLog(@"User Info : %@",response.notification.request.content.userInfo);
    
    NSString * notificationBodyTxt = response.notification.request.content.body;
    
    if ([notificationBodyTxt isEqualToString:@"Missed Call"]) {
        
        NSLog(@"Move to call History");
        [self openCallHistoryViewController];
        return;
    }
    
    completionHandler();
}

- (void)application:(UIApplication*)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData*)deviceToken {
    
    if(deviceToken.length == 0) {
        NSLog(@"NO Push token");
        return;
    }
    
    const unsigned char *tokenBytes = deviceToken.bytes;
    NSMutableString *deviceTokenString  = [NSMutableString stringWithCapacity:(deviceToken.length * 2)];
    for (int i = 0; i < deviceToken.length; ++i) {
        [deviceTokenString appendFormat:@"%02x", tokenBytes[i]];
    }
    
    if (deviceTokenString != nil) {
        NSLog(@"Device token : %@", deviceTokenString);
        [CSSettings setRemoteDeviceToken:deviceTokenString];
    }
}

- (void)application:(UIApplication*)application didFailToRegisterForRemoteNotificationsWithError:(NSError*)error {
    NSLog(@"FailToRegisterForRemoteNotifications %@", error.localizedDescription);
}

#pragma mark - PushKit Delegates

- (void)pushRegistry:(PKPushRegistry *)registry didUpdatePushCredentials:(PKPushCredentials *)credentials forType:(NSString *)type{
    
    if([credentials.token length] == 0) {
        NSLog(@"NO VOIP Push token");
        return;
    }
    
    NSLog(@"Voip Token: %@", credentials.token);
    
    const unsigned *tokenBytes = [credentials.token bytes];
    
    NSString *deviceTokenString = [NSString stringWithFormat:@"%08x%08x%08x%08x%08x%08x%08x%08x",
                                   ntohl(tokenBytes[0]), ntohl(tokenBytes[1]), ntohl(tokenBytes[2]),
                                   ntohl(tokenBytes[3]), ntohl(tokenBytes[4]), ntohl(tokenBytes[5]),
                                   ntohl(tokenBytes[6]), ntohl(tokenBytes[7])];
    
    if (deviceTokenString != nil) {
        NSLog(@"VOIP Device token : %@", deviceTokenString);
        [CSSettings setVoipDeviceToken:deviceTokenString];
    }
    
}


- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(PKPushType)type withCompletionHandler:(void (^)(void))completion{
    
    NSDictionary *aps = payload.dictionaryPayload[@"aps"];
    NSLog(@"Push Notification payload : %@", payload.dictionaryPayload);
    NSData *data = [[aps valueForKey:@"alert"] dataUsingEncoding:NSUTF8StringEncoding];
    NSError *err = nil;
    NSDictionary *callData = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&err];
    NSString *callId = [callData valueForKey:@"scallid"];
    
    [[NSUserDefaults standardUserDefaults] setObject:callId forKey:@"scallid"];
    
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    
    [[CallManager sharedInstance] reportNewIncomingCallToCallKitWithCallData:callData];
    [[CallManager sharedInstance] setCallFrom:TRUE];
    [[CSClient sharedInstance] processPushNotification:payload.dictionaryPayload];
    [[CallManager sharedInstance] startRemotePushCall:callData];
    
    
}

-(void)moveToHomeViewController{
    UIStoryboard *story=[UIStoryboard storyboardWithName:@"Main" bundle:nil];
    UITabBarController *tabbarController = [story instantiateViewControllerWithIdentifier:@"TabBarController"];
    
    [tabbarController setSelectedIndex:0];
    self.window.rootViewController = tabbarController;
    [self.window makeKeyAndVisible];
}


- (void)moveToLoginScreen {
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    
    // Instantiate the UINavigationController (Initial View Controller)
    UINavigationController *navController = [storyboard instantiateInitialViewController];
    
    [self.window setRootViewController:navController];
    [self.window makeKeyAndVisible];
}


-(void)openCallHistoryViewController{
    
    UIStoryboard *story=[UIStoryboard storyboardWithName:@"Main" bundle:nil];
    UITabBarController *tabbarController = [story instantiateViewControllerWithIdentifier:@"TabBarController"];
    [tabbarController setSelectedIndex:1];
    self.window.rootViewController = tabbarController;
    [self.window makeKeyAndVisible];
    
}

#pragma mark - ConnectSDK Notifications

@end

#pragma mark Rotation overrides

@implementation UITabBarController (AutoRotationForwarding)

-(BOOL)shouldAutorotate {
	
    return [self.selectedViewController shouldAutorotate];
}

-(NSUInteger)supportedInterfaceOrientations {
    
    return [self.selectedViewController supportedInterfaceOrientations];
}

- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation {
	
    return [self.selectedViewController preferredInterfaceOrientationForPresentation];
} 

@end

@implementation UINavigationController (AutoRotationForwarding)

-(BOOL)shouldAutorotate {
    
    return [self.topViewController shouldAutorotate];
}

-(NSUInteger)supportedInterfaceOrientations {

    return [self.topViewController supportedInterfaceOrientations];
}

- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation {
    
    return [self.topViewController preferredInterfaceOrientationForPresentation];
}

@end

#import <QuartzCore/QuartzCore.h>

@implementation CALayer (Additions)

- (void)setBorderColorFromUIColor:(UIColor *)color
{
	self.borderColor = color.CGColor;
}
- (void)setShadowColorFromUIColor:(UIColor *)color
{
	self.shadowColor = color.CGColor;
}

@end
