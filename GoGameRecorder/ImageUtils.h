

int doadd(int x);
void makeBoardArray(int boardsize, std::vector<std::vector<int>> &board);
void getContourCentroid(std::vector<cv::Point> contour, cv::Point &centroid);

void getContoursForMove(cv::Mat &image,
                        cv::Mat pmap,
                        std::vector<std::vector<cv::Point> > &contours,
                        std::vector<cv::Vec4i> &hierarchy);
void drawMoves(cv::Mat &boardImage,cv::Mat& curImage, std::vector<Node*> &moves,int boardsize,int lastmoveIndex);

void drawMove(cv::Mat &boardImage,int boardsize, cv::Mat &curImage,Node* move);
int findPointClosestToOrigin(std::vector<cv::Point> rect);
cv::Mat drawBoard(cv::Mat curImage,int boardsize);
void grabframe(VideoCapture *cap, Mat &theframe, int scale);
void doErode( int erosion_size, Mat &src, Mat &dst );
int diffFrames(Mat &image1, Mat &image2, cv::Mat &diff);
void doDilate( int dilation_size , Mat &src, Mat &dst );
void findMaxAreaContour(std::vector<std::vector<cv::Point> > &contours, int &index, double &maxarea);

void findConvexHull(cv::Mat frame,std::vector<cv::Point> &maxAreaContour,std::vector<cv::Point> &convexHull);
cv::Mat getPerspectiveMap(cv::Size s, std::vector<cv::Point> &srcVec, int orientation);
void initdiffminmax(int boardsize, int &diffmin , int &diffmax);
void processFrame1( Mat &inputImage, std::vector<cv::Point> &transRect,std::vector<cv::Point> &convexHull,int orientation);
void drawpoly(Mat& inputImage, std::vector<cv::Point> transRect);
