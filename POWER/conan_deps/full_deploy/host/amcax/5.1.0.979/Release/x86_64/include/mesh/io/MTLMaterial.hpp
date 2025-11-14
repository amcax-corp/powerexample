/**
 * @file MTLMaterial.hpp
 * @brief Material definition of MTL file.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

#include <mesh/TriSoup.hpp>

namespace AMCAX::Meshing::Mesh {

/// @brief MTL file data type for obj reader.
template <typename Vec3>
class MTLMaterial
{
public:
	using iNT = std::remove_reference_t<decltype(std::declval<Vec3>()[0])>;

public:
	MTLMaterial()
	  : m_Tr{0.0}
	  , m_illum{1}
	  , m_Ns{0.0}
	  , m_index_map_Kd{0}
	  , m_global_id{static_cast<size_t>(-1)}
	{
		clear();
	}

	void clear()
	{
		m_has_Kd     = false;
		m_has_Ka     = false;
		m_has_Ks     = false;
		m_has_Tr     = false;
		m_has_illum  = false;
		m_has_Ns     = false;
		m_has_map_Kd = false;
		m_global_id  = static_cast<size_t>(-1);
	}

	bool is_valid() const
	{
		return m_has_Kd || m_has_Ka || m_has_Ks || m_has_Tr || m_has_illum ||
		       m_has_Ns || m_has_map_Kd;
	}

	bool has_Kd() const { return m_has_Kd; }
	bool has_Ka() const { return m_has_Ka; }
	bool has_Ks() const { return m_has_Ks; }
	bool has_Tr() const { return m_has_Tr; }
	bool has_illum() const { return m_has_illum; }
	bool has_Ns() const { return m_has_Ns; }
	bool has_map_Kd() const { return m_has_map_Kd; }

	void set_Kd(iNT r, iNT g, iNT b)
	{
		m_Kd     = Vec3{r, g, b};
		m_has_Kd = true;
	}

	void set_Ka(iNT r, iNT g, iNT b)
	{
		m_Ka     = Vec3{r, g, b};
		m_has_Ka = true;
	}

	void set_Ks(iNT r, iNT g, iNT b)
	{
		m_Ks     = Vec3{r, g, b};
		m_has_Ks = true;
	}

	void set_Tr(iNT Tr)
	{
		m_Tr     = Tr;
		m_has_Tr = true;
	}

	void set_illum(int illum)
	{
		m_illum     = illum;
		m_has_illum = true;
	}

	void set_Ns(iNT Ns)
	{
		m_Ns     = Ns;
		m_has_Ns = true;
	}

	void set_map_Kd(const std::string &Kd_name, size_t index_map_Kd)
	{
		m_map_Kd       = Kd_name;
		m_index_map_Kd = index_map_Kd;
		m_has_map_Kd   = true;
	}

	void set_global_id(size_t id) { m_global_id = id; }

	const Vec3        &Kd() const { return m_Kd; }
	const Vec3        &Ka() const { return m_Ka; }
	const Vec3        &Ks() const { return m_Ks; }
	iNT                Tr() const { return m_Tr; }
	int                illum() const { return m_illum; }
	iNT                Ns() const { return m_Ns; }
	const std::string &map_Kd() const { return m_map_Kd; }
	size_t             map_Kd_index() const { return m_index_map_Kd; }
	size_t             global_id() const { return m_global_id; }

private:
	Vec3        m_Kd;           // diffuse
	Vec3        m_Ka;           // ambient
	Vec3        m_Ks;           // specular
	iNT         m_Tr;           // transperency
	int         m_illum;        // illumination model
	iNT         m_Ns;           // shininess
	std::string m_map_Kd;       // texture
	size_t      m_index_map_Kd; // texture index
	size_t      m_global_id;    // material index

	bool m_has_Kd;
	bool m_has_Ka;
	bool m_has_Ks;
	bool m_has_Tr;
	bool m_has_illum;
	bool m_has_Ns;
	bool m_has_map_Kd;
};

} // namespace AMCAX::Meshing::Mesh