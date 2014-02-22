//
//  AppDelegate.m
//  GoGameRecorder
//
//  Created by Larry on 6/28/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//



#include "ViewController.h"



#import "AppDelegate.h"

@implementation AppDelegate
- (void)dealloc
{
    [super dealloc];
}

-(int) setboardsize{
    int boardsize[] ={9,13,19};
    int i;
    for(i=0;i< 3;i++){
        if([[[self.boardSize submenu] itemAtIndex:i] state] == NSOnState){
            self.viewController->_boardsize   = boardsize[i];
            break;
        }
    }
    return i;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    
    self.viewController =
    [[ViewController alloc] initWithNibName:@"ViewController" bundle:nil];
    
   [self.window.contentView addSubview:self.viewController.view];
    self.viewController.view.frame = ((NSView*)self.window.contentView).bounds;
    self.viewController.textViewForLog = self.textViewForLog;
    [self setboardsize];
 
    
}

- (IBAction)doAutoCalibrate:(id)sender {
    [self.viewController startAutoCalibrate:sender];
}

- (IBAction)doRecordGame:(id)sender {
    [self.viewController doRecordGame:sender];
}

- (IBAction)doStopRecordGame:(id)sender {
    [self.viewController stopRecording:sender];
}

- (IBAction)doContinueRecord:(id)sender {
    [self.viewController continueRecording:sender];
}

- (IBAction)doRecordSnapshots:(id)sender {
    [self.viewController recordSnapshots:sender];
}

- (IBAction)doStopRecordSnapshots:(id)sender {
    [self.viewController stopRecording:sender];
}

- (IBAction)doContinueRecodSnapshots:(id)sender {
   [self.viewController continueRecordingSnaphots:sender];
}
- (IBAction)doEditSnapshots:(id)sender {
    [self.viewController editSnapshots:sender];
}
- (IBAction)doExportSGF:(id)sender {
    [self.viewController savetoSGF:sender];
}

- (IBAction)doRotateBoard:(id)sender
{
    [self.viewController rotateBoard:sender];
}
- (IBAction)doResetSavedView:(id)sender
{
    [self.viewController resetSavedView:sender];
}

- (IBAction)doManualCalibration:(id)sender {
    [self.viewController doManualCalibration:sender];
}

- (IBAction)handleNavigateMenus:(id)sender {
    [self.viewController handleNavigateMenus: sender];
}

- (IBAction)handleBoardSizeMenus:(id)sender {
    int selected = [self setboardsize];
    [[[self.boardSize submenu] itemAtIndex:selected] setState:NSOffState];
    [(NSMenuItem*)sender setState:NSOnState];
}

-(IBAction) handleWhoseMoveMenu:(id)sender
{
    NSMenuItem* item = (NSMenuItem*)sender;
    NSMenu* movemenu = [[item parentItem] submenu];
    [item setState:NSOnState];
    int index = [item tag] == 0 ? 1:0;
    [[movemenu itemAtIndex:index] setState:NSOffState];
    self.viewController->_blacksmove  = [[movemenu itemAtIndex:0] state] == NSOnState;
    
}
@end
