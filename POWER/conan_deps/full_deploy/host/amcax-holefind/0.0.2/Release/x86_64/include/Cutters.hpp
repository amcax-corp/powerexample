#pragma once
#include <vector>
#include <string>

struct face_node;
class CommonHole;
class SewThread;

enum CutterType
{
	STD_DRIL, //钻孔
	REAMER,//铰孔
	BORING_BAR_STD,//镗孔
  TAP,//攻丝
	THREAD_MILL,//螺纹铣
	T_CUTTER,//T型铣刀
	MCT_POCKET,//锥形刀
	COUNTER_SINK,//锥形沉头铣刀
	COUNTER_BORE,//沉头端铣刀
	other
};

class CutterDrill
{
public:
	CutterDrill() = default;
	virtual CutterType GetType() const = 0;

	double diameter = 0;
	double length = 0;

};

class StdDrill:public CutterDrill
{
public:
	StdDrill() = default;
	StdDrill(double _diameter, double _length, double _angle) ;

	CutterType GetType() const override;

	double angle;
};
class Reamer :public CutterDrill
{
public:
	Reamer() = default;
	Reamer(double _diameter, double _length, double _angle);

	CutterType GetType() const override;

	double angle;//锥角

};
class BoringBarStd :public CutterDrill
{
public:
	BoringBarStd() = default;

	CutterType GetType() const override;

	double LA;//前倾角
	double hilt_diameter;//颈部直径
	double lA;//刀片角
	double PL;//前导长度

};

class Tab :public CutterDrill
{
public:
	Tab() = default;
	CutterType GetType() const override;

	double hilt_diameter;
	double TD; //刀尖直径
	double pitch;//螺距
	double L;//刀刃长度
};

class ThreadMILL :public CutterDrill
{
public:
	ThreadMILL() = default;
	ThreadMILL(double _diameter, double _length, double _hilt_diameter, double _pith);
	
	CutterType GetType() const override;

	double hilt_diameter; //刀柄直径
	double pitch; //螺距

};

class Tcutter : public CutterDrill 
{
public:
	Tcutter() = default;
	Tcutter(double _diameter, double _length, double _hilt_diameter);

	CutterType GetType() const override;

	double hilt_diameter; //刀柄直径
};
class CounterSink: public CutterDrill
{
public:
	CounterSink() = default;
	CounterSink(double _diameter, double _length, double _angle);

	CutterType GetType() const override;

	double angle;
};
class CounterBore : public CutterDrill
{
public:
	CounterBore() = default;
	CounterBore(double _diameter, double _length, double _hilt_diameter);

	CutterType GetType() const override;

	double hilt_diameter; //前导直径
};
class ToolOther :public CutterDrill
{
public:
	ToolOther() = default;

	CutterType GetType() const override;

};

struct myPoint
{
	double x = 0;
	double y = 0;
	double z = 0;
	myPoint() = default;
	myPoint(const myPoint& other);
	myPoint(double _x, double _y, double _z) :x(_x), y(_y), z(_z) {};
	bool operator==(const myPoint& other) const;
	bool operator!=(const myPoint& other) const;
	
};

struct toolpath
{
	myPoint stpos;
	double deep;
	int index = -1;
	double radius;
	double angle;
};

/*@brief: 同一个加工面的加工路径优化
* @param: pathHoles:当前加工面下的所有需要加工的孔，带有分组信息
* @param: direct：加工方向
* @param: _plane：参考加工平面
* @param: hole:加工圆柱面孔的加工路径标记
* @param: threads:所有螺纹
* @param: chamfer:所有倒角
* @param: fillet:所有圆角
*/
std::string ImprovePath(const std::vector<std::vector<CommonHole>>& partHoles, myPoint direct,
	std::vector<toolpath>& hole,std::vector<SewThread>& threads,
	std::vector<face_node>& chamfer,std::vector<face_node>& fillet);