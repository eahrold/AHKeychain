//  AHKeychain.h
//  AHKeychain
//
//  Created by Eldon Ahrold on 5/7/14.
//  https://github.com/eahrold/ahkeychain/
//
// This project is a derivative of SSKeychain https://github.com/soffes/sskeychain/
// And released under the same license.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <Foundation/Foundation.h>
#import <Security/Security.h>
#import "AHKeychainItem.h"

/**
 *  Keychain Domains
 */
typedef NS_ENUM(int, AHKeychainDomain) {
    /**
     *  Unset Domain
     */
    kAHKeychainDomainNotSet = -1,
    /**
     *  Indicates the user preference domain preferences.
     */
    kAHKeychainDomainUser = kSecPreferencesDomainUser,
    /**
     *  Indicates the system preference domain preferences.
     */
    kAHKeychainDomainSystem = kSecPreferencesDomainSystem,
    /**
     *  Indicates the shared preference domain preferences.
     */
    kAHKeychainDomainShared = kSecPreferencesDomainCommon,
    /**
     *  Indicates Indicates a dynamic search list.
     */
    kAHKeychainDomainDynamic = kSecPreferencesDomainDynamic,
};

/**
 *  Constant used for specifying system keychain
 */
extern NSString *const kAHKeychainSystemKeychain;

/**
 *  Constant used for specifying system keychain
 */
extern NSString *const kAHKeychainLoginKeychain;

/**
 *  Class for working with a specific keycahin
 */
@interface AHKeychain : NSObject

/**
 *  Name of, or full path to, keychain. kSecUseKeychain
 *  @discussion if setting full path, include .keychain file extension
 */
@property (copy, nonatomic) NSString *name;

/**
 *  Search domain used to locate keychains
 */
@property (nonatomic) AHKeychainDomain keychainDomain;

/**
 *  Status return of the last executed method.
 *  @discussion this is useful for seeing the result of initializer methods. See initializer methods for more info.
 */
@property (nonatomic, readonly) OSStatus keychainStatus;

/**
 *  A description of the current keychainStatus
 */
@property (copy, nonatomic, readonly) NSString *statusDescription;

#pragma mark - Modifying Keychain
/**
 *  Initialize keychain object to work with
 *
 *  @param name Name of, or full path to, keychain. kSecUseKeychain
 *  @discussion if setting full path, include .keychain file extension
 *
 *  @return initialized AHKeychain object ready for modification
 */
- (instancetype)initWithKeychain:(NSString *)name;

/**
 *  Create a new keychain at a path using password
 *
 *  @param path     full path where keychain should be created
 *  @param password password for the newly created keychain
 *
 *  @return A new keychain that you can start adding items to.
 *  @discussion if a keychain already exists at the requested path the return will be that object, with a keychainStatus of -1.  If you only want to use a new keychain, you look for this return code and handle accordingly.
 *  @note Useing this method will register the keychain with the user search domain
 */
- (instancetype)initCreatingNewKeychainAtPath:(NSString *)path password:(NSString *)password;

/**
 *  Create a new keychain at a path and display cocoa dialog prompting for password
 *
 *  @param path full path where keychain should be created
 *
 *  @return A new keychain that you can start adding items to.
 *  @discussion if a keychain already exists at the requested path the return will be that object, with a keychainStatus of -1.  If you only want to use a new keychain, you look for this return code and handle accordingly.
 *  @note Useing this method will register the keychain with the user search domain
 */
- (instancetype)initCreatingNewKeychainAtPath:(NSString *)path;

/**
 *  Create a new user keychain
 *
 *  @param name     name of the new keychain
 *  @param password password for the newly created keychain
 *
 *  @return A new AHKeychain that you can start adding items to.
 *  @discussion if a keychain with the name already exists the object returned will be that, with a keychainStatus of -1.  If you only want to use a new keychain, you look for this return code and handle accordingly.
 */
- (instancetype)initCreatingNewKeychain:(NSString *)name password:(NSString *)password;

/**
 *  Create a new user keychain and display cocoa dialog prompting for password
 *
 *  @param name name of the new keychain
 *
 *  @return A new AHKeychain that you can start adding items to.
 *  @discussion if a keychain with the name already exists the object returned will be that, with a keychainStatus of -1.  If you only want to use a new keychain, you look for this return code and handle accordingly.
 */
- (instancetype)initCreatingNewKeychain:(NSString *)name;

/**
 *  Change the password for the Keychain.
 *
 *  @param oldpass old/current password
 *  @param newpass new/desired password
 *  @param error   populated should error occur
 *
 *  @return YES on success, NO on failure
 */
- (BOOL)changeKeychainPassword:(NSString *)oldpass to:(NSString *)newpass error:(NSError **)error;

/**
 *  delete the Keychain.
 *  @warning this is destructive.  It will completely remove the specified keychain and all of the passwords/items included.
 *  @param error populated should error occur
 *
 *  @return YES on success, NO on failure
 */
- (BOOL)deleteKeychain:(NSError **)error;

/**
 *  Lock the keychain
 *
 *  @return YES if keychain was successfully locked
 */
- (BOOL)lock;
/**
 *  Unlock a keychain
 *
 *  @return YES if the keychain was successfully unlocked
 */
- (BOOL)unlock;

/**
 *  Unlock a keychain with a supplied password
 *
 *  @param password password used to unlock keychain
 *
 *  @return YES if the keychain was successfully unlocked
 */
- (BOOL)unlockWithPassword:(NSString *)password;

#pragma mark - Modifying Keychain Items
/**
 *  Save a new password item to the keychain
 *
 *  @param item  populated AHKeychainItem, requires service,account, and password
 *  @param error populated should error occur
 *
 *  @return YES on success, NO on failure
 */
- (BOOL)saveItem:(AHKeychainItem *)item error:(NSError **)error;
/**
 *  remove an item from the keychain
 *
 *  @param item  populated AHKeychainItem, requires service,account
 *  @param error populated should error occur
 *
 *  @return YES on success, NO on failure
 */
- (BOOL)deleteItem:(AHKeychainItem *)item error:(NSError **)error;
/**
 *  populate a AHKeychainItem with it's password data
 *
 *  @param item  populated AHKeychainItem, requires service,account
 *  @param error populated should error occur
 *
 *  @return YES on success, NO on failure
 *  @discussion if return is YES, you can get the password data by accessing item.password
 */
- (BOOL)getItem:(AHKeychainItem *)item error:(NSError **)error;

/**
 *  test wether a specific keychain item exists in the current keychain
 *
 *  @param item  populated AHKeychainItem, requires service,account
 *  @param error populated should error occur
 *
 *  @return YES if the keychain item exists, NO if not
 */
- (BOOL)findItem:(AHKeychainItem *)item error:(NSError **)error;
/**
 *  get all items in the current keychain
 *
 *  @param error populated should error occur
 *
 *  @return Array of all items in keychain
 */
- (NSArray *)findAllItems:(NSError **)error;

#pragma mark - Convenience Initializers
/**
 *  Convenience initializer for the "login" keychain in the user's home directory.
 *
 *  @return the default user keychain
 *  @discussion This is not a singleton.  If performing multiple actions on a keychain create an instance using this.
 */
+ (AHKeychain *)loginKeychain;

/**
 *  Convenience initializer for the /Library/Keychains/System.keychain
 *
 *  @return the system keychain
 *  @discussion This is not a singleton.  If performing multiple actions on a keychain create an instance using this.
 */
+ (AHKeychain *)systemKeychain;

/**
 *  Convenience initializer for a keychain at a specific path
 *
 *  @param path full path to the keychain file including the .keychain extension
 *
 *  @return keychain at the path or nil if item doesn't exist
 *  @discussion This is not a singleton.  If performing multiple actions on a keychain create an instance using this.
 */
+ (AHKeychain *)keychainAtPath:(NSString *)path;

/**
 *  Convenience initializer for a keychain at a specific path
 *
 *  @param name name of the user keycahin item
 *
 *  @return keychain item located in the user's ~/Library/Keycahin/ directory, or nil if the item doesn't exist.
 *  @discussion This is not a singleton.  If performing multiple actions on a keychain create an instance using this.
 */
+ (AHKeychain *)keychainWithName:(NSString *)name;

#pragma mark - Class Methods
/**
 *  Set A Keychain Password
 *
 *  @param password    password for keychain itme
 *  @param service     service name for keychain itme
 *  @param account     account name for keychain itme
 *  @param keychain    either path for the keychain, keychain name constant, or initialized AHKeychain object
 *  @param trustedApps array of full paths to trusted apps that should be granted access to the keychain
 *  @param error       populated error object should error occur
 *
 *  @return YES if password was successfully set, NO on failure
 */
+ (BOOL)setPassword:(NSString *)password
            service:(NSString *)service
            account:(NSString *)account
           keychain:(id)keychain
        trustedApps:(NSArray *)trustedApps
              error:(NSError **)error;

/**
 *  Set A Keychain Password
 *
 *  @param password    password for keychain itme
 *  @param service     service name for keychain itme
 *  @param account     account name for keychain itme
 *  @param keychain    either path for the keychain, keychain name constant, or initialized AHKeychain object
 *  @param error       populated error object should error occur
 *
 *  @return YES if password was successfully set, NO on failure
 */
+ (BOOL)setPassword:(NSString *)password
            service:(NSString *)service
            account:(NSString *)account
           keychain:(id)keychain
              error:(NSError **)error;

/**
 *  Get the password for a specific keychain
 *
 *  @param service     service name for keychain itme
 *  @param account     account name for keychain itme
 *  @param keychain    either path for the keychain, keychain name constant, or initialized AHKeychain object
 *  @param error       populated error object should error occur
 *
 *  @return Password for specified keychain item
 */
+ (NSString *)getPasswordForService:(NSString *)service
                            account:(NSString *)account
                           keychain:(id)keychain
                              error:(NSError **)error;

/**
 *  Remove password for specific keychain item
 *
 *  @param service     service name for keychain itme
 *  @param account     account name for keychain itme
 *  @param keychain    either path for the keychain, keychain name constant, or initialized AHKeychain object
 *  @param error       populated error object should error occur
 *
 *  @return YES if password was successfully set, NO on failure
 */
+ (BOOL)removePasswordForService:(NSString *)service
                         account:(NSString *)account
                        keychain:(id)keychain
                           error:(NSError **)error;

/**
 *  Check if a keychain exists at the given path
 *
 *  @param path     Path to test
 *
 *  @return YES if a keychain exists at the path
 *
 *  @note This will accomidate variances in sierra where keychain path is appended with -db
 */
+ (BOOL)keychainExistsAtPath:(NSString *)path;
@end
