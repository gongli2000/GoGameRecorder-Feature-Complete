////
////  ddd.cpp
////  GoGameRecorder
////
////  Created by Larry on 7/4/13.
////  Copyright (c) 2013 Larry. All rights reserved.
////
//
//#include "ddd.h"
////
////  ViewController.m
////  GoGameRecorder
////
////  Created by Larry on 6/29/13.
////  Copyright (c) 2013 Larry. All rights reserved.
////
//#include "float.h"
//#import "ViewController.h"
//#import "NSImage+OpenCV.h"
//
//#include "ImageUtils.mm"
//#import "Node.h"
//
//enum {LEFT,BOTTOM,RIGHT,TOP};
//
//
//static int group=1;
//
//
//@interface ViewController ()
//
//@end
//
//@implementation ViewController
//
//
//
//void makeBoardArray(int boardsize, std::vector<std::vector<int>> &board){
//    board.resize(boardsize);
//    for(int i=0;i<boardsize;i++){
//        board[i].resize(boardsize);
//        for(int j=0;j<boardsize;j++){
//            board[i][j]=0;
//        }
//    }
//}
//void getContourCentroid(std::vector<cv::Point> contour, cv::Point &centroid){
//    CvMoments moments = cv::moments(contour);
//    double M00, M01, M10;
//    M00 = cvGetSpatialMoment(&moments,0,0);
//    M10 = cvGetSpatialMoment(&moments,1,0);
//    M01 = cvGetSpatialMoment(&moments,0,1);
//    centroid.x = M10/M00;
//    centroid.y = M01/M00;
//    
//}
//
//void getContoursForMove(cv::Mat &image,
//                        cv::Mat pmap,
//                        std::vector<std::vector<cv::Point> > &contours,
//                        std::vector<cv::Vec4i> &hierarchy){
//    
//    cv::Mat diff2clone = image.clone();
//    findContours(diff2clone, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
//}
//
//void drawMoves(cv::Mat &boardImage,cv::Mat& curImage, std::vector<Node*> &moves,int boardsize,int lastmoveIndex){
//    int bs = boardsize+1;
//    int dx = round(curImage.cols/bs);
//    int dy = round(curImage.rows/bs);
//    float radius= min(dx/2.1,dy/2.1);
//    std::vector<std::vector<int> > board;
//    std::vector<std ::vector<cv::Point> > blackGroups;
//    std::vector<std ::vector<cv::Point> > whiteGroups;
//    std::vector<int> blacklibs;
//    std::vector<int> whitelibs;
//    
//    for(int i=0;i < lastmoveIndex;i++){
//        
//        
//        cv::Point p(moves[i]->coord.x*dx+dx, moves[i]->coord.y*dy+dy);
//        
//        if(moves[i]->isblack){
//            cv::circle(boardImage, p, radius, CV_RGB(0,0,0),-1);
//        }else{
//            cv::circle(boardImage, p, radius, CV_RGB(255,255,255),-1);
//        }
//    }
//}
//
//
//
//void drawMove(cv::Mat &boardImage,int boardsize, cv::Mat &curImage,Node* move){
//    
//    int bs = boardsize+1;
//    int dx = round(curImage.cols/bs);
//    int dy = round(curImage.rows/bs);
//    float radius= min(dx/2.1,dy/2.1);
//    cv::Point p(move->coord.x*dx+dx, move->coord.y*dy+dy);
//    if(move->isblack){
//        cv::circle(boardImage, p, radius, CV_RGB(0,0,0),-1);
//    }else{
//        cv::circle(boardImage, p, radius, CV_RGB(255,255,255),-1);
//    }
//    
//}
//cv::Mat drawBoard(cv::Mat curImage,int boardsize)
//{
//    int stardel ;
//    int bs = boardsize+1;
//    int dx = round(curImage.cols/bs);
//    int dy = round(curImage.rows/bs);
//    CvSize s = cvSize(bs*dx, bs*dy);
//    cv::Mat boardImage(s.height,s.width,matdatatypecolor,cv::Scalar(181,101,29));
//    if(boardsize == 9){
//        stardel = 3;
//    }else{
//        stardel = 4;
//    }
//    for(int i=1;i< bs;i++){
//        cv::line(boardImage, cv::Point(dx,dy*i), cv::Point(boardImage.cols-dx,dy*i), CV_RGB(255,255,255),2);
//        cv::line(boardImage, cv::Point(dx*i,dy), cv::Point(dx*i,boardImage.rows-dy), CV_RGB(255,255,255),2);
//    }
//    if(boardsize == 19){
//        int b2 = floor(boardsize/2.0);
//        int starpts[] = {stardel-1,b2,boardsize-stardel};
//        for(int  k = 0; k < 3;k++){
//            int rowstar = starpts[k];
//            for(int j = 0; j < 3 ; j++){
//                int colstar = starpts[j];
//                cv::circle(boardImage, cv::Point(dx+colstar*dx,dy+rowstar*dy), 4, CV_RGB(0,0,0),-1);
//            }
//        }
//    }else{
//        int starpts[] = {stardel-1,boardsize-stardel};
//        for(int  k = 0; k < 2;k++){
//            int rowstar = starpts[k];
//            for(int j = 0; j < 2 ; j++){
//                int colstar = starpts[j];
//                cv::circle(boardImage, cv::Point(dx+colstar*dx,dy+rowstar*dy), 4, CV_RGB(0,0,0),-1);
//            }
//        }
//    }
//    
//    
//    return boardImage;
//}
//void grabframe(VideoCapture *cap, Mat &theframe, int scale){
//    
//    
//    Mat frame,grayframe;
//    (*cap) >> frame;
//    
//    //grabframe(cap, frame);
//    cvtColor(frame, grayframe, CV_BGR2GRAY);
//    transpose(grayframe,theframe);
//    flip(theframe,theframe,0);
//    //cv::pyrDown(grayframe,theframe);
//    
//    float sigma = 1.0;
//    //GaussianBlur(theframe, theframe, Size(0,0), sigma, sigma);
//    
//    
//}
//
//void doErode( int erosion_size, Mat &src, Mat &dst )
//{
//    int types[] = {MORPH_RECT,MORPH_CROSS,MORPH_ELLIPSE};
//    
//    int erosion_elem =MORPH_RECT;
//    int erosion_type = types[erosion_elem];
//    
//    Mat element = getStructuringElement( erosion_type,
//                                        cv::Size( 2*erosion_size + 1, 2*erosion_size+1 ),
//                                        cv::Point( erosion_size, erosion_size ) );
//    erode( src, dst, element );
//    
//}
//int diffFrames(Mat &image1, Mat &image2, cv::Mat &diff){
//    absdiff(image1, image2, diff);
//    threshold(diff,diff,50,256,CV_THRESH_BINARY);
//    cv::erode(diff, diff, Mat(), cv::Point(-1,-1), 3);
//    cv::dilate(diff, diff, Mat(), cv::Point(-1,-1), 1);
//    return countNonZero(diff);
//}
///** @function Dilation */
//void doDilate( int dilation_size , Mat &src, Mat &dst )
//{
//    int types[] = {MORPH_RECT,MORPH_CROSS,MORPH_ELLIPSE};
//    int erosion_elem=MORPH_RECT;
//    int dilation_type = types[erosion_elem];
//    
//    Mat element = getStructuringElement( dilation_type,
//                                        cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),
//                                        cv::Point( dilation_size, dilation_size ) );
//    /// Apply the dilation operation
//    dilate( src, dst, element );
//}
//
//void findMaxAreaContour(std::vector<std::vector<cv::Point> > &contours, int &index, double &maxarea)
//{
//    maxarea = 0;
//    index =0;
//    
//    for(int i=0;i< contours.size();i++){
//        double area = cv::contourArea(contours[i]);
//        if(area > 100.0){
//            
//            if(area > maxarea ){
//                index=i;
//                maxarea = area;
//            }
//        }
//    }
//    
//}
//
//void writeImage2JPEG(cv::Mat image, string file){
//    
//}
//
//void findConvexHull(cv::Mat frame,std::vector<cv::Point> &maxAreaContour,std::vector<cv::Point> &convexHull)
//{
//    std::vector<cv::Point> hull;
//    cv::convexHull( maxAreaContour, hull, false );
//    
//    double peri = cv::arcLength(hull,true);
//    cv:: approxPolyDP( hull, convexHull, 0.01*peri, true );
//    
//    //    std::vector<std::vector<cv::Point> >  contours_poly;
//    //    contours_poly.push_back(convexHull);
//    //    cv::fillPoly(frame, contours_poly, CV_RGB(255,0,0));
//}
//
//cv::Mat getPerspectiveMap(cv::Size s, std::vector<cv::Point> &srcVec, int orientation){
//    int rightIndices[] = {0,1,2,3} ;
//    int botIndices[] = {1,2,3,0};
//    int leftIndices[] = {2,3,0,1};
//    int topIndices[] = {3,0,1,2};
//    int* indicesArray[] = {rightIndices,botIndices,leftIndices,topIndices};
//    int *indices = indicesArray[orientation];
//    cv::Point2f dst[]={
//        cv::Point2f(0,0),
//        cv::Point(s.width,0),
//        cv::Point(s.width,s.height),
//        cv::Point(0,s.height)};
//    cv::Point2f src[]={srcVec[indices[0]],srcVec[indices[1]],srcVec[indices[2]],srcVec[indices[3]]};
//    
//    return cv::getPerspectiveTransform(src,dst);
//}
//
//void drawpoly(Mat& inputImage, std::vector<cv::Point> transRect){
//    for(int i=0;i<transRect.size();i++){
//        cv::Point p = transRect[i];
//        cv::line(inputImage,p, transRect[(i+1)%transRect.size()],CV_RGB(255,0,0),2);
//    }
//    
//}
//void processFrame1( Mat &inputImage, std::vector<cv::Point> &transRect,std::vector<cv::Point> &convexHull,int orientation)
//{
//    Mat  outerBox,test;
//    Mat grayFrame = inputImage.clone();
//    
//    cv::adaptiveThreshold(grayFrame,grayFrame,255,1,1,11,2);
//    
//    std::vector<std::vector<cv::Point> > contours;
//    std::vector<cv::Vec4i> hierarchy;
//    //cv::Mat x = grayFrame.clone();
//    findContours(grayFrame, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
//    
//    
//    
//    int index;
//    double maxarea;
//    convexHull.clear();
//    findMaxAreaContour(contours,index,maxarea);
//    findConvexHull(grayFrame,contours[index],convexHull);
//    
//    
//    
//    transRect.clear();
//    for(int i=0;i<4;i++){
//        //cv::Point p = convexHull[indices[i]];
//        //cv::line(inputImage,p, convexHull[indices[(i+1)%4]],CV_RGB(255,0,0),2);
//        transRect.push_back(convexHull[i]);
//        
//    }
//    
//    
//    
//    
//}
//
//void initdiffminmax(int boardsize, int &diffmin , int &diffmax)
//{
//    switch(boardsize){
//        case 9:
//            diffmax = 3;
//            diffmin = 100;
//            break;
//        case 13:
//            diffmax =1200;
//            diffmin =100;
//            break;
//        case  19:
//            diffmax = 600;
//            diffmin = 20;
//            break;
//    }
//}
//
//-(void) initdata{
//    _docalibrate = true;
//    _orientation = RIGHT;
//    _currentMoveIndex   =0;
//    _moves.clear();
//    _blackGroups.clear();
//    _whiteGroups.clear();
//    int sizes[]={9,13,19};
//    _boardsize = sizes[self.boardSize.selectedSegment];
//    initdiffminmax(_boardsize,_diffmin,_diffmax);
//    makeBoardArray(_boardsize, _board);
//}
//
//- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
//{
//    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
//    if (self) {
//        [self initdata];
//        _videoCapture = new cv::VideoCapture(0);
//        if (!_videoCapture->open(CV_CAP_AVFOUNDATION))
//        {
//            NSLog(@"Failed to open video camera");
//        }
//        
//        self.runTimer = [NSTimer
//                         scheduledTimerWithTimeInterval:.1
//                         target:self
//                         selector:@selector(captureframeForLoop)
//                         userInfo:nil
//                         repeats:YES];
//    }
//    return self;
//}
//
//-(void) writeImage: (NSImage*)image toFile: (NSString*) file
//{
//    NSArray*  representations  = [image representations];
//    NSData* bitmapData = [NSBitmapImageRep
//                          representationOfImageRepsInArray: representations
//                          usingType: NSJPEGFileType properties:nil];
//    
//    [bitmapData writeToFile:file atomically:YES];
//}
//
//
//int findNumLiberties(std::vector< std::vector<int>> &board,
//                     std::vector< cv::Point> &group)
//{
//    std::set<int> pts;
//    int bs = (int)board.size();
//    for(int i=0;i< group.size();i++){
//        cv::Point &p = group[i];
//        int x[] = {p.x-1,p.x+1,p.x,p.x};
//        int y[] = {p.y,p.y,p.y-1,p.y+1};
//        for(int a =0;a<4;a++){
//            if(y[a] < 0 || y[a] >= bs || x[a] <0 || x[a] >= bs)continue;
//            if(board[y[a]][x[a]] == 0){
//                int val = y[a]*100+x[a];
//                cout << "found liberty at " << val << endl;
//                pts.insert(val);
//            }
//        }
//        
//    }
//    int kk = pts.size();
//    return (int)pts.size();
//}
//
//int findEnemyGroups(std::vector<std::vector<int>> &board,
//                    bool isblack,
//                    cv::Point p,
//                    std::set<int> &groups)
//{
//    int x[] = {p.x-1,p.x+1,p.x,p.x};
//    int y[] = {p.y,p.y,p.y-1,p.y+1};
//    
//    for(int i =0;i<4;i++){
//        if(x[i] <0 || x[i]>= board.size() || y[i] < 0 || y[i] >= board.size())continue;
//        int valueAtPoint = board[y[i]][x[i]];
//        if(valueAtPoint != 0){
//            if(isblack)
//            {
//                if(valueAtPoint > 0){
//                    groups.insert(valueAtPoint-1);
//                }
//            }else{
//                if(valueAtPoint < 0){
//                    groups.insert(-valueAtPoint-1);
//                }
//            }
//        }
//    }
//}
//
//int findGroups(std::vector<std::vector<int>> &board,
//               bool isblack,
//               cv::Point p,
//               std::vector<int> &groupsArray,
//               std::vector<int> &blacklibs,
//               std::vector<int> &whitelibs,
//               int &numlibs,
//               int &numfriends)
//{
//    std::set<int> groups;
//    int deadGroupIndex = -1;
//    int x[] = {p.x-1,p.x+1,p.x,p.x};
//    int y[] = {p.y,p.y,p.y-1,p.y+1};
//    
//    
//    numfriends = 0;
//    numlibs=4;
//    
//    
//    for(int i =0;i<4;i++){
//        if(x[i] <0 || x[i]>= board.size() || y[i] < 0 || y[i] >= board.size())continue;
//        int valueAtPoint = board[y[i]][x[i]];
//        if(valueAtPoint != 0){
//            numlibs--;
//            if(isblack){
//                if(valueAtPoint < 0){
//                    numfriends++;
//                    groups.insert(-valueAtPoint);
//                }else{
//                    whitelibs[valueAtPoint-1]--;
//                    if(whitelibs[valueAtPoint-1] == 0){
//                        deadGroupIndex=valueAtPoint-1;
//                    }
//                }
//            }else{
//                if(valueAtPoint > 0){
//                    numfriends++;
//                    groups.insert(valueAtPoint);
//                }else{
//                    blacklibs[-valueAtPoint-1]--;
//                    if(blacklibs[-valueAtPoint-1] == 0){
//                        deadGroupIndex = -valueAtPoint-1;
//                    }
//                }
//            }
//        }
//    }
//    
//    for(std::set<int>::iterator it = groups.begin(); it!= groups.end(); it++){
//        groupsArray.push_back(*it);
//    }
//    return deadGroupIndex;
//    
//}
//
//void handleDeadStones(
//                      std::vector< std::vector<int> > &board,
//                      std ::vector<cv::Point> &deadGroup,
//                      bool isblackmove,
//                      std::vector<int> &blacklibs,
//                      std::vector<int> &whitelibs)
//{
//    
//    std::set<int> enemyGroups;
//    for(int groupindex = 0; groupindex < deadGroup.size();groupindex++)
//    {
//        cv::Point &p = deadGroup[groupindex];
//        
//        findEnemyGroups(board, !isblackmove, p, enemyGroups);
//        int n = enemyGroups.size();
//        for(std::set<int> ::iterator i = enemyGroups.begin(); i!=enemyGroups.end(); i++){
//            if(isblackmove){
//                blacklibs[*i]++;
//            }else{
//                whitelibs[*i]++;
//                
//            }
//        }
//        
//        board[p.y][p.x]=0;
//    }
//}
//
//
//bool domove(std::vector< std::vector<int> > &board,
//            std::vector<std ::vector<cv::Point> > &blackGroups,
//            std::vector<std ::vector<cv::Point> > &whiteGroups,
//            std::vector<int> &blacklibs,
//            std::vector<int> &whitelibs,
//            cv::Point movept, bool isblackmove)
//{
//    
//    bool founddead=false;
//    std::vector<int> groups;
//    int numlibs,numfriends;
//    int groupnum;
//    int  deadGroupIndex = findGroups(board, isblackmove, movept, groups,blacklibs,whitelibs ,numlibs,numfriends);
//    
//    int mult = isblackmove? -1: 1;
//    
//    if(numlibs != 0)
//    {
//        if(groups.size() == 0){
//            std::vector<cv::Point> g;
//            g.push_back(movept);
//            
//            if(isblackmove){
//                blackGroups.push_back(g);
//                blacklibs.push_back(numlibs);
//                groupnum = (int)blackGroups.size();
//            }else{
//                whiteGroups.push_back(g);
//                whitelibs.push_back(numlibs);
//                groupnum = (int)whiteGroups.size();
//            }
//            board[movept.y][movept.x]=groupnum*mult;
//            
//            
//        }else if(groups.size() == 1){
//            int groupindex = groups[0]-1;
//            board[movept.y][movept.x] = mult* groups[0];
//            std::vector<cv::Point> pp;
//            
//            if(isblackmove){
//                pp  = blackGroups[groupindex];
//                pp.push_back(movept);
//                blacklibs[groupindex] = findNumLiberties(board,pp);;
//                blackGroups[groupindex]=pp;
//            }else{
//                pp = whiteGroups[groupindex];
//                pp.push_back(movept);
//                whitelibs[groupindex] = findNumLiberties(board,pp);;
//                whiteGroups[groupindex]=pp;
//            }
//            
//            
//        }else
//        {
//            std::sort(groups.begin(),groups.end());
//            std::reverse(groups.begin(), groups.end());
//            std::vector <cv::Point> mergedGroups;
//            int groupnum;
//            for(int i =0;i< groups.size();i++)
//            {
//                std::vector< cv::Point > group;
//                if(isblackmove){
//                    blackGroups[groups[i]-1];
//                }else{
//                    whiteGroups[groups[i]-1];
//                }
//                mergedGroups.insert(mergedGroups.end(), group.begin(),group.end());
//                
//                if(isblackmove){
//                    blackGroups.erase(blackGroups.begin() + groups[i]-1 );
//                    blacklibs.erase(blacklibs.begin()+groups[i]-1);
//                }else{
//                    whiteGroups.erase(blackGroups.begin() + groups[i]-1 );
//                    whitelibs.erase(whitelibs.begin()+ groups[i]-1);
//                }
//            }
//            mergedGroups.push_back(movept);
//            if(isblackmove){
//                blackGroups.push_back(mergedGroups);
//                groupnum =  (int)blackGroups.size();
//            }else{
//                whiteGroups.push_back(mergedGroups);
//                groupnum =  (int)whiteGroups.size();
//            }
//            
//            for(int k=0;k< mergedGroups.size();k++){
//                cv::Point &p = mergedGroups[k];
//                board[p.y][p.x]=groupnum*mult;
//            }
//            int numgrouplibs = findNumLiberties(board,mergedGroups);
//            if(isblackmove){
//                blacklibs.push_back(numgrouplibs);
//            }else{
//                whitelibs.push_back(numgrouplibs);
//                
//            }
//            
//        }
//        if(deadGroupIndex != -1){
//            if(isblackmove){
//                handleDeadStones(board, whiteGroups[deadGroupIndex], isblackmove, blacklibs, whitelibs);
//            }else{
//                handleDeadStones(board, blackGroups[deadGroupIndex], isblackmove, blacklibs, whitelibs);
//            }
//            NSAlert* msgBox = [[[NSAlert alloc] init] autorelease];
//            [msgBox setMessageText: @"Remove dead stones than click continue recording"];
//            [msgBox addButtonWithTitle: @"OK"];
//            [msgBox runModal];
//            founddead=true;
//            
//        }
//        
//    }else if(numlibs ==0) {
//        cout << "num lib 0";
//    }
//}
//
//bool pointinrect(float x, float y , cv::Rect &r)
//{
//    return !(x < r.x || x > r.x+r.width || y < r.y || y > r.y+r.height);
//}
//
//void findrowcol(cv::Rect &r, int row, int col, float dx, float dy,int &newrow, int &newcol)
//{
//    
//    int dyy[] = {row-1,row,row+1};
//    int dxx[]={col-1,col,col+1};
//    newrow=row;
//    newcol=col;
//    bool dobreak=false;
//    for(int a=0;a< 3;a++){
//        for(int b=0;b<3;b++){
//            if(pointinrect(dx*dxx[a],dy * dyy[b],r)){
//                newrow = dyy[b];
//                newcol = dxx[a];
//                dobreak=true;
//                break;
//            }
//        }
//        if(dobreak)break;
//    }
//}
//-(void) capturemoves
//{
//    
//    std::vector<std::vector<cv::Point> > contours;
//    std::vector<cv::Vec4i> hierarchy;
//    
//    Mat grayImage,curImage,curImage2,diffPrevImage,diffSavedImage,diffSavedImage2;
//    cv::Mat framePrev,frameCur,frameDif,transformedImage,frame;
//    
//    grabframe(_videoCapture, frame, 1);
//    grabframe(_videoCapture, frame, 1);
//    grabframe(_videoCapture, frame, 1);
//    grabframe(_videoCapture, frame, 1);
//    
//    cv::Mat map =  getPerspectiveMap(frame.size(),_transRect,_orientation);
//    cv::warpPerspective(frame, curImage, map, frame.size());
//    
//    
//    
//    int diffprev = diffFrames(curImage, _prevImage, diffPrevImage);
//    int difsaved = diffFrames(curImage, _savedImage,diffSavedImage);
//    
//    
//    doDilate(5, diffSavedImage, diffSavedImage);
//    //doDilate(5, diffSavedImage, diffSavedImage2);
//    //doErode(5, diffSavedImage, diffSavedImage);
//    
//    [self.savedViewContinuous setImage: [NSImage imageWithCVMat: diffSavedImage]];
//    
//    cout <<  " diff prev= " << diffprev <<" diff saved=" << difsaved << endl;
//    
//    getContoursForMove(diffSavedImage,_map,contours,hierarchy);
//    if(contours.size() > 0){
//        cv::Rect r = cv::boundingRect(contours[0]);
//        float ecc = r.width/(float)r.height;
//        if( diffprev == 0 && difsaved > _diffmin && difsaved < _diffmax  )
//        {
//            _savedImage = curImage.clone( );
//            
//            [self.diffView setImage: [NSImage imageWithCVMat: diffSavedImage]];
//            
//            
//            float dx = _savedImage.cols/(_boardsize -1);
//            float dy = _savedImage.rows/(_boardsize -1);
//            
//            if(contours.size()>0){
//                Node* node =[[[Node alloc] init] retain];
//                float darea = dx*dy;
//                float maxarea = -1;
//                bool saveisblack;
//                cv::Point savept;
//                for( int i = 0; i< contours.size(); i++ )
//                {
//                    double area =  cv::contourArea(contours[i]);
//                    cv::Rect r = cv::boundingRect(contours[i]);
//                    cv::drawContours(_savedImage, contours, i,CV_RGB(255,255,255));
//                    cv::rectangle(_savedImage,r.tl(), r.br(), CV_RGB(255,255,255))
//                    ;
//                    if(area > maxarea){
//                        cv::Point p;
//                        getContourCentroid(contours[i],p);
//                        int row = round(p.y/dy) ;
//                        int col = round(p.x/dx);
//                        int newrow,newcol;
//                        if(row == 0 || row == _boardsize-1 || col == 0 || col == _boardsize-1)
//                        {
//                            findrowcol(r,row, col, dx,dy,newrow, newcol);
//                            row=newrow;
//                            col=newcol;
//                            
//                        }
//                        
//                        cv::Point centerCoords(col,row);
//                        
//                        //cv::rectangle(boardImage, r.tl(), r.br(), CV_RGB(255,255,255));
//                        cv::Scalar ave = cv::mean(_savedImage(r));
//                        float x = ave[0];
//                        saveisblack = x < 135;
//                        maxarea = area;
//                        savept = centerCoords;
//                    }
//                }
//                
//                [self.savedView setImage: [NSImage imageWithCVMat: _savedImage]];
//                if(contours.size() >1){
//                    cout << contours.size() << endl;
//                }
//                if(maxarea > 0){
//                    node->isblack = saveisblack;
//                    node->groupNum = 0;
//                    node->coord = savept;
//                    _moves.push_back(node);
//                    _currentMoveIndex=_moves.size();
//                    bool founddead;
//                    if(saveisblack){
//                        founddead=domove(_board,_blackGroups,_whiteGroups,_blackGroupLiberties,_whiteGroupLiberties,node->coord,saveisblack);
//                    }else{
//                        founddead = domove(_board,_blackGroups,_whiteGroups,_blackGroupLiberties,_whiteGroupLiberties,node->coord,saveisblack);
//                        
//                    }
//                    drawMove(_boardImage, _boardsize, curImage,node);
//                    if(founddead){
//                        [self killTimers];
//                    }
//                    
//                    //       stringstream strm;
//                    //       strm << "/Users/macbookpro/test/image" << _imageindex++ << ".jpg";
//                    //       NSString *filename = [[NSString alloc] initWithCString: strm.str().c_str() encoding:NSMacOSRomanStringEncoding];
//                    //       [self writeImage: savedimage toFile: filename ];
//                    //
//                    
//                }
//            }
//            
//        }
//    }
//    
//    // cv::Mat boardImage =drawBoard(curImage, _board,_moves,_moves.size());
//    
//    [self.boardView setImage: [NSImage imageWithCVMat: _boardImage]];
//    
//    
//    _prevImage=curImage.clone();
//    [self.imageWell setImage: [NSImage imageWithCVMat: _prevImage]];
//    }
//    
//    - (void) captureframeForLoop
//    {
//        
//        Mat colorImage;
//        grabframe(_videoCapture, _prevImage, 1);
//        if(_docalibrate){
//            processFrame1(_prevImage,_transRect,_convexHull,_orientation);
//            drawpoly(_prevImage,_transRect);
//        }
//        
//        drawpoly(_prevImage,_transRect);
//        
//        [self.savedView setImage:[NSImage imageWithCVMat: _prevImage]];
//        
//        cv::Mat rotboard;
//        cv::Mat map =  getPerspectiveMap(_prevImage.size(),_transRect,_orientation);
//        cv::warpPerspective(_prevImage, rotboard, map, _prevImage.size());
//        [self.boardView setImage:[NSImage imageWithCVMat: rotboard]];
//        
//        //    [imageView setImage: image1];
//        //    [imageView display];
//        
//        
//    }
//    
//    -(void) killTimers{
//        [self.runTimer invalidate];
//        self.runTimer= NULL;
//        
//        [self.runTimer2 invalidate];
//        self.runTimer2 = NULL;
//    }
//    - (IBAction)stopAutoCalibrate:(id)sender {
//        [self killTimers];
//        _docalibrate=false;
//    }
//    
//    - (IBAction)startAutoCalibrate:(id)sender {
//        [self killTimers];
//        _docalibrate=true;
//        self.runTimer = [NSTimer
//                         scheduledTimerWithTimeInterval:.1
//                         target:self
//                         selector:@selector(captureframeForLoop)
//                         userInfo:nil
//                         repeats:YES];
//    }
//    
//    
//    
//    
//    - (IBAction)doRecordGame:(id)sender {
//        [self killTimers];
//        for(int i =0;i< _moves.size();i++){
//            [_moves[i] release];
//        }
//        _moves.clear();
//        _startmotion = false;
//        _imageindex=0;
//        
//        cv::Mat curImage,frame;
//        grabframe(_videoCapture, frame, 1);
//        cv::Mat map =  getPerspectiveMap(frame.size(),_transRect,_orientation);
//        cv::warpPerspective(frame, curImage, map, frame.size());
//        _savedImage = curImage.clone();
//        _prevImage = curImage.clone();
//        
//        
//        _boardImage = drawBoard(curImage, _boardsize);
//        
//        [self.boardView setImage: [NSImage imageWithCVMat: _boardImage]];
//        [self.savedView setImage: [NSImage imageWithCVMat: curImage]];
//        
//        self.runTimer2 = [NSTimer
//                          scheduledTimerWithTimeInterval:.1
//                          target:self
//                          selector:@selector(capturemoves)
//                          userInfo:nil
//                          repeats:YES];
//    }
//    
//    - (IBAction)resetSavedView:(id)sender {
//        _savedImage = _prevImage.clone();
//        [self.savedView setImage: [NSImage imageWithCVMat:_savedImage]];
//    }
//    
//    - (IBAction)rotateBoard:(id)sender {
//        _orientation = (_orientation+1)%4;
//        cv::Mat rotboard;
//        cv::Mat map =  getPerspectiveMap(_prevImage.size(),_transRect,_orientation);
//        cv::warpPerspective(_prevImage, rotboard, map, _prevImage.size());
//        [self.diffView setImage:[NSImage imageWithCVMat: rotboard]];
//        
//    }
//    
//    - (std::string) makeSGFstring{
//        std::stringstream s;
//        s <<  "(;FF[4]GM[1]SZ[" << _boardsize << "];";
//        string alpha = "abcdefghijklmnopqrstuvwxyz";
//        for(int i = 0;i < _moves.size();i++){
//            if(_moves[i]->isblack){
//                s << "B[";
//            }else{
//                s<< "W[";
//            }
//            s << alpha.at(_moves[i]->coord.x) << alpha.at(_moves[i]->coord.y) <<  "];";
//        }
//        s << ")";
//        return s.str();
//    }
//    - (IBAction)savetoSGF:(id)sender {
//        std::string  sgfstring = [self makeSGFstring];
//        NSString *sgfNSstring = [[NSString alloc] initWithCString: sgfstring.c_str() encoding:NSMacOSRomanStringEncoding];
//        NSSavePanel *panel = [NSSavePanel savePanel];
//        NSInteger clicked = [panel runModal];
//        
//        if (clicked ==   NSFileHandlingPanelOKButton) {
//            
//            NSString * filename = [panel filename];
//            [sgfNSstring writeToFile:filename atomically:YES encoding: NSUTF8StringEncoding error: NULL];
//        }
//        
//    }
//    
//    - (IBAction)pauseRecording:(id)sender {
//    }
//    
//    - (IBAction)continueRecording:(id)sender {
//        cv::Mat curImage,frame;
//        grabframe(_videoCapture, frame, 1);
//        cv::Mat map =  getPerspectiveMap(frame.size(),_transRect,_orientation);
//        cv::warpPerspective(frame, curImage, map, frame.size());
//        _savedImage = curImage.clone();
//        _prevImage = curImage.clone();
//        
//        _boardImage = drawBoard(curImage, _boardsize);
//        drawMoves(_boardImage, curImage, _moves, _boardsize, (int)_currentMoveIndex);
//        
//        [self.boardView setImage: [NSImage imageWithCVMat: _boardImage]];
//        [self.savedView setImage: [NSImage imageWithCVMat: curImage]];
//        
//        self.runTimer2 = [NSTimer
//                          scheduledTimerWithTimeInterval:.1
//                          target:self
//                          selector:@selector(capturemoves)
//                          userInfo:nil
//                          repeats:YES];
//    }
//    
//    - (IBAction)firstMove:(id)sender {
//        _currentMoveIndex=0;
//        _boardImage = drawBoard(_prevImage, _boardsize);
//        drawMoves(_boardImage, _prevImage, _moves, _boardsize, (int)_currentMoveIndex);
//        [self.boardView setImage: [NSImage imageWithCVMat: _boardImage]];
//        
//    }
//    
//    - (IBAction)prevMove:(id)sender {
//        
//        if(_currentMoveIndex > 0){
//            _currentMoveIndex --;
//        }
//        _boardImage = drawBoard(_prevImage, _boardsize);
//        drawMoves(_boardImage, _prevImage, _moves, _boardsize, (int)_currentMoveIndex);
//        [self.boardView setImage: [NSImage imageWithCVMat: _boardImage]];
//    }
//    
//    - (IBAction)nextMove:(id)sender {
//        unsigned long ind = _currentMoveIndex +1;
//        if(ind > _moves.size()){
//            _currentMoveIndex = _moves.size();
//        }else{
//            _currentMoveIndex = ind;
//        }
//        _boardImage = drawBoard(_prevImage, _boardsize);
//        drawMoves(_boardImage, _prevImage, _moves, _boardsize, (int)_currentMoveIndex);
//        [self.boardView setImage: [NSImage imageWithCVMat: _boardImage]];
//    }
//    
//    - (IBAction)lastMove:(id)sender {
//        _currentMoveIndex=_moves.size();
//        _boardImage = drawBoard(_prevImage, _boardsize);
//        drawMoves(_boardImage, _prevImage, _moves, _boardsize, (int)_currentMoveIndex);
//        [self.boardView setImage: [NSImage imageWithCVMat: _boardImage]];
//    }
//    
//    - (IBAction)stopRecording:(id)sender {
//        [self killTimers];
//    }
//    
//    - (IBAction)selectBoardSize:(id)sender {
//        NSSegmentedCell* seg = sender;
//        int sizes[] = {9,13,19};
//        _boardsize= sizes[seg.selectedSegment];
//        initdiffminmax(_boardsize,_diffmin,_diffmax);
//        [self initdata];
//    }
//    @end
