#include "../opencv2/imgproc.hpp"
#include "../opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;
#define PI 3.14159265

class LineFinder{
	private:
		cv::Mat img;
		std::vector< cv::Vec4i > lines;
		double deltaRho;
		double deltaTheta;
		int minVote;
		double minLength;
		double	maxGap;
	public:
		LineFinder():deltaRho(1), 
			deltaTheta( PI/180 ),
			minVote(10), 
			minLength(0.),
			maxGap(0.){}
	void setAccResolution(double dRho, double dTheta)
	{
		deltaRho = dRho;
		deltaTheta = dTheta;
	}
	void setMinVote( int minv)
	{
		minVote = minv;
	}
	void setLineLengthAndGap( double length, double gap )
	{
		minLength = length;
		maxGap = gap;
	}
	std::vector< cv::Vec4i >findLines( cv::Mat &binary)
	{
		lines.clear();
		cv::HoughLinesP(binary, lines, 
			deltaRho, deltaTheta, 
			minVote, minLength, maxGap );
		return lines;

	}
	void drawDetectedLines(cv::Mat &images,
		cv::Scalar color = cv::Scalar(0, 255, 0)){
			vector<cv::Vec4i>::const_iterator it2 = lines.begin();
			while ( it2 !=lines.end() )
			{
				cv::Point pt1( (*it2)[0], (*it2)[1] );
				cv::Point pt2( (*it2)[2], (*it2)[3] );
				cv::line( images, pt1, pt2, color);
				++it2;
			}
	}
};

int main()
{
	cv::Mat image = cv::imread( "2010-11-08-18-14-41.jpg" );
	cv::Mat result, test;  
	cv::cvtColor (image,result,COLOR_BGR2GRAY);  
	cv::imshow( "gray", result );
	cv::Mat contours;   
	cv::Canny (result,contours,125,350);  
	LineFinder finder;  
	finder.setMinVote (160); 
	finder.setLineLengthAndGap (100,20);  
	finder.findLines (contours);  
	finder.drawDetectedLines (image);  

	cv::namedWindow ("hough");  
	cv::imshow("hough",image);  
	cv::waitKey (0); 

}
