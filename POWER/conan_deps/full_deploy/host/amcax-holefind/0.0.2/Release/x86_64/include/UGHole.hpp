#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Hole.hpp"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

enum class ChamferType
{
	Fillet, //RADIUS_TOP_CHAMFER
	Straight,//ANGLE_TOP_CHAMFER
	Error
};

enum class ThreadRotation
{
	left, //左旋
	right, //右旋
	Unknow //不知道
};

class Chamfer
{
public:
	Chamfer() = default;
	Chamfer(const face_node& face);
	ChamferType GetType();
	double GetMessage() const;
	double GetDeepth()const;

	bool m_hasdate = false;
	face_node m_shape;
};

class SideCylinder
{
public:
	SideCylinder() = default;
	SideCylinder(const face_node& _side);

	double GetDiameter()const;
	
	double m_roughness=6.3;
	face_node m_side;
};

class BottomFace
{
public:
	BottomFace() = default;
	BottomFace(const face_node& _bottom);

	double GetAngle()const;
	double m_roughness=6.3;
	bool hasbottom=false;
	face_node m_bottom;
};

enum class UGHoleType
{
	STEPXHOLE,    //通孔
	STEPXHOLE_THREAD,//带螺纹通孔
	STEPXPOCKET, //盲孔
	STEPXPOCKET_THREAD,//带螺纹盲孔
	POCKET_ROUND_TAPERED, //锥形盲孔
	HOLE_ROUND_TAPERED //锥形通孔
};

class __declspec(dllexport) UGHole
{
public:
	UGHole() = default;
	virtual UGHoleType GetHoleType() const = 0;
	virtual std::string GetTypeName() const = 0;
	virtual json WriteJson() const = 0;

	std::vector<face_node> m_parts;
    std::vector<face_node> m_rest_parts;
	std::vector<std::string> name;
};

class __declspec(dllexport) STEP_X_Hole:public UGHole
{
public:
	STEP_X_Hole() = default;
	STEP_X_Hole(size_t n);
	STEP_X_Hole(const std::vector<face_node>& parts);
	STEP_X_Hole(const CommonHole& hole);

	UGHoleType GetHoleType() const override;
	std::string GetTypeName() const override;
	json WriteJson() const override;

	void Init(const std::vector<face_node>& parts);
	
	size_t m_X = 1;
	Chamfer m_bottom_chamfer;
	Chamfer m_top_chamfer;

  std::vector<BottomFace> m_Bottoms;  //数量为X-1
	std::vector<Chamfer> m_BottomChamferXs; //数量为X
	std::vector<Chamfer> m_TopChamferXs;//X

	double m_Depth=0;
	std::vector<double> m_SingleDepths; //数量为X-1
	std::vector<SideCylinder> m_sides;

	int m_subtype = 0;
	double m_TILTES_BOTTOM_DEPTH = 0;//底部倾斜深度
	double m_TILTER_TOP_DEPTH = 0;//顶部倾斜深度


};

class __declspec(dllexport) HOLE_ROUND_TAP :public UGHole
{
public:
	HOLE_ROUND_TAP() = default;
	HOLE_ROUND_TAP(const std::vector<face_node>& parts);
	HOLE_ROUND_TAP(const CommonHole& hole);
	UGHoleType GetHoleType() const override;
	std::string GetTypeName() const override;
	json WriteJson() const override;

	SideCylinder side;
	double m_Depth = 0;
	double m_TILTES_BOTTOM_DEPTH = 0;//底部倾斜深度
	double m_TILTER_TOP_DEPTH = 0;//顶部倾斜深度

};

class __declspec(dllexport) POCKET_ROUND_TAP :public UGHole
{
public:
	POCKET_ROUND_TAP() = default;
	POCKET_ROUND_TAP(const std::vector<face_node>& parts);
	POCKET_ROUND_TAP(const CommonHole& hole);
	UGHoleType GetHoleType() const override;
	std::string GetTypeName() const override;
	json WriteJson() const override;

	SideCylinder side;
	BottomFace m_bottom;
	double m_Depth = 0;
	double m_TILTER_TOP_DEPTH = 0;//顶部倾斜深度

};
class __declspec(dllexport) STEPXHOLE_THREAD :public STEP_X_Hole
{
public:
	STEPXHOLE_THREAD() = default;
	STEPXHOLE_THREAD(size_t n);
	STEPXHOLE_THREAD(const std::vector<face_node>& parts);
	STEPXHOLE_THREAD(const CommonHole& hole);

	UGHoleType GetHoleType() const override;
	std::string GetTypeName() const override;
	json WriteJson() const override;

	void InitThread(const Thread& thread);
	
	std::string ThreadCallout="MXX";
	double m_ThreadAngle = 60;
	int m_ThreadDiameterNR = 1;
	std::string m_ThreadForm ="M Profile";
	double m_ThreadLength=0;
	double m_ThreadMajorDiameter=0;
	double m_ThreadMinorDiameter = 0;
	std::string threadMethod = "CUT"; //螺纹生成方式，没见过其他的方式，类型应该最好是枚举类
	size_t m_ThreadNumberOfStarts = 1;//螺纹头数
	double m_ThreadPitch=0;//螺距
	ThreadRotation m_rotation = ThreadRotation::Unknow;
	bool m_ThreadTapered = false;//不支持锥度螺纹，
	double m_ThreadTappedDrilSize=0;//螺纹底孔直径


private:
	Thread m_thread;
};

class __declspec(dllexport) STEP_X_POCKET :public UGHole
{
public:
	STEP_X_POCKET() = default;
	STEP_X_POCKET(size_t n);
	STEP_X_POCKET(const std::vector<face_node>& parts);
	STEP_X_POCKET(const CommonHole& hole);

	UGHoleType GetHoleType() const override;
	std::string GetTypeName() const override;
	json WriteJson() const override;

	void Init(const std::vector<face_node>& parts);

	size_t m_X;

	Chamfer m_top_chamfer;
	BottomFace m_bottom;
	std::vector<BottomFace> m_Bottoms;  //数量为X-1
	std::vector<Chamfer> m_BottomChamferXs; //数量为X
	std::vector<Chamfer> m_TopChamferXs;//X

	double m_Depth;
	std::vector<double> m_SingleDepths;//数量为X
	std::vector<SideCylinder> m_sides;

	int m_subtype = 0;
	double m_TILTER_TOP_DEPTH = 0;//顶部倾斜深度

};

class __declspec(dllexport) STEPX_POCKET_THREAD :public STEP_X_POCKET
{
public:
	STEPX_POCKET_THREAD() = default;
	STEPX_POCKET_THREAD(size_t n);
	STEPX_POCKET_THREAD(const std::vector<face_node>& parts);
	STEPX_POCKET_THREAD(const CommonHole& hole);

	UGHoleType GetHoleType() const override;
	std::string GetTypeName() const override;
	json WriteJson() const override;

	void InitThread(const Thread& thread);

	std::string ThreadCallout="MXX";
	double m_ThreadAngle = 60;
	int m_ThreadDiameterNR = 1;
	std::string m_ThreadForm="M Profile";
	double m_ThreadLength=0;
	double m_ThreadMajorDiameter=0;
	double m_ThreadMinorDiameter = 0;
	std::string threadMethod = "CUT"; //螺纹生成方式，没见过其他的方式，类型应该最好是枚举类
	size_t m_ThreadNumberOfStarts=1;//螺纹头数
	double m_ThreadPitch=0;//螺距
	ThreadRotation m_rotation = ThreadRotation::Unknow;
	bool m_ThreadTapered = false;//不支持锥度螺纹，
	double m_ThreadTappedDrilSize = 0;//螺纹底孔直径

private:
	Thread m_thread;
};

__declspec(dllexport)
std::shared_ptr<UGHole> GetUGHoleMessage(const std::vector<face_node>& faces);

__declspec(dllexport)
std::shared_ptr<UGHole> GetUGHoleMessage(const CommonHole& hole);