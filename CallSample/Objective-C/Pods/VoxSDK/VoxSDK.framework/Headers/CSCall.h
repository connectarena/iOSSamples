//
//  CSCall.h
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
#import <AVFoundation/AVFoundation.h>

#import "CSConstants.h"
#import "CSContact.h"

@class CSCall;

typedef NS_ENUM(NSInteger, CSBool) {
     CSFalse,
     CSTrue
};

typedef NS_ENUM(NSInteger, CSMediaType) {
     CSUnknownMediaType,
     CSMediaTypeVoice,
     CSMediaTypeVideo,
     CSMediaTypeVoiceVideo
};


typedef NS_ENUM(NSInteger, CSMuteType) {
    CSVideoType,
    CSAudioType,
    CSAudioVideo
};



/**
 Call State Constants
 */
typedef NS_ENUM(NSInteger, CSCallState) {
    /// Default Call State
    CSCallStateNew, //0
    /// Initiating Outgoing Call
    CSCallStateCalling, //1
    /// Ringing Outgoing Call
    CSCallStateRinging, //2
    /// Incoming Call
    CSCallStateIncomingCall, //3
    /// Call Connecting
    CSCallStateConnecting, //4
    /// Call Connected
    CSCallStateConnected, //5
    /// Call on Hold
    CSCallStateHold, //6
    /// Call Reconnecting
    CSCallStateReconnecting, //7
    /// Call end In-Progress
    CSCallStateEnding //8
};

/**
 Call Type Constants
 */
typedef NS_ENUM(NSInteger, CSCallType) {
    
    /// Default Call Type
    CSCallTypeNone, ///0
    /// Voice Call
    CSCallTypeVoiceCall, ///1
    /// Voice Call to PSTN
    CSCallTypeVoiceCallPSTN,///2
    /// Video Call
    CSCallTypeVideoCall,///3
    /// Live Stream
    CSCallTypeStreamOut,///4
    /// View Live Stream
    CSCallTypeStreamIn,///5
    /// Voice Call Incoming PSTN
    CSCallTypeVoiceCallIncomingPSTN///6
};

typedef NS_ENUM(NSInteger, CSVideoGravity) {
    
    CSVideoGravityAspectFit,
    CSVideoGravityAspectFill
};

/**
 Hold State Constants
 */
typedef NS_ENUM(NSInteger, CSCallHoldState) {
    /// Default Hold State
    CSCallHoldNone,
    /// Local Hold
    CSCallHoldLocal,
    /// Remote Hold
    CSCallHoldRemote,
    /// Both
    CSCallHoldBoth,
};


/**
 * Delegate for Call events
 */
@protocol  CSCallDelegate <NSObject>

/**
 * To indicate new call event
 */
//-(void) didReceiveCallEvent:(CSCall*)callObject event:(NSDictionary*) event;

/**
 * Initiated Call
 */
-(void) callDidProgress:(CSCall*)call;

-(void) callDidStartRinging:(CSCall*)call inAnotherCall:(BOOL)inAnotherCall;

/**
 * call connected
 */
-(void) callDidConnect:(CSCall*)call;

/**
 * call put on hold locally
 */
-(void) callDidHold:(CSCall*)call;

/**
 * Call put on hold by remote end
 */
-(void) callDidRemoteHold:(CSCall*)call;

/**
 * Un-holded call
 */
-(void) callDidUnhold:(CSCall*)call;

/**
 * Call un-holded by remote end
 */
-(void) callDidRemoteUnhold:(CSCall*)call;

/**
 * completed send DTMF digit
 */
-(void) callDidSentDTMF:(CSCall*)call digit:(NSString*)digit;

/**
 * Call Session ended
 */
-(void) callDidEnd:(CSCall*)callObject reason:(NSDictionary*) reason;

/**
 * Call Session ended with error
 */
-(void) callDidEndWithError:(CSCall*)call reason:(NSDictionary*) reason;

/**
 * Lost Network Connectivity while in Call
 */
-(void) callDidLostConnectivity:(CSCall*)call;

/**
 * Gained Network Connectivity while in Call
 */
-(void) callDidGainConnectivity:(CSCall*)call;

@end

/**
 `CSCallSession` holds call context and interface to manage an Audio / Video Call
 */
@interface CSCall : NSObject

#pragma mark - Properties

/** 
 Call delegate for call events
 */
@property (weak, nonatomic) id<CSCallDelegate> delegate;

#pragma mark - Setup Call

/// Start a new Call to number
///
/// @warning `CSClient` must be in `CSClientStateActive` State
///
/// @param number number to call
///
/// @param enableRecording Whether to enable call recording or not
///
/// @return Possible error codes returned
///
///		+ `CSErrorCodeInvalidParameter`
///		+ `CSErrorCodeClientNotActive`
///		+ `CSErrorCodeNotRegistered`
///		+ `CSErrorCodeNoNetwork`
///
/// <pre>
/// Usage:
///
///
/// </pre>
///
/// @see <code>CSCallSessionDelegate</code>
///
-(CSErrorCode) startCallToNumber:(NSString*)number enableRecording:(BOOL)enableRecording;

/// Start a new PSTN Call to number
///
/// @warning `CSClient` must be in `CSClientStateActiveWithSIP` State
///
/// @param number number to call
///
/// @return Possible error codes returned
///
///		+ `CSErrorCodeInvalidParameter`
///		+ `CSErrorCodeClientNotActive`
///		+ `CSErrorCodeNotRegistered`
///		+ `CSErrorCodeNoNetwork`
///
/// <pre>
/// Usage:
///
///
/// </pre>
///
/// @see <code>CSCallSessionDelegate</code>
///
-(CSErrorCode) startPSTNCallToNumber:(NSString *)number;

-(CSErrorCode) startVideoCallToNumber:(NSString*)number videoView:(UIView*)videoView;

#pragma mark - Manage Call

-(CSErrorCode) indicateRinging:(BOOL)inAnotherCall;

/// Answer Call
///
/// @return Possible error codes returned
///
/// @see <code>CSCallSessionDelegate</code>
///
-(CSErrorCode) answerCall;

-(CSErrorCode) answerVideoCall:(UIView*)videoView;

/// Put call on hold
///
/// @return Possible error codes returned
///
/// @see <code>CSCallSessionDelegate</code>
///
-(CSErrorCode) holdCall;

/// Unhold call
///
/// @return Possible error codes returned
///
/// @see <code>CSCallSessionDelegate</code>
///
-(CSErrorCode) unholdCall;

/// Send DTMF digit in call
///
/// @return Possible error codes returned
///
/// @see <code>CSCallSessionDelegate</code>
///
-(CSErrorCode) sendDTMFDigit:(NSString*)digit;

/// End call
///
/// @return Possible error codes returned
///
/// @see <code>CSCallSessionDelegate</code>
///
-(CSErrorCode) endCall:(NSString*)reason;

#pragma mark - Audio Management

/// Mute call
///
/// @return Possible error codes returned
///
/// @see <code>CSCallSessionDelegate</code>
///
-(CSErrorCode) mute:(enum CSMuteType) type;
/// Unmute call
///
/// @return Possible error codes returned
///
/// @see <code>CSCallSessionDelegate</code>
///
-(CSErrorCode) unmute:(enum CSMuteType) type;
/// Enable speaker
///
/// @return Possible error codes returned
///
/// @see <code>CSCallSessionDelegate</code>
///
-(CSErrorCode) enableSpeaker:(BOOL)status;

    /// Enable Bluetooth
    ///
    /// @return Possible error codes returned
    ///
    /// @see <code>CSCallSessionDelegate</code>
    ///
-(CSErrorCode) enableBluetooth:(BOOL)status;

#pragma mark - Get/Setters

///
///Get if an Active Call already exists
///
///
-(BOOL)isActiveCallExists;

///Check if the User On An Active Call
-(BOOL)isUserOnAnActiveCall;

/// Get current state of the call
///
/// @return Call state
///
-(CSCallState) getCallState;

-(CSCallType) getCallType;

/// Is audio on mute
///
/// @return mute status
///
-(BOOL) isMuted;

/// Is audio on speaker
///
/// @return speaker status
///
-(BOOL) isOnSpeaker;

    /// Is audio on Bluetooth
    ///
    /// @return speaker status
    ///
-(BOOL) isOnBluetooth;


-(BOOL) isActive;

-(NSString*) getCallID;

/// Callee number
///
/// @return number
///
-(NSString*) getRemoteNumber;

/// Receiver DID number
///
/// @return NSDictionary
///
-(NSDictionary*) getOtherCallInfo;

/// Callee Contact
///
/// @return contact
///
-(CSContact*) getRemoteContact;

-(NSDate*) getCallStartTime;
-(NSTimeInterval) getCallDuration;

-(CSCallHoldState) getHoldState;

+(void)audioSessionDidActivate:(AVAudioSession *)session;

+(void)audioSessionDidDeactivate:(AVAudioSession *)session;

#pragma mark - Video API

-(CSErrorCode) toggleCamera;

-(void) setVideoView:(UIView*)view;

-(void) setVideoPreviewPosition:(CSVideoPreviewPosition)position
                     withOffset:(CGPoint)offset
                       orBounds:(CGRect)bounds
                andCornerRadius:(CGFloat)cornerRadius;

-(void) setRemoteVideoViewGravity:(CSVideoGravity)gravity;

-(CSVideoGravity) getRemoteVideoViewGravity;

-(void) sendDTMFDigit:(NSString*)digit duration:(NSTimeInterval )duration interToneGap:(NSTimeInterval)interToneGap;

-(CSErrorCode) endCall:(NSInteger)statusCode reason:(NSString *)reason;

@end
