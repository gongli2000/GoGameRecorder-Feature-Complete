//
//  EditWindowController.m
//  GoGameRecorder
//
//  Created by Larry on 6/30/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#import "EditWindowController.h"

@interface EditWindowController ()

@end

@implementation EditWindowController

-(id) awakeFromNib(
- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    if (self) {
        NSImage* image = [[NSImage alloc]
                          initWithContentsOfFile:@"/Users/macbookpro/test/image1.jpg"] ;
        
        [self.imageView setImage:image];
    }
    
    return self;
}

- (void)windowDidLoad
{
    [super windowDidLoad];
   
}
@end
