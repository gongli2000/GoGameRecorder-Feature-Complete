//
//  Board.cpp
//  GoGameRecorder
//
//  Created by Larry on 7/4/13.
//  Copyright (c) 2013 Larry. All rights reserved.
//

#include "Board.h"



Board::Board(){
    init(9);
}
Board::Board(int boardsize){
    init(boardsize);
}

void Board::init(int boardsize)
{
    _currentMoveIndex =0;

    for(auto &move:moves){
        [move release];
    }
    moves.clear();
    _groupsmap.init();
    boardData.clear();
    boardData.resize(boardsize);
    for(int i=0;i<boardsize;i++){
        boardData[i].resize(boardsize);
        for(int j=0;j<boardsize;j++){
            boardData[i][j]=0;
        }
    }
}

void Board::resize(int boardsize){
    boardData.clear();
    boardData.resize(boardsize);
    init(boardsize);
}




int Board::findGroups(
                      bool blacksMove,
                      cv::Point p,
                      std::vector<int> &groups,
                      int &numLiberties)
{
    set<int> groupset;
    int deadgroupindex=-1;
    int deadgroupindexmap = -1;
    int x[] = {p.x-1,p.x+1,p.x,p.x};
    int y[] = {p.y,p.y,p.y-1,p.y+1};
    numLiberties=4;
    for(int i =0;i<4;i++){
        if(x[i] <0 || x[i]>= boardData.size() || y[i] < 0 || y[i] >= boardData.size())continue;
        int valueAtPoint = boardData[y[i]][x[i]];
        if(valueAtPoint < 0){
            if(blacksMove){
                groupset.insert(valueAtPoint);
            }else{
                numLiberties--;
                deadgroupindexmap = _groupsmap.decLiberties(valueAtPoint);
            }
        }else if(valueAtPoint > 0){
            if(blacksMove){
                 numLiberties--;
                deadgroupindexmap = _groupsmap.decLiberties(valueAtPoint);
           
            }else{
                groupset.insert(valueAtPoint);
            }
        }
    }
    groups.clear();
    for(set<int>::iterator it = groupset.begin(); it!=groupset.end();it++){
        groups.push_back(*it);
    }
    return deadgroupindex;
    
}

void Board::setCurrentMove(int i){
    _currentMoveIndex=i;
}

int Board::addstone( StoneColor color,cv::Point movept)
{
    bool isblackmove = color == StoneColor::BLACK;
    std::vector<int> groups;
    int numlibs;
    int groupnum;
    int deadgroupindex = findGroups(isblackmove, movept, groups,numlibs);
    if(numlibs != 0)
    {
        if(groups.size() == 0){
            std::vector<cv::Point> g;
            g.push_back(movept);
            groupnum = _groupsmap.addgroup(color, g, numlibs);
            boardData[movept.y][movept.x]=groupnum;
            
        }else if(groups.size() == 1){
            _groupsmap.addpoint2group(color, boardData, movept, groups[0]);
            
        }else
        {
            std::sort(groups.begin(),groups.end());
            std::reverse(groups.begin(), groups.end());
            _groupsmap.merge(color, boardData, movept, groups);
            
        }
    }else if(numlibs ==0) {
        
    }
    return deadgroupindex;
}

int Board::domove( StoneColor color,cv::Point movept)
{
    Node* node =[[[Node alloc] init] retain];
    node->isblack = color==StoneColor::BLACK;
    node->groupNum = 0;
    node->coord = movept;

    int deadgroupindex = addstone(color,movept);
    list<Node*>::iterator i = moves.begin();
    advance(i,_currentMoveIndex);
    moves.insert(i,node);
    _currentMoveIndex++;
   
    return deadgroupindex;
}

list<Node*>::iterator Board::findmove(int row, int col)
{
    list<Node*>::iterator it = moves.begin();
    while((**it).coord.x != col || (**it).coord.y != row){
        it++;
    }
    return it;
}
bool Board::movestone(int fromrow,int fromcol, int torow,int tocol){
    bool isblack = boardData[fromrow][fromcol] < 0;
    bool addedok=false;
    list<Node*>::iterator movepos = findmove(fromrow,fromcol);
    if(movepos != moves.end() && boardData[torow][tocol]==0){
        removestone(cv::Point(fromcol,fromrow));
        addstone(isblack? StoneColor::BLACK:StoneColor::WHITE, cv::Point(tocol,torow));
        list<Node*>::iterator movepos = findmove(fromrow,fromcol);
        if(movepos != moves.end()){
            (**movepos).coord = cv::Point(tocol,torow);
        }
        
        addedok=true;
    }
    return addedok;
}

StoneColor Board::getColor(int threshold, int blackmax, int whitemin){
    StoneColor color;
    if(threshold < blackmax){
        color=StoneColor::BLACK;
    }else if(threshold > whitemin){
        color=StoneColor::WHITE;
    }else{
        color=StoneColor::BOARD;
    }
    return color;
}



void Board::findAllGroups(cv::Point p,std::set<int> &groups)
{
    int x[] = {p.x-1,p.x+1,p.x,p.x};
    int y[] = {p.y,p.y,p.y-1,p.y+1};
    
    for(int i =0;i<4;i++){
        if(x[i] <0 || x[i]>= boardData.size() || y[i] < 0 || y[i] >= boardData.size())continue;
        int valueAtPoint = boardData[y[i]][x[i]];
        if(valueAtPoint != 0){
            groups.insert(valueAtPoint);
        }
    }
}

void Board::findEnemyGroupsAdj2Group(bool isblack,int groupindex, set<int> &groups)
{
    vector<cv::Point>&group = _groupsmap._groups[groupindex]->elements;
    for(auto& p : group){
        findEnemyGroups(isblack, p, groups);
    }
}



void Board::findEnemyGroups(bool isblack, cv::Point p,std::set<int> &groups)
{
    int x[] = {p.x-1,p.x+1,p.x,p.x};
    int y[] = {p.y,p.y,p.y-1,p.y+1};
    
    for(int i =0;i<4;i++){
        if(x[i] <0 || x[i]>= boardData.size() || y[i] < 0 || y[i] >= boardData.size())continue;
        int valueAtPoint = boardData[y[i]][x[i]];
        if(valueAtPoint != 0 && ((isblack && valueAtPoint > 0 ) || (!isblack && valueAtPoint < 0)))
        {
            groups.insert(valueAtPoint);
        }
    }
}

void Board::removestone(cv::Point p)
{
    std::set<int> groups;
    findAllGroups( p, groups);
    int groupindex = boardData[p.y][p.x];
    bool stoneIsBlack = groupindex < 0;
    vector<cv::Point> &group = _groupsmap._groups[groupindex]->elements;
    // find all enemy groups adjacent
    set<int> enemyGroups;
    findEnemyGroupsAdj2Group(stoneIsBlack, groupindex, enemyGroups);
  
    //erase the whole group to which the point belongs
    _groupsmap.deletegroup(groupindex);
    // erase group from board
    for(int i=0;i < group.size();i++){
        cv::Point p = group[i];
        boardData[p.y][p.x]=0;
    }
 

    StoneColor color;
    if(stoneIsBlack){
        color=StoneColor::BLACK;
    }else{
        color=StoneColor::WHITE;
    }
    
    // remove stone from group
    // put back remaining stones back on the board
    group.erase(std::remove(group.begin(), group.end(), p), group.end());
    // add reminaing stones in group back
    for(int i=0;i< group.size();i++){
        addstone( color,group[i]);
    }
    //recompute liberties for enemy groups
    //for(std::set<int> ::iterator it = enemyGroups.begin(); it!=enemyGroups.end(); it++){
    for(auto& i : enemyGroups)
    {
        GroupNode* &g = _groupsmap._groups[i];
        g->numLiberties = Utils::findNumLiberties(boardData,g->elements);
    }

}

void Board::handleDeadStones(int deadgroupindex,bool isblackmove)
{

    GroupNode* deadgroup = _groupsmap._groups[deadgroupindex];
    std::set<int> enemyGroups;
   // for(int i = 0; i < deadGroup.size();i++)
    for(auto& p : deadgroup->elements)
    {
        findEnemyGroups( !isblackmove, p, enemyGroups);
        for(auto& i : enemyGroups){
            GroupNode* g = _groupsmap._groups[i];
            g->numLiberties++;
        }
        boardData[p.y][p.x]=0;
    }
    _groupsmap.deletegroup(deadgroupindex);
}


