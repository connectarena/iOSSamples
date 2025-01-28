//
//  CSClient.h
//  VoxSDK
//
//  Created by Kiran Vangara on 29/03/15.
//  Copyright © 2015-2018, Connect Arena Private Limited. All rights reserved.
//
//
//  The information contained herein is confidential, proprietary
//  to Connect Arena Private Limited., and considered a trade secret as
//  defined in section 499C of the penal code of the State of
//  California. Use of this information by anyone other than
//  authorized employees of "Connect Arena" is granted only
//  under a written non-disclosure agreement, expressly
//  prescribing the scope and manner of such use.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//   /// Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//   /// Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//   /// Neither the name of Connect Arena Private Limited. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#import <Foundation/Foundation.h>
#import "CSConstants.h"

/// Different states of Client State machine
typedef NS_ENUM(NSInteger, CSClientState) {
	/// Default Client State - 0
    CSClientStateNone,
    
    /// Client is initialized - 1
    CSClientStateInit,
    
    /// Client is connected to server - 2
    CSClientStateReady,
    
    /// Progress state for login - 3
    CSClientStateConnecting,
    
    /// Login to server successful - 4
    CSClientStateActive,
    
    /// Login to server with out SIP Support - 5
    CSClientStateActiveWithoutSIP,
    /// Login to server with SIP Support - 6
    CSClientStateActiveWithSIP,		
    /// Progress state for logout
    CSClientStateDisconnecting,
    /// Inactive due to no network
    CSClientStateInactive
};

FOUNDATION_EXPORT NSString *const CSClientErrorDomain;

typedef NS_ENUM(NSInteger, CSClientErrorType) {
	CSClientErrorUnknown,
	CSClientError,
};

typedef NS_ENUM(NSInteger, CSClientStatusPrivacy) {
    ///
    All_APPCONTACTS = 0,
    ///
    EXCEPTEDCONTACTS = 1,
    ///
    SELECTEDCONTACTS = 2,
};


/// `CSClient` is the starting point for usage of VoxSDK.
/// This is a Singleton Class. Use shared instance of `CSClient` 
/// to manage User account, Login, manage profile & get client status 
@interface CSClient : NSObject

#pragma mark - Instance Methods

- (instancetype)init NS_UNAVAILABLE;

/// Get shared instance of `CSClient`
///
/// @return `CSClient` Object
///
+(CSClient*) sharedInstance;

#pragma mark - Setup/Teardown SDK

/// Initializes SDK and all dependent components
/// 
/// @return Error Code
/// 
-(CSErrorCode) initialize;

/// De-Initialize SDK
/// 
/// @return Error Code
/// 
-(CSErrorCode) deinitialize;

/// Get Client State
/// 
/// @return State of Client
/// 
-(CSClientState) getClientState;

-(CSClientStatusPrivacy)getStatusPrivacySettings;

#pragma mark - Account Management

/// Use this interface to signup for new user account
/// 
/// @warning `CSClient` must be in `CSClientStateReady` State
///
/// @param loginID Login ID of new user. Must be unique across the App
/// 
/// @param password Password for user. Password complexity is application defined
/// 
/// @return Possible error code returned
///
///		+ `CSErrorCodeClientNotReady`
/// 
/// 	@note Response will be notified by <code>CSClientSignupNotification</code>
///
/// <pre>
/// Usage:
/// 
/// CSClient* client = [CSClient sharedInstance];
/// [client signupAccountWithID:@"userID" andPassword:@"password"];
///
/// </pre>
/// 
/// @see <code>-activate:withOTP:</code>
/// 
-(CSErrorCode) signUpWithLoginID:(NSString*)loginID
					 andPassword:(NSString*)password
			   completionHandler:(void (^)(NSDictionary *response, NSError *error))completionHandler;

-(CSErrorCode) resendActivationCodeForLoginID:(NSString*)loginID
								  byVoiceCall:(BOOL)byVoiceCall
			   completionHandler:(void (^)(NSDictionary *response, NSError *error))completionHandler;

/// Activate user account using OTP
/// 
/// @warning `CSClient` must be in `CSClientStateReady` State
///
/// @param loginID Login ID of User
/// 
/// @param OTP OTP sent to mobile or any other means
/// 
/// @return Possible error code returned
///
///		+ `CSErrorCodeClientNotReady`
/// 
/// 	Response will be notified by <code>CSClientActivationNotification</code>
/// 
/// <pre>
/// Usage:
/// 
/// CSClient* client = [CSClient sharedInstance];
/// [client activate:@"userID" withOTP:@"OTP"];
///
/// </pre>
/// 
/// @see <code>-signupAccountWithID:andPassword:</code>
/// 
-(CSErrorCode) activate:(NSString*)loginID
				withOTP:(NSString*)OTP
	  completionHandler:(void (^)(NSDictionary *response, NSError *error))completionHandler;

/// Delete user account. User must be logged in to delete account.
/// 
/// @warning `CSClient` must be in `CSClientStateActive` State.
/// 
/// @return Possible Error Code(s) returned
///
///		+ `CSErrorCodeClientNotActive`
/// 
-(CSErrorCode) deleteAccount;

#pragma mark - Login/Logout

/// Login user
/// 
/// @warning `CSClient` must be in `CSClientStateReady` State
/// 
/// @param loginID Login ID of User
/// 
/// @param password password
/// 
/// @return Possible Error Code(s) returned
///
///		+ `CSErrorCodeClientNotReady`
/// 
/// 	Response will be notified by <code>CSClientAppStateNotification</code>
/// 
-(CSErrorCode) login:(NSString*)loginID
		withPassword:(NSString*)password
   completionHandler:(void (^)(NSDictionary *response, NSError *error))completionHandler;

///
///Method to change Client state
///
///
-(BOOL) changeClientState:(CSClientState)newState
               reasonCode:(CSReasonCodes)reasonCode
                   reason:(NSString*)reason;
///
///Method to generate Device ID from LoginID and Voip Device Token
///
///
-(NSString *)generateDeviceIDFromLoginID:(NSString *)loginID;

/// Logout user
/// 
/// @warning `CSClient` must be in `CSClientStateActive` State.
/// 
/// @return Possible error code returned
///
///		+ `CSErrorCodeClientNotActive`
/// 
/// 	Response will be notified by <code>CSClientAppStateNotification</code>
/// 
-(CSErrorCode) logoutWithCompletionHandler:(void (^)(NSDictionary *response, NSError *error)) completionHandler;

#pragma mark - Manage Profile

/// Set profile details of user. 
/// 
/// @warning `CSClient` must be in `CSClientStateActive` State
/// 
/// @param displayName Display name of user
/// 
/// @param statusMessage Status Message
/// 
/// @param profilePhoto Image data of profile photo
/// 
/// @return Possible error code returned
///
///		+ `CSErrorCodeClientNotActive`
///
-(CSErrorCode) setProfile:(NSString*)displayName
			statusMessage:(NSString*)statusMessage
			 profilePhoto:(NSData*)profilePhoto
			  contentType:(NSString*)contentType
			  removePhoto:(BOOL)removePhoto
		completionHandler:(void (^)(NSDictionary *response, NSError *error))completionHandler;

/// Update password of user.
///
/// @warning `CSClient` must be in `CSClientStateActive` State
///
/// @param password password of user
///
/// @param completionHandler completion handler
///
-(void) updatePassword:(NSString*)password
	 completionHandler:(void (^)(NSDictionary *response, NSError *error))completionHandler;


-(void) syncHistoryFromServerWithCompletionHandler:(void (^)(NSDictionary *response, NSError *error))completionHandler;

    
///Delete User from the Device
///
///@param deviceID deviceID to be deleted
///
///@param completionHandler completion handler
///

-(CSErrorCode) deleteUserFromDevice:(NSString *)deviceID
                  completionHandler:(void (^)(NSDictionary *response, NSError *error))completionHandler;

-(void)fetchSelfProfileDetails;

-(void) cancelSyncHistoryFromServer;

#pragma mark - Push Notifications

/// Process push notification
///
/// @param payload payload received from push notification
/// 
/// @return error code
/// 
///

//-(CSErrorCode) mute:()

-(CSErrorCode) processPushNotification:(NSDictionary*)payload;

#pragma mark - Utilities

/// Get full path of log files. SDK maintains a maximum of 7 most recent logs.
/// 
/// @return Array of log file path(s) or nil
/// 
-(NSArray*) getLogFilePaths;

/// Get SDK Version
/// 
/// @return Version Number
/// 
-(NSString*) getVersionString;


//For Mute all notification for both calls and chat notification (implemented for CCPhone):
-(void)muteNotifications:(BOOL)muteOption forType:(enum CSMuteAction)muteAction;

//To fetch blocked contact list from server
-(void)requestForBlockedContactsListFromServer;

//To fetch blocked groups list from server
-(void)requestForBlockedGroupListFromServer;





@end
