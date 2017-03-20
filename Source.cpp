#include <iostream>
#include <cmath>
#include <cstdlib>
#define PI 3.1415926

struct MYPOINT
{
	double longitude;
	double latitude;
};



_declspec(dllexport) void initializePoint(MYPOINT  *point);
_declspec(dllexport) double distanceLongLat(double longitudeA, double longitudeB, double latitudeA, double latitudeB);
_declspec(dllexport) void minLonmaxLat(MYPOINT * point, int NUM, double *minLongitude, double* maxLatitude);
_declspec(dllexport) double makeScreenPoint(MYPOINT * point, int NUM);

//其它程序调用动态链接库的接口
_declspec(dllexport) double mymain(MYPOINT *mypoint, int NUM)
{
	double maxdistance = makeScreenPoint(mypoint, NUM);
	return maxdistance;
}


_declspec(dllexport) double distanceLongLat(double longitudeA, double longitudeB, double latitudeA, double latitudeB)
{
	//弧度转换成度
	double longA = longitudeA * PI / 180;
	double longB = longitudeB * PI / 180;
	double latA = latitudeA * PI / 180;
	double latB = latitudeB * PI / 180;
	double dellatlong = longB - longA;
	//角AOB
	double radianAB = acos(sin(latA) * sin(latB) + cos(latA) * cos(latB) * cos(dellatlong));

	return (radianAB * 6378000);
}



//获取经度最小纬度最大
_declspec(dllexport) double makeScreenPoint(MYPOINT * point, int NUM)
{
	double minLongitude = point[0].longitude;
	double maxLatitude = point[0].latitude;
	minLonmaxLat(point, NUM, &minLongitude, &maxLatitude);
//求距离参照点最远的点
	double maxdistance = distanceLongLat(minLongitude, point[0].longitude, maxLatitude, point[0].latitude);
	for (int i = 0; i < NUM; i++)
	{
		maxdistance = __max(maxdistance, distanceLongLat(minLongitude, point[i].longitude, maxLatitude, point[i].latitude));
	}
	return maxdistance;
}


_declspec(dllexport) void minLonmaxLat(MYPOINT * point, int NUM, double * minLongitude, double * maxLatitude)
{
	for (int i = 0; i < NUM; i++)
	{
		*minLongitude = __min(*minLongitude, point[i].longitude);
		*maxLatitude = __max(*maxLatitude, point[i].latitude);
	}
}


