# Map
C++电子地图

source.cpp是一个用c++写的关于地理坐标(经纬度)转换成屏幕坐标的动态链接库
程序调用动态链接库的主要接口是_declspec(dllexport) double mymain(MYPOINT *mypoint, int NUM)函数,函数返回的是最大距离数
参数：MYPOINT
struct MYPOINT
{
	double longitude;
	double latitude;
};




参数：NUM
点的个数(若干个(经度,纬度))
