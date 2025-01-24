//
//  CSStatus.h
//  VoxSDK
//
//  Copyright © 2022 Connect Arena. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/Foundation.h>
#import "CSContact.h"
#import "CSConstants.h"
#import "CSHistory.h"
#import "CSChat.h"

NS_ASSUME_NONNULL_BEGIN

@class CSStatus;

@protocol  CSStatusDelegate <NSObject>

/**
 * Received message
 */
-(void) status:(CSStatus*)status didReceiveMessage:(CSHistory*)record;

/**
 * Presence status updated
 */
-(void) chat:(CSChat*)chat
  didUpdatePresence:(int)status
          timestamp:(NSDate*)timestamp;

@end


@interface CSStatus : NSObject

@property (nonatomic) NSInteger statusMode;
@property (nonatomic) NSInteger groupType;

/// Delegate for chat events.<br>
/// An object conforming to `CSChatDelegate` protocol.
@property (weak, nonatomic) id<CSStatusDelegate> delegate;

+(CSStatus*) sharedInstance;

-(instancetype) init;

-(instancetype) initForIndex:(NSInteger*)index msg:(NSString *)message appparam1:(NSString *)appparam1 apparam2:(NSString *)appparam2 photoData:(nullable NSData *)data PhotofromURL:(nullable NSURL *)fileUrl fileName:(NSString *)fileName grpContentType:(GRPSTATUSTYPE)contType contentType:(NSString *)contentType fromCamera:(BOOL)fromCamera withCaptionMessage:(NSString *)caption withDelegate:(id)delegate ;

#pragma mark - Create Status Method

-(BOOL)createGroupStatus;

-(BOOL)createGroupStatus:(NSString*)message appparam1:(NSString*)appparam1 apparam2:(NSString*)appparam2 photoData:(nullable NSData*)data PhotofromURL:(nullable NSURL*)fileUrl fileName:(NSString*)fileName grpContentType:(GRPSTATUSTYPE)contType contentType:(NSString*)contentType fromCamera:(BOOL)fromCamera withCaptionMessage:(NSString*)caption;

-(BOOL)createStatusforGroup:(NSString*)groupID message:(NSString*)message appparam1:(NSString*)appparam1 apparam2:(NSString*)appparam2 photoData:(nullable NSData*)data PhotofromURL:(nullable NSURL*)fileUrl fileName:(NSString*)fileName grpContentType:(GRPSTATUSTYPE)contType contentType:(NSString*)contentType fromCamera:(BOOL)fromCamera withCaptionMessage:(NSString*)caption;

-(NSMutableArray *)getStatusChatList:(BOOL)forSelf;


-(void) handleCSStatusNotification:(NSNotification*)notification ;

@property (strong, nonatomic) NSString* m_groupID;
@property (strong, nonatomic) NSString* m_statusMessage;
@property (strong, nonatomic) NSString* m_appparam1;
@property (strong, nonatomic) NSString* m_appparam2;
@property (strong, nonatomic) NSData* m_photoData;
@property (strong, nonatomic) NSURL* m_fileURL;
@property (strong, nonatomic) NSString* m_fileName;
@property (nonatomic) GRPSTATUSTYPE contType;
@property (strong, nonatomic) NSString* m_contentType;
@property (nonatomic) BOOL m_fromCamera;
@property (strong, nonatomic) NSString* m_captionMessage;

@property (strong, nonatomic) NSOperationQueue *queue;

@end

NS_ASSUME_NONNULL_END
