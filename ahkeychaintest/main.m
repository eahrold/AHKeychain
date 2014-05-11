//
//  main.m
//  ahkeychaintest
//
//  Created by Eldon on 5/8/14.
//  Copyright (c) 2014 Eldon Ahrold. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AHKeychain.h"

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        NSError *error;
        AHKeychainItem *item = [[AHKeychainItem alloc]init];
        item.service = @"com.eeaapps.test.systemkc";
        item.label = @"AHKeychain Test System Keychain Item";
        item.account = @"daemonapp";
        item.password = @"mySy5kcpaSs";
        
        if(![[AHKeychain systemKeychain] saveItem:item error:&error]){
            NSLog(@"Save Error: %@",error.localizedDescription);
        }
        
        item.password = nil;
        
        if(![[AHKeychain systemKeychain] getItem:item error:&error])
            NSLog(@"Get Error [%ld]: %@",error.code,error.localizedDescription);
        else
            NSLog(@"Password from Item: %@",item.password);
        
//        if(![[AHKeychain systemKeychain] deleteItem:item error:&error])
//            NSLog(@"Remove Error [%ld]: %@",error.code,error.localizedDescription);
        
    }
    return 0;
}

