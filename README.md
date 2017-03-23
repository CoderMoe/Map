# Map
C++电子地图
相关理论参考于http://blog.csdn.net/liqiancao/article/details/50480229
http://blog.csdn.net/u011627980/article/details/51518827

以经度最小值和纬度最大值作为坐标原点(minLongitude,maxLatitude)
求其他点到坐标原点的距离（实际地理空间距离），找出最大距离maxDistance
获取屏幕宽度和高度，求出斜对角线的长度，勾股定理
算出最大距离与屏幕斜对角线的比值，再乘以2作为换算比率，ratio
求出每个点相对于原点的x，y轴的距离，除以换算比率得到屏幕坐标


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
