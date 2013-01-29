//
//  main.m
//  iphone
//
//  Created by Walzer on 10-11-16.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

int main(int argc, char *argv[]) {
    
    const char *prefix = "GCOV_PREFIX";
    const char *prefixValue = [[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] cStringUsingEncoding:NSASCIIStringEncoding]; // This gets the filepath to the app's Documents directory
    const char *prefixStrip = "GCOV_PREFIX_STRIP";
    const char *prefixStripValue = "1";
    setenv(prefix, prefixValue, 1); // This sets an environment variable which tells gcov where to put the .gcda files.
    setenv(prefixStrip, prefixStripValue, 1); // This tells gcov to strip the default prefix, and use the filepath that we just declared.
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, @"AppController");
    [pool release];
    return retVal;
}
