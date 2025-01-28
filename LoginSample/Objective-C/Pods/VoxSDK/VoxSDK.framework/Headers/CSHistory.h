//
//  CSHistory.h
//  VoxSDK
//
//  Created by Kiran Vangara on 07/03/15.
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
#import "CSConstants.h"

/**
 * History entry details
 */
@interface CSHistory : NSObject

/**
 * Status of incoming / outgoing chat
 */
typedef NS_ENUM(NSInteger, CSChatStatus) {
	
	/// Outgoing Message - initial state
    CSChatStatusSending = 0, 
    /// Outgoing Message - after server Acknowledgment
    CSChatStatusSent,        
    /// Outgoing Message - delivery request / response
    CSChatStatusDelivered,   
    /// Outgoing Message - read request / response
    CSChatStatusDisplayed,   
    /// Incoming Message - Initial state after chat request
    CSChatStatusReceiving,   
    /// Incoming Message - after server ack for delivery notification
    CSChatStatusReceived,
    /// Incoming Message - after server ack for display notification
    CSChatStatusRead,
    /// Incoming Message - reply message
    CSChatStatusReply,
    /// Incoming Message - forward message
    CSChatStatusForward,
    /// Edit existing message
    CSChatStatusEdit,
    
    CSChatStatusLocalDeletePending,
    
    CSChatStatusLocalDeleted,
    
    CSChatStatusRemoteDeletePending,
    
    CSChatStatusRemoteDeleted,
};


//public static final int MESSAGE_LOCAL_DELETE_PENDING         = 10;
//    public static final int MESSAGE_LOCAL_DELETED         = 11;
//    public static final int MESSAGE_REMOTE_DELETE_PENDING         = 12;
//    public static final int MESSAGE_REMOTE_DELETED         = 13;

/**
 * Status of incoming / outgoing chat
 */
typedef NS_ENUM(NSInteger, CSSMSStatus) {
    
        /// Outgoing Message - initial state
    CSSMSStatusSending = 0,
        /// Outgoing Message - after server Acknowledgment
    CSSMSStatusSent,
        /// Outgoing Message - delivery request / response
    CSSMSStatusDelivered,
        /// Outgoing Message - read request / response
    CSSMSStatusDisplayed,
        /// Incoming Message - Initial state after chat request
    CSSMSStatusReceiving,
        /// Incoming Message - after server ack for delivery notification
    CSSMSStatusReceived,
        /// Incoming Message - after server ack for display notification
    CSSMSStatusRead,
    /// Incoming Message - reply message
    CSSMSChatStatusReply,
    /// Incoming Message - forward message
    CSSMSChatStatusForward,
    /// Edit existing message
    CSSMSStatusEdit,
};

typedef NS_ENUM(NSInteger, CSMSGSendingStatus) {
    
    /// Outgoing Message - initial state
    CSMSGStatusSending = 0,
    /// Outgoing Message - reply state
    CSMSGStatusReply,
    /// Outgoing Message - Edit state
    CSMSGStatusEdit,
    /// Outgoing Message - Forward state
    CSMSGStatusForward,
};

/** Remote Number */
@property (nonatomic, retain)   NSString*   remoteNumber;

/** User Number */
@property (nonatomic, retain)   NSString*   memberNumber;

/** type of record */
@property (nonatomic)			CSHistoryType	recordType;

//direction 0 = you, 1 = other
@property (nonatomic)			NSInteger	direction;

/** message data in case of chat */
@property (nonatomic, retain)	NSString*	data;

/** Unique ID of entry */
@property (nonatomic, retain)	NSString*	messageID;

/** status of entry */
@property (nonatomic)	        NSInteger	status;

@property (nonatomic)            NSInteger    accessStatus;


@property (nonatomic)            NSInteger    groupStatus;

/** status of entry for reply , edit and forward */
@property (nonatomic)           CSMSGSendingStatus    msgStatus;

/** Unique ID of entry */
@property (nonatomic, retain)    NSString*    oldChatID;


/** caption data in case of chat */
@property (nonatomic, retain)    NSString*    captionData;

/** caption content type   */
@property (nonatomic, retain)    NSString*     captionContentType;
/** lat pos in case of location share
 *
 *  @remark valid only in case of chat
 */
@property (nonatomic)	        double      latpos;

/** lon pos in case of location share
 *
 *  @remark valid only in case of chat
 */
@property (nonatomic)	        double      lonpos;

/** start time of event */
@property (nonatomic, retain)	NSDate*     startTime;

/** delivered time
 *
 *  @remark valid only in case of chat
 */
@property (nonatomic, retain)	NSDate*     deliveredTime;

/** end time
 *
 *  @remark valid only in case of call
 */
@property (nonatomic, retain)	NSDate*     endTime;

/**
 * File Transfer status
 */
@property (nonatomic) CSFileTransferStatus transferStatus;

@property (nonatomic, retain)	NSString*	fileName;

@property (nonatomic)			NSInteger	fileSize;

@property (nonatomic, retain)	NSString* 	localPath;

@property (nonatomic, retain)	NSString* 	contentType;

@property (nonatomic, retain)	NSString* thumbnailPath;

@property (nonatomic) CSFileTransferStatus thumbnailStatus;


@property (nonatomic, retain)    NSString* replyRemoteNumber;

@property (nonatomic, retain)    NSString* replyData;

@property (nonatomic, retain)    NSString* replyThumbnail;

@property (nonatomic)  CSHistoryType replyRecordType;

//direction 0 = you, 1 = other
@property (nonatomic)            NSInteger    replyDirection;

//star 0 = false, 1 = true (starred chat)
@property (nonatomic)            NSInteger    starChatStatus;

/** user mention message data in case of chat */
@property (nonatomic, retain)    NSString*    userMentionData;

@property (nonatomic, retain)    NSString*    mobileNumber;

@property (nonatomic, retain)    NSString*    email;

@end
