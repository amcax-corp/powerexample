/// @file      BlockMacros.hpp
/// @brief     Parameter class in NextMesh Block
/// @details   Operations related to generated block-structured mesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <nextmesh/Macros.hpp>
#include <string>

namespace AMCAX {
namespace NextMesh {

/// @brief Type of node
enum class NodeType
{
	Unknown,
	Vertex,
	CtrlNode,
};

/// @brief Control node structure
struct CtrlNode
{
	Indext   _id;
	Indext   _eid;
	Indext   _discreteId;
	NMPoint3 _pos;
	double _dist;
	double _t;	//normalized distance from the start point along the edge
	bool _dir; // true: from start to middle, false: from end to middle
};

/// @brief Type of edge distribution
enum class SpacingType
{
	Number,
	Length,
	Linear,
	Geometric,
	BellCurve,
	AutoCFD,
};


/// @brief Control parameters for edge distribution
struct SpacingParam
{
	SpacingType _type;     ///< Distribution type
	unsigned    _mode : 2; ///< 0=count factor, 1=size control
	double      _factor;   ///< Spacing ratio factor
	unsigned    _num;      ///< Number of nodes/segments
	double      _startLen; ///< Starting spacing length
	double      _endLen;   ///< Ending spacing length
	bool        _reverse = false;  ///< Reverse distribution direction
	bool        _parallel = false; ///< Apply distribution to parallel edges

	// AutoCFD specific parameters
	double _growthRate;      ///< Growth rate
	double _maxLength;       ///< Maximum spacing
	double _minLength;       ///< Minimum spacing
	double _distortionAngle; ///< Distortion angle (degrees)
	bool   _constraintFlag = false;  ///< Strict constraint flag
};

/// @brief Edge distribution information
struct SpacingInfo
{
    std::string _mode;
    unsigned _num;

    std::vector<double> _segLen;
	std::vector<NMPoint3> _pnts;
};

/// @brief Type of mesh smooth
enum class SmoothType
{
    LAPLACIAN = 0,
    ENERGY_BASED = 1
};

/// @brief Control parameters for mesh smooth
struct SmoothParam
{
	std::vector<Indext> _faceIds;
	std::vector<Indext> _blockIds;
	std::vector<Indext> _orthogonalityFaceIds;
	std::vector<Indext> _boundaryFaceIds;
	std::vector<Indext> _featureLineIds;
	SmoothType          _optimizerType;
	unsigned            _layers;
	unsigned            _maxIteration;
	double              _relaxationFactor;
};

}
}