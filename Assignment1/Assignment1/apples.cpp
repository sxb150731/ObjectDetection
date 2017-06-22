#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main (int argc, char** argv)
{
	//DISPLAY IMAGE
	Mat img1;
	img1 = imread("origin.jpg", IMREAD_COLOR);

	if (!img1.data)
	{
		cout << "Could not open or find the image." << std::endl;
		system("pause");
		return -1;
	}

	imshow("Origional Image", img1);
	waitKey(0);
//********************************************//

	//BRIGHTNESS
	Mat img2 = img1.clone();

	const int factor = 50;

	//operation
	for (int x = 0; x < img2.rows; x++)
	{
		for (int y = 0; y < img2.cols; y++)
		{
			for (int c = 0; c < 3; c++)
			{
				img2.at<Vec3b>(x, y)[c] = saturate_cast<uchar>(img2.at<Vec3b>(x, y)[c] + factor);
			}
		}
	}
	//create window and display image
	imshow("Brightness", img2);
	waitKey(0);
//********************************************//

	//ORIGINAL IMAGE TO HSV
	float R, G, B;

	Mat img3 = img1.clone();
	Mat img4 = img2.clone();

	//OPERATION-IMG3
	for (int x = 0; x < img3.rows; x++)
	{
		for (int y = 0; y < img4.cols; y++)
		{
			B = img3.at<Vec3b>(x, y)[0];
			G = img3.at<Vec3b>(x, y)[1];
			R = img3.at<Vec3b>(x, y)[2];
			float Cmax = MAX(B, MAX(G, R));
			float Cmin = MIN(B, MIN(G, R));
			float delta = Cmax - Cmin;
			
			float H, S, V;
			if (Cmax == 0){
				H = S = V = 0;
			}
			else{
				V = Cmax/255.0;
				S = float(delta)/float(Cmax);
				if (delta == 0){
				H = 0;
				}
				else if (Cmax == R){
				H = 60.0 * (float((G - B))/float(delta));
					if (H < 0){
						H = H + 360.0;
					}
				}
				else if (Cmax == G){
					H = 60.0 * (float((B - R))/float(delta) + 2.0);
					if (H < 0){
						H = H + 360.0;
					}
				}
				else if (Cmax == B){
					H = 60.0 * (float((R - G))/float(delta) + 4.0);
					if (H < 0){
						H = H + 360.0;
					}
				}
			}
					img3.at<Vec3b>(x, y)[0] = V*255;
					img3.at<Vec3b>(x, y)[1] = S*255;
					img3.at<Vec3b>(x, y)[2] = H/2;
		}
	}

	imshow("HSV(Original) image", img3);
	waitKey(0);
//********************************************//

	//BRIGHTNESS IMAGE TO HSV
	for (int x = 0; x < img4.rows; x++)
	{
		for (int y = 0; y < img4.cols; y++)
		{
			B = img4.at<Vec3b>(x, y)[0];
			G = img4.at<Vec3b>(x, y)[1];
			R = img4.at<Vec3b>(x, y)[2];
			float Cmax = MAX(B, MAX(G, R));
			float Cmin = MIN(B, MIN(G, R));
			float delta = Cmax - Cmin;
			
			float H, S, V;
			if (Cmax == 0){
				H = S = V = 0;
			}
			else{
				V = Cmax/255.0;
				S = float(delta)/float(Cmax);
				if (delta == 0){
				H = 0;
				}
				else if (Cmax == R){
				H = 60.0 * (float((G - B))/float(delta));
					if (H < 0){
						H = H + 360.0;
					}
				}
				else if (Cmax == G){
					H = 60.0 * (float((B - R))/float(delta) + 2.0);
					if (H < 0){
						H = H + 360.0;
					}
				}
				else if (Cmax == B){
					H = 60.0 * (float((R - G))/float(delta) + 4.0);
					if (H < 0){
						H = H + 360.0;
					}
				}
			}
					img4.at<Vec3b>(x, y)[0] = V*255;
					img4.at<Vec3b>(x, y)[1] = S*255;
					img4.at<Vec3b>(x, y)[2] = H/2;
		}
	}

	imshow("HSV(Brightness) image", img4);
	waitKey(0);
//********************************************//

	//ORIGIN FIND RED (RGB)
	int count1 =0 ;
	int totalx = 0;
	int totaly =0;
	Mat img5 = img1.clone();

	for (int x = 0; x < img5.rows; x++)
	{
		for (int y = 0; y < img5.cols; y++)
		{
			if (((img5.at<Vec3b>(x, y)[0] >= 0) && (img5.at<Vec3b>(x, y)[1] >= 0) && (img5.at<Vec3b>(x, y)[2] >= 100)) && ((img5.at<Vec3b>(x, y)[0] <= 75) && (img5.at<Vec3b>(x, y)[1] <= 75) && (img5.at<Vec3b>(x, y)[2] <= 255)))
			{
				img5.at<Vec3b>(x, y)[0] = 255;
				img5.at<Vec3b>(x, y)[1] = 255;
				img5.at<Vec3b>(x, y)[2] = 255;
				count1 = count1 + 1;
				totalx = totalx + x;
				totaly = totaly + y;
			}

			else
			{
				img5.at<Vec3b>(x, y)[0] = 0;
				img5.at<Vec3b>(x, y)[1] = 0;
				img5.at<Vec3b>(x, y)[2] = 0;
			}			
		}
	}

	Point center;
	center.x = (totaly)/count1;
	center.y = (totalx)/count1;
	int radius = 130;
	circle(img5, center, radius, Scalar(0, 0, 255), 3, 8);

	imshow("ORIGIN-FIND-RED(RGB) image", img5);
	waitKey(0);

//********************************************//

	//BRIGHTNESS FIND RED(RGB)
	int count2 =0 ;
	int totalx2 = 0;
	int totaly2 =0;
	Mat img6 = img2.clone();

	for (int x = 0; x < img6.rows; x++)
	{
		for (int y = 0; y < img6.cols; y++)
		{
			if (((img6.at<Vec3b>(x, y)[0] >= 20) && (img6.at<Vec3b>(x, y)[1] >= 20) && (img6.at<Vec3b>(x, y)[2] >= 140)) && ((img6.at<Vec3b>(x, y)[0] <= 130) && (img6.at<Vec3b>(x, y)[1] <= 130) && (img6.at<Vec3b>(x, y)[2] <= 255)))
			{
				img6.at<Vec3b>(x, y)[0] = 255;
				img6.at<Vec3b>(x, y)[1] = 255;
				img6.at<Vec3b>(x, y)[2] = 255;
				count2 = count2 + 1;
				totalx2 = totalx2 + x;
				totaly2 = totaly2 + y;
			}

			else
			{
				img6.at<Vec3b>(x, y)[0] = 0;
				img6.at<Vec3b>(x, y)[1] = 0;
				img6.at<Vec3b>(x, y)[2] = 0;
			}			
		}
	}

	Point center2;
	center2.x = (totaly2)/count2;
	center2.y = (totalx2)/count2;
	int radius2 = 130;
	circle(img6, center2, radius2, Scalar(0, 0, 255), 3, 8);

	imshow("BRIGHTNESS-FIND-RED(RGB) image", img6);
	waitKey(0);
//********************************************//

	//ORIGIN FIND RED(HSV)
	int count3 = 0 ;
	int totalx3 = 0;
	int totaly3 = 0;
	Mat img7 = img3.clone();

	for (int x = 0; x < img7.rows; x++)
	{
		for (int y = 0; y < img7.cols; y++)
		{
			if (((img7.at<Vec3b>(x, y)[0] >= 95) && (img7.at<Vec3b>(x, y)[1] >= 180) && (img7.at<Vec3b>(x, y)[2] >= 0)) && ((img7.at<Vec3b>(x, y)[0] <= 255) && (img7.at<Vec3b>(x, y)[1] <= 255) && (img7.at<Vec3b>(x, y)[2] <= 15)))
			{
				img7.at<Vec3b>(x, y)[0] = 255;
				img7.at<Vec3b>(x, y)[1] = 255;
				img7.at<Vec3b>(x, y)[2] = 255;
				count3 = count3 + 1;
				totalx3 = totalx3 + x;
				totaly3 = totaly3 + y;
			}

			else
			{
				img7.at<Vec3b>(x, y)[0] = 0;
				img7.at<Vec3b>(x, y)[1] = 0;
				img7.at<Vec3b>(x, y)[2] = 0;
			}			
		}
	}

	Point center3;
	center3.x = (totaly3)/count3;
	center3.y = (totalx3)/count3;
	int radius3 = 130;
	circle(img7, center3, radius3, Scalar(0, 0, 255), 3, 8);

	imshow("ORIGIN-FIND-RED(HSV) image", img7);
	waitKey(0);
//********************************************//

	//BRIGHTNESS FIND RED(HSV)
	int count4 = 0 ;
	int totalx4 = 0;
	int totaly4 = 0;
	Mat img8 = img4.clone();

	for (int x = 0; x < img8.rows; x++)
	{
		for (int y = 0; y < img8.cols; y++)
		{
			if (((img8.at<Vec3b>(x, y)[0] >= 140) && (img8.at<Vec3b>(x, y)[1] >= 125) && (img8.at<Vec3b>(x, y)[2] >= 0)) && ((img8.at<Vec3b>(x, y)[0] <= 255) && (img8.at<Vec3b>(x, y)[1] <= 219) && (img8.at<Vec3b>(x, y)[2] <= 15)))
			{
				img8.at<Vec3b>(x, y)[0] = 255;
				img8.at<Vec3b>(x, y)[1] = 255;
				img8.at<Vec3b>(x, y)[2] = 255;
				count4 = count4 + 1;
				totalx4 = totalx4 + x;
				totaly4 = totaly4 + y;
			}

			else
			{
				img8.at<Vec3b>(x, y)[0] = 0;
				img8.at<Vec3b>(x, y)[1] = 0;
				img8.at<Vec3b>(x, y)[2] = 0;
			}			
		}
	}

	Point center4;
	center4.x = (totaly4)/count4;
	center4.y = (totalx4)/count4;
	int radius4 = 130;
	circle(img8, center4, radius4, Scalar(0, 0, 255), 3, 8);

	imshow("BRIGHTNESS-FIND-RED(HSV) image", img8);
	waitKey(0);
//********************************************//
	
	//SWAP COLOR
	Mat img9 = img1.clone();

	//operation
	for (int x = 0; x < img9.rows; x++)
	{
		for (int y = 0; y < img9.cols; y++)
		{
			img9.at<Vec3b>(x, y)[0] = img1.at<Vec3b>(x, y)[0];
			img9.at<Vec3b>(x, y)[2] = img1.at<Vec3b>(x, y)[1];
			img9.at<Vec3b>(x, y)[1] = img1.at<Vec3b>(x, y)[2];
		}
	}
	 imshow( "Swap Color", img9);

	waitKey(0);
	return 0;
}