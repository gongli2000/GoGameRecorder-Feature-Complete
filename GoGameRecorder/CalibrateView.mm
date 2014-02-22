//
//  CalibrateView.m
//  GoGameRecorder
//
//  Created by Larry on 7/7/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#import "CalibrateView.h"
#import "NSImage+OpenCV.h"

@implementation CalibrateView

-(void) clearBoardRect{
    self->_boardRect.clear();
    [self setNeedsDisplay:true];
}
-(void) setBoardRect: (std::vector<cv::Point>&) rects
{
    self->_boardRect = rects;
    [self setNeedsDisplay:true];
    
}
- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}


- (void) drawline:(NSPoint) startPoint to: (NSPoint) endPoint{
    NSBezierPath * path = [NSBezierPath bezierPath];
    [path setLineWidth: 1];
    [path  moveToPoint: startPoint];
    [path lineToPoint:endPoint];
    [[NSColor blackColor] set];
    [path stroke];
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect:dirtyRect];
    std::vector<CGPoint> pts;
    if(self.image != NULL && self->_boardRect.size() > 0){
        cv::Mat image = [self.image CVGrayscaleMat];
        NSBezierPath * path = [NSBezierPath bezierPath];
        [path setLineWidth: 3];
        
        [path  moveToPoint: [NSImage image2Screen:image :[self bounds] : self->_boardRect[0]]];
        for(int i=1;i< self->_boardRect.size();i++){
            [path lineToPoint: [NSImage image2Screen:image :[self bounds] : self->_boardRect[i]]];
        }
        [path lineToPoint: [NSImage image2Screen:image :[self bounds] : self->_boardRect[0]]];
        [[NSColor blackColor] set];
        [path stroke];
    }
}

-(int) findPtBdRectClose2MouseDown:(NSPoint) mouseloc{
    int index=-1;
    cv::Mat image = [self.image CVGrayscaleMat];
    for(int i=0; i< self->_boardRect.size();i++){
       NSPoint p = [NSImage image2Screen:image :[self bounds] : self->_boardRect[i]];
      float dist = (mouseloc.x-p.x)*(mouseloc.x-p.x) + (mouseloc.y-p.y)*(mouseloc.y-p.y);
        if(dist < 30){
            index=i;
            break;
        }
    }
    return index;
}

-(void) mouseDragged:(NSEvent *)theEvent
{
     NSPoint mouseLoc;
}


- (void)mouseDown:(NSEvent *)e {
    BOOL keepOn = YES;
    cv::Mat image = [self.image CVGrayscaleMat];
    e = [[self window] nextEventMatchingMask: NSLeftMouseUpMask | NSLeftMouseDraggedMask];
    self._mouseLoc = [self convertPoint:[e locationInWindow] fromView:nil];
    int i = [self findPtBdRectClose2MouseDown:self._mouseLoc];
    
    while (keepOn) {
        e = [[self window] nextEventMatchingMask: NSLeftMouseUpMask | NSLeftMouseDraggedMask];
        self._mouseLoc = [self convertPoint:[e locationInWindow] fromView:nil];
        if(i >= 0){
            self->_boardRect[i] = [NSImage screen2Image:image :[self bounds] :self._mouseLoc];
            [self setNeedsDisplay:true];
        }
        
        switch ([e type]) {
            case NSLeftMouseDragged:
                break;
            case NSLeftMouseUp:
                [viewcontroller doManualCalibration:nil ];
                keepOn = NO;
                break;
            default:
                break;
        }
    };
    return;
}

- (void)mouseEntered:(NSEvent *)theEvent {
    
}



- (void)mouseMoved:(NSEvent *)theEvent {
    
    
    
}



- (void)mouseExited:(NSEvent *)theEvent {
    
    
    
}
- (void)viewDidMoveToWindow {
    
    // trackingRect is an NSTrackingRectTag instance variable
    
    // eyeBox is a region of the view (instance variable)
    
    self.trackingRect = [self
                         addTrackingRect:NSMakeRect(0,0, 500, 500)
                         owner:self
                         userData:NULL
                         assumeInside:NO];
    
}

@end
