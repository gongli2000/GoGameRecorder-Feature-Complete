//
//  MyImageView.h
//  GoGameRecorder
//
//  Created by Larry on 7/1/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Board.h"

@interface MyImageView : NSImageView
{
    @public
    Board _board;
    bool _drawmoves;
    bool _drawboard;
    bool _blacksmove;
    bool _clickonstone;
    bool _dragged;
    int _saverow;
    int _savecol;
    Node* _node;

}
-(void) doinit:(int)boardsize setdraw:(bool)setdraw blacksmove:(bool)bm;

-(void) updateBoard:(bool)drawmoves currentMove: (int) n;
-(void) drawMove:(bool)isblack x:(float)x y:(float)y;
-(void) drawBoard;
- (void) drawGrid;
-(void)  drawMoves:(int)lastmoveIndex;
-(void) setDraw:(bool)draw;
-(void) setCurrentMove:(int) i;
-(void) setColor:(bool) bm;

@property (assign) NSTrackingRectTag trackingRect;

@end
