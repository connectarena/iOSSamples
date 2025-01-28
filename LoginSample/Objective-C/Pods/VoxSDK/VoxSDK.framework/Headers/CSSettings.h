//
//  CSSettings.h
//  VoxSDK
//
//  Created by Kiran Vangara on 10/04/15.
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
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Connect Arena Private Limited. nor the names of its
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

@interface CSSettings : NSObject

/*!
 
 @brief Get shared instance of CSSettings.
 
 @return CSSettings object.
 
 
 */

+ (CSSettings*)sharedInstance;

+(NSString*) getLoginId;
+(NSString*) getPassword;

+(NSString*) getFirstName;
+(NSString*) getLastName;
+(NSString*) getEmail;

+(void) setStatusPrivacy:(int)value;
+(int) getStatusPrivacy;

+(NSString*)getProfileImagePath;
+(NSString*)getDisplayName;
+(NSString*)getStatusText;

+(void) setAutoSignin :(bool)flag;
+(bool) getAutoSignin;

//+(void) setDeviceToken:(NSString*)value;
//+(NSString*) getDeviceToken;

+(void) setRemoteDeviceToken:(NSString*)value;
+(NSString*) getRemoteDeviceToken;

+(void) setVoipDeviceToken:(NSString*)value;
+(NSString*) getVoipDeviceToken;

+(void) setDeviceID:(NSString *)deviceID;
+(NSString *) getDeviceID;

+(void) enableSaveToCameraRoll:(bool)flag;
+(bool) isSaveToCameraRollEnabled;

+(void) enableAutoDownload:(bool)flag;
+(bool) isAutoDownloadEnabled;



//To get Privacy control for user presence, last seen, typing status and read receipts. Values the inter maps to the enum CSControlOptions
+(NSInteger) getPresencePrivacyControl;
+(NSInteger) getLastSeenPrivacyControl;
+(NSInteger) getTypingPrivacyControl;
+(BOOL) getReadReceiptsPrivacyControl;


//To get status of mute status for all type of notification like call and chat
+(bool)getMuteAllNotificationStatus;
 

// To set preffered codec like opus, g729...  for app to app calls
+(void) setCSPreferredCodecForAppCalls:(NSString*)value;
+(NSString*)getCSPreferredCodecForAppCalls;


// To set preffered codec like opus, g729...  for PSTN calls
+(void) setCSPreferredCodecForPSTNCalls:(NSString*)value;
+(NSString*)getCSPreferredCodecForPSTNCalls;


// To set preffered codec like opus, g729...  for video calls
+(void) setCSPreferredCodecForVideoCalls:(NSString*)value;
+(NSString*)getCSPreferredCodecForVideoCalls;

// To set Media download option with enum CSMediaDownloadOption
+(void) setMediaDownloadSettings:(NSNumber *)value;
// will get value related to enum CSMediaDownloadOption
+(NSInteger) getMediaDownloadSettings;

// TRUE Archived chat will remain archived when you receive a new message
// FALSE Archive chat will become unarchive if the receive a new message
+(void) enableArchiveChatSettings:(bool)flag;
+(bool) isArchiveChatSettingsEnabled;

// Pass the ptime value string like (80, 20, 90....)
+(void) setPreferredPTime:(NSString*)value;
+(NSString*)getPreferredPTime;

@end
