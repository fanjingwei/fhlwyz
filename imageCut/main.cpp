/*************************************************************************
	> File Name: main.cpp
	> Author: Bruce Zhang
	> Mail: zhangxb.sysu@gmail.com 
	> Created Time: 2015年10月08日 星期四 15时14分01秒
 ************************************************************************/

#include "preprocess.h"
#include "cut.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <dirent.h>
#include "opencv2/core/core.hpp"  
#include"opencv2/highgui/highgui.hpp"  
#include"opencv2/imgproc/imgproc.hpp"  
using namespace std;


/*
 * 读取图片简历，分析存储文本行（textLine），切分（cut），
 * 重切分（recut），合并（merge）
 */


void preprocessImage(char *filename, char *output_folder) {

	cv::Mat dst = cv::imread(filename);
	//cvtColor(img, dst, CV_BGR2GRAY);
    /*cv::Mat out_pic; 
    cv::Mat binary;    
    medianBlur( dst, out_pic, 7);  
    cv:threshold(out_pic, binary, 100, 255, CV_THRESH_BINARY);
    cv::imwrite("out.jpg", binary);*/

    PreImageProcessor *pip = new PreImageProcessor(dst);
	pip->init();
	
	vector<cv::Mat> textLines = pip->getTextLines();
	vector<cv::RotatedRect> rotatedRects = pip->getRotatedRects();
	vector<pair<int, int> > tlIndex = pip->getTextLineIndex();
	pip->drawRectangles(dst, pip->getRotatedRects());

	// 创建和清空文本
	fstream out("region.txt", ios::out);
	out.close();
	int len = textLines.size();
	//char myfile[16];
	//cout << "序号\t汉字数\t英文数\t高度\t类型" << endl;
	int regionSize = 0;
	for (int i = 0; i < len; ++ i) {
		Region region = cut(textLines[i]);
        char cutpath[64];
        sprintf(cutpath, "%s/tempFiles/cut", output_folder);
        mkdir(cutpath , 0755);
		drawCutLine(region, i, cutpath);
		/*reCut(region);
        char recutpath[32];
        sprintf(recutpath, "%s/tempFiles/recut", output_folder);
        mkdir(recutpath , 0755);
		drawCutLine(region, i, recutpath);*/
		merge(region);
        char mergepath[64];
        sprintf(mergepath, "%s/tempFiles/merge", output_folder);
        mkdir(mergepath , 0755);
		drawCutLine(region, i, mergepath);
        
        cv::RotatedRect rotate = rotatedRects[i];
		cv::Rect rect = rotate.boundingRect();
		saveTextLines(region, i, output_folder, rect.x, rect.y);
		//divideLangRegion(region, i);
		//findTextlineType(region, i);
		//findPatchType(region, i);
		//findEnglishText(region, i);
		saveRegionToFile(region, i, "region.txt", tlIndex[i].first, tlIndex[i].second);
	}
}



int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Please specify the input image and output folder!" << endl;
		return -1;
	}
	mkdir(argv[2], 0755);
    char temppath[32];
    sprintf(temppath, "%s/tempFiles", argv[2]);
    mkdir(temppath , 0755);
	preprocessImage(argv[1], argv[2]);
	
	return 0;
}
