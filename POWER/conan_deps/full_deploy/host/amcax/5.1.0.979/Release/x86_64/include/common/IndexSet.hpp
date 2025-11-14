/// @file      IndexSet.hpp
/// @brief     Template class of indexed set
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <cassert>
#include <deque>
#include <unordered_map>

#include <common/Exception.hpp>

namespace AMCAX
{
/// @brief Template class of indexed set
/// @tparam key_type Type of key
/// @tparam hasher Type of hasher
/// @tparam keyeq Type of equality operator
template<class key_type, class hasher = std::hash<key_type>, class keyeq = std::equal_to<key_type>>
class IndexSet
{
public:
	/// @brief Internal map type
	using map_type = std::unordered_map<key_type, int, hasher, keyeq>;

	/// @brief Internal vector of pointers
	using vector_type = std::deque<typename map_type::value_type*>;

	/// @brief Default constructor
	IndexSet() noexcept(noexcept(map_type()) && noexcept(vector_type())) = default;

	/// @brief Construct from a range of keys
	/// @tparam iter The type of iterator
	/// @param first The first iterator
	/// @param last The last iterator
	template<typename iter>
	explicit IndexSet(iter first, iter last)
	{
		for (iter it = first; it != last; ++it)
		{
			insert(*it);
		}
	}

	/// @brief Copy constructor
	/// @param other The other indexed set
	IndexSet(const IndexSet& other)
	{
		operator=(other);
	}

	/// @brief Default move constructor
	IndexSet(IndexSet&& other) noexcept
		: data(std::move(other.data)),
		  map(std::move(other.map))
	{
	}

	/// @brief Default desctructor
	~IndexSet() noexcept = default;

	/// @brief Copy assignment
	/// @details Copy the map and reconstruct the vector of iterators
	/// @param other The other indexed set
	/// @return The reference to self
	IndexSet& operator=(const IndexSet& other)
	{
		if (this != &other)
		{
			map = other.map;
			data.resize(other.data.size());
			for (auto it = map.begin(); it != map.end(); ++it)
			{
				data[it->second] = &(*it);
			}
		}
		return *this;
	}

	/// @brief Default move assignment
	IndexSet& operator=(IndexSet&& other) noexcept
	{
		if (this != &other)
		{
			map = std::move(other.map);
			data = std::move(other.data);
		}
		return *this;
	}

	/// @brief Is the set empty
	/// @return True if the set is empty
	[[nodiscard]] bool empty() const noexcept
	{
		return data.empty();
	}

	/// @brief Get the size of the set
	/// @return The size of the set
	[[nodiscard]] int size() const noexcept
	{
		return static_cast<int>(data.size());
	}

	/// @brief Clear the indexed set
	void clear() noexcept
	{
		data.clear();
		map.clear();
	}

	/// @brief Insert a new key
	/// @details If there is a key equal to the new key, do nothing and return the index of the existed key
	/// @tparam T The type of new key
	/// @param key The new key
	/// @return The index of the new key
	template<typename T>
	int insert(T&& key)
	{
		int id = static_cast<int>(data.size());
		auto [it, success] = map.try_emplace(std::forward<T>(key), id);
		if (success)
		{
			data.push_back(&(*it));
		}
		return it->second;
	}

	/// @brief Erase the i-th element
	/// @details Swap the last element and the i-th element and erase the last element
	/// @param i The index
	/// @return True if the index is valid
	bool erase(int i) noexcept
	{
		if (i < 0 || i >= size())
		{
			return false;
		}
		std::swap(data[i], data.back());
		data[i]->second = i;
		map.erase(data.back()->first);
		data.pop_back();
		return true;
	}

	/// @brief Erase a key if it is in the set
	/// @param key The key
	/// @return True if the key is erased
	bool erase_data(const key_type& key)
	{
		const auto it = map.find(key);
		if (it == map.end())
		{
			return false;
		}
		std::swap(data[it->second], data.back());
		data[it->second]->second = it->second;
		data.pop_back();
		map.erase(it);
		return true;
	}

	/// @brief Exchange the i-th and j-th elements
	/// @param i The first index
	/// @param j The second index
	/// @return True if the indices are valid
	bool exchange(int i, int j) noexcept
	{
		if (i >= 0 && i < size() && j >= 0 && j < size())
		{
			if (i != j)
			{
				std::swap(data[i]->second, data[j]->second);
				std::swap(data[i], data[j]);
			}
			return true;
		}
		return false;
	}

	/// @brief Erase the last element
	/// @return True if the set is not empty
	bool erase_last() noexcept
	{
		if (data.empty())
		{
			return false;
		}
		map.erase(data.back()->first);
		data.pop_back();
		return true;
	}

	/// @brief Get the i-th element
	/// @param i The index
	/// @return The i-the element
	[[nodiscard]] const key_type& operator[](int i) const noexcept
	{
		assert(i >= 0 && i < size());
		return data[i]->first;
	}

	/// @brief Does the set contain a given key
	/// @param key The given key
	/// @return True if the set contains the given key
	[[nodiscard]] bool contains(const key_type& key) const
	{
		return map.find(key) != map.end();
	}

	/// @brief Get the index of a given key
	/// @param key The given key
	/// @return The index of the given key if the key is found, or the invalid index otherwise
	[[nodiscard]] int index(const key_type& key) const
	{
		const auto it = map.find(key);
		if (it != map.end())
		{
			return it->second;
		}
		return InvalidIndex;
	}

	/// @brief Set the i-th element by a given key
	/// @tparam T The type of key
	/// @param i The index
	/// @param key The key
	/// @return True if the index is valid, and the key is not in the set
	template<typename T>
	bool set(int i, T&& key)
	{
		if (i < 0 || i >= size() || map.find(key) != map.end())
		{
			return false;
		}
		map.erase(data[i]->first);
		data[i] = &(*map.try_emplace(std::forward<T>(key), i).first);
		return true;
	}

	/// @brief Get the iterator of the first element
	/// @return The begin iterator
	[[nodiscard]] constexpr auto begin() noexcept
	{
		return data.begin();
	}

	/// @brief Get the const iterator of the first element
	/// @return The const begin iterator
	[[nodiscard]] constexpr auto begin() const noexcept
	{
		return data.begin();
	}

	/// @brief Get the const iterator of the first element
	/// @return The const begin iterator
	[[nodiscard]] constexpr auto cbegin() const noexcept
	{
		return data.cbegin();
	}

	/// @brief Get the iterator after the last element
	/// @return The end iterator
	[[nodiscard]] constexpr auto end() noexcept
	{
		return data.end();
	}

	/// @brief Get the const iterator after the last element
	/// @return The end iterator
	[[nodiscard]] constexpr auto end() const noexcept
	{
		return data.end();
	}

	/// @brief Get the const iterator after the last element
	/// @return The end iterator
	[[nodiscard]] constexpr auto cend() const noexcept
	{
		return data.cend();
	}

	/// @brief Get the reversed iterator of the last element
	/// @return The revserd begin iterator
	[[nodiscard]] constexpr auto rbegin() noexcept
	{
		return data.rbegin();
	}

	/// @brief Get the reversed const iterator of the last element
	/// @return The reversed const begin iterator
	[[nodiscard]] constexpr auto rbegin() const noexcept
	{
		return data.rbegin();
	}

	/// @brief Get the reversed const iterator of the last element
	/// @return The reversed const begin iterator
	[[nodiscard]] constexpr auto crbegin() const noexcept
	{
		return data.crbegin();
	}

	/// @brief Get the reversed iterator before the first element
	/// @return The reversed end iterator
	[[nodiscard]] constexpr auto rend() noexcept
	{
		return data.rend();
	}

	/// @brief Get the reversed const iterator before the first element
	/// @return The reversed const end iterator
	[[nodiscard]] constexpr auto rend() const noexcept
	{
		return data.rend();
	}

	/// @brief Get the reversed const iterator before the first element
	/// @return The reversed const end iterator
	[[nodiscard]] constexpr auto crend() const noexcept
	{
		return data.crend();
	}

	/// @brief Get the map from key to index
	/// @return The map from key to index
	[[nodiscard]] constexpr auto& inverse_map() const noexcept
	{
		return map;
	}

	/// @brief Invalid index
	static constexpr int InvalidIndex = -1;

private:
	/// @brief Data of the indexed set, from index to key
	vector_type data;

	/// @brief Map from key to index
	map_type map;
};
} // namespace AMCAX
