#include<opencv2\opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main() {
	Mat img = imread("case13.jpeg");
	static int arr1[4000][4000][3];
	int n = 0, a, b, o = 0, m = 0;
	static int arr2[90200][2];
	static int arr3[90200][2];
	static int arr4[90200][2];
	int arr5[9][2];
	//matrix formation
	for (int r = 0; r < img.rows; r++) {
		for (int c = 0; c < img.cols; c++) {
			int a, b, d;
			a = img.at<Vec3b>(r, c)(0);
			b = img.at<Vec3b>(r, c)(1);
			d = img.at<Vec3b>(r, c)(2);
			int arr[] = { a,b,d };
			for (int i = 0; i < 3; i++) {
				arr1[r][c][i] = arr[i];
			}

		}
	}
	//column search
	for (int r = 0; r < img.rows; r++) {
		for (int c = 1; c < img.cols; c++) {
			int x, y, z, avg;
			x = arr1[r][c][0] - arr1[r][c - 1][0];
			y = arr1[r][c][1] - arr1[r][c - 1][1];
			z = arr1[r][c][2] - arr1[r][c - 1][2];
			if (x < 0)x = x * (-1);
			else;
			if (y < 0)y = y * (-1);
			else;
			if (z < 0)z = z * (-1);
			else;
			avg = (x + y + z) / 3;
			if (avg > 20) {           //level of color difference
				arr2[n][0] = r;
				arr2[n][1] = c;
				n++;
			}
			else;
		}
	}
	a = n - 1;
	n = 0;
	//row search
	for (int c = 0; c < img.cols; c++) {
		for (int r = 1; r < img.rows; r++) {
			int x, y, z, avg;
			x = arr1[r][c][0] - arr1[r - 1][c][0];
			y = arr1[r][c][1] - arr1[r - 1][c][1];
			z = arr1[r][c][2] - arr1[r - 1][c][2];
			if (x < 0)x = x * (-1);
			else;
			if (y < 0)y = y * (-1);
			else;
			if (z < 0)z = z * (-1);
			else;
			avg = (x + y + z) / 3;
			if (avg > 20) {          //level of color difference
				arr3[n][0] = r;
				arr3[n][1] = c;
				n++;
			}
			else;
		}
	}
	b = n - 1;
	n = 0;
	cout << "value of a is " << a << endl << "value of b is " << b << endl;

	//deleting the double points
	for (int r2 = 0; r2 < a; r2++) {
		for (int r3 = 0; r3 < b - n; r3++) {
			if (arr2[r2][0] == arr3[r3][0] && arr2[r2][1] == arr3[r3][1]) {
				for (int q = r3; q < b - n; q++) {
					arr3[q][0] = arr3[q + 1][0];
					arr3[q][1] = arr3[q + 1][1];
					//cout << "hi" << endl;
				}
				n++;
			}
			else;

		}

	}
	cout << "number of double points are " << n;


	//marking the boundary for cols
	/*for (int r = 0; r <= a; r++) {
		int x, y;
		x = arr2[r][0];
		y = arr2[r][1];
		img.at<Vec3b>(x, y)(0) = 0;
		img.at<Vec3b>(x, y)(1) = 200;
		img.at<Vec3b>(x, y)(2) = 0;

	}

	//marking the boundary for rows
	for (int c = 0; c <= b - n; c++) {
		int x, y;
		x = arr3[c][0];
		y = arr3[c][1];
		img.at<Vec3b>(x, y)(0) = 0;
		img.at<Vec3b>(x, y)(1) = 200;
		img.at<Vec3b>(x, y)(2) = 0;

	}
	*/
	//combining arr2 and arr3
	for (int r = a + 1; o <= b; o++) {
		arr2[r][0] = arr3[o][0];
		arr2[r][1] = arr3[o][1];
	}

	//searching for neighbouring marks and deleting
	int f = 0;
	for (int r = 0; r < o; r++) {
		int x, y, e = 0;
		x = arr2[r][0];
		y = arr2[r][1];
		for (int r1 = -1; r1 < 2; r1++) {
			for (int c1 = -1; c1 < 2; c1++) {
				if (x == arr2[r][0] + r1 && y == arr2[r][1] + c1) {
					e++;
				}
				else;
				if (e < 1) {
					arr4[f][0] = x;
					arr4[f][1] = y;
					f++;
				}
				else;
			}


		}
	}

	//searching with new algorithm
	/*int f = 0;
	for (int r = 1; r < o; r++) {
		int x, y, i = 0, length;
		for (int r1 = -1; r1 < 2; r1++) {
			for (int c1 = -1; c1 < 2; c1++) {              //formation of array
				arr5[i][0] = arr3[r][0] + r1;
				arr5[i][1] = arr3[r][1] + c1;
				i++;
			}
			for (int r3 = 0; r3 < 9; r3++) {                //comparing and deleting
				for (int r2 = 0; r2 < length; length) {
					if (arr5[r3][0] == arr3[r2][0] && arr5[r3][1] == arr3[r2][1]) {
						arr4[f][0] = arr5[r3][0];           //adding to new array
						arr4[f][1] = arr5[r3][1];
						arr3[][0] = arr3[][0];              //deleting from old array
						arr3[][1] = arr3[][1];
					}
				}

		}
		}
	}*/

	//marking new boundary after grouping
	for (int r = 0; r < f; r++) {
		int x, y;
		x = arr4[r][0];
		y = arr4[r][1];
		img.at<Vec3b>(x, y)(0) = 0;
		img.at<Vec3b>(x, y)(1) = 200;
		img.at<Vec3b>(x, y)(2) = 0;
	}
	

	namedWindow("result", WINDOW_NORMAL);
	imshow("result", img);
	waitKey();
}
