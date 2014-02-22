//
//  AppDelegate.h
//  GoGameRecorder
//
//  Created by Larry on 6/28/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (assign) IBOutlet NSMenuItem *boardSize;

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet NSScrollView *textLogView;
@property (assign) IBOutlet NSTextView *textViewForLog;

- (IBAction)doitem:(id)sender;
- (IBAction)doAutoCalibrate:(id)sender;
- (IBAction)doRecordGame:(id)sender;
- (IBAction)doStopRecordGame:(id)sender;
- (IBAction)doContinueRecord:(id)sender;
- (IBAction)doRecordSnapshots:(id)sender;
- (IBAction)doStopRecordSnapshots:(id)sender;
- (IBAction)doContinueRecodSnapshots:(id)sender;
- (IBAction)doEditSnapshots:(id)sender;
- (IBAction)doExportSGF:(id)sender;
- (IBAction)doRotateBoard:(id)sender;
- (IBAction)doResetSavedView:(id)sender;
- (IBAction)doManualCalibration:(id)sender;
- (IBAction)handleNavigateMenus:(id)sender;
- (IBAction)handleBoardSizeMenus:(id)sender;
-(IBAction) handleWhoseMoveMenu:(id)sender;



@property (nonatomic,strong) IBOutlet ViewController *viewController;

@end
