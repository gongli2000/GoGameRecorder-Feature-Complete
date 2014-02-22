//
//  Group.h
//  GoGameRecorder
//
//  Created by Larry on 7/8/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#ifndef __GoGameRecorder__Group__
#define __GoGameRecorder__Group__

#include "Constants.h"
#include <iostream>
#include <opencv2/opencv.hpp>

#include "Utils.h"

using namespace std;


class Group{
    
public:
    vector< vector<cv::Point> >  blackGroups;
    vector<int> blackLiberties;
    
    vector< vector<cv::Point> >  whiteGroups;
    vector<int> whiteLiberties;
    void init();
    int addgroup(StoneColor color,vector<cv::Point>  &group,int numlibs);
    void deletegroup(StoneColor color,int groupnum);
    void merge( StoneColor color,vector<vector<int> > &boardData,cv::Point p, vector<int> &groups);
    void incLiberties(StoneColor color, int groupnum);
    int decLiberties(StoneColor color, int groupnum);
    void addpoint2group(StoneColor color, vector<vector<int> > &boardData, cv::Point movept,int groupindex, int mult);
};



#endif /* defined(__GoGameRecorder__Group__) */
