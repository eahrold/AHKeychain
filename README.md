##AHKeychain
###Objective-c Class for working accessing OSX keychains and keychain items.

_This is project is a derivative of SSKeychain https://github.com/soffes/sskeychain/_

The main added feature is the ability to specify which keychain to add to or get from, such as the system keychain or an Keychain on an external drive/SD card.

The other added feature is the ability to specify an Array of trusted apps granted access to the keychain item.

#####To specify the default login keychain
```Objective-c
    AHKeychain *keychain = [AHKeychain loginKeychain];
```
#####To specify the system keychain  
_*to write to this keychain you application needs to run as root_

```Objective-c    
    AHKeychain *keychain = [AHKeychain systemKeychain];
```

#####To specify a keychain at a particular path (external drive)
```Objective-c    
    AHKeychain *keychain = [AHKeychain keychainAtPath:@"/Volumes/MyExternalHD/Library/Keychains/myextkc.keychain"];
```

#####or to create a new user keychain
```Objective-c  
	AHKeychain *keychain = [AHKeychain alloc]initCreatingNewKeychain:@"Test Keychain"
    														password:@"realfakepsswd"];
```
#####then to add/update an item in the keychain
```Objective-c  
	AHKeychainItem *item = [AHkeychainItem alloc]init];
    item.service = @"com.eeaapps.test";
    item.account = @"myusername";
	item.label = @"AHKeychain Test Keychain Item";
    item.password = @"mysecretpass";

	// also if you want to allow other app to access the keychain item
    NSArray *trustedApps = [NSArray arrayWithObjects:@"/Applications/Mail.app",
                                                     @"/Applications/Preview.app",
                      								 nil];
    item.trustedApplications = trustedApps;

    
    [keychain saveItem:item error:&error];
```

#####or to get it's password
```Objective-c  
	AHKeychainItem *item = [AHkeychainItem alloc]init];
    item.service = @"com.eeaapps.test";
    item.account = @"myusername";
    
    [keychain getItem:item error:&error];
	
    NSLog(@"The Password is %@",item.password);
```

#####to remove a keychain item 
```Objective-c  
	AHKeychainItem *item = [AHkeychainItem alloc]init];
    item.service = @"com.eeaapps.test";
    item.account = @"myusername";
    [keychain deleteItem:item error:&error];
```

#####And finally to remove the keychain file a keychain. It's Destructive.  
_*you cannot delete either the login keychain or the system keychain_
```Objective-c  
	[keychain deleteKeychain];
```
====

##Class Methods for connivence
_you can specify kAHKeychainLoginKeychain, kAHKeychainSystemKeychain, or a full path to the keychain_
#####Setting a password
```Objective-c  
    [AHKeychain setPassword:@"mysecretpass" 
    				service:@"com.eeaapps.testkc" 
                    account:@"myusername" 
                   keychain:kAHKeychainLoginKeychain 
                      error:&error];
```

#####Getting a password
```
    NSError *error;    
    NSString *password = [AHKeychain getPasswordForService:item.service
                                                   account:item.account
                                                  keychain:kAHKeychainLoginKeychain
                                                     error:&error];
                                                     
    NSLog(@"The Password is %@",item.password);
```
