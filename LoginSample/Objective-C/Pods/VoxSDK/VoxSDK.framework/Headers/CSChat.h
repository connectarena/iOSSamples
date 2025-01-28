//
//  CSChat.h
//  VoxSDK
//
//  Created by Kiran Vangara on 29/03/15.
//  Copyright © 2015-2017, Connect Arena Private Limited. All rights reserved.
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
#import "CSContact.h"
#import "CSConstants.h"
#import "CSHistory.h"

@class CSChat;

/**
 * Delegate for chat events
 */
@protocol  CSChatDelegate <NSObject>

/**
 * Received message
 */
-(void) chat:(CSChat*)chat didReceiveMessage:(CSHistory*)record;

/**
 * Received photo
 */
-(void) chat:(CSChat*)chat didReceivePhoto:(NSString*)photoUrl;

/**
 * Received Video
 */
-(void) chat:(CSChat*)chat didReceiveVideo:(NSString*)videoUrl;

/**
 * Received Location
 */
-(void) chat:(CSChat*)chat didReceiveLocation:(NSString*)message;

/**
 * Received Contact
 */
-(void) chat:(CSChat*)chat didReceiveContact:(CSContact*)contact;

/**
 * Received Delivery Status
 */
-(void) chat:(CSChat*)chat didReceiveDeliveryStatus:(int)status;

-(void) chat:(CSChat*)chat downloadCompleted:(NSString*)messageID;

-(void) chatRemoteEndIsTyping:(CSChat*)chat;

/**
 * Presence status updated
 */
-(void) chat:(CSChat*)chat
  didUpdatePresence:(int)status
		  timestamp:(NSDate*)timestamp;

@end

/// `CSChat` holds chat context and interface to Chat
@interface CSChat : NSObject
 
#pragma mark - Properties

/// Chat mode 0 - Group Chat 1 - 1-1 Chat
@property (nonatomic) NSInteger chatMode;
@property (nonatomic) NSInteger groupType;

/// Delegate for chat events.<br>
/// An object conforming to `CSChatDelegate` protocol.
@property (weak, nonatomic) id<CSChatDelegate> delegate;

#pragma mark - Initialisers

/**
 * Unavailable
 */
-(instancetype) __unavailable init; 

/// Start a new chat with number
///
/// @warning `CSClient` must be in `CSClientStateActive` State
///
/// @param remoteNumber number to chat
///
/// @return Possible error codes returned
///
///		+ `CSErrorCodeInvalidParameter`
///		+ `CSErrorCodeClientNotActive`
///		+ `CSErrorCodeNoNetwork`
///
/// <pre>
/// Usage:
///
///
/// </pre>
///
/// @see <code>CSChatDelegate</code>
///
-(instancetype) initForNumber:(NSString*)remoteNumber
				 withDelegate:(id)delegate;

-(instancetype) initForGroup:(NSString*)groupID
				withDelegate:(id)delegate;

-(void) sendResponse:(NSString*)messageID transactionID:(NSNumber*)transactionID;

-(void) sendStatus:(NSString*)messageID status:(int)status timestamp:(NSDate*)timestamp;

#pragma mark - Send Methods

/// Send chat message
///
/// @warning `CSClient` must be in `CSClientStateActive` State
///
/// @param message message to send
///
/// @return Possible error codes returned
///
/// <pre>
/// Usage:
///
///
/// </pre>
///
/// @see <code>CSChatDelegate</code>
///

-(NSString*) sendMessage:(NSString*)message;

-(NSString*) sendMessage:(NSString*)message
        groupStatusType:(NSInteger)grptype;

-(NSString*) sendMessage:(NSString*)message oldChatID:(NSString*)oldChatID isEditedMessage:(BOOL)isEditedMessage isReplyMessage:(BOOL)isReplyMessage isForwardedMessage:(BOOL)isForwardedMessage;

-(NSString*) sendMessage:(NSString*)message oldChatID:(NSString*)oldChatID isEditedMessage:(BOOL)isEditedMessage isReplyMessage:(BOOL)isReplyMessage isForwardedMessage:(BOOL)isForwardedMessage groupStatusType:(NSInteger)grptype;


/// Send photo
///
/// @warning `CSClient` must be in `CSClientStateActive` State
///
/// @param data image data of Photo
///
/// @return Possible error codes returned
///
/// <pre>
/// Usage:
///
///
/// </pre>
///
/// @see <code>CSChatDelegate</code>
///

-(NSString*) sendPhoto:(NSData*)data
              fileName:(NSString*)fileName
           contentType:(NSString*)contentType
            fromCamera:(BOOL)fromCamera;

-(NSString*) sendPhoto:(NSData*)data
			  fileName:(NSString*)fileName
		   contentType:(NSString*)contentType
	   		fromCamera:(BOOL)fromCamera groupStatusType:(NSInteger)grptype;

-(NSString*) sendPhoto:(NSData*)data
             fileName:(NSString*)fileName
             contentType:(NSString*)contentType
             fromCamera:(BOOL)fromCamera
             oldChatID:(NSString*)oldChatID
             isReplyMessage:(BOOL)isReplyMessage
             isForwardedMessage:(BOOL)isForwardedMessage
             withCaptionMessage:(NSString*)caption
    captionContentType:(NSString*)captionContentType;

-(NSString*) sendPhoto:(NSData*)data
             fileName:(NSString*)fileName
             contentType:(NSString*)contentType
             fromCamera:(BOOL)fromCamera
             oldChatID:(NSString*)oldChatID
             isReplyMessage:(BOOL)isReplyMessage
             isForwardedMessage:(BOOL)isForwardedMessage
             withCaptionMessage:(NSString*)caption
             captionContentType:(NSString*)captionContentType groupStatusType:(NSInteger)grptype;

-(NSString*) sendPhoto:(NSURL*)fileUrl
              fileName:(NSString*)fileName
            fromCamera:(BOOL)fromCamera;

-(NSString*) sendPhoto:(NSURL*)fileUrl
			  fileName:(NSString*)fileName
			fromCamera:(BOOL)fromCamera groupStatusType:(NSInteger)grptype;

-(NSString*) sendPhotofromURL:(NSURL*)fileUrl
              fileName:(NSString*)fileName
           contentType:(NSString*)contentType
            fromCamera:(BOOL)fromCamera
             oldChatID:(NSString*)oldChatID
             isReplyMessage:(BOOL)isReplyMessage
             isForwardedMessage:(BOOL)isForwardedMessage
             withCaptionMessage:(NSString*)caption
           captionContentType:(NSString*)captionContentType;

-(NSString*) sendPhotofromURL:(NSURL*)fileUrl
              fileName:(NSString*)fileName
           contentType:(NSString*)contentType
            fromCamera:(BOOL)fromCamera
             oldChatID:(NSString*)oldChatID
             isReplyMessage:(BOOL)isReplyMessage
             isForwardedMessage:(BOOL)isForwardedMessage
             withCaptionMessage:(NSString*)caption
    captionContentType:(NSString*)captionContentType groupStatusType:(NSInteger)grptype;

/// Send video
///
/// @warning `CSClient` must be in `CSClientStateActive` State
///
/// @param url file path of video to send
///
/// @return Possible error codes returned
///
/// <pre>
/// Usage:
///
///
/// </pre>
///
/// @see <code>CSChatDelegate</code>
///

-(NSString*) sendVideo:(NSURL*)url
             fromCamera:(BOOL)fromCamera
              fileName:(NSString*)fileName;

-(NSString*) sendVideo:(NSURL*)url
             fromCamera:(BOOL)fromCamera
             fileName:(NSString*)fileName groupStatusType:(NSInteger)grptype;

-(NSString*) sendVideo:(NSURL*)url
             fromCamera:(BOOL)fromCamera
             fileName:(NSString*)fileName
             oldChatID:(NSString*)oldChatID
             isReplyMessage:(BOOL)isReplyMessage
             isForwardedMessage:(BOOL)isForwardedMessage
             withCaptionMessage:(NSString*)caption
    captionContentType:(NSString*)captionContentType;

-(NSString*) sendVideo:(NSURL*)url
             fromCamera:(BOOL)fromCamera
             fileName:(NSString*)fileName
             oldChatID:(NSString*)oldChatID
             isReplyMessage:(BOOL)isReplyMessage
             isForwardedMessage:(BOOL)isForwardedMessage
             withCaptionMessage:(NSString*)caption
             captionContentType:(NSString*)captionContentType groupStatusType:(NSInteger)grptype;

/// Send audio
///
/// @warning `CSClient` must be in `CSClientStateActive` State
///
/// @param url file path of audio to send
///
/// @return Possible error codes returned
///
/// <pre>
/// Usage:
///
///
/// </pre>
///
/// @see <code>CSChatDelegate</code>
///

-(NSString*) sendAudio:(NSURL*)fileurl fileName:(NSString*)fileName;

-(NSString*) sendAudio:(NSURL*)fileurl fileName:(NSString*)fileName groupStatusType:(NSInteger)grptype;

-(NSString*) sendAudio:(NSURL*)fileurl
             fileName:(NSString*)fileName
             oldChatID:(NSString*)oldChatID
             isReplyMessage:(BOOL)isReplyMessage
             isForwardedMessage:(BOOL)isForwardedMessage
             withCaptionMessage:(NSString*)caption
    captionContentType:(NSString*)captionContentType;

-(NSString*) sendAudio:(NSURL*)fileurl
             fileName:(NSString*)fileName
             oldChatID:(NSString*)oldChatID
             isReplyMessage:(BOOL)isReplyMessage
             isForwardedMessage:(BOOL)isForwardedMessage
             withCaptionMessage:(NSString*)caption
             captionContentType:(NSString*)captionContentType groupStatusType:(NSInteger)grptype;

-(NSString*) sendFile:(NSURL*)fileUrl fileName:(NSString*)fileName;

-(NSString*) sendFile:(NSURL*)fileUrl
             fileName:(NSString*)fileName
            oldChatID:(NSString*)oldChatID
            isReplyMessage:(BOOL)isReplyMessage
            isForwardedMessage:(BOOL)isForwardedMessage
            withCaptionMessage:(NSString*)caption
   captionContentType:(NSString*)captionContentType;

-(NSString*) sendFile:(NSURL*)fileUrl
             fileName:(NSString*)fileName
            oldChatID:(NSString*)oldChatID
            isReplyMessage:(BOOL)isReplyMessage
            isForwardedMessage:(BOOL)isForwardedMessage
            withCaptionMessage:(NSString*)caption
            captionContentType:(NSString*)captionContentType groupStatusType:(NSInteger)grptype;

/// Send location
///
/// @warning `CSClient` must be in `CSClientStateActive` State
///
/// @param message description of location
///
/// @param latpos latitude
///
/// @param lonpos longitude
///
/// @return Possible error codes returned
///
/// <pre>
/// Usage:
///
///
/// </pre>
///
/// @see <code>CSChatDelegate</code>
///

-(NSString*) sendLocation:(NSString*)message
                    latpos:(double)latpos
                   lonpos:(double)lonpos;

-(NSString*) sendLocation:(NSString*)message
					latpos:(double)latpos 
					lonpos:(double)lonpos groupStatusType:(NSInteger)grptype;

-(NSString*) sendLocation:(NSString*)message
             latpos:(double)latpos
             lonpos:(double)lonpos
             oldChatID:(NSString*)oldChatID
             isReplyMessage:(BOOL)isReplyMessage
             isForwardedMessage:(BOOL)isForwardedMessage
             withCaptionMessage:(NSString*)caption
       captionContentType:(NSString*)captionContentType;

-(NSString*) sendLocation:(NSString*)message
             latpos:(double)latpos
             lonpos:(double)lonpos
             oldChatID:(NSString*)oldChatID
             isReplyMessage:(BOOL)isReplyMessage
             isForwardedMessage:(BOOL)isForwardedMessage
             withCaptionMessage:(NSString*)caption
             captionContentType:(NSString*)captionContentType groupStatusType:(NSInteger)grptype;

/// Send contact
///
/// @warning `CSClient` must be in `CSClientStateActive` State
///
/// @param contact contact to send
///
/// @return Possible error codes returned
///
/// <pre>
/// Usage:
///
///
/// </pre>
///
/// @see <code>CSChatDelegate</code>
///

-(NSString*) sendContact:(CSContact*)contact;

-(NSString*) sendContact:(CSContact*)contact groupStatusType:(NSInteger)grptype;

-(NSString*) sendContact:(CSContact*)contact
               oldChatID:(NSString*)oldChatID
               isReplyMessage:(BOOL)isReplyMessage
               isForwardedMessage:(BOOL)isForwardedMessage
               withCaptionMessage:(NSString*)caption
      captionContentType:(NSString*)captionContentType;

-(NSString*) sendContact:(CSContact*)contact
               oldChatID:(NSString*)oldChatID
               isReplyMessage:(BOOL)isReplyMessage
               isForwardedMessage:(BOOL)isForwardedMessage
               withCaptionMessage:(NSString*)caption
               captionContentType:(NSString*)captionContentType groupStatusType:(NSInteger)grptype;

/// Send delivery status of chat
///
/// @warning `CSClient` must be in `CSClientStateActive` State
///
/// @param messageID Unique Message ID
///
/// <pre>
/// Usage:
///
///
/// </pre>
///
/// @see <code>CSChatDelegate</code>
///
-(void) sendReadReceipt:(NSString*)messageID;

-(void) sendReadReceiptForMessages:(NSArray*)messageIDs;
-(void) sendTypingStatus:(BOOL)startOrStop;

/// Query presence of remote number
///
/// @warning `CSClient` must be in `CSClientStateActive` State
///
/// <pre>
/// Usage:
///
///
/// </pre>
///
/// @see <code>CSChatDelegate</code>
///
-(void) getPresenceStatus;

/// API to delete the Chat
/// @param chatID This is needed to send the Chat ID

-(void)deleteChat:(NSString *)chatID;

#pragma mark - File Transfer

-(void) suspendTransfer:(NSString*)messageID;
-(void) resumeTransfer:(NSString*)messageID;

-(void) startTransfer:(NSString*)messageID;
-(void) cancelTransfer:(NSString*)messageID;

-(NSProgress*) getProgressForMessage:(NSString*)messageID;
-(CSFTState) getFileTransferState:(NSString*)messageID;

//Delete message for all in chat
-(void)deleteChatForAllWithChatID:(NSString *)messageID isGroupChat:(BOOL)isGroupChat;

//To set disappear message in chat
-(NSString *)setDisappearSettingsOnChatWithTime:(enum CSChatDisappearTime)disappearTime;


@end
