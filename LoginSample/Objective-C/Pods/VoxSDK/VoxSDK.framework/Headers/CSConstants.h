//
//  Constants.h
//  VoxSDK
//
//  Created by Kiran Vangara on 13/04/15.
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

#ifndef VoxSDK_CONSTANTS_H
#define VoxSDK_CONSTANTS_H


extern NSString*  const kARDestNumber;
extern NSString*  const kARIsRemoteNumber;
extern NSString*  const kARMuteCallId;
extern NSString*  const kARMute;
extern NSString*  const kARMuteAll;

extern NSString*  const kARMuteType;
extern NSString*  const kARMuteAction;
extern NSString*  const kARMuteExpiry;

extern NSString*  const kARPresenceControl;
extern NSString*  const kARLastSeenControl;
extern NSString*  const kARTypingControl;
extern NSString*  const kARReadReceipt;

extern NSString* const kARBoolType;
/**
 * :nodoc:
 */
#define TimeStamp [NSString stringWithFormat:@"%f",[[NSDate date] timeIntervalSince1970] * 1000];

extern NSString* const kARMediaType;


extern NSString* const kARRemoteDeviceToken;


extern NSString* const kARVoipDeviceToken;
/**
 * :nodoc:
 */
extern NSString* const kARMessageType;

/**
 * :nodoc:
 */
extern NSString* const kARLoginId;
/**
 * :nodoc:
 */
extern NSString* const kARClientId;
/**
 * :nodoc:
 */
extern NSString* const kARTransactionId;
/**
 * :nodoc:
 */
extern NSString* const kARMessageCode; // TODO needed?
/**
 * :nodoc:
 */
extern NSString* const kAROSType;
/**
 * :nodoc:
 */
extern NSString* const kAROSVersion;
/**
 * :nodoc:
 */
extern NSString* const kARSendOTP;
/**
 * :nodoc:
 */
extern NSString* const kARAppName;


extern NSString* const kARFeaturesSupported;
/**
 * :nodoc:
 */
extern NSString* const kARAppKey;
///**
// * :nodoc:
// */
//extern NSString* const kARAppSecret;
///**
// * :nodoc:
// */
//extern NSString* const kARDeveloperID;
/**
 * :nodoc:
 */
extern NSString* const kARDeviceID;
/**
 * :nodoc:
 */
extern NSString* const kARAccessKey;
/**
 * :nodoc:
 */
extern NSString* const kARAccessSecret;
/**
 * :nodoc:
 */
extern NSString* const kARBucketName;
/**
 * :nodoc:
 */
extern NSString* const kARS3Region;
/**
 * :nodoc:
 */
extern NSString* const kARPermanentFolder;
/**
 * :nodoc:
 */
extern NSString* const kARTemporaryFolder;
/**
 * :nodoc:
 */
extern NSString* const kARCallRecordingFolder;

/**
 * :nodoc:
 */
extern NSString* const kARProfileName;
/**
 * :nodoc:
 */
extern NSString* const kARMailId;
/**
 * :nodoc:
 */
extern NSString* const kARPassword;
/**
 * :nodoc:
 */
extern NSString* const kARPasswordHash;
/**
 * :nodoc:
 */
extern NSString* const kARPresenceUpdateFlag;
/**
 * :nodoc:
 */
extern NSString* const kARNotificationType;
/**
 * :nodoc:
 */
extern NSString* const kARDeviceToken;
/**
 * :nodoc:
 */
extern NSString* const kARVoipDeviceToken;

/**
 * :nodoc:
 */
extern NSString* const kARPresence;
/**
 * :nodoc:
 */
extern NSString* const kARPresenceStatus;

/**
 * :nodoc:
 */
extern NSString* const kAROTP;

/**
 * :nodoc:
 */
extern NSString* const kAROTPFlag;

/**
 * :nodoc:
 */
extern NSString* const kARReturnCode;

/**
 * :nodoc:
 */
extern NSString* const kARReasonPhrase;

/**
 * :nodoc:
 */
extern NSString* const kARCount;
/**
 * :nodoc:
 */
extern NSString* const kARPhoneNumbers;
/**
 * :nodoc:
 */
extern NSString* const kARContactTypes;
/**
 * :nodoc:
 */
extern NSString* const kARList;

/**
 * :nodoc:
 */
extern NSString* const kARUserName;
/**
 * :nodoc:
 */

extern NSString* const kARRemoteUserName;
/**
 * :nodoc:
 */

extern NSString* const kARStatusMessage;
/**
 * :nodoc:
 */
extern NSString* const kARProfilePicture;

/**
 * :nodoc:
 */
extern NSString* const kARSourceNumber;
/**
 * :nodoc:
 */
extern NSString* const kARRemoteNumber;

/**
 * :nodoc:
 */
extern NSString* const kDIDNumber;

/**
 * :nodoc:
 */
extern NSString* const kARMessageID;
/**
 * :nodoc:
 */
extern NSString* const kARSequenceNumber;
/**
 * :nodoc:
 */
extern NSString* const kARDirection;
/**
 * :nodoc:
 */
extern NSString* const kARTimestamp;
/**
 * :nodoc:
 */
extern NSString* const kARChatType;
/**
 * :nodoc:
 */
extern NSString* const kARReportFlags;
/**
 * :nodoc:
 */
extern NSString* const kARChatMessage;
/**
 * :nodoc:
 */
extern NSString* const kARDeliveryStatus;
/**
 * :nodoc:
 */
extern NSString* const kARDeliveryTime;
/**
 * :nodoc:
 */
extern NSString* const kARDisplayedTime;
/**
 * :nodoc:
 */
extern NSString* const kARThumbnailUrl;
/**
 * :nodoc:
 */
extern NSString* const kARFileName;
/**
 * :nodoc:
 */
extern NSString* const kARFileSize;

/**
 * :nodoc:
 */
extern NSString* const kARContentType;

/**
 * :nodoc:
 */
extern NSString* const kARisEdit;

/**
 * :nodoc:
 */
extern NSString* const kARbIsForMe;

extern NSString* const kARisReply;

extern NSString* const kARisForwarded;

extern NSString* const kAROldChatId;

extern NSString* const kARCaptionMessage;

extern NSString* const kARCaptionContentType;

extern NSString* const kARisMuted;

/**
 * :nodoc:
 */
extern NSString* const kARIsTyping;

/**
 * :nodoc:
 */
extern NSString* const kARGroupName;
/**
 * :nodoc:
 */
extern NSString* const kARGroupDescription;

extern NSString* const kARGroupStatus;

extern NSString* const kARCreationTime;
/**
 * :nodoc:
 */
extern NSString* const kARGroupID;

extern NSString* const kARGroupIDs;
/**
 * :nodoc:
 */
extern NSString* const kARAdminNumbers;

/**
 * :nodoc:
 */
extern NSString* const kARChannelID;
/**
 * :nodoc:
 */
extern NSString* const kARChannelName;
/**
 * :nodoc:
 */
extern NSString* const kARChannelDescription;
/**
 * :nodoc:
 */
extern NSString* const kARChannelType;
/**
 * :nodoc:
 */
extern NSString* const kARLocation;
/**
 * :nodoc:
 */
extern NSString* const kARPictureUrl;
/**
 * :nodoc:
 */
extern NSString* const kARChannelRating;

/**
 * :nodoc:
 */
extern NSString* const kARPageSize;
/**
 * :nodoc:
 */
extern NSString* const kARPageOffset;
/**
 * :nodoc:
 */
extern NSString* const kARChannelCategory;
/**
 * :nodoc:
 */
extern NSString* const kARSearchString;
/**
 * :nodoc:
 */
extern NSString* const kARChannelPopularity;
/**
 * :nodoc:
 */
extern NSString* const kARNumberOfLikes;
/**
 * :nodoc:
 */
extern NSString* const kARAverageRating;

/**
 * :nodoc:
 */
extern NSString* const kARChannelInfo;

/**
 * :nodoc:
 */
extern NSString* const kARCallType;
/**
 * :nodoc:
 */

extern NSString* const kARCallState;
/**
 * :nodoc:
 */
extern NSString* const kARCallID;
/**
 * :nodoc:
 */
extern NSString* const kARCallSession;
/**
 * :nodoc:
 */
extern NSString* const kARCallActive;
/**
 * :nodoc:
 */
extern NSString* const kARCallWaiting;

/**
 * :nodoc:
 */
extern NSString* const kARStreamID;
/**
 * :nodoc:
 */
extern NSString* const kARStreamType;
/**
 * :nodoc:
 */
extern NSString* const kARStreamCreator;
/**
 * :nodoc:
 */
extern NSString* const kARSDPOffer;
/**
 * :nodoc:
 */
extern NSString* const kARSDPAnswer;
/**
 * :nodoc:
 */
extern NSString* const kARSDPRemoteOffer;
/**
 * :nodoc:
 */
extern NSString* const KARSDPRemoteAnswer;
/**
 * :nodoc:
 */
extern NSString* const kARICECandidates;
/**
 * :nodoc:
 */
extern NSString* const kARJSONICECandidates;
/**
 * :nodoc:
 */
extern NSString* const kARIsRecordable;
/**
 * :nodoc:
 */
extern NSString* const kARIsSharable;
/**
 * :nodoc:
 */
extern NSString* const kARIsChatEnabled;
/**
 * :nodoc:
 */
extern NSString* const kARIsStreamActive;
/**
 * :nodoc:
 */
extern NSString* const kARBitrate;
/**
 * :nodoc:
 */

extern NSString* const kARServer;
/**
 * :nodoc:
 */
extern NSString* const kARPort;
/**
 * :nodoc:
 */
extern NSString* const kARBrandPin;
/**
 * :nodoc:
 */
extern NSString* const kARSIPEvent;
/**
 * :nodoc:
 */
extern NSString* const kARSIPEventCode;
/**
 * :nodoc:
 */
extern NSString* const kARIsRegisterEvent;
/**
 * :nodoc:
 */
extern NSString* const kARCallEndStatus;
/**
 * :nodoc:
 */
extern NSString* const kARCallEndReason;
/**
 * :nodoc:
 */
extern NSString* const kARHoldFlag;
/**
 * :nodoc:
 */
extern NSString* const kARDTMFDigit;

/**
 * :nodoc:
 */
extern NSString* const kARCallStatus;
/**
 * :nodoc:
 */
extern NSString* const kARStartTime;
/**
 * :nodoc:
 */
extern NSString* const kARAnswerTime;
/**
 * :nodoc:
 */
extern NSString* const kAREndTime;
/**
 * :nodoc:
 */
extern NSString* const kARMediaServerID;
/**
 * :nodoc:
 */
extern NSString* const kARCallRecordingFlag;

/**
 * :nodoc:
 */
extern NSString* const kANAppState;
/**
 * :nodoc:
 */
extern NSString* const kANReasonCode;
/**
 * :nodoc:
 */
extern NSString* const kANReasonDescription;
/**
 * :nodoc:
 */
extern NSString* const kANBalanceUrl;
/**
 * :nodoc:
 */
extern NSString* const kANBrandName;
/**
 * :nodoc:
 */
extern NSString* const kANBrandUrls;

#pragma mark - Notifications

/**
 * Client State Notification
 */
extern NSString* const CSClientStateNotification;
/**
 * Signup Response Notification
 */
extern NSString* const CSClientSignupNotification;
/**
 * Activation Response Notification
 */
extern NSString* const CSClientActivationNotification;
/**
 * Contact Refresh Notification
 */
extern NSString* const CSContactReloadNotification;
/**
 * Chat Notification
 */
extern NSString* const CSChatNotification;
/**
 * Chat Delivery Notification
 */
extern NSString* const CSChatDeliveryNotification;
/**
 * Chat Delivery Notification
 */

extern NSString* const kARDidNumber;


#pragma mark - SMS
/**
 *SMS ID
 */
extern NSString* const kSMSID;
extern NSString* const kOldSMSID;
extern NSString* const kARSMSMessage;
extern NSString* const kARSMSIsReply;
extern NSString* const kSMSStatus;
extern NSString* const kSMSStatusCode;
extern NSString* const kSMSPageSize;
extern NSString* const kSMSOffSet;
extern NSString* const kSMSFromNumber;

#pragma mark - Content Types

extern NSString* const CSImageJpeg;
extern NSString* const CSImagePng;
extern NSString* const CSImageGif;
extern NSString* const CSDocumentPdf;
extern NSString* const CSDocumentDoc;
extern NSString* const CSDocumentDocx;
extern NSString* const CSAudioAac;
extern NSString* const CSAudioMp3;
extern NSString* const CSVideoMp4;
extern NSString* const CSVideoMov;

#pragma mark - enums


/**
 * Reason Codes
 */
typedef NS_ENUM(NSInteger, CSReasonCodes) {
	/// Success	
    CSReasonCodeSuccess,
    /// Failure
    CSReasonCodeFailure,
    /// Unauthorized
    CSReasonCodeUnauthorized,
    /// Not Allowed
    CSReasonCodeNotAllowed,
    /// Internal Error
    CSReasonCodeInternalError,
    /// Forbidden
    CSReasonCodeForbidden,
    /// Not Found
    CSReasonCodeNotFound,
    /// Request Timeout
    CSReasonCodeRequestTimeout,
    /// Inactive Opcode
    CSReasonCodeInactiveOpcode,
    /// Wrong Opcode
    CSReasonCodeWrongOpcode,
    /// Signup Limit Exceeded
    CSReasonCodeLimitExceeded,
    /// User attached to another device
	CSReasonCodeUserAlreadyAttached,
    
	CSReasonCodeUserDeactivated
};

/**
 * Return codes in responses
 */
typedef NS_ENUM(NSInteger, CSReturnCodes) {
 	/// Default status
   E_UNKNOWN_RETURN_CODE,			
    /// 200 OK	
    E_200_OK,
    /// 202 OK						
    E_202_OK,					
    /// 401 Unauthorized	
    E_401_UNAUTHORIZED,		
    /// 409 Not Allowed		
    E_409_NOTALLOWED,
    /// 500 Internal Error				
    E_500_INTERNALERR,		
    /// 204 Resend Activation Code		
    E_204_RESENDACTIVATIONCODE,		
    /// 403 Forbidden
    E_403_FORBIDDEN,				
    /// 701 Inactive OpCode
    E_701_INACTIVE_OPCODE,		
    /// 702 Wrong OpCode	
    E_702_WRONG_OPCODE,				
    /// 703 Registration Limit Exceeded
    E_703_LIMIT_EXCEEDED,	
    /// 499 User already attached on another device		
    E_499_USER_ALREADY_ATTACHED,
	E_800_INVALID_APP_ID,
	E_801_WRONG_APP_CREDENTIALS,
	E_802_APP_ALREADY_CREATED,
	E_803_USER_DEACTIVATED
};

/**
 * SDK Error Codes
 */
typedef NS_ENUM(NSInteger, CSErrorCode) {
	/// Success
    CSErrorCodeSuccess,	
    /// Failure			
    CSErrorCodeFailure,		
    /// Parameter is nil		
    CSErrorCodeNullParameter,	
    /// Invalid Parameter	
    CSErrorCodeInvalidParameter,	
    /// Invalid Number
    CSErrorCodeInvalidNumber,	
    /// Network not available	
    CSErrorCodeNoNetwork,		
    /// Not Registered	
    CSErrorCodeNotRegistered,	
    /// Not Allowed in current state	
    CSErrorCodeNotAllowed,	
    /// Client not active		
    CSErrorCodeClientNotActive,	
    /// Client not ready	
    CSErrorCodeClientNotReady,		
    /// Active call exists
    CSErrorCodeActiveCallExists,	
    /// Active call doesnt exists
    CSErrorCodeNoActiveCallExists,	
	CSErrorCodeRecordExists
};

/**
 * History record type
 */
typedef NS_ENUM(NSInteger, CSHistoryType) {
	/// Voice Call - 0
	CSHistoryTypeCall,
	/// Video Call - 1
	CSHistoryTypeVideoCall,
	/// PSTN Call - 2
	CSHistoryTypePSTNCall,
	/// Chat Message - 3
	CSHistoryTypeMessage,	
	/// Photo - 4
	CSHistoryTypePhoto,	
	/// Video - 5
	CSHistoryTypeVideo,
	/// File - 6
	CSHistoryTypeDocument,
	/// Location - 7
	CSHistoryTypeLocation,	
	/// Contact - 8
	CSHistoryTypeContact,	
	/// Info - 9
	CSHistoryTypeInfo,
	/// Group Info - 10
	CSHistoryTypeGroupInfo,
	/// Audio - 11
	CSHistoryTypeAudio,
    /// SMS - 12
    CSHistoryTypeSMS,
    ///  Media (Photo & Video)- 13
    CSHistoryTypeMedia,
    ///   Links -14
    CSHistoryTypeLinks,
    ///   AllChats -15
    CSHistoryTypeAllChats,
    ///   UserAnnouncements -16
    CSHistoryTypeUserAnnouncements,
    ///   GIFS -17
    CSHistoryTypeGIFS,
    ///   CSHistoryTypeChatCallLogAudio -18
    CSHistoryTypeChatCallLogAudio,
    ///   CSHistoryTypeChatCallLogVideo -19
    CSHistoryTypeChatCallLogVideo
};

/**
 * File Transfer Status
 */
typedef NS_ENUM(NSInteger, CSFileTransferStatus) {
	/// Default Status
	CSFileTransferNone = 0,
	/// Yet to download
	CSFileDownloadPending = 1,
	/// Downloaded
	CSFileDownloadCompleted = 3,
	/// Failed to download
	CSFileDownloadFailed = 4,
	/// Yet to upload
	CSFileUploadPending = 5,
	/// Uploaded
	CSFileUploadCompleted = 7,
	/// Failed to upload
	CSFileUploadFailed = 8,
	/// Download paused
	CSFileDownloadPaused = 9,
	/// Download paused
	CSFileUploadPaused = 10
};

typedef NS_ENUM(NSInteger, CSVideoPreviewPosition) {
	
	CSVideoPreviewPositionTopRight,
	CSVideoPreviewPositionTopLeft,
	CSVideoPreviewPositionBottomRight,
	CSVideoPreviewPositionBottomLeft,
	CSVideoPreviewPositionCustom
};


typedef NS_ENUM(NSInteger, CSContactType){
    E_PHONE_CONTACT = 0,
    E_CUSTOM_CONTACT
};

typedef NS_ENUM(NSInteger, CSChatType){
    E_UNKNOWN_CHAT_TYPE = 0,
    E_TEXTPLAIN = 1,
    E_TEXTHTML = 2,
    E_LOCATION = 3,
    E_IMAGE = 4,
    E_VIDEO = 5,
    E_CONTACT = 6,
    E_DOCUMENT = 7,
    E_AUDIO = 8,
    E_ANNOUNCEMENTS = 9
};

/**
 * File Transfer Status
 */
typedef NS_ENUM(NSInteger, CSFTState) {
	///
	CSFTStateNone,
	///
	CSFTInProgress,
	///
	CSFTSuspended,
	///
	CSFTCancelled,
};


typedef NS_ENUM(NSInteger, CSGroupType){
    E_PERMANANT = 0,
    E_BROADCAST = 1,
    E_STATUS = 2,
    E_NOTIFICATION = 3
};

typedef NS_ENUM(NSInteger, CSNotificationMuteType){
    E_INVALID = 0,
    E_MUTE = 1,
    E_UNMUTE = 2
};


typedef NS_ENUM(NSInteger, CSMuteOption){
    E_Never = 0,
    E_1Hour = 1,
    E_1Day = 2,
    E_1Week = 3,
    E_Always = 4
};

typedef NS_ENUM(NSInteger, CSMuteAction){
    E_NONE = 0,
    E_CALL = 1,
    E_CHAT = 2,
    E_GROUP = 3,
    E_ALL = 4
};


typedef NS_ENUM(NSInteger, CSControlOptions){
    E_CONTROL_OPTIONS_EVERYONE = 0,
    E_CONTROL_OPTIONS_MY_CONTACTS = 1,
    E_CONTROL_OPTIONS_NOBODY = 2
};

typedef NS_ENUM(NSInteger, CSMediaDownloadOption){
    E_MEDIA_AUTO_DOWNLOAD_OVER_WIFI = 0,
    E_MEDIA_AUTO_DOWNLOAD_OVER_MOBILE_DATA = 1,
    E_MEDIA_AUTO_DOWNLOAD_NEVER = 2
};

typedef NS_ENUM(NSInteger, CSChatDisappearTime){
    CSChatDisappearTimeOff = 0,
    CSChatDisappearTimeOneDay = 1,
    CSChatDisappearTimeSevenDays = 2
};

typedef NS_ENUM(NSInteger, CSChatAnnouncementsType){
    CSChatAnnouncementsTypeNone = 0,
    CSChatAnnouncementsTypeDisappearMessages = 1,
    CSChatAnnouncementsTypeLocalAnnouncements = 2
};



typedef NS_ENUM(NSInteger, CSCallEndStatusCodes){
    E_NoAnswer = 487,
    E_NoMedia  = 415,
    E_UserTerminated = 200,
    E_UserBusy = 486,
    E_UnKnown = 0,
    E_Error = 500
};



#endif
