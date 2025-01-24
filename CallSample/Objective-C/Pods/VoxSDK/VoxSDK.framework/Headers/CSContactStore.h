    //
    //  CSContactStore.h
    //  VoxSDK
    //
    //  Created by Kiran Vangara on 07/03/15.
    //  Copyright © 2015-2018, Connect Arena Private Limited. All rights reserved.
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
#import "CSConstants.h"

    /// `CSContactStore` provides interface to manage Contacts & Groups
@interface CSContactStore : NSObject

- (instancetype)init NS_UNAVAILABLE;

#pragma mark - Instance Methods

    /// Get Shared Instance
+ (CSContactStore*)sharedInstance;

    /// Check if it is a valid Phone number
    ///
    /// @param number number to validate
    ///
    /// @param defaultRegion region code to check against
    ///
+(BOOL) isValidPhoneNumber:(NSString *)number defaultRegion:(NSString*)defaultRegion;

#pragma mark - Contact Permissions

    /// Check for native contacts permissions
-(void) promptContactAccess;

    /// Status of permission for contacts
    ///
    /// @return Status
    ///
-(bool) isAccessGrantedForContacts;

    /// Get presence of number
-(void) getPresenceForNumber:(NSString*)number;



//To SET Privacy control for user presence, last seen, typing status and read receipts. Values the inter maps to the enum CSControlOptions

-(void) setUserLastSeenSettings:(enum CSControlOptions)ctrlOption;

-(void) setUserTypingSettings:(enum CSControlOptions)ctrlOption;

-(void) setUserPresenceSettings:(enum CSControlOptions)ctrlOption;

-(void) setUserReadReceiptSettings:(BOOL)readReceiptValue;


#pragma mark - Fetch Contacts

    /// Get contact list
    ///
    /// @param contactArray Array of contacts
    ///
    /// @param allContactsFlag flag to specify all contacts or app contacts
    ///
    ///                TRUE  - All Contacts
    ///                FALSE - App Contacts ( users of app)
    ///
    /// @return TRUE - Success FALSE - Failure
    ///
- (BOOL) getContactList:(NSMutableArray **)contactArray flag:(BOOL)allContactsFlag;

    /// Get specific contact
    ///
    /// @param recordID Unique ID of the contact
    ///
    /// @return `CSContact` Object
    ///
//-(CSContact*) getContactRecord:(NSString*) recordID;

//Fetch all native contacts to update
-(void)fetchNativeContacts;

#pragma mark - Contact Management

    /// Add new contact
    ///
    /// @param userID Unique ID of the user
    ///
-(void) addContactWithID:(NSString*)userID;
//-(void) addContactWithID:(NSString*)userID sipUsername:(NSString *)sipUsername;
-(void) addContactWithID:(NSString*)userID sipUsername:(NSString *)sipUsername mobNumber:(NSString*)mobileNumber email:(NSString*)email;

    /// Delete contact
    ///
    /// @param userID Unique ID of the user
    ///
-(void) deleteContactWithID:(NSString*)userID;

-(void) blockContact:(NSString*)number
   completionHandler:(void (^)(NSError *error))completionHandler;

-(void) unblockContact:(NSString*)number
     completionHandler:(void (^)(NSError *error))completionHandler;

#pragma mark - Fetch Groups

    /// Get group list
    ///
    /// @return Array of groups
    ///
-(NSArray*) getGroups;
/// Get group list
///
/// @return Array of Status groups

-(NSArray*) getStatusGroups ;

    /// Get group by Group ID
    ///
    /// @param groupID Unique ID of group
    ///
    /// @return `CSGroup` Object
    ///

#pragma mark - MuteNotification

//Mute notification for specific user for specific duration
//remoteId — user number
//muteStatus — true to mute, false to unmute

-(void)setMuteNotificationForRemoteId:(NSString *)remoteId withMuteStatus:(BOOL)muteStatus forType:(enum CSMuteAction)muteAction andWithExpiry:(enum CSMuteOption)muteExpiry;



-(CSGroup*) getGroup:(NSString*) groupID;

#pragma mark - Search Methods

    //! TODO There can be multiple contact matches for number

    /// Lookup Contacts for a specified number
    ///
    /// @param number phone number
    ///
    /// @return `CSContact` Object
    ///
- (CSContact*) lookupContactsByNumber:(NSString*)number;

    /// Lookup Groups by Group ID
    ///
    /// @param groupID Unique ID of group
    ///
    /// @return `CSGroup` Object
    ///
-(CSGroup*) lookupGroupsByID:(NSString*)groupID;

    //! TODO There can be multiple matches for name

    /// Search Groups for a specific Group ID
    ///
    /// @param groupName Name of the Group
    ///
    /// @return `CSGroup` Object
    ///
    //-(CSGroup*) lookupGroupsByName:(NSString*)groupName;

#pragma mark - Create/Delete Groups

    /// Create a new Group
    ///
    /// @param groupName Group Name
    ///
    /// @param description Group description
    ///
    /// @param photoUrl Group photo Url
    ///
-(void) createGroup:(NSString*)groupName
    withDescription:(NSString*)description
           andPhoto:(NSData*)photo
        contentType:(NSString*)contentType
  completionHandler:(void (^)(NSDictionary* response, NSError* error))completionHandler;

    /// Delete group by Group ID
    ///
    /// @param groupID Unique ID of group
    ///
    /// @param completionHandler completion handler called on response.
    ///
-(void) createGroupforStatus:(NSString*)name
           completionHandler:(void (^)(NSDictionary* response, NSError* error))completionHandler;
 

-(void) createSelfGroupforStatus:(NSString*)name
               completionHandler:(void (^)(NSDictionary* response, NSError* error))completionHandler;

    
-(void) updateGroupforStatus:(NSString*)groupID
         addMembers:(NSArray*)members
           completionHandler:(void (^)(NSError *error))completionHandler;



-(void)deleteAllStatusGroupfromRemote;

-(void)deleteChat:(NSString *)msgID forRemote:(BOOL)forRemote;

-(void)deleteChat:(NSString *)number messageID:(NSString *)msgID ForGroup:(BOOL)forgrp;

-(void)deleteAllChatforStatus:(BOOL)forRemote;

-(void)deleteSelfUserStatusfromRemote:(NSString *)groupID messageID:(NSString *)msgID;

-(void) deleteGroup:(NSString*)groupID
  completionHandler:(void (^)(NSError *error))completionHandler;

    /// Leave group by Group ID
    ///
    /// @param groupID Unique ID of group
    ///
    /// @param completionHandler completion handler called on response.
    ///
-(void) leaveGroup:(NSString*)groupID
 completionHandler:(void (^)(NSDictionary *response, NSError *error))completionHandler;

#pragma mark - Manage Groups

    /// Add members to group
    ///
    /// @param groupID Unique ID of group
    ///
    /// @param members Array of members to add to group
    ///
    /// @param completionHandler completion handler called on response.
    ///
-(void) updateGroup:(NSString*)groupID
         addMembers:(NSArray*)members
  completionHandler:(void (^)(NSError *error))completionHandler;

    /// Remove member from group
    ///
    /// @param groupID Unique ID of group
    ///
    /// @param member member to be removed from group
    ///
    /// @param completionHandler completion handler called on response.
    ///
-(void) updateGroup:(NSString*)groupID
       removeMember:(NSString*)member
  completionHandler:(void (^)(NSError* error))completionHandler;

    /// Change group name, description, profile photo
    ///
    /// @param groupID Unique ID of group
    ///
    /// @param name name of group
    ///
    /// @param description Description of group
    ///
    /// @param photoUrl Profile photo of group
    ///
    /// @note Response will be notified through `CSContactStoreDelegate`
    ///

-(void) updateGroup:(NSString*)groupID
           withName:(NSString*)name
        description:(NSString*)description
           photoUrl:(NSURL*)photoUrl
  completionHandler:(void (^)(NSError *error))completionHandler;

    /// Add admin
    ///
    /// @param groupID Unique ID of group
    ///
    /// @param member member to be made admin or newly added to group
    ///
    /// @note Response will be notified through `CSContactStoreDelegate`
    ///
-(void) updateGroup:(NSString*)groupID
           addAdmin:(NSString*)member
  completionHandler:(void (^)(NSError *error))completionHandler;

    /// Remove admin
    ///
    /// @param groupID Unique ID of group
    ///
    /// @param member member to be removed as admin from group
    ///
    /// @note Response will be notified through `CSContactStoreDelegate`
    ///
-(void) updateGroup:(NSString*)groupID
        removeAdmin:(NSString*)member
  completionHandler:(void (^)(NSError *error))completionHandler;

-(void) doPullGroups;

//Allow or stop all users in group to post messages
-(void)allowUsersToPostMessageWithGroupID:(NSString *)groupID allow:(BOOL)allowStatus;

@end
