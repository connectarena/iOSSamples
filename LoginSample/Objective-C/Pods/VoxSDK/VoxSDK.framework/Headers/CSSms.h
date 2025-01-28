//
//  CSSms.h
//  VoxSDK
//
//  Created by Pradeep Reddy Kypa on 28/12/20.
//  Copyright © 2020 Connect Arena. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CSSms;

/**
 * Delegate for SMS Events
 */
@protocol  CSSmsDelegate <NSObject>



@end

@interface CSSms : NSObject

#pragma mark - Properties

    /// Delegate for SMS Events.<br>
    /// An object conforming to `CSSmsDelegate` protocol.
@property (weak, nonatomic) id<CSSmsDelegate> delegate;

#pragma mark - Initialisers

/**
 * Unavailable
 */
-(instancetype) __unavailable init;
    
-(instancetype) initForNumber:(NSString*)remoteNumber
                 withDelegate:(nullable id)delegate;

-(NSString*) sendSMS:(NSString*)message toNumber:(NSString *)remoteNumber withDIDNumber:(NSString *)number;

-(void)fetchSMSHistory;

@end

NS_ASSUME_NONNULL_END
