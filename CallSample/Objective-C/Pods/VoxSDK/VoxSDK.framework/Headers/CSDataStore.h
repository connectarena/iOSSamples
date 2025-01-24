//
//  CSDataStore.h
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
#import "CSContact.h"
#import "CSGroup.h"
#import "CSHistory.h"
#import "CSCallHistoryIndex.h"

/**
 * Grouping for Call history indexes
 */
typedef NS_ENUM(NSInteger, CSHistoryGroupByType) {
	/// Group by number
	CSHistoryGroupByNumber,
	/// Custom grouping
	CSHistoryGroupByCustom
};

/// `CSDataStore` provides interface for persistent storage
/// It manages call and chat history
@interface CSDataStore : NSObject

#pragma mark - Instance Methods

- (instancetype)init NS_UNAVAILABLE;

/// Get Shared Instance
+(CSDataStore*) sharedInstance;

#pragma mark - Fetch Call History

/// Get most recent call details
///
/// @return `CSHistory` Object or nil
///
-(CSHistory*) getRecentCall;

/// Get call history of a number
///
/// @param number phone number
///
/// @param limit record limit
///
-(void) getCallHistory:(NSMutableArray**)recordResults
			 forNumber:(NSString*)number
	   withRecordLimit:(NSUInteger)limit;

-(void) updateGroupStatusForNumbers:(NSArray*)numbers withStatus:(NSInteger)status;

-(NSMutableArray*) statushistoryRecordIsMessageSeenByAll:(NSString*)messageID
                                                 inGroup:(NSString*)groupID ;

-(NSDate*)getStatusGroupCreationDate;

/// Get call history of a Contact
///
/// @param recordResults Array of `CSCallHistory` Objects
///
/// @param contact Contact Object
///
/// @param limit record limit
///
-(void) getCallHistory:(NSMutableArray**)recordResults
			forContact:(CSContact*)contact
	   withRecordLimit:(NSUInteger)limit;

/*
 This method is needed for resetting the Missed Call Count Status for a Message ID.
 Missed Call Count Status is the status for showing the unread missed calls.
 Once the user reads the missed calls in the Call History Detail, Its important to update the Read status of Missed Call.
 So resetMissedCallCountForMessageID resets the status to 0. Default Status is 1.
 Call this method in Call History Detail View to reset the read status to 0.
 */

-(void)resetMissedCallCountForMessageID:(NSString *)messageID;


-(BOOL) getMissedCallCountStatusForMessageID:(NSString *)messageID;

-(NSInteger) getUnreadMissedCallsCountForRemoteNumber:(NSString *)remoteNumber;

/*
 This method is needed for getting the Unread Missed Call Count
 */

-(NSInteger) getUnreadMissedCallsCountForCallHistoryIndex:(CSCallHistoryIndex *)callHistoryIndex;

-(NSMutableArray*) fetchNumbersInAGroupWithGroupID:(NSString*)groupID;

-(NSMutableArray*)fetchNumbersForaGroupStatusfromContacts:(NSInteger)groupStatus;

-(NSMutableArray *)getNumbersInAGroup:(CSGroup *)group;

-(BOOL) isChatRecordsExist;


/// Get Index of call history grouped by
///
/// @param recordResults Array of `CSCallHistory` Objects
///
/// @param groupBy grouping mode
///
-(void) getCallHistoryIndexRecords:(NSMutableArray **)recordResults
						 groupedBy:(CSHistoryGroupByType)groupBy;

-(void) getCallHistoryIndexForMissedCalls:(NSMutableArray **)recordResults;

#pragma mark - Fetch History

/// Get History Indexes
///
/// return Array of `CSHistoryIndex` Objects
///
-(void) getChatHistoryIndexRecords:(NSMutableArray **)recordResults;

-(void) getChatHistoryStatusIndexRecords:(NSMutableArray **)recordResults
                                forself:(BOOL)forself;

-(void) getChatHistoryGroupStatusIndexRecords:(NSMutableArray **)recordResults memberNumber:(NSString *)memberNumber;

-(void) getViewedGroupStatusIndexRecords:(NSMutableArray **)viewedRecordResults unviewedRecrods:(NSMutableArray **)unViewedRecords memberNumber:(NSString *)memberNumber;

-(void) getChatIDforAllStatusRecords:(NSMutableArray **)recordResults;

-(void)getAllStatusMembers:(NSMutableArray **)memberArray messageID:(NSString *)msgID;

-(void) checkTimeDurationForStatusGreater24;


-(CSNumber*) fetchCSNumberRecord:(NSString*)number;

-(void) updateMuteStatusForNumber:(NSString*)number withMuteStatus:(NSInteger)muteStatus;



/// Get History Details
///
/// return Array of `CSHistory` Objects
///
-(void) getChatHistoryFromOldestUnreadMessage:(NSMutableArray **)recordResults
									forNumber:(NSString*)number
					  withOptionalRecordLimit:(NSInteger)recordLimit;

-(void) getChatHistoryRecords:(NSMutableArray **)records
				 forNumber:(NSString*)number
		   withRecordLimit:(NSUInteger)limit;

-(void) getSMSHistoryRecords:(NSMutableArray **)recordResults;

-(void) getSMSHistoryRecords:(NSMutableArray **)records
                    forNumber:(NSString*)number
              withRecordLimit:(NSUInteger)limit;

-(void) getChatHistoryRecords:(NSMutableArray **)recordResults
					   before:(CSHistory*)currentRecord
			  withRecordLimit:(NSUInteger)limit;

-(CSHistory*) getHistoryRecordByID:(NSString *)messageID;

-(CSHistory*) getHistoryRecordByMessageID:(NSString*)messageID;

// DEPRECATED API
-(void) loadHistoryIndexRecords:(NSMutableArray **)recordResults;

-(void) loadHistoryRecords:(NSMutableArray **)records
				 forNumber:(NSString*)number
		   withRecordLimit:(NSUInteger)limit;

-(void) getDeliveryStatus:(NSMutableArray **)recordResults
			 forMesssgeID:(NSString*)messageID;

-(void) getDisplayStatus:(NSMutableArray **)recordResults
			 forMesssgeID:(NSString*)messageID;

-(void) fetchBlockedContacts:(NSMutableArray **)blockedContacts;

-(BOOL) isContactBlocked:(NSString*)number;

#pragma mark - Delete Call History

/// Delete call history for a Number
///
/// @param number phone number
///
-(void) deleteCallHistoryByNumber:(NSString*)number;

/// Delete call history for a contact
///
/// @param contact Contact Object
///
-(void) deleteCallHistoryForContact:(CSContact*)contact;

/// Delete call history by index
///
/// @param index history index
///
-(void) deleteCallHistoryByIndex:(CSCallHistoryIndex*)index;

/// Delete Call History by Record ID
///
/// @param recordID Unique record ID
///
-(void) deleteCallHistoryByRecordID:(NSInteger)recordID;

#pragma mark - Delete History

/// Delete History entry
-(void) deleteHistoryRecord:(NSString*)messageID;

-(void) deleteStatusHistoryRecord:(NSInteger)groupStatus;

-(void) deleteAllSMSRecords;

/// @param number phone number
///
-(void) deleteHistoryForNumber:(NSString *)number;

-(void) deleteSMSHistoryForNumber:(NSString *)number;

/// Erase complete history
-(void) deleteAllHistory;

-(void) deleteAll;

-(void) deleteAllGroupStatusIDandRecords;

-(void) deleteContactGroupForStatus:(NSInteger)groupStatus;

-(void) deleteContactGroupForSelfStatus:(NSString *)groupID;

-(void) deleteChatForMessageID:(NSString *)msgID;



#pragma mark - Notification Count

/// Clear Call Notification Count
-(void) clearCallNotificationCount;

    /// Clear Chat Notification Count
-(void) clearChatNotificationCount;

/// Get Call and Chat Notification Count
-(NSDictionary*) getNotificationCount;


-(void) contactRecord:(NSString*)number updateFavouriteContact:(BOOL)favValue;
-(void) contactRecord:(NSString*)number updateFavouriteNameContact:(NSString*)favName;
-(BOOL) isGroupStatusExist:(NSString*)groupID;

-(BOOL) isMessageIDExistStatusGroup:(NSString*)messageID;

-(void) contactRecord:(NSString*)number updateContactSipUsername:(NSString *)sipUsername;
-(void) contactRecord:(NSString*)number updateMobileNumber:(NSString *)mobileNumber;
-(CSNumber *) fetchContactNameBySipusernameRecord:(NSString*)number;

//To set archive chat for archiveStatus 0 == false, 1 == true
-(void) setArchiveforChat:(NSString*)number withArchiveStatus:(NSInteger)archiveStatus;

//- To set pin chat for pinStatus 0 == false, 1 == true
-(void) setPinforChat:(NSString*)number withPinStatus:(NSInteger)pinStatus;

//To check chat is muted for notification, will return enum CSMuteOption
-(NSInteger) getChatRecordNotificationMutedValueFor:(NSString*)number;


//To check chat is pinned in chat history
-(BOOL) isChatRecordPinned:(NSString*)number;


//To check chat is archived in chat history
-(BOOL) isChatRecordArchived:(NSString*)number;

//To check whether the message sent by login user
-(BOOL)isMsgSentByMe:(NSString*)messageID;

//- To delete chat history with remote number
-(void)deleteChatHistoryWithNumber:(NSString *)remoteNumber;

//To change Group type to the enum CSGroupType
-(void)updateGroupPermission:(NSString *)groupID withPermission:(NSInteger)groupStatus;

//To find the number is admin in the given group id
-(BOOL)isContactIsAdminWithNumber:(NSString *)number ForGroupID:(NSString *)groupID;
   

//To find number is favourite contact
-(BOOL) isFavouriteContact:(NSString*)number;

//To get List of all favourite contacts
-(NSMutableArray*) getAllFavouriteContacts;

//To get favourite name for contacts
-(NSString *)getFavouriteNameForNumber:(NSString *)number;

//To get list of groups user is in common with you
-(NSMutableArray *)getAllGroupsInCommonWithNumber:(NSString *)number;

-(BOOL) isFromStatusHistoryWithMessageID:(NSString*)messageId;

//-(CSHistory*) getReplyHistoryRecordByID:(NSString*)messageID;

//To get status privacy contact list, for status feature
-(NSMutableArray*) getStatusPrivacyExceptContacts;

-(NSMutableArray*) getStatusPrivacyOnlyShareWithContacts;


//- To set, get and remove the star chat
-(void) setStarforChat:(NSString*)messageID withStarStatus:(NSInteger)starStatus;

-(void) removeStarForAllChats;

-(void) getChatAllStarHistoryRecords:(NSMutableArray**)recordResults
                     withRecordLimit:(NSUInteger)limit;


//To search the chat with text from its message and caption with filter of record type also
-(NSMutableArray *) searchChatHistoryRecordsWithRecordType:(enum CSHistoryType)recordType withText:(NSString *)messageValue;


//To search the chat with text from its message and caption with filter of record type also for specific number or group id
-(NSMutableArray *) searchChatHistoryRecordsWithRecordType:(enum CSHistoryType)recordType withText:(NSString *)messageValue forRemoteNumber:(NSString *)remoteNumber;

//To set wallpaper of chat with remote number or groupID
-(void)setWallPaperForChatWith:(NSString *)remoteChatId andImageData:(NSData *)imageData;

//To get wallpaper of chat with remote number or groupID
-(NSString *) getChatWallpaperPath:(NSString*)remoteChatId;

//To get all the chat history of the archived chats
-(void) getArchivedChatHistoryIndexRecords:(NSMutableArray **)recordResults;

//To receive msg as support ex: welcome message, this message won’t send to server
-(void)sendSupportMessageToNumber:(NSString *)supportNumber withMessage:(NSString *)message;


-(void)insertDisappearIdsWithRemoteID:(NSString *)remoteID disappearStatus:(BOOL)status disappearTimeInMilliSec:(long long)TimeInMilliSec withDisappearTimeValue:(enum CSChatDisappearTime) disappearTimeValue;


//To get chat disappear time enum
-(enum CSChatDisappearTime)getChatDisappearValueForRemoteID:(NSString *)remoteID;


//To search the chat with text from its message and caption with filter of record type also., In return we will get array of message ids, this will be useful for the highlighting the chat cell with searched text
-(NSMutableArray *) searchChatForMessageIdsWithRecordType:(enum CSHistoryType)recordType withText:(NSString *)messageValue forRemoteNumber:(NSString *)remoteNumber;

//To get group Type with group ID will return enum CSGroupType
-(enum CSGroupType)getGroupTypeWith:(NSString *)groupId;


-(BOOL)checkHasNameMentionWithMessage:(NSString *)message;

// To check group exists in DB with groupID
-(BOOL) isGroupExists:(NSString*)groupID;


//To remote wallaper for specic number or group id
-(void)removeWallpaperForChatWith:(NSString *)remoteId;


//Delete all chat of single user or group with remote number or group id , were we can stop deleting media and star messaging by passing value as false
-(void)deleteChatHistoryWithNumber:(NSString *)remoteNumber WithMedia:(BOOL)deleteMedia andWithStarredChat:(BOOL)deleteStarChat;


-(NSString *)getFinalMessageWithMention:(NSString *)message;


//- To get all frequently used contacts or groups with limit
-(NSMutableArray *)getFrequentlyUsedContactsWithLimit:(NSInteger)limit;

//To get other users updated profile status
-(NSString *)getUserStatusForNumber:(NSString *)number;

//To clear call notification count for specific number
-(void) clearCallNotificationCountForNumber:(NSString *)number;

//To clear all SMS count
-(void) clearSMSNotificationCount;

//To clear SMS notification count for specific number
-(void) clearSMSNotificationCountForNumber:(NSString *)number;

//Get ProfilePath for app contact
-(CSNumber*)getProfilePicForRemoteUser:(NSString*)number;

//Get Destination ToNumber in which number you got the call
-(NSString *)getDestinationToNumber:(NSString *)callID;
@end
