
#define matdatatype CV_8UC1
#define matdatatypecolor CV_8UC4

#include "ImageUtils.h"

void getContourCentroid(std::vector<cv::Point> contour, cv::Point &centroid){
    CvMoments moments = cv::moments(contour);
    double M00, M01, M10;
    M00 = cvGetSpatialMoment(&moments,0,0);
    M10 = cvGetSpatialMoment(&moments,1,0);
    M01 = cvGetSpatialMoment(&moments,0,1);
    centroid.x = M10/M00;
    centroid.y = M01/M00;
    
}
void getContoursForMove(cv::Mat &image,
                        cv::Mat pmap,
                        std::vector<std::vector<cv::Point> > &contours,
                        std::vector<cv::Vec4i> &hierarchy){
    
    cv::Mat diff2clone = image.clone();
    findContours(diff2clone, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
}




void grabframe(VideoCapture *cap, Mat &theframe, int scale){
    
    
    Mat frame,grayframe;
    (*cap) >> frame;
    
    //grabframe(cap, frame);
    cvtColor(frame, grayframe, CV_BGR2GRAY);
    transpose(grayframe,theframe);
    flip(theframe,theframe,0);
    //cv::pyrDown(grayframe,theframe);
    
    float sigma = 1.0;
    //GaussianBlur(theframe, theframe, Size(0,0), sigma, sigma);
    
    
}




void doErode( int erosion_size, Mat &src, Mat &dst )
{
    int types[] = {MORPH_RECT,MORPH_CROSS,MORPH_ELLIPSE};
    
    int erosion_elem =MORPH_RECT;
    int erosion_type = types[erosion_elem];
    
    Mat element = getStructuringElement( erosion_type,
                                        cv::Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                        cv::Point( erosion_size, erosion_size ) );
    erode( src, dst, element );
    
}


int diffFrames(Mat &image1, Mat &image2, cv::Mat &diff){
    absdiff(image1, image2, diff);
    threshold(diff,diff,40,256,CV_THRESH_BINARY);
    cv::erode(diff, diff, Mat(), cv::Point(-1,-1), 3);
    //cv::dilate(diff, diff, Mat(), cv::Point(-1,-1), 1);
    return countNonZero(diff);
}
/** @function Dilation */
void doDilate( int dilation_size , Mat &src, Mat &dst )
{
    int types[] = {MORPH_RECT,MORPH_CROSS,MORPH_ELLIPSE};
    int erosion_elem=MORPH_RECT;
    int dilation_type = types[erosion_elem];
    
    Mat element = getStructuringElement( dilation_type,
                                        cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                        cv::Point( dilation_size, dilation_size ) );
    /// Apply the dilation operation
    dilate( src, dst, element );
}
void findMaxAreaContour(std::vector<std::vector<cv::Point> > &contours, int &index, double &maxarea)
{
    maxarea = 0;
    index =0;
    
    for(int i=0;i< contours.size();i++){
        double area = cv::contourArea(contours[i]);
        if(area > 100.0){
            
            if(area > maxarea ){
                index=i;
                maxarea = area;
            }
        }
    }
    
}

void findConvexHull(cv::Mat frame,std::vector<cv::Point> &maxAreaContour,std::vector<cv::Point> &convexHull)
{
    std::vector<cv::Point> hull;
    cv::convexHull( maxAreaContour, hull, false );
    
    double peri = cv::arcLength(hull,true);
    cv:: approxPolyDP( hull, convexHull, 0.01*peri, true );
    
    //    std::vector<std::vector<cv::Point> >  contours_poly;
    //    contours_poly.push_back(convexHull);
    //    cv::fillPoly(frame, contours_poly, CV_RGB(255,0,0));
}

cv::Mat getPerspectiveMap(cv::Size s, std::vector<cv::Point> &srcVec, int orientation)
{
//    int  botIndices[]= {0,1,2,3} ;
//    int rightIndices[] = {1,2,3,0};
//    int leftIndices[] = {2,3,0,1};
//    int topIndices[] = {3,0,1,2};
//    int* indicesArray[] = {rightIndices,botIndices,leftIndices,topIndices};
//    int *indices = indicesArray[orientation];
   
   
    cv::Point2f dst[]={
        cv::Point2f(0,0),
        cv::Point(s.width,0),
        cv::Point(s.width,s.height),
        cv::Point(0,s.height)};
    //cv::Point2f src[]={srcVec[indices[0]],srcVec[indices[1]],srcVec[indices[2]],srcVec[indices[3]]};
    cv::Point2f src[]={srcVec[0],srcVec[1],srcVec[2],srcVec[3]};
    
    return cv::getPerspectiveTransform(src,dst);
}


void drawpoly(Mat& inputImage, std::vector<cv::Point> transRect){
    for(int i=0;i<transRect.size();i++){
        cv::Point p = transRect[i];
        cv::line(inputImage,p, transRect[(i+1)%transRect.size()],CV_RGB(255,0,0),2);
    }
    
}
void processFrame1( Mat &inputImage, std::vector<cv::Point> &transRect,std::vector<cv::Point> &convexHull,int orientation)
{
    Mat  outerBox,test;
    Mat grayFrame = inputImage.clone();
    
    cv::adaptiveThreshold(grayFrame,grayFrame,255,1,1,11,2);
    
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    //cv::Mat x = grayFrame.clone();
    findContours(grayFrame, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
    
    
    
    int index;
    double maxarea;
    convexHull.clear();
    findMaxAreaContour(contours,index,maxarea);
    findConvexHull(grayFrame,contours[index],convexHull);
    
    
    
    transRect.clear();
    for(int i=0;i<4;i++){
        //cv::Point p = convexHull[indices[i]];
        //cv::line(inputImage,p, convexHull[indices[(i+1)%4]],CV_RGB(255,0,0),2);
        transRect.push_back(convexHull[i]);
        
    }
    
    
    
    
}

