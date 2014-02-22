//
//  MyImageView.m
//  GoGameRecorder
//
//  Created by Larry on 7/1/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#import "MyImageView.h"


@implementation MyImageView

-(void) doinit:(int)boardsize setdraw:(bool)setdraw blacksmove:(bool)bm{
    [self setDraw:setdraw];
    _board.init(boardsize);
    self->_blacksmove = bm;
    self->_node = [[Node alloc] init];
    self->_node->groupNum=0;
    [self setNeedsDisplay:true];
}
- (id)initWithFrame:(NSRect)frame
{
    _drawboard=false;
    _drawmoves=true;
    _node= NULL;
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}



-(void) updateBoard:(bool)drawmoves currentMove: (int) n{
    
    if(n<0){
        _board.setCurrentMove(_board.moves.size());
    }else{
        _board.setCurrentMove(n);
    }
    _drawmoves=drawmoves;
    [self setNeedsDisplay:true];
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect:dirtyRect];
    if(_drawboard){
        [self drawGrid];
        if(_drawmoves){
            [self drawMoves: _board._currentMoveIndex];
        }else{
            [self drawBoard];
        }
        if(self->_node != NULL && self->_node->groupNum ==-1){
            [self drawMove:self->_node->isblack x:self->_node->coord.x y:self->_node->coord.y];
        }
    }
    
}
-(void) setColor:(bool)bm{
    self->_blacksmove=bm;
}
-(void) setCurrentMove:(int) i{
    _board.setCurrentMove(i);
    [self setNeedsDisplay:YES];
}
-(void) drawcircle:(NSColor*)color p:(NSPoint)p  radius: (NSPoint) radius dxy:(NSPoint) dxy
{
    float dx = dxy.x;
    float dy = dxy.y;
    NSRect rect = NSMakeRect(dx+p.x*dx-radius.x/2,dy+p.y*dy-radius.y/2,radius.x,radius.y);
    NSBezierPath* path = [NSBezierPath bezierPath];
    [color set];
    [path appendBezierPathWithOvalInRect: rect];
    [path fill];
}

- (void) drawline:(NSPoint) startPoint to: (NSPoint) endPoint{
    NSBezierPath * path = [NSBezierPath bezierPath];
    [path setLineWidth: 1];
    [path  moveToPoint: startPoint];
    [path lineToPoint:endPoint];
    [[NSColor blackColor] set];
    [path stroke];
}

- (void) drawGrid
{
    NSColor *boardcolor = [self boardColor:255.0f green:204.0f blue:102.0f];
    [boardcolor setFill];
    NSRectFill([self bounds]);
    float stardel ;
    float width = self.bounds.size.width;
    float height = self.bounds.size.height;
    int boardsize = _board.boardData.size();
    int bs = _board.boardData.size()+1;
    float dx = round(width/bs);
    float dy = round(height/bs);
    if(boardsize == 9){
        stardel = 3;
    }else{
        stardel = 4;
    }
    
    for(int i=1;i< bs;i++){
        [self drawline: NSMakePoint(dx,dy*i) to: NSMakePoint(dx*(bs-1),dy*i)];
        [self drawline: NSMakePoint(dx*i,dy) to: NSMakePoint(dx*i,dy*(bs-1))];
        
    }
    float b2 = floor(boardsize/2.0);
    float startpts19[] = {stardel-1,b2,boardsize-stardel};
    float startpts9[] = {stardel-1,boardsize-stardel};
    float *startpts;
    int ns;
    if(boardsize == 19){
        startpts = startpts19;
        ns = 3;
    }else{
        startpts = startpts9;
        ns=2;
    }
    for(int  k = 0; k < ns;k++){
        int rowstar = startpts[k];
        for(int j = 0; j < ns ; j++){
            int colstar = startpts[j];
            [self drawcircle:
                      [NSColor blackColor]
                      p:NSMakePoint(colstar,rowstar)
                      radius:NSMakePoint(dx/2,dy/2)
                      dxy:NSMakePoint(dx,dy) ];
        }
    }
    [self setNeedsDisplay:true];
}



-(void) drawBoard{
    float width = self.bounds.size.width;
    float height = self.bounds.size.height;
    int bs = _board.boardData.size()+1;
    float dx = round(width/bs);
    float dy = round(height/bs);
    for(int i=0;i< _board.boardData.size() ;i++){
        for(int j=0; j< _board.boardData.size() ;j++){
            if(_board.boardData[i][j]!=0){
                [self drawcircle:
                    (_board.boardData[i][j]<0)? [NSColor blackColor] : [NSColor whiteColor]
                    p:NSMakePoint(j,bs-i-2)//(i,bs-j-2)
                    radius:NSMakePoint(dx,dy)
                    dxy:NSMakePoint(dx,dy)];
            }
        }
    }
    [self setNeedsDisplay:true];
}

-(void) drawMove:(bool)isblack x:(float)x y:(float)y{
    float width = self.bounds.size.width;
    float height = self.bounds.size.height;
    int bs = _board.boardData.size()+1;
    float dx = round(width/bs);
    int dy = round(height/bs);
    [self drawcircle:
        isblack? [NSColor blackColor]: [NSColor whiteColor]
        p:NSMakePoint(x, bs-y-2)//y,bs-x-2)//(i,bs-j-2)
        radius:NSMakePoint(dx*.9,dy*.9)
        dxy:NSMakePoint(dx,dy)];
    [self setNeedsDisplay:true];
}



-(void)drawMoves:(int)lastmoveIndex{
    int i=0;
    for(list<Node*>::iterator move=_board.moves.begin(); move!=_board.moves.end(); move++)
    {
        if(i++ == lastmoveIndex)break;
        [self drawMove: (**move).isblack   x:(**move).coord.x y:(**move).coord.y];
        
    }
    [self setNeedsDisplay:true];
}


-(NSColor*) boardColor:(float)red green:(float) green blue:(float)blue
{
    return [NSColor
            colorWithCalibratedRed:red/255.0
            green:green/255.0
            blue:blue/255.0
            alpha:1.0f];
}

-(void) setDraw:(bool)draw
{
    _drawboard=draw;
    [self setNeedsDisplay:true];
}


- (void)mouseDown:(NSEvent *)theEvent {
    float width ;
    float height ;
    int bs;
    float dx ;
    float dy ;
    NSPoint savemouseLoc = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    width = self.bounds.size.width;
    height = self.bounds.size.height;
    bs = (int)_board.boardData.size()+1;
    dx = round(width/bs);
    dy = round(height/bs);
    _saverow = bs-round(savemouseLoc.y/dy)-1;
    _savecol = round(savemouseLoc.x/dx)-1;
    if(_node==NULL)return;
    
  
    _clickonstone=false;
    bool isblack;
    if(_saverow >=0 && _saverow < _board.boardData.size() &&
       _savecol>=0 && _savecol <_board.boardData.size())
    {
        int val = _board.boardData[_saverow][_savecol] ;
        _clickonstone = val !=0;
        if( _clickonstone){
            _blacksmove= val < 0;
            _node->isblack = _blacksmove;
            _node->groupNum = -1;
            _node->coord = cv::Point(_savecol,_saverow);
        }
    }
}

-(void) mouseDragged:(NSEvent *)theEvent{
    _dragged=true;
    if(_node==NULL)return;
    if(_clickonstone){
        NSPoint mouseLoc = [self convertPoint:[theEvent locationInWindow] fromView:nil];
        float width = self.bounds.size.width;
        float height = self.bounds.size.height;
        int bs = (int)_board.boardData.size()+1;
        float dx = round(width/bs);
        float dy = round(height/bs);
        int row = bs-round(mouseLoc.y/dy)-1;
        int col = round(mouseLoc.x/dx)-1;
        _node->groupNum=-1;
        _node->isblack = _blacksmove;
        _node->coord = cv::Point(col,row);
        [self setNeedsDisplay:true];
        
    }
}

-(void) mouseUp:(NSEvent*) theEvent{
    _node->groupNum=0;
    if(_dragged){
        if(_clickonstone){
            if(_node==NULL)return;
            float width = self.bounds.size.width;
            float height = self.bounds.size.height;
            int bs = (int)_board.boardData.size()+1;
            float dx = round(width/bs);
            float dy = round(height/bs);
            NSPoint mouseLoc = [self convertPoint:[theEvent locationInWindow] fromView:nil];
            int row = bs-round(mouseLoc.y/dy)-1;
            int col = round(mouseLoc.x/dx)-1;
            
            bool moved=_board.movestone(_saverow,_savecol,row,col);
            if(!moved){
                NSAlert* msgBox = [[[NSAlert alloc] init] autorelease];
                [msgBox setMessageText: @"Can't move a stone to existing stone"];
                [msgBox addButtonWithTitle: @"OK"];
                [msgBox runModal];
            }
        }
    }
    else{
        if(_clickonstone){
            _board.removestone(cv::Point(_savecol,_saverow));
            list<Node*>::iterator movepos = _board.findmove(_saverow,_savecol);
            _board.moves.erase(movepos);
        }else{
            BOOL shiftkeydown = (([[NSApp currentEvent] modifierFlags] & NSShiftKeyMask) == NSShiftKeyMask);
            _board.domove(shiftkeydown?StoneColor::WHITE:StoneColor::BLACK, cv::Point(_savecol,_saverow));
        }
    }
    _dragged=false;
    [self setNeedsDisplay:true];
   
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
