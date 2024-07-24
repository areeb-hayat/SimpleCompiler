#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include<string>
#include<conio.h>
#include <fstream>
#include "Queue.h"
#include "stack.h"
#include "Functions.h"
using namespace std;
using namespace cv;


int task4(string p)
{
	string path("F:\\University\\DS\\Assignment 2\\Images\\");
	path += p;
	path += ".png";

	//cout << path;

	Mat img = imread(path);
	int galaxies = 0;
	float x, y, z;
	float rows = img.rows;
	float cols = img.cols;
	float** imgmat = new float* [rows];
	for (int i = 0; i < rows; i++)
	{
		imgmat[i] = new float[cols] {0};
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			x = img.at<Vec3b>(i, j)[0];
			y = img.at<Vec3b>(i, j)[1];
			z = img.at<Vec3b>(i, j)[2];
			imgmat[i][j] = (x + y + z) / 3;
		}
	}
	imshow("Original", img);
	waitKey(0);
	destroyAllWindows();


	bool filezero = false;
	for (int k = 0; k < rows; k++)
	{
		for (int z = 0; z < cols; z++)
		{
			if (imgmat[k][z] == 255)
			{
				filezero = false;
				break;
			}
			else
				filezero = true;
		}
		if (!filezero)
			break;
	}



	while (!filezero)
	{
		float** newimg = new float* [rows];
		for (int i = 0; i < rows; i++)
		{
			newimg[i] = new float[cols] {0};
		}

		Queue<float> rowq;
		Queue<float> colq;
		int i = 0, j = 0;
		bool noz = false;
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				if (imgmat[r][c] == 255)
				{
					rowq.enqueue(r);
					colq.enqueue(c);
					imgmat[r][c] = 0;
					noz = true;
					break;
				}
			}
			if (noz)
				break;
		}

		while (!rowq.isEmpty() && !colq.isEmpty())
		{
			i = rowq.dequeue();
			j = colq.dequeue();
			newimg[i][j] = 1;
			if (imgmat[i - 1][j - 1] == 255)
			{
				imgmat[i - 1][j - 1] = 0;
				rowq.enqueue(i - 1);
				colq.enqueue(j - 1);
			}

			if (imgmat[i - 1][j] == 255)
			{
				imgmat[i - 1][j] = 0;
				rowq.enqueue(i - 1);
				colq.enqueue(j);
			}

			if (imgmat[i - 1][j + 1] == 255)
			{
				imgmat[i - 1][j + 1] = 0;
				rowq.enqueue(i - 1);
				colq.enqueue(j + 1);
			}

			if (imgmat[i][j - 1] == 255)
			{
				imgmat[i][j - 1] = 0;
				rowq.enqueue(i);
				colq.enqueue(j - 1);
			}

			if (imgmat[i][j + 1] == 255)
			{
				imgmat[i][j + 1] = 0;
				rowq.enqueue(i);
				colq.enqueue(j + 1);
			}

			if (imgmat[i + 1][j - 1] == 255)
			{
				imgmat[i + 1][j - 1] = 0;
				rowq.enqueue(i + 1);
				colq.enqueue(j - 1);
			}

			if (imgmat[i + 1][j] == 255)
			{
				imgmat[i + 1][j] = 0;
				rowq.enqueue(i + 1);
				colq.enqueue(j);
			}

			if (imgmat[i + 1][j + 1] == 255)
			{
				imgmat[i + 1][j + 1] = 0;
				rowq.enqueue(i + 1);
				colq.enqueue(j + 1);
			}
		}


		string outpath("F:\\University\\DS\\Assignment 2\\Output_files\\Img-result");
		string g = to_string(galaxies + 1);
		outpath += g;
		outpath += ".png";
		imwrite(outpath, img);

		for (int k = 0; k < rows; k++)
		{
			for (int z = 0; z < cols; z++)
			{
				if (newimg[k][z] == 1)
				{
					newimg[k][z] = 255;
					img.at<Vec3b>(k, z)[0] = 255;
					img.at<Vec3b>(k, z)[1] = 255;
					img.at<Vec3b>(k, z)[2] = 255;
				}
				else
				{
					newimg[k][z] = 0;
					img.at<Vec3b>(k, z)[0] = 0;
					img.at<Vec3b>(k, z)[1] = 0;
					img.at<Vec3b>(k, z)[2] = 0;
				}
			}
		}

		imshow("Output", img);
		waitKey(0);
		destroyAllWindows();

		for (int k = 0; k < rows; k++)
		{
			for (int z = 0; z < cols; z++)
			{
				if (imgmat[k][z] == 255)
				{
					filezero = false;
					break;
				}
				else
					filezero = true;
			}
			if (!filezero)
				break;
		}

		galaxies++;
	}

	return galaxies;
}