
#define CMAKE_WINDOWS_BUILD
#include "extractDeepFeature.h"
#include "cJSON.h"
#include<iostream>
#include<fstream>
#include <stdbool.h>
#include <omp.h>
#include<string>
//#include<io.h>


using namespace std;

cv::Mat alignFace(cv::Mat img, cv::Rect rects, std::vector<cv::Point2d>& points);

typedef struct faceFeature {
	string name;
	vector<float> feature;
};

//从文件读入到string里
string readFileIntoString(char * filename)
{
	ifstream ifile(filename);
	//将文件读入到ostringstream对象buf中
	ostringstream buf;
	char ch;
	while (buf&&ifile.get(ch))
		buf.put(ch);
	//返回与流对象buf关联的字符串
	return buf.str();
}




void Create_Pkgs(char* option1, char* option2)
{
	cJSON *root, *fld;
	char *out;
	FILE* fp = fopen("test.json", "w+");
	root = cJSON_CreateArray();

	cJSON_AddItemToArray(root, fld = cJSON_CreateObject());
	cJSON_AddStringToObject(fld, "id", "c1");
	cJSON_AddStringToObject(fld, "option", option1);
	cJSON_AddStringToObject(fld, "fid", "1");

	cJSON_AddItemToArray(root, fld = cJSON_CreateObject());
	cJSON_AddStringToObject(fld, "id", "p1");
	cJSON_AddStringToObject(fld, "option", option2);
	cJSON_AddStringToObject(fld, "fid", "2");

	out = cJSON_Print(root);
	fprintf(fp, out);
	fclose(fp);

	cJSON_Delete(root);
	//free(out);

	out = NULL;
	root = NULL;
}


void addobject(char*option1, char*simil, cJSON *root, cJSON *fld) {
	cJSON_AddItemToArray(root, fld = cJSON_CreateObject());
	cJSON_AddStringToObject(fld, "pair", option1);
	cJSON_AddStringToObject(fld, "similarity", simil);

}



void  ReadDataFromFileLBLIntoString() //比数组好 大小不限制 更灵活的按行读取
{
	ifstream fin("lfw_left.txt");
	string  s;
	string table[1000];
	int n=0 ;
	while (getline(fin, s))
	{ 
		cout << s << endl;
		table[n] = s;
		n += 1;
	}
	
}



int main() {


	vector<faceFeature> hugeVector;

	//boost::shared_ptr<Net<float> > _net;
	string model_file = "face_deploy.prototxt";
	string trained_file = "face_model.caffemodel";
	//Caffe::set_mode(Caffe::CPU);
	FaceRecognition moModel(model_file, trained_file);





	ifstream fin("lfw_left.txt");
	string  s;
	string table1[1000];
	string table2[1000];
	int n = 0;
	while (getline(fin, s))
	{
		//cout << s << endl;
		if (n <= 999) {
		    table1[n] = s;   
		}
		else {
			table2[n - 1000] = s;
		}
		n += 1;

	}
	    // line by line存入数组

	cout << table2[0] << endl;
	cout << table1[999] << endl;

	double table_result[1000];
	for (int i = 0; i < 1000; i++) {
		

		cv::Mat lhs_origin = cv::imread(table1[i]);
		cv::Mat rhs_origin = cv::imread(table2[i]);
		//cv::imshow("1", lhs_origin);
		//
		//cv::imshow("2", rhs_origin);
		
	  // std::cout << moModel.getSimilarity(lhs_origin, rhs_origin)<<endl;

	   double  similarity = moModel.getSimilarity(lhs_origin, rhs_origin) ;
	   table_result[i] = similarity;
	   cout << table_result[i]  << endl;

	}


	 fstream outfile;
	 outfile.open("lable_pridic.txt", ios::out);
	 if (!outfile)
	 {
		cout << "file can not open" << endl;
		abort();
    }
	 cout << "saving similariyt" << endl;
	 for (int i = 0; i<1000; i++)
	 {
	 
	 	outfile << to_string(table_result[i]) + "\n";
	 }
	 outfile.close();
	 std::system("pause");

	


//	
//	cJSON* omg =NULL;
//	string jsonString = readFileIntoString("final_result.json");
//	omg = cJSON_Parse(jsonString.c_str());
//	int num = cJSON_GetArraySize(omg);
//	cJSON* node=NULL;
//	cJSON* node1 =NULL ;
//	
//
//	/*
//	std::string file_path = "C:\\Users\\24330\\Desktop\\mxnet_mtcnn_face_detection-master\\pics\\*.png";
//	std::vector<std::string> file_names;
//	
//	intptr_t hFile = 0;
//	_finddata_t fileInfo;
//	hFile = _findfirst(file_path.c_str(), &fileInfo);
//	if (hFile != -1) {
//		
//		do {
//			//如果为文件夹，可以通过递归继续遍历，此处我们不需要
//			//if ((fileInfo.attrib &  _A_SUBDIR)) {
//			//	continue;
//			cout << "ssssssssssssssssssssssssssssss" << endl;
//			//}
//			//如果为单个文件直接push_back
//			//else {
//				
//			file_names.push_back(fileInfo.name);
//			num += 1;
//			cout << fileInfo.name << endl;
//			//}
//
//		} while (_findnext(hFile, &fileInfo) == 0);
//
//		_findclose(hFile);
//	}
//
//
//	for (int i = 0; i < num; i++) {
//		faceFeature face;
//		face.name = "C:\\Users\\24330\\Desktop\\mxnet_mtcnn_face_detection-master\\pics\\"+file_names[i];
//	    cv::Mat lhs = cv::imread(face.name);
//		face.feature = moModel.getvec(lhs);
//		hugeVector.push_back(face);
//		
//	}
//	*/
//   
//	for (int i = 0; i <    num; i++) {
//		faceFeature face;
//
//		node = cJSON_GetArrayItem(omg, i);
//		cout << "nodeget" << endl;
//		char* param = NULL;
//		char* param1 = NULL;
//		
//		param = cJSON_GetObjectItem(node, "path")->valuestring;
//		face.name = param;
//		cout << param << endl;
//		cv::Mat lhs_origin = cv::imread(param);
//		//sprintf(param, "%s", cJSON_GetObjectItem(node, "path")->valuestring);
//		//cout << param << endl;
//
//	    float x, y, width, height;
//		x = atof(cJSON_GetObjectItem(node, "x1")->valuestring);
//		y = atof(cJSON_GetObjectItem(node, "y1")->valuestring);
//		width = atof(cJSON_GetObjectItem(node, "x2")->valuestring) - x;
//		height = atof(cJSON_GetObjectItem(node, "y2")->valuestring) - y;
//		cout << x << endl;
//
//		cJSON *fivepoints = NULL;
//		cJSON *fivepoint = NULL;
//		fivepoints = cJSON_GetObjectItemCaseSensitive(node, "fivepoints");
//		int c_x;
//		int c_y;
//		cv::Rect rect1(x, y, width, height);
//		std::vector<cv::Point2d> originCoordinate1;
//
//		cJSON_ArrayForEach(fivepoint, fivepoints)
//		{
//			cJSON *x = cJSON_GetObjectItemCaseSensitive(fivepoint, "x");
//			cJSON *y = cJSON_GetObjectItemCaseSensitive(fivepoint, "y");
//			c_x = atoi(x->valuestring);
//			c_y = atoi(y->valuestring);
//			cout << c_x << " " << c_y << endl;
//
//			originCoordinate1.push_back(cv::Point2d(c_x, c_y));
//		}
//
//
//
//		cv::Mat lhs = alignFace(lhs_origin, rect1, originCoordinate1);
//		cv::imshow("pic", lhs);
//		cv::imwrite(std::to_string(i) + ".jpg", lhs);
//		face.feature = moModel.getvec(lhs);
//		hugeVector.push_back(face);
//
//
//		//for (int j = i + 1; j < num; j++) {
//		//	node1 = cJSON_GetArrayItem(omg, j);
//		//	sprintf(param1, "%s", cJSON_GetObjectItem(node, "path")->valuestring);
//		//	cout << param1 << endl;
//		//}
//	}
//	
//
//	cJSON *root, *fld;
//	
//	//FILE* fp = fopen("3.json", "w+");
//	ofstream writeFile;
//	writeFile.open("test.json", ios::app);
//	
///*****************for pictures has been alingment ********************/
////	for (int i = 0; i < num; i++) {
////		printf("Current i=%d\n", i);
////		float max = 0.1;
////		int maxnum = 0;
////		float secondmax = 0.0;
////		int secondnum = 0;
////#pragma omp parallel for
////		for (int j = 0; j < num; j++) {
////
////			if (j == i) {
////				continue;
////			}
////
////
////			float similarity = moModel.getsim(hugeVector[i].feature, hugeVector[j].feature);
////
////			root = cJSON_CreateArray();
////			char arrayFloat[20];
////			string pair;
////			cout << similarity << endl;
////			sprintf(arrayFloat, "%f", similarity);
////			pair = hugeVector[i].name + "$" + hugeVector[j].name;
////			cout << pair << endl;
////			addobject((char*)pair.c_str(), arrayFloat, root, fld);
////	
////		}
////		char *out;
////		out = cJSON_Print(root);
////		writeFile << out << endl;
////		cJSON_Delete(root);
////		free(out);
////		out = NULL;
////		root = NULL;
////
////	}
//
//	
//	for (int i = 0; i < num; i++) {
//		printf("Current i=%d\n", i);
//		float max = 0.1;
//		int maxnum = 0;
//		float secondmax = 0.0;
//		int secondnum = 0;
//#pragma omp parallel for
//		for (int j = 0; j < num; j++) {
//
//			if (j == i) {
//				continue;
//			}
//
//
//			float similarity =moModel.getsim(hugeVector[i].feature, hugeVector[j].feature);
//
//			if (similarity > secondmax) {
//
//				if (similarity > max) {
//					maxnum = j;
//					max = similarity;
//				}
//				else {
//					secondmax = similarity;
//					secondnum = j;
//				}
//
//			}
//		}
//
//
//		char *out;
//		root = cJSON_CreateArray();
//		char arrayFloat[20];
//		string pair;
//		cout << max << endl;
//		sprintf(arrayFloat, "%f", max);
//		pair = hugeVector[i].name + "$" + hugeVector[maxnum].name;
//		addobject((char*)pair.c_str(), arrayFloat, root, fld);
//
//		sprintf(arrayFloat, "%f", secondmax);
//		pair = hugeVector[i].name + "$" + hugeVector[secondnum].name;
//		addobject((char*)pair.c_str(), arrayFloat, root, fld);
//		out = cJSON_Print(root);
//		writeFile << out << endl;
//		cJSON_Delete(root);
//		free(out);
//		out = NULL;
//		root = NULL;
//	}
//	
//	//printf(fp, out);
//
//	//fclose(fp);
//
//
//	writeFile.close();
//
//
	
	

	std::system("pause");



	cv::Mat rhs_origin = cv::imread("68488464.jpg");


	float x, y, width, height;

	x = 257.0;
	y = 288.0;
	width = 638.0 - 257.0;
	height = 782.0 - 288.0;
	cv::Rect rect1(x, y, width, height);





	std::vector<cv::Point2d> originCoordinate2;
	originCoordinate2.push_back(cv::Point2d(98.0, 206.0));
	originCoordinate2.push_back(cv::Point2d(190.0, 206.0));
	originCoordinate2.push_back(cv::Point2d(144.0, 265.0));
	originCoordinate2.push_back(cv::Point2d(112.0, 310.0));
	originCoordinate2.push_back(cv::Point2d(181.0, 308.0));

	//cv::Mat lhs = alignFace(lhs_origin, rect1, originCoordinate1);
	//cv::Mat rhs = alignFace(rhs_origin, rect2, originCoordinate2);

	 


	//std::cout << moModel.getSimilarity(lhs_origin, rhs_origin);
	/*
	while (1) {
		cv::imshow("1", lhs);
		cv::imshow("2", rhs);
		cv::imwrite("mtcnn_mxy.jpg", rhs);
		cv::waitKey(1);
	}
	
	system("pause");
	*/

	return 0;
}



cv::Mat alignFace(cv::Mat img, cv::Rect rects, std::vector<cv::Point2d>& points)
{
	std::vector<cv::Point2d> targrtCoordinate;

	targrtCoordinate.push_back(cv::Point2d(30.2946, 51.6963));
	targrtCoordinate.push_back(cv::Point2d(65.5318, 51.5014));
	targrtCoordinate.push_back(cv::Point2d(48.0252, 71.7366));
	targrtCoordinate.push_back(cv::Point2d(33.5493, 92.3655));
	targrtCoordinate.push_back   (cv::Point2d(62.7299, 92.2041));
	cv::Mat alignImg;
	cv::Mat transform = cv::estimateRigidTransform(points, targrtCoordinate, 0);
	if (((transform.type() == CV_32F || transform.type() == CV_64F) && transform.rows == 2 && transform.cols == 3))
	{
		cout << "1" << endl;
		//必须要能正确的进行刚体转换才行
		cv::warpAffine(img, alignImg, transform, cv::Mat::zeros(112, 96, img.type()).size());

		cv::waitKey(1);
		//std::system("pause");
	}
	else
	{
		//直接根据检测坐标进行裁切
		cout << "2" << endl;
		cv::Mat crop = img(cv::Rect(rects.x, rects.y, rects.width, rects.height));
		cv::resize(crop, alignImg, cv::Size(96, 112), 0, 0, CV_INTER_LINEAR);

	}

	return alignImg;
}