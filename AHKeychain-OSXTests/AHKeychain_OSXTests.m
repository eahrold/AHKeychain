//
//  AHKeychain_OSXTests.m
//  AHKeychain-OSXTests
//
//  Created by Eldon on 5/6/14.
//  Copyright (c) 2014 Eldon Ahrold. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "AHKeychain.h"

@interface AHKeychain_OSXTests : XCTestCase{
    AHKeychainItem *item;
}

@end

@implementation AHKeychain_OSXTests{
}

- (void)setUp
{
    [super setUp];
    [self buildKeychainItem];
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testExample
{
    XCTFail(@"No implementation for \"%s\"", __PRETTY_FUNCTION__);
}

-(void)testClassSet{
    NSError *error;
    BOOL rc = [AHKeychain setPassword:item.password
                              service:item.service
                              account:item.account
                             keychain:kAHKeychainLoginKeychain
                                error:&error];
    XCTAssertTrue(rc, @"Unable to save item: %@", error);
}

-(void)testClassGet{
    NSError *error;
    NSString *password = [AHKeychain getPasswordForService:item.service
                                                   account:item.account
                                                  keychain:kAHKeychainLoginKeychain
                                                     error:&error];
    
    XCTAssertTrue(password != nil, @"Unable to get item: %@", error);
}

- (void)testAddWithTrustedApps
{
    NSError *error;
    item.trustedApplications = @[@"/Applications/Mail.app",@"/Applications/Preview.app" ];
    XCTAssertTrue([[AHKeychain loginKeychain] saveItem:item error:&error], @"Unable to save item: %@", error);
}

- (void)testAddToSystemKeychainAsNonRoot
{
    NSError *error;
    XCTAssertFalse([[AHKeychain systemKeychain] saveItem:item error:&error]);
    if(error) NSLog(@"%@",error);
}

- (void)testAdd
{
    NSError *error;
    XCTAssertTrue([[AHKeychain loginKeychain] saveItem:item error:&error], @"Unable to save item: %@", error);
}

-(void)testFind
{
    NSError *error;
    XCTAssertTrue([[AHKeychain loginKeychain] findItem:item error:&error], @"Unable to find item: %@", error);
}

- (void)testRemove
{
    NSError *error;
    XCTAssertTrue([[AHKeychain loginKeychain] deleteItem:item error:&error], @"Unable to remove item: %@", error);

}

-(void)testFindShouldFail
{
    NSError *error;
    XCTAssertFalse([[AHKeychain loginKeychain] findItem:item error:&error], @"Unable to find item: %@", error);
}

- (void)testRemoveShouldFail
{
    NSError *error;
    XCTAssertFalse([[AHKeychain loginKeychain] deleteItem:item error:&error], @"Unable to remove item: %@", error);
}


-(void)testCreateKeycahinAtInit{
    NSError *error;
    BOOL rc;
    AHKeychain *keychain = [[AHKeychain alloc]initCreatingNewKeychain:@"Test Keychain" password:@"realfakepsswd"];
    
    XCTAssertTrue(keychain.keychainStatus == errSecSuccess, @"error creating keycahin %@",keychain.statusDescription);
    
    if(keychain.keychainStatus <= 0){        
        item.password = @"theinitialpassword";

        rc = [keychain saveItem:item error:&error];
        XCTAssertTrue(rc, @"Unable to save item to Keychain: %@",error.localizedDescription);
       
        item.password = @"updated_password";
        
        rc = [keychain saveItem:item error:&error];
        XCTAssertTrue(rc, @"Unable to update item in Keychain: %@",error.localizedDescription);
        
        rc = [keychain getItem:item error:&error];
        XCTAssertTrue(rc, @"Unable to fetch item from keychain: %@",error.localizedDescription);

        
        XCTAssertFalse([item.password isEqualToString:@"theinitialpassword"], @"These shouldn't match");

        rc = [keychain deleteItem:item error:&error];
        XCTAssertTrue(rc, @"Unable to remove item from keychain: %@",error.localizedDescription);

        rc = [keychain getItem:item error:&error];
        XCTAssertFalse(rc, @"The keychain item should has been removed, but it's still there oopps : %@",error.localizedDescription);

        rc = [keychain deleteKeychain:&error];
        XCTAssertTrue(rc, @"Unable to delete Keychain: %@",error.localizedDescription);
    }

}


-(void)buildKeychainItem{
    item = [[AHKeychainItem alloc]init];
    item.service = @"com.eeaapps.test";
    item.label = @"AHKeychain Test Keychain Item";
    item.account = @"frowbrow";
    item.password = @"mysecretpasslogin";
    
}


@end
