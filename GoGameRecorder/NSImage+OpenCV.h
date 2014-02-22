//
//  NSImage+OpenCV.h
//  GoGameRecorder
//
//  Created by Larry on 6/29/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//


#include <opencv2/opencv.hpp>
#import <Cocoa/Cocoa.h>

@interface NSImage (OpenCV) {
    
}

+(NSImage*)imageWithCVMat:(const cv::Mat&)cvMat;
-(id)initWithCVMat:(const cv::Mat&)cvMat;

+(CGPoint) image2Screen:(cv::Mat)imageRect :(NSRect)screenRect :(cv::Point) p;

+(cv::Point) screen2Image:(cv::Mat)imageRect :(NSRect)screenRect :(CGPoint) p;

@property(nonatomic, readonly) cv::Mat CVMat;
@property(nonatomic, readonly) cv::Mat CVGrayscaleMat;

@end
