//
//  AnchorView.m
//  GoGameRecorder
//
//  Created by Larry on 7/7/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#import "AnchorView.h"

@implementation AnchorView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect:dirtyRect];
    float xpos = 0,ypos=0;
    float r = 0, g=0,b=0;

 
    
    NSPoint textPoint = NSMakePoint(xpos, ypos);
    NSMutableDictionary *textAttrib = [[NSMutableDictionary alloc] init];
    [textAttrib setObject:[NSFont fontWithName:@"Menlo" size:11] forKey:NSFontAttributeName];
    [textAttrib setObject:
     [NSColor colorWithCalibratedRed:(r/255.0f)
                               green:(g/255.0f)
                               blue:(b/255.0f)
                               alpha:1.0]
                forKey:NSForegroundColorAttributeName];
    [[self identifier] drawAtPoint:textPoint withAttributes:textAttrib];
   
}


@end
