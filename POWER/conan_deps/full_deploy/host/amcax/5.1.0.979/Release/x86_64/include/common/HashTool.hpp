/// @file      HashTool.hpp
/// @brief     Template classes used to compute hash values
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <climits>
#include <cstdint>
#include <functional>

namespace AMCAX
{
/// @brief Mixture function of new values, used for combination of
/// @tparam Bits Number of bits in a value
template<size_t Bits>
struct MixImpl;

/// @brief Mixture function for 64-bit hash values
template<>
struct MixImpl<64>
{
	/// @brief Get the mixture of a 64-bit hash value
	/// @param x The value
	/// @return The hash mixture
	[[nodiscard]] static constexpr uint64_t Value(uint64_t x) noexcept
	{
		constexpr uint64_t m = (uint64_t{0xe9846af} << 32) + 0x9b1a615d;
		x ^= x >> 32;
		x *= m;
		x ^= x >> 32;
		x *= m;
		x ^= x >> 28;
		return x;
	}
};

/// @brief Mixture function for 32-bit hash values
template<>
struct MixImpl<32>
{
	/// @brief Get the mixture of a 32-bit hash value
	/// @param x The value
	/// @return The hash mixture
	[[nodiscard]] static constexpr uint32_t Value(uint32_t x) noexcept
	{
		constexpr uint32_t m1 = 0x21f0aaad;
		constexpr uint32_t m2 = 0x735a2d97;
		x ^= x >> 16;
		x *= m1;
		x ^= x >> 15;
		x *= m2;
		x ^= x >> 15;
		return x;
	}
};

/// @brief Tool for compute hash values
class HashTool
{
private:
	/// @brief Base combine function, do nothing
	static void _Combine(size_t& /*seed*/) noexcept
	{
	}

	/// @brief Recursive computation of combination of arbitrary number of values
	/// @tparam T1 The type of the first value
	/// @tparam ...T2 The types of the other values
	/// @param[in,out] seed The hash value
	/// @param[in] v The first value
	/// @param[in] ...vs The other values
	template<typename T1, typename... T2>
	static void _Combine(size_t& seed, const T1& v, const T2&... vs) noexcept
	{
		Combine(seed, v);
		_Combine(seed, vs...);
	}

	/// @brief Base combine function, do nothing
	static void _UnorderedCombine(size_t& /*seed*/) noexcept
	{
	}

	/// @brief Recursive computation of unordered combination of arbitrary number of values
	/// @tparam T1 The type of the first value
	/// @tparam ...T2 The types of the other values
	/// @param[in,out] seed The hash value
	/// @param[in] v The first value
	/// @param[in] ...vs The other values
	template<typename T1, typename... T2>
	static void _UnorderedCombine(size_t& seed, const T1& v, const T2&... vs) noexcept
	{
		size_t r(seed);
		Combine(r, v);
		_UnorderedCombine(seed, vs...);
		seed += r;
	}

public:
	/// @brief Mix the hash value
	/// @param v The hash value
	/// @return The mixed hash value
	[[nodiscard]] static constexpr size_t Mix(size_t v) noexcept
	{
		return MixImpl<sizeof(size_t) * CHAR_BIT>::Value(v);
	}

	/// @brief Combine the hash value with another value
	/// @tparam T The type of value
	/// @param seed The hash value
	/// @param v The value to be hashed
	template<typename T>
	static void Combine(size_t& seed, const T& v) noexcept
	{
		seed = Mix(seed + 0x9e3779b9 + std::hash<T>{}(v));
	}

	/// @brief Compute the hash value for a sequence of values
	/// @tparam ...T The types of the values
	/// @param ...vs The values
	/// @return The hash value
	template<typename... T>
	[[nodiscard]] static size_t Value(const T&... vs) noexcept
	{
		size_t seed = 0;
		_Combine(seed, vs...);
		return seed;
	}

	/// @brief Compute the hash value for an unordered sequence of values
	/// @tparam ...T The types of the values
	/// @param ...vs The values
	/// @return The hash value
	template<typename... T>
	[[nodiscard]] static size_t UnorderedValue(const T&... vs) noexcept
	{
		size_t seed = 0;
		_UnorderedCombine(seed, vs...);
		return seed;
	}

	/// @brief Combine the hash value with a sequence of values
	/// @tparam Iter The type of iterator
	/// @param[in,out] seed The hash value
	/// @param[in] first The begin iterator
	/// @param[in] last The end iterator
	template<typename Iter>
	static void Range(size_t& seed, Iter first, Iter last) noexcept
	{
		for (; first != last; ++first)
		{
			Combine(seed, *first);
		}
	}

	/// @brief Compute the hash value for a sequence of values
	/// @tparam Iter The type of iterator
	/// @param first The begin iterator
	/// @param last The end iterator
	/// @return The hash value
	template<typename Iter>
	[[nodiscard]] static size_t Range(Iter first, Iter last) noexcept
	{
		size_t seed = 0;
		Range(seed, first, last);
		return seed;
	}

	/// @brief Combine the hash value with an unordered sequence of values
	/// @tparam Iter The type of iterator
	/// @param[in,out] seed The hash value
	/// @param[in] first The begin iterator
	/// @param[in] last The end iterator
	template<typename Iter>
	static void UnorderedRange(size_t& seed, Iter first, Iter last) noexcept
	{
		size_t r = 0;
		const size_t s2 = seed;
		for (; first != last; ++first)
		{
			size_t s3(s2);
			Combine(s3, *first);
			r += s3;
		}
		seed += r;
	}

	/// @brief Compute the hash value for an unordered sequence of values
	/// @tparam Iter The type of iterator
	/// @param first The begin iterator
	/// @param last The end iterator
	/// @return The hash value
	template<typename Iter>
	[[nodiscard]] static size_t UnorderedRange(Iter first, Iter last) noexcept
	{
		size_t seed = 0;
		UnorderedRange(seed, first, last);
		return seed;
	}
};
} // namespace AMCAX

namespace std
{
/// @brief Compute a hash value for a pair
/// @tparam T1 The type of the first value
/// @tparam T2 The type of the second value
template<typename T1, typename T2>
struct hash<pair<T1, T2>>
{
	/// @brief Compute a hash value for a pair
	/// @param pair The pair
	/// @return The hash value
	[[nodiscard]] size_t operator()(const pair<T1, T2>& pair) const noexcept
	{
		return AMCAX::HashTool::Value(pair.first, pair.second);
	}
};

/// @brief Compute a hash value for a vector
/// @tparam T The type of vector element
template<typename T>
struct hash<vector<T>>
{
	/// @brief Compute a hash value for a vector
	/// @param vec The vector
	/// @return The hash value
	[[nodiscard]] size_t operator()(const vector<T>& vec) const noexcept
	{
		return AMCAX::HashTool::Range(vec.begin(), vec.end());
	}
};
} // namespace std
