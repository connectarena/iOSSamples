//
//  CallManager.m
//  CallSample
//
//  Created by Kiran Vangara on 03/08/18.
//  Copyright © 2018 Connect Arena Private Limited. All rights reserved.
//

#import "CallManager.h"
#import "CallViewController.h"
#import "VideoCallViewController.h"
#import "AppDelegate.h"
@import Contacts;

#define keyForCallID @"IsCallEndedBeforeLoginFromCallKit"

@import AVFoundation;
@import CallKit;
@import UserNotifications;
@import Photos;
@import CoreLocation;

@import VoxSDK;

@interface CallManager () <CXProviderDelegate>

@property (nonatomic, strong) AVAudioPlayer* audioPlayer;
@property (nonatomic, strong) NSTimer* ringtoneTimer;

@property (nonatomic) BOOL needCallScreenDisplay;
@property (nonatomic) BOOL activeCallExists;

@property (nonatomic, strong) CXProvider *callKitProvider;
@property (nonatomic, strong) CXCallController *callKitCallController;
@property (strong, nonatomic) CSContact* sdkContact;

@end

@implementation CallManager

+(CallManager*) sharedInstance {
	
	static CallManager *instance;
	static dispatch_once_t predicate;
	
	dispatch_once(&predicate, ^ {
		
		instance = [[CallManager alloc] init];
		instance.needCallScreenDisplay = NO;
		instance.activeCallExists = NO;
        instance.secondCallExists = NO;
		instance.calls = [[NSMutableDictionary alloc] init];
		instance.callsList = [[NSMutableArray alloc] init];
		[[NSNotificationCenter defaultCenter] addObserver:instance selector:@selector(handleIncomingCallNotification:) name:@"IncomingCallNotification" object:nil];
		[[NSNotificationCenter defaultCenter] addObserver:instance selector:@selector(handleEndCallNotification:) name:@"EndCallNotification" object:nil];
		[[NSNotificationCenter defaultCenter] addObserver:instance selector:@selector(handleMuteNotification:) name:@"MuteNotification" object:nil];
		[[NSNotificationCenter defaultCenter] addObserver:instance selector:@selector(handleStartCallNotification:) name:@"StartCallNotification" object:nil];
		[[NSNotificationCenter defaultCenter] addObserver:instance selector:@selector(handleMissedCallNotification:) name:@"MissedCallNotification" object:nil];
		[[NSNotificationCenter defaultCenter] addObserver:instance
												 selector:@selector(handleAppBecomeActive:)
													 name:UIApplicationDidBecomeActiveNotification
												  object :nil];
        [[NSNotificationCenter defaultCenter] addObserver:instance selector:@selector(callDeclineNotification:) name:@"callDeclineNotification" object:nil];

		[instance configureCallKit];
	});
	
	return instance;
}


#pragma mark - CXProviderDelegate

- (void)providerDidReset:(CXProvider *)provider {

}

- (void)providerDidBegin:(CXProvider *)provider {
	}

- (void)provider:(CXProvider *)provider didActivateAudioSession:(AVAudioSession *)audioSession {
	
	
	[CSCall audioSessionDidActivate:audioSession];
}

- (void)provider:(CXProvider *)provider didDeactivateAudioSession:(AVAudioSession *)audioSession {
	
	[CSCall audioSessionDidDeactivate:audioSession];
}

- (void)provider:(CXProvider *)provider timedOutPerformingAction:(CXAction *)action {
	
}

- (void)provider:(CXProvider *)provider performStartCallAction:(CXStartCallAction *)action {

	
	[action fulfillWithDateStarted:[NSDate date]];
}

- (void)provider:(CXProvider *)provider performAnswerCallAction:(CXAnswerCallAction *)action {
    
    NSLog(@"provider:performAnswerCallAction:");
    
    NSString* uuid = [[action callUUID] UUIDString];
    
    NSLog(@"\n");
    NSLog(@"**AppLog** Calls List and the current UUID is %@ and %@",self.calls,uuid);
    NSLog(@"\n");
    
    CSCall* callObject = self.calls[uuid];

    NSLog(@"Call Session in Answer Call Scenario %@",callObject);
    NSLog(@"Call Type in Answer Call Scenario %ld",(long)[callObject getCallType]);

    [action fulfill];
    
    NSLog(@"**AppLog** Count of CallsList is %lu",(unsigned long)self.callsList.count);
    
    self.isCallAnsweredFromCallKit = YES;
    
    double delayInSeconds = 1.0;
    
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
       
        if (callObject != nil) {

            [self.callsList addObject:callObject];
            [callObject answerCall];
            NSLog(@"**AppLog** Count of CallsList after adding is %lu",(unsigned long)self.callsList.count);

            /* Show the Call View Controller when the call is answered in Foreground scenario. This method gets called only for Foreground scenarios after hitting HandleIncomingCalls Method.*/
            [self showCallViewFromBackground:true withCallSession:callObject];
        }
    });
}

- (void)provider:(CXProvider *)provider performEndCallAction:(CXEndCallAction *)action {
	NSString* uuid = [[action callUUID] UUIDString];
	CSCall* call = self.calls[uuid];

	if(call) {
		// TODO : if user cancelled?
		[call endCall:@"User ended"];
		[self.calls removeObjectForKey:uuid];
        
	}
	
	self.needCallScreenDisplay = NO;
	
	[action fulfillWithDateEnded:[NSDate date]];
}

- (void)provider:(CXProvider *)provider performSetHeldCallAction:(CXSetHeldCallAction *)action {
	
	NSString* uuid = [[action callUUID] UUIDString];
	CSCall* call = self.calls[uuid];

	if([action isOnHold])
    {
        self.secondCallExists = YES;
        
        [call holdCall];
    }else
    {
		[call unholdCall];
    }
	
	[action fulfill];
}

- (void)provider:(CXProvider *)provider performSetMutedCallAction:(CXSetMutedCallAction *)action {
	
	NSString* uuid = [[action callUUID] UUIDString];
	CSCall* call = self.calls[uuid];

	if([action isMuted])
		[call mute:CSAudioVideo];
	else
		[call unmute:CSAudioVideo];
	
	[action fulfill];
}

- (void)provider:(CXProvider *)provider performSetGroupCallAction:(CXSetGroupCallAction *)action {
    
	
}

- (void)provider:(CXProvider *)provider performPlayDTMFCallAction:(CXPlayDTMFCallAction *)action {
	
}

#pragma mark - CallKit Actions

- (void)performStartCallActionWithUUID:(NSUUID *)uuid handle:(NSString *)handle {
	
	if (uuid == nil || handle == nil) {
		return;
	}
	
	CXHandle *callHandle = [[CXHandle alloc] initWithType:CXHandleTypePhoneNumber value:handle];
	CXStartCallAction *startCallAction = [[CXStartCallAction alloc] initWithCallUUID:uuid handle:callHandle];
	CXTransaction *transaction = [[CXTransaction alloc] initWithAction:startCallAction];
	
	[self.callKitCallController requestTransaction:transaction completion:^(NSError *error) {
		if (error) {
			NSLog(@"StartCallAction transaction request failed: %@", [error localizedDescription]);
		} else {
			NSLog(@"StartCallAction transaction request successful");
			
			CXCallUpdate *callUpdate = [[CXCallUpdate alloc] init];
			callUpdate.remoteHandle = callHandle;
			callUpdate.supportsDTMF = NO;
			callUpdate.supportsHolding = YES;
			callUpdate.supportsGrouping = YES;
			callUpdate.supportsUngrouping = YES;
			callUpdate.hasVideo = NO;
			
			[self.callKitProvider reportCallWithUUID:uuid updated:callUpdate];
		}
	}];
}

- (void)performEndCallActionWithUUID:(NSUUID *)uuid {
	if (uuid == nil) {
		return;
	}
	
	CXEndCallAction *endCallAction = [[CXEndCallAction alloc] initWithCallUUID:uuid];
	CXTransaction *transaction = [[CXTransaction alloc] initWithAction:endCallAction];
	
	[self.callKitCallController requestTransaction:transaction completion:^(NSError *error) {
		if (error) {
			NSLog(@"EndCallAction transaction request failed: %@", [error localizedDescription]);
		}
		else {
			NSLog(@"EndCallAction transaction request successful");
		}
	}];
}

- (void)performMuteCallActionWithUUID:(NSUUID *)uuid muted:(BOOL)muted {
	if (uuid == nil) {
		return;
	}
	
	CXSetMutedCallAction *muteCallAction = [[CXSetMutedCallAction alloc] initWithCallUUID:uuid muted:muted];
	CXTransaction *transaction = [[CXTransaction alloc] initWithAction:muteCallAction];
	
	[self.callKitCallController requestTransaction:transaction completion:^(NSError *error) {
		if (error) {
			NSLog(@"muteCallAction transaction request failed: %@", [error localizedDescription]);
		}
		else {
			NSLog(@"muteCallAction transaction request successful");
		}
	}];
}

- (void)configureCallKit {
	
	CXProviderConfiguration *configuration = [[CXProviderConfiguration alloc] initWithLocalizedName:@"CallSample"];
	configuration.maximumCallGroups = 3;
	configuration.maximumCallsPerCallGroup = 3;
	
	UIImage *callkitIcon = [UIImage imageNamed:@"logo_callkit"];
	configuration.iconTemplateImageData = UIImagePNGRepresentation(callkitIcon);
	
	self.callKitProvider = [[CXProvider alloc] initWithConfiguration:configuration];
	[self.callKitProvider setDelegate:self queue:nil];
	
	self.callKitCallController = [[CXCallController alloc] init];
    
}

-(void)reportNewIncomingCallToCallKitWithCallData:(NSDictionary *)callData{
    
    NSString* uuidString = [[callData valueForKey:@"scallid"] uppercaseString];
    NSUUID *uuid = [[NSUUID alloc] initWithUUIDString:uuidString];
    CXHandle *callHandle = [[CXHandle alloc] initWithType:CXHandleTypePhoneNumber
                                                    value:[callData valueForKey:@"smobnu"]];
    
    CXCallUpdate *callUpdate = [[CXCallUpdate alloc] init];
    callUpdate.remoteHandle = callHandle;
    callUpdate.supportsDTMF = NO;
    callUpdate.supportsHolding = true;
    callUpdate.supportsGrouping = true;
    callUpdate.supportsUngrouping = true;
    
    
    if ([callData valueForKey:@"stcalltype"] != nil) {
        
        //TODO: Remove the || condition once the changes of stcalltype is changed from the Server
        //TODO: Get the changes of stcalltype done in the server after verifying the proto.
        if ([[callData valueForKey:@"stcalltype"] intValue] == 1 || [[callData valueForKey:@"stcalltype"] intValue] == 4) {
            callUpdate.hasVideo = NO;
            self.isIncomingCallAVideoCall = false;
        }else{
            callUpdate.hasVideo = YES;
            self.isIncomingCallAVideoCall = true;
        }
    }else{
        callUpdate.hasVideo = NO;
        self.isIncomingCallAVideoCall = false;
    }
    
    [self.callKitProvider reportNewIncomingCallWithUUID:uuid update:callUpdate completion:^(NSError *error) {
        if (!error) {
            NSLog(@"Incoming Push call successfully reported.");
        }
        else {
            NSLog(@"Failed to report incoming call successfully: %@.", [error localizedDescription]);
        }
    }];
}

-(void) dealloc {
	
	NSLog(@"CallManager : dealloc");
	if(self.callKitProvider) {
		[self.callKitProvider invalidate];
		self.callKitProvider = nil;
	}
}

#pragma mark - System Notifications

-(void) handleAppBecomeActive:(NSNotification*)notification {
	
	if(self.needCallScreenDisplay) {
		[self stopRingtone];
//		[self showCallView];
	}
}

#pragma mark - ConnectSDK Notifications

-(void) handleStartCallNotification:(NSNotification*)notification {
	
	CSCall* call = [notification.userInfo objectForKey:kARCallSession];
	NSUUID *uuid = [[NSUUID alloc] initWithUUIDString:[[call getCallID] uppercaseString]];
    if (uuid == nil) {
         [call endCall:@"User ended"];
        return;
    }
    self.calls[[uuid UUIDString]] = call;
	[self performStartCallActionWithUUID:uuid handle:[call getRemoteNumber]];
}


-(void) handleIncomingCallNotification:(NSNotification*)notification {
    CSCall* callSession = [notification.userInfo objectForKey:kARCallSession];
    
    NSLog(@"**AppLog** 📲📲📲 CallSession in IncomingCallNotification is 📲📲📲 %@",callSession);
    
    /*Below Fix is to send Signaling Request for End Call when the call is ended in background State in Call Kit Screen before Login. PreviousCallID is saved to UserDefaults to compare with the current Call ID in performEndCallAction method when there is no valid call is available.*/
    
    NSString *currentCallID = [[callSession getCallID] uppercaseString];
    NSString *callIDSavedInPerformEndCallAction = [[NSUserDefaults standardUserDefaults] objectForKey:keyForCallID];
    
    NSLog(@"CurrentCallID is %@",currentCallID);
    NSLog(@"PreviousCallID is %@",callIDSavedInPerformEndCallAction);
    
    if ([currentCallID isEqualToString:callIDSavedInPerformEndCallAction]) {
        NSLog(@"#########Call Ended Signal sent to SDK#########");
        [callSession endCall:@"User Terminated"];
        return;
    }
    
    NSString* uuidString = [[callSession getCallID] uppercaseString];
    
    NSLog(@"\n");
    NSLog(@"**AppLog** UUID String is %@",uuidString);
    NSLog(@"\n");
    
    self.calls[uuidString] = callSession;
    
    NSLog(@"\n");
    NSLog(@"**AppLog** Calls Dictionary after Incoming Call is %@",self.calls);
    NSLog(@"\n");
    
    self.needCallScreenDisplay = YES;
    
    CSCallType callType = [callSession getCallType];
    
    NSUUID *uuid = [[NSUUID alloc] initWithUUIDString:uuidString];
    
    NSLog(@"\n");
    NSLog(@"**AppLog**   %@",[self fetchDisplayContactNameFromCallSession:callSession]);
    NSLog(@"\n");
    
    CXHandle *callHandle = [[CXHandle alloc]
                            initWithType:CXHandleTypeGeneric
                            value:[self fetchDisplayContactNameFromCallSession:callSession]];
    
    CXCallUpdate *callUpdate = [[CXCallUpdate alloc] init];
    callUpdate.remoteHandle = callHandle;
    callUpdate.supportsDTMF = NO;
    callUpdate.supportsHolding = true;
    callUpdate.supportsGrouping = true;
    callUpdate.supportsUngrouping = true;
    
    if(callType == CSCallTypeVideoCall){
        callUpdate.hasVideo = YES;
        self.isIncomingCallAVideoCall = true;
//        self.isInVideoCall = YES;
    }
    else{
        callUpdate.hasVideo = NO;
//        self.isInVideoCall = NO;
        self.isIncomingCallAVideoCall = false;
    }

    NSLog(@"\n");
    NSLog(@"**AppLog** ");
    NSLog(@"\n");
    
    NSLog(@"\n");
    NSLog(@"**AppLog** uuidString is %@ and scallid saved in UserDefaults is %@",uuidString,[[NSUserDefaults standardUserDefaults] stringForKey:@"scallid"]);
    NSLog(@"\n");
    
    NSString *callIDSavedInUserDefaultsForPushCall = [[NSUserDefaults standardUserDefaults] stringForKey:@"scallid"];
    
    /*Check if the call is from a Push Call and the App being in background*/
    if([uuidString isEqualToString:[callIDSavedInUserDefaultsForPushCall uppercaseString]]){
        
        NSLog(@"**AppLog** ☎️ ☎️ ☎️ Incoming Call Reported in Push Scenario ☎️ ☎️ ☎️");

        [self.callKitProvider reportCallWithUUID:uuid updated:callUpdate];
        [callSession indicateRinging:FALSE];
        /*Show AudioCallViewController or VideoCallViewController when the call is received from Push Usecase*/
        if (self.isCallAnsweredFromCallKit) {
            [self showCallViewFromBackground:true withCallSession:callSession];
        }
    }else{
        NSLog(@"**AppLog** 📱 📱 📱 New Incoming Call Reported in Foreground Scenario 📱 📱 📱");
        
        [self.callKitProvider reportNewIncomingCallWithUUID:uuid update:callUpdate completion:^(NSError *error) {
            if (!error) {
                
                    // RCP: Workaround per https://forums.developer.apple.com/message/169511
                    //[[VoiceClient sharedInstance] configureAudioSession];
                NSLog(@"\n");
                NSLog(@"**AppLog** Call Session when reporting Incoming Call inside Handle Incoming Call Notification is %@",callSession);
                NSLog(@"\n");
                
                if (callSession) {
                    NSString *callID = [callSession getCallID];
                    if (callID != nil) {
                        [callSession indicateRinging:FALSE];
                        
//                        if (self.isCallAnsweredFromCallKit) {
//                            [self showCallViewFromBackground:true withCallSession:callSession];
//                        }
                    }else{
                        NSLog(@"No Call ID when reporting Multiple Incoming Calls is %@",callID);
                    }
                }
            }
            else {
                NSLog(@"==============Failed to report incoming call successfully: %@.", [error localizedDescription]);
            }
        }];
    }
    
    [self setCallFrom:NO];
}

-(void) handleEndCallNotification:(NSNotification*)notification {
	self.needCallScreenDisplay = NO;
    self.secondCallExists = NO;
    self.isCallAnsweredFromCallKit = false;
    [self.callsList removeAllObjects];
	CSCall* callSession = [notification.userInfo objectForKey:kARCallSession];
	
	UIApplicationState state = [[UIApplication sharedApplication] applicationState];
	if (state == UIApplicationStateBackground || state == UIApplicationStateInactive) {
		
		UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
		
		[center getDeliveredNotificationsWithCompletionHandler:^(NSArray *notifications) {
			
			for(UNNotification* notification in notifications) {
				
				if([notification.request.identifier isEqualToString:[callSession getCallID]]) {
					
					[center removeDeliveredNotificationsWithIdentifiers:@[notification.request.identifier]];
					
					UNMutableNotificationContent *notifContent = [[UNMutableNotificationContent alloc] init];
					
					CSContact* contact = [callSession getRemoteContact];
					
					if(contact != nil)
						notifContent.title = contact.name;
					else
						notifContent.title = [callSession getRemoteNumber];
					
					notifContent.body = @"Missed call";
					
					UNNotificationRequest *request = [UNNotificationRequest requestWithIdentifier:[callSession getCallID]
																						  content:notifContent
																						  trigger:nil];
					[center addNotificationRequest:request withCompletionHandler:nil];
					break;
				}
			}
		}];
	}
	
	NSString* uuidString = [[callSession getCallID] uppercaseString];
	
	if([self.calls objectForKey:uuidString]) {
        
		[self performEndCallActionWithUUID:[[NSUUID alloc] initWithUUIDString:uuidString]];
		[self.calls removeObjectForKey:uuidString];
	}
	
}
-(void) callDeclineNotification:(NSNotification*)notification {
    CSCall* callSession = [notification.userInfo objectForKey:kARCallSession];
    NSString* uuidString = [[callSession getCallID] uppercaseString];
   
    if([self.calls objectForKey:uuidString]) {
         [self performEndCallActionWithUUID:[[NSUUID alloc] initWithUUIDString:uuidString]];
         [self.calls removeObjectForKey:uuidString];
         [self.callsList removeObject:callSession];
    }
    
    
}

-(void)endRemotePushCall:(NSDictionary *) jsonData{
    NSString* uuidString = [[jsonData valueForKey:@"scallid"] uppercaseString];
    NSUUID *uuid = [[NSUUID alloc] initWithUUIDString:uuidString];
    [self performEndCallActionWithUUID:uuid];
}

-(void)startRemotePushCall:(NSDictionary *) jsonData{
    
    NSString* uuidString = [[jsonData valueForKey:@"scallid"] uppercaseString];
    NSUUID *uuid = [[NSUUID alloc] initWithUUIDString:uuidString];
    
    NSLog(@"shiva startRemotePushCall uuid %@.", uuid);
    
    CXHandle *callHandle = [[CXHandle alloc] initWithType:CXHandleTypePhoneNumber
                                                    value:[jsonData valueForKey:@"smobnu"]];
    
    NSLog(@"shiva startRemotePushCall smobnu %@.", [jsonData valueForKey:@"smobnu"]);
    CXCallUpdate *callUpdate = [[CXCallUpdate alloc] init];
    callUpdate.remoteHandle = callHandle;
    callUpdate.supportsDTMF = NO;
    callUpdate.supportsHolding = YES;
    callUpdate.supportsGrouping = YES;
    callUpdate.supportsUngrouping = YES;
    
    if ([jsonData valueForKey:@"stcalltype"] != nil) {
               
         //TODO: Remove the || condition once the changes of stcalltype is changed from the Server
         //TODO: Get the changes of stcalltype done in the server after verifying the proto.
         if ([[jsonData valueForKey:@"stcalltype"] intValue] == 1 || [[jsonData valueForKey:@"stcalltype"] intValue] == 4) {
            callUpdate.hasVideo = NO;
             self.isIncomingCallAVideoCall = NO;
           }else{
               callUpdate.hasVideo = YES;
               self.isIncomingCallAVideoCall = YES;
           }
    }else{
        callUpdate.hasVideo = NO;
        self.isIncomingCallAVideoCall = NO;
    }
    
    [self.callKitProvider reportNewIncomingCallWithUUID:uuid update:callUpdate completion:^(NSError *error) {
        if (!error) {
            NSLog(@"Incoming Push call successfully reported.");
        }
        else {
            NSLog(@"Failed to report incoming call successfully: %@.", [error localizedDescription]);
        }
    }];
}

-(void) handleMuteNotification:(NSNotification*)notification {
	
	BOOL muted = [notification.userInfo[@"MuteStatus"] boolValue];
	NSString* callID = [notification.userInfo[kARCallID] uppercaseString];
	
	NSUUID *uuid = [[NSUUID alloc] initWithUUIDString:callID];
	
	[self performMuteCallActionWithUUID:uuid muted:muted];
}

-(void) handleMissedCallNotification:(NSNotification*)notification {
	
    NSLog(@"CallManager : handleMissedCallNotification %@", notification);
    
    CSContact* contact = notification.userInfo[@"RemoteContact"];
    NSString* remoteNumber = notification.userInfo[kARRemoteNumber];
    NSString* callID = notification.userInfo[kARCallID];
    
    CSCallState callState = [notification.userInfo[kARCallState] integerValue];
    if (callState == CSCallStateIncomingCall) {
        
        if (callID != nil) {
            NSLog(@"**AppLog** Performing CallEnd for MissedCall Scenario");
            [self performEndCallActionWithUUID:[[NSUUID alloc] initWithUUIDString:callID]];
            
            [self.calls removeObjectForKey:callID];
        }
    }
    
    NSString *notificationBody;
    
    NSString* callEndReason = notification.userInfo[kARCallEndReason];
    
    if ([callEndReason isEqualToString:@"Answered Else Where"]) {
        
        notificationBody = @"Answered Call on Some Other Device";
        
    }else{
        notificationBody = @"Missed Call";
    }
    
    UIApplicationState state = [[UIApplication sharedApplication] applicationState];
    if (state == UIApplicationStateBackground || state == UIApplicationStateInactive) {
        
        UNMutableNotificationContent *notifContent = [[UNMutableNotificationContent alloc] init];
        
        if(contact != nil)
            notifContent.title = contact.name;
        else
            notifContent.title = remoteNumber;
        
        notifContent.body = notificationBody;
        
        notifContent.sound = [UNNotificationSound defaultSound];
        
        UNNotificationRequest *request = [UNNotificationRequest requestWithIdentifier:callID
                                                                              content:notifContent
                                                                              trigger:nil];
        
        UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
        
        [center addNotificationRequest:request withCompletionHandler:^(NSError * _Nullable error) {
            if (!error) {
                NSLog(@"Missed Call Local User Notification Succeeded");
            }
            else {
                NSLog(@"Missed Call Notification failed");
            }
        }];
    }
}

-(void) showCallView {
    
    CSCall* callSession = [[self.calls allValues] firstObject];
    self.needCallScreenDisplay = NO;
    
    CSCallType callType = [callSession getCallType];
    
    UIViewController* topViewController = [self topViewController];
    
    if([topViewController isKindOfClass:[VideoCallViewController class]] ||
       [topViewController isKindOfClass:[CallViewController class]])
        return;
    
    if(callType == CSCallTypeVideoCall) {
        
        VideoCallViewController* callViewController = (VideoCallViewController*)[topViewController.storyboard instantiateViewControllerWithIdentifier:@"VideoCallViewController"];
        
        CSContact* contact = [callSession getRemoteContact];
        if(contact != nil) {
            callViewController.recordID = contact.recordID;
        }
        
        callViewController.remoteNumber = [callSession getRemoteNumber];
        callViewController.outgoingCall = FALSE;
        callViewController.callSession = callSession;
        
        [topViewController presentViewController:callViewController animated:YES completion:nil];
    }
    else {
        dispatch_async(dispatch_get_main_queue(), ^{
            
            CallViewController* callViewController = [[UIStoryboard storyboardWithName:@"Main" bundle:nil] instantiateViewControllerWithIdentifier:@"CallViewController"];
            CSContact* contact = [callSession getRemoteContact];
            if(contact != nil) {
                callViewController.recordID = contact.recordID;
            }
            
            callViewController.remoteNumber = [callSession getRemoteNumber];
            callViewController.outgoingCall = FALSE;
            callViewController.callSession = callSession;
            
            [topViewController presentViewController:callViewController animated:YES completion:nil];
            
            
        });
        
        
        
        
    }
}

-(void) showCallViewFromBackground:(BOOL)isCallAnsweredFromBackground withCallSession:(CSCall *)callObject{
        
    CSClientState clientState = [[CSClient sharedInstance] getClientState];
    
    NSLog(@"\n");
    NSLog(@"**AppLog** ClientState is %ld",clientState);
    NSLog(@"\n");
    
    CSCall* callSession = callObject;
    self.needCallScreenDisplay = NO;

    CSCallType callType = [callSession getCallType];
    
    NSLog(@"\n");
    NSLog(@"**AppLog** ShowCallViewFromBackground Call Type: %ld %@", [callSession getCallType], callSession);
    NSLog(@"\n");
    
    UIViewController* topViewController = [self topViewController];
    if (topViewController == nil) {
        AppDelegate *appDelegate = (AppDelegate *) [[UIApplication sharedApplication] delegate];
        UIStoryboard *story=[UIStoryboard storyboardWithName:@"Main" bundle:nil];
        UITabBarController *tabbarController = [story instantiateViewControllerWithIdentifier:@"TabBarController"];
        
        [tabbarController setSelectedIndex:0];
        appDelegate.window.rootViewController = tabbarController;
        [appDelegate.window makeKeyAndVisible];
        
    }
    /*This is a case where there is an Audio Call going on and there is a request from a different user for a Video Call*/
    if ([topViewController isKindOfClass:[CallViewController class]] && self.isIncomingCallAVideoCall){
        NSLog(@"%@", [topViewController presentingViewController]);
        
        [topViewController dismissViewControllerAnimated:YES completion:^{
            
            double delayInSeconds = 0.5;
            
            dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
            
            dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
               
                [self displayVideoCallViewControllerWithCallSession:callSession
                                             usingTopViewController:topViewController];
            });
        }];
    }
    /*This is a case where there is an Video Call going on and there is a request from a different user for a Audio Call*/
    else if (([topViewController isKindOfClass:[VideoCallViewController class]] && !self.isIncomingCallAVideoCall)){
        
        NSLog(@"%@", [topViewController presentingViewController]);
        
        [topViewController dismissViewControllerAnimated:YES completion:^{
            
            [self displayAudioCallViewControllerWithCallSession:callSession
                                    usingTopViewController:topViewController];
        }];
    }

    /*This condition is to check if there is an existing CallViewController or VideoCallViewController. If there is an existing Call going on, Update the delegate and the Remote Number for the Call*/
    else if([topViewController isKindOfClass:[VideoCallViewController class]] ||
             [topViewController isKindOfClass:[CallViewController class]]){
        
        if(callType == CSCallTypeVideoCall) {
            
            NSLog(@"**AppLog** Updating the existing Video Calls");
            
            VideoCallViewController* videoCallViewController = (VideoCallViewController *)topViewController;
            videoCallViewController.callSession = callSession;
            videoCallViewController.callSession.delegate = videoCallViewController;
            CSContact* contact = [callSession getRemoteContact];
            if(contact != nil) {
                videoCallViewController.recordID = contact.recordID;
            }
            
            [[NSNotificationCenter defaultCenter] postNotificationName:@"AnswerVideoCall" object:callObject];
        }
        else{
            
            NSLog(@"**AppLog** Updating the existing Audio Calls");
            
            CallViewController* callViewController = (CallViewController *)topViewController;
            callViewController.callSession = callSession;
            callViewController.callSession.delegate = callViewController;
            CSContact* contact = [callSession getRemoteContact];
            if(contact != nil) {
                callViewController.recordID = contact.recordID;
            }
            
            [[NSNotificationCenter defaultCenter] postNotificationName:@"AnswerAudioCall" object:callObject];
        }
//        return;
    }
    else{
        /*Show VideoCallViewController or CallViewController for an answered Incoming Call. This is for a single Call scenario*/
        if(callType == CSCallTypeVideoCall) {
            
            NSLog(@"**AppLog** Presenting Video CallViewController");
            VideoCallViewController* videoCallViewController = [[UIStoryboard storyboardWithName:@"Main" bundle:nil] instantiateViewControllerWithIdentifier:@"VideoCallViewController"];
            
            CSContact* contact = [callSession getRemoteContact];
            if(contact != nil) {
                videoCallViewController.recordID = contact.recordID;
            }
            
            videoCallViewController.remoteNumber = [callSession getRemoteNumber];
            videoCallViewController.outgoingCall = FALSE;
            videoCallViewController.callSession = callSession;
            videoCallViewController.isCallAnsweredFromBackground = isCallAnsweredFromBackground;
            videoCallViewController.answerVideoCallForAnIncomingCallForMultiCalls = false;
            
            [topViewController presentViewController:videoCallViewController animated:YES completion:nil];
        }
        else {
            dispatch_async(dispatch_get_main_queue(), ^{
                
                NSLog(@"**AppLog** Presenting Audio CallViewController");
                CallViewController* callViewController = [[UIStoryboard storyboardWithName:@"Main" bundle:nil] instantiateViewControllerWithIdentifier:@"CallViewController"];
                
                CSContact* contact = [callSession getRemoteContact];
                
                if(contact != nil) {
                    callViewController.recordID = contact.recordID;
                }
                
                callViewController.remoteNumber = [callSession getRemoteNumber];
                callViewController.outgoingCall = FALSE;
                callViewController.callSession = callSession;
                
                [topViewController presentViewController:callViewController animated:YES completion:nil];
            });
        }
    }
}

-(void) stopRingtone {
	
	if([self.audioPlayer isPlaying])
		[self.audioPlayer stop];
	self.audioPlayer=nil;
}

-(void) ringtoneTimeout:(NSTimer*)timer {
	[self stopRingtone];
	
	if(self.ringtoneTimer != nil) {
		[self.ringtoneTimer invalidate];
		self.ringtoneTimer = nil;
	}
}


- (UIViewController*)topViewController {
	return [self topViewControllerWithRootViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
}

- (UIViewController*)topViewControllerWithRootViewController:(UIViewController*)viewController {
	if ([viewController isKindOfClass:[UITabBarController class]]) {
		UITabBarController* tabBarController = (UITabBarController*)viewController;
		return [self topViewControllerWithRootViewController:tabBarController.selectedViewController];
	} else if ([viewController isKindOfClass:[UINavigationController class]]) {
		UINavigationController* navContObj = (UINavigationController*)viewController;
		return [self topViewControllerWithRootViewController:navContObj.visibleViewController];
	} else if (viewController.presentedViewController && !viewController.presentedViewController.isBeingDismissed) {
		UIViewController* presentedViewController = viewController.presentedViewController;
		return [self topViewControllerWithRootViewController:presentedViewController];
	}
	else {
		for (UIView *view in [viewController.view subviews])
		{
			id subViewController = [view nextResponder];
			if ( subViewController && [subViewController isKindOfClass:[UIViewController class]])
			{
				if ([(UIViewController *)subViewController presentedViewController]  && ![subViewController presentedViewController].isBeingDismissed) {
					return [self topViewControllerWithRootViewController:[(UIViewController *)subViewController presentedViewController]];
				}
			}
		}
		return viewController;
	}
}

#pragma mark utils

-(void)checkForMicrophonePermissionWithCompletionHandler:(void (^)(BOOL success))completionHandler {
	
	// Check for microphone permissions
	switch ([[AVAudioSession sharedInstance] recordPermission]) {
		case AVAudioSessionRecordPermissionGranted: {
			// Success
			completionHandler(TRUE);
		}
			break;
			
		case AVAudioSessionRecordPermissionDenied: {
			// Failure
			completionHandler(FALSE);
		}
			break;
			
		case AVAudioSessionRecordPermissionUndetermined: {
			// prompt for permission
			[[AVAudioSession sharedInstance] requestRecordPermission:^(BOOL granted) {
				if(granted) {
					// Success
					completionHandler(TRUE);
				}
				else {
					// Failure
					completionHandler(FALSE);
				}
			}];
		}
			break;
			
		default:
			break;
	}
}

-(void)checkForCameraPermissionWithCompletionHandler:(void (^)(BOOL success))completionHandler {
	
	// Check for camera permissions
	NSString *mediaType = AVMediaTypeVideo;
	
	AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:mediaType];
	if(authStatus == AVAuthorizationStatusAuthorized) {
		completionHandler(TRUE);
	} else if(authStatus == AVAuthorizationStatusDenied){
		completionHandler(FALSE);
	} else if(authStatus == AVAuthorizationStatusRestricted){
		completionHandler(FALSE);
	} else if(authStatus == AVAuthorizationStatusNotDetermined){
		// not determined?!
		[AVCaptureDevice requestAccessForMediaType:mediaType completionHandler:^(BOOL granted) {
			if(granted){
				completionHandler(TRUE);
			} else {
				completionHandler(FALSE);
			}
		}];
	} else {
		completionHandler(FALSE);
	}
}

//! TODO : Move all permission checks to a seperate file

-(void)checkForPhotosPermissionWithCompletionHandler:(void (^)(BOOL success))completionHandler {
	
	// Check for photos permission
	PHAuthorizationStatus status = [PHPhotoLibrary authorizationStatus];
	
	if (status == PHAuthorizationStatusAuthorized) {
		completionHandler(TRUE);
	}
	else if (status == PHAuthorizationStatusDenied) {
		completionHandler(FALSE);
	}
	else if (status == PHAuthorizationStatusRestricted) {
		completionHandler(FALSE);
	}
	else if (status == PHAuthorizationStatusNotDetermined) {
		
		// Access has not been determined.
		[PHPhotoLibrary requestAuthorization:^(PHAuthorizationStatus status) {
			
			if (status == PHAuthorizationStatusAuthorized) {
				completionHandler(TRUE);
			}
			else {
				completionHandler(FALSE);
			}
		}];
	}
	else {
		completionHandler(FALSE);
	}
}

#pragma mark utils

-(NSString *)fetchDisplayContactNameFromCallSession:(CSCall *)callSession{
    
    NSString *contactName;
    
    self.sdkContact = [[CSContactStore sharedInstance] lookupContactsByNumber:[callSession getRemoteNumber]];
    
    NSArray *keys = @[CNContactFamilyNameKey, CNContactMiddleNameKey, CNContactGivenNameKey, CNContactNamePrefixKey, CNContactNameSuffixKey, CNContactOrganizationNameKey, CNContactNicknameKey, CNContactTypeKey, CNContactPhoneNumbersKey, CNContactThumbnailImageDataKey];
    
    CNContactStore* store = [[CNContactStore alloc] init];
    
    NSError* error;
    CNContact* contact = [store unifiedContactWithIdentifier:self.recordID
                                                 keysToFetch:keys
                                                       error:&error];
    
    CSNumber* phoneNumber = [self.sdkContact.numbers objectAtIndex:0];
    
    for(int i = 0; i < self.sdkContact.numbers.count; i++) {
        CSNumber* number = [self.sdkContact.numbers objectAtIndex:i];
        if(number.contactStatus == CSContactAppStatusUser) {
            phoneNumber = number;
            break;
        }
    }
    
    if(contact) {
            // get name
        NSString* name = [CNContactFormatter stringFromContact:contact                                                                                 style:CNContactFormatterStyleFullName];
        
        NSLog(@"**AppLog** Name of the contact is %@",name);
        
        if(name != nil)
            contactName = name;
        else {
            if(self.sdkContact != nil) {
                
                if(phoneNumber.profileName != nil &&
                   phoneNumber.profileName.length > 0) {
                    contactName = phoneNumber.profileName;
                }
                else {
                    contactName = [callSession getRemoteNumber];
                }
            }
            else {
                contactName = [callSession getRemoteNumber];
            }
        }
    }
    else {
        if(self.sdkContact != nil) {
            CSNumber* phoneNumber = [self.sdkContact.numbers objectAtIndex:0];
            if(phoneNumber.profileName != nil &&
               phoneNumber.profileName.length > 0) {
                contactName = phoneNumber.profileName;
            }
            else {
                contactName = [callSession getRemoteNumber];
            }
        }
        else {
            contactName = [callSession getRemoteNumber];
        }
    }
    
    return  contactName;
}


-(void)displayVideoCallViewControllerWithCallSession:(CSCall *)callSession usingTopViewController:(UIViewController *)topViewController{
    NSLog(@"\n");
    NSLog(@"**AppLog** Posting ShowVideoCallScreen Notification");
    NSLog(@"\n");
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"ShowVideoCallScreen" object:callSession];
}

-(void)displayAudioCallViewControllerWithCallSession:(CSCall *)callSession usingTopViewController:(UIViewController *)topViewController{
    NSLog(@"\n");
    NSLog(@"**AppLog** Posting ShowAudioCallScreen Notification");
    NSLog(@"\n");
    [[NSNotificationCenter defaultCenter] postNotificationName:@"ShowAudioCallScreen" object:callSession];
}


-(BOOL)isCallFromPush{
    return [[NSUserDefaults standardUserDefaults] boolForKey:@"setCallFrom"];
}

-(void)setCallFrom:(BOOL)value{
    [[NSUserDefaults standardUserDefaults] setBool:value  forKey:@"setCallFrom"];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

@end
