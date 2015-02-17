//
//  main.m
//  ahkeychaintest
//
//  Created by Eldon on 5/8/14.
//  Copyright (c) 2014 Eldon Ahrold. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AHKeychain.h"

AHKeychainItem *newItem(){
    AHKeychainItem *item = [[AHKeychainItem alloc] init];
    item.service = @"com.eeaapps.test.systemkc";
    item.label = @"AHKeychain Test System Keychain Item";
    item.account = @"daemonapp";
    return item;
}

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        NSError *error;

        // Save
        AHKeychainItem *item = newItem();
        item.password = @"mySy5kcpaSs";
        if(![[AHKeychain systemKeychain] saveItem:item error:&error]){
            NSLog(@"Save1 Error: %@",error.localizedDescription);
        }

        // Get
        AHKeychainItem *getItem = newItem();
        if(![[AHKeychain systemKeychain] getItem:getItem error:&error])
            NSLog(@"Get1 Error [%ld]: %@",error.code,error.localizedDescription);
        else
            NSLog(@"Password from Item: %@",getItem.password);

        // Re-save
        AHKeychainItem *item2 = newItem();
        item2.password = @"myNewSecret Password";
        if(![[AHKeychain systemKeychain] saveItem:item2 error:&error]){
            NSLog(@"Save2 Error: %@",error.localizedDescription);
        }

        // Get again
        AHKeychainItem *getItemAgain = newItem();
        if(![[AHKeychain systemKeychain] getItem:getItemAgain error:&error])
            NSLog(@"Get2 Error [%ld]: %@",error.code,error.localizedDescription);
        else
            NSLog(@"Password from Item: %@",getItemAgain.password);

        // Delete
        if(![[AHKeychain systemKeychain] deleteItem:newItem() error:&error])
            NSLog(@"Remove Error [%ld]: %@",error.code,error.localizedDescription);

    }
    return 0;
}

