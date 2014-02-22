//
//  Board.h
//  GoGameRecorder
//
//  Created by Larry on 7/4/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#ifndef __GoGameRecorder__Board__
#define __GoGameRecorder__Board__
#include "Node.h"
#include "Group.h"
#include "GroupMap.h"

#include <iostream>
#include <opencv2/opencv.hpp>

#include "Utils.h"


using namespace std;
using namespace cv;
#define matdatatype CV_8UC1
#define matdatatypecolor CV_8UC4



class Board{
public:
    int _currentMoveIndex;
    list<Node*> moves;
    vector<vector<int>> boardData;
    GroupMap _groupsmap;
    Board(int boardsize);
    Board();
    
    void init(int boardsize);
    void resize(int boardsize);
    void setCurrentMove(int i);
    int findGroups(bool isblack,cv::Point p, vector<int> &groups, int &numLiberties);
    void findAllGroups( cv::Point p,std::set<int> &groups);
    int findNumLiberties(vector< cv::Point> &group);
    void findEnemyGroups(bool isblack, cv::Point p,std::set<int> &groups);
    void findEnemyGroupsAdj2Group(bool isblack,int groupindex, set<int> &enemyGroups);
    void handleDeadStones(int deadgroupindex,bool isblackmove);
    void removestone(cv::Point p);
    int addstone( StoneColor color,cv::Point movept);
    int domove(StoneColor color,cv::Point movept);
    bool movestone(int fromrow,int fromcol, int torow,int tocol);
    list<Node*>::iterator findmove(int row, int col);
    StoneColor getColor(int threshold, int blackmax, int whitemin);

  
};

#endif /* defined(__GoGameRecorder__Board__) */
