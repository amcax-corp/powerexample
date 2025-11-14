/// @file      Bimap.hpp
/// @brief     Template class of bidirectional map
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <unordered_map>

namespace AMCAX
{
/// @brief Template class of bidirectional map
/// @tparam key_type Type of key
/// @tparam value_type Type of value
template<typename key_type, typename value_type>
class Bimap
{
public:
	/// @brief Type of the forward map
	using map_type1 = std::unordered_map<key_type, value_type>;

	/// @brief Type of the inverse map
	using map_type2 = std::unordered_map<value_type, key_type>;

	/// @brief Iterator of the forward map
	using map_iterator1 = typename map_type1::iterator;

	/// @brief Iterator of the inverse map
	using map_iterator2 = typename map_type2::iterator;

	/// @brief Constant iterator of the forward map
	using map_const_iterator1 = typename map_type1::const_iterator;

	/// @brief Constant iterator of the inverse map
	using map_const_iterator2 = typename map_type2::const_iterator;

	/// @brief Default constructor
	Bimap() noexcept(noexcept(map_type1()) && noexcept(map_type2())) = default;

	/// @brief Construct from a normal map
	/// @param smap The map
	explicit Bimap(const std::unordered_map<key_type, value_type>& smap)
		: map1(smap)
	{
		for (map_iterator1 it1 = map1.begin(); it1 != map1.end(); ++it1)
		{
			const map_iterator2 it2 = map2.find(it1->second);
			if (it2 != map2.end())
			{
				map1.erase(it2->second);
				it2->second = it1->first;
			}
			else
			{
				map2.insert({it1->second, it1->first});
			}
		}
	}

	/// @brief Is the map empty
	/// @return True if the map is empty
	[[nodiscard]] bool empty() const noexcept
	{
		return map1.empty();
	}

	/// @brief Get the size of map
	/// @return The size of map
	[[nodiscard]] int size() const noexcept
	{
		return static_cast<int>(map1.size());
	}

	/// @brief Clear the map
	void clear() noexcept
	{
		map1.clear();
		map2.clear();
	}

	/// @brief Insert a pair of key and value
	/// @details If either the key or the value is found in the map, do nothing
	/// @param key The key to be inserted
	/// @param value The value to be inserted
	/// @return True if the insertion succeed
	bool insert(const key_type& key, const value_type& value)
	{
		const map_iterator1 it1 = map1.find(key);
		const map_iterator2 it2 = map2.find(value);
		if (it1 == map1.end() && it2 == map2.end())
		{
			map1.insert({key, value});
			map2.insert({value, key});
			return true;
		}
		return false;
	}

	/// @brief Insert a pair of key and value, replace the data if existed
	/// @details If the key and value are both found in the map, but not mapped to each other, the insertion fails.
	/// @param key The key to be inserted
	/// @param value The value to be inserted
	/// @return True if the insertion succeed
	bool insert_replace(const key_type& key, const value_type& value)
	{
		const map_iterator1 it1 = map1.find(key);
		const map_iterator2 it2 = map2.find(value);
		if (it1 == map1.end() && it2 == map2.end())
		{
			map1.insert({key, value});
			map2.insert({value, key});
		}
		else if (it1 == map1.end())
		{
			map1.erase(map1.find(it2->second));
			map1.insert({key, value});
			it2->second = key;
		}
		else if (it2 == map2.end())
		{
			map2.erase(map2.find(it1->second));
			map2.insert({value, key});
			it1->second = value;
		}
		else if (it1->second != value || it2->second != key)
		{
			return false;
		}
		return true;
	}

	/// @brief Erase the data by key
	/// @param key The key to be erased
	/// @return True if the key is erased
	bool erase_key(const key_type& key)
	{
		const auto it = map1.find(key);
		if (it == map1.end())
		{
			return false;
		}
		map2.erase(it->second);
		map1.erase(it);
		return true;
	}

	/// @brief Erase the data by iterator of forward map
	/// @param it The iterator of forward map
	/// @return The iterator after the erased iterator
	map_iterator1 erase_key(map_iterator1 it) noexcept
	{
		map2.erase(it->second);
		return map1.erase(it);
	}

	/// @brief Erase the data by constant iterator of forward map
	/// @param it The constant iterator of forward map
	/// @return The iterator after the erased iterator
	map_iterator1 erase_key(map_const_iterator1 it) noexcept
	{
		map2.erase(it->second);
		return map1.erase(it);
	}

	/// @brief Erase the data by value
	/// @param value The value to be erased
	/// @return True if the value is erased
	bool erase_value(const value_type& value)
	{
		const auto it = map2.find(value);
		if (it == map2.end())
		{
			return false;
		}
		map1.erase(it->second);
		map2.erase(it);
		return true;
	}

	/// @brief Erase the data by iterator of inverse map
	/// @param it The iterator of inverse map
	/// @return The iterator after the erased iterator
	map_iterator2 erase_value(map_iterator2 it) noexcept
	{
		map1.erase(it->second);
		return map2.erase(it);
	}

	/// @brief Erase the data by constant iterator of inverse map
	/// @param it The constant iterator of inverse map
	/// @return The iterator after the erased iterator
	map_iterator2 erase_value(map_const_iterator2 it) noexcept
	{
		map1.erase(it->second);
		return map2.erase(it);
	}

	/// @brief Swap with another bimap
	/// @param other The other bimap
	void swap(Bimap& other) noexcept(noexcept(std::declval<map_type1>().swap(other.map1)) && noexcept(std::declval<map_type2>().swap(other.map2)))
	{
		map1.swap(other.map1);
		map2.swap(other.map2);
	}

	/// @brief Find the value from a key
	/// @param k The key
	/// @return The pair of iterator of map and a boolean which shows whether the key is found
	[[nodiscard]] std::pair<map_const_iterator1, bool> find_value_from_key(const key_type& k) const
	{
		map_const_iterator1 it = map1.find(k);
		return {it, it != map1.end()};
	}

	/// @brief Find the key from a value
	/// @param v The value
	/// @return The pair of iterator of inverse map and a boolean which shows whether the value is found
	[[nodiscard]] std::pair<map_const_iterator2, bool> find_key_from_value(const value_type& v) const
	{
		map_const_iterator2 it = map2.find(v);
		return {it, it != map2.end()};
	}

	/// @brief Get the begin iterator
	/// @return The begin iterator
	[[nodiscard]] constexpr auto begin() noexcept
	{
		return map1.begin();
	}

	/// @brief Get the constant begin iterator
	/// @return The constant begin iterator
	[[nodiscard]] constexpr auto begin() const noexcept
	{
		return map1.begin();
	}

	/// @brief Get the constant begin iterator
	/// @return The constant begin iterator
	[[nodiscard]] constexpr auto cbegin() const noexcept
	{
		return map1.cbegin();
	}

	/// @brief Get the end iterator
	/// @return The end iterator
	[[nodiscard]] constexpr auto end() noexcept
	{
		return map1.end();
	}

	/// @brief Get the constant end iterator
	/// @return The constant end iterator
	[[nodiscard]] constexpr auto end() const noexcept
	{
		return map1.end();
	}

	/// @brief Get the constant end iterator
	/// @return The constant end iterator
	[[nodiscard]] constexpr auto cend() const noexcept
	{
		return map1.cend();
	}

	/// @brief Get the inverse map
	/// @return The inverse map
	[[nodiscard]] constexpr auto& inverse_map() const noexcept
	{
		return map2;
	}

protected:
	/// @brief Map from key to value
	map_type1 map1;

	/// @brief Map from value to key
	map_type2 map2;
};
} // namespace AMCAX
