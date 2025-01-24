//
//  CSSIPExtensions.h
//  VoxSDK
//
//  Created by Kiran Vangara on 09/06/17.
//  Copyright © 2017 Connect Arena. All rights reserved.
//

#import <VoxSDK/VoxSDK.h>

#pragma mark - SIP Extensions of CSClient

@interface CSClient ()

/*!
 
 @brief Register with SIP credentials.
 
 @param[in] username SIP Username
 
 @param[in] password SIP Password
 
 @param[in] brandPin SIP Brand Pin
 
 */

- (CSErrorCode) registerSIPUser:(NSString*)username
                       password:(NSString*)password
                       brandPin:(NSString*)brandPin;

/*!
 
 @brief Create a default Connect Account when directly 
        registering with SIP details.
 
 */

- (CSErrorCode) createAutoAccount;

/*!
 
 @brief Get Brand Name.
 
 @return Brand name.
 
 */
-(NSString*) getBrandName;

/*!
 
 @brief Get Balance Url.
 
 @return Balance url.
 
 */
-(NSString*) getBalanceUrl;

/*!
 
 @brief Get Brand Urls.
 
 @return dictionary of brand urls.
 
 */
-(NSDictionary*) getBrandUrl;

/*!
 
 @brief Request server for Brand Urls. 
        The response will be notified through
		"UpdateBrandUrlsNotification".
 
 @param[in] brandPin Brand Pin
 
 @return error code.
 
 */
-(CSErrorCode) fetchBrandUrls:(NSString*)brandPin;

@end
