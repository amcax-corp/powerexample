/// @file      IndexMap.hpp
/// @brief     Template class of indexed map
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <cassert>
#include <deque>
#include <unordered_map>

#include <common/Exception.hpp>

namespace AMCAX
{
/// @brief Template class of indexed map
/// @tparam key_type Type of key
/// @tparam value_type Type of value
/// @tparam hasher Type of hasher
/// @tparam keyeq Type of equality operator
template<class key_type, class value_type, class hasher = std::hash<key_type>, class keyeq = std::equal_to<key_type>>
class IndexMap
{
public:
	/// @brief Internal map type
	using map_type = std::unordered_map<key_type, int, hasher, keyeq>;

	/// @brief Internal vector of pointers
	using vector_type = std::deque<typename map_type::value_type*>;

	/// @brief Internal vector of values
	using value_vector_type = std::deque<value_type>;

	/// @brief Default constructor
	IndexMap() noexcept(noexcept(map_type()) && noexcept(vector_type()) && noexcept(value_vector_type())) = default;

	/// @brief Construct from a range of key-value pairs
	/// @tparam iter The type of iterator
	/// @param first The first iterator
	/// @param last The last iterator
	template<typename iter>
	explicit IndexMap(iter first, iter last)
	{
		for (iter it = first; it != last; ++it)
		{
			insert(it->first, it->second);
		}
	}

	/// @brief Copy constructor
	/// @param other The other indexed map
	IndexMap(const IndexMap& other)
	{
		operator=(other);
	}

	/// @brief Default move constructor
	IndexMap(IndexMap&& other) noexcept
		: data(std::move(other.data)),
		  values(std::move(other.values)),
		  map(std::move(other.map))
	{
	}

	/// @brief Default destructor
	~IndexMap() = default;

	/// @brief Copy assignment
	/// @details Copy the map and reconstruct the vector of iterators
	/// @param other The other indexed map
	/// @return The reference to self
	IndexMap& operator=(const IndexMap& other)
	{
		if (this != &other)
		{
			map = other.map;
			values = other.values;
			data.resize(other.data.size());
			for (auto it = map.begin(); it != map.end(); ++it)
			{
				data[it->second] = &(*it);
			}
		}
		return *this;
	}

	/// @brief Default move assignment
	IndexMap& operator=(IndexMap&& other) noexcept
	{
		if (this != &other)
		{
			map = std::move(other.map);
			values = std::move(other.values);
			data = std::move(other.data);
		}
		return *this;
	}

	/// @brief Is the map empty
	/// @return True if the map is empty
	[[nodiscard]] bool empty() const noexcept
	{
		return data.empty();
	}

	/// @brief Get the size of the map
	/// @return The size of the map
	[[nodiscard]] int size() const noexcept
	{
		return static_cast<int>(data.size());
	}

	/// @brief Clear the indexed map
	void clear() noexcept
	{
		data.clear();
		values.clear();
		map.clear();
	}

	/// @brief Insert a key with a value
	/// @details If there is a key in the map equal to the given key, do nothing and return the index of the existed key
	/// @tparam K Type of new key
	/// @tparam V Type of new value
	/// @param key The new key
	/// @param value The new value
	/// @return The index of the new key
	template<typename K, typename V>
	int insert(K&& key, V&& value)
	{
		int id = static_cast<int>(data.size());
		auto [it, success] = map.try_emplace(std::forward<K>(key), id);
		if (success)
		{
			data.push_back(&(*it));
			values.push_back(std::forward<V>(value));
		}
		return it->second;
	}

	/// @brief Insert a key with a value in-place construction
	/// @details If there is a key in the map equal to the given key, do nothing and return the index of the existed key
	/// @tparam K Type of new key
	/// @tparam ...V Type of new value
	/// @param key The new key
	/// @param ...value The new value
	/// @return The index of the new key
	template<typename K, typename... V>
	int emplace(K&& key, V&&... value)
	{
		int id = static_cast<int>(data.size());
		auto [it, success] = map.try_emplace(std::forward<K>(key), id);
		if (success)
		{
			data.push_back(&(*it));
			values.emplace_back(std::forward<V>(value)...);
		}
		return it->second;
	}

	/// @brief Insert a new key with a value or replace a value of an existed key
	/// @tparam K Type of new key
	/// @tparam V Type of new value
	/// @param key The new key
	/// @param value The new value
	/// @return The index of the new key or the existed key
	template<typename K, typename V>
	int insert_replace(K&& key, V&& value)
	{
		const auto it = this->map.find(key);
		if (it == this->map.end())
		{
			int id = static_cast<int>(data.size());
			data.push_back(&(*map.try_emplace(std::forward<K>(key), id).first));
			values.push_back(std::forward<V>(value));
			return id;
		}
		else
		{
			values[it->second] = std::forward<V>(value);
			return it->second;
		}
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
		std::swap(values[i], values.back());
		data[i]->second = i;
		map.erase(data.back()->first);
		data.pop_back();
		values.pop_back();
		return true;
	}

	/// @brief Erase a key if it is in the map
	/// @param key The key
	/// @return True if the key is erased
	bool erase_key(const key_type& key)
	{
		const auto it = map.find(key);
		if (it == map.end())
		{
			return false;
		}
		std::swap(data[it->second], data.back());
		std::swap(values[it->second], values.back());
		data[it->second]->second = it->second;
		data.pop_back();
		values.pop_back();
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
				std::swap(values[i], values[j]);
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
		values.pop_back();
		return true;
	}

	/// @brief Get the value from a key
	/// @param key The key
	/// @return The corresponding value
	[[nodiscard]] const value_type& operator[](const key_type& key) const
	{
		const auto it = map.find(key);
		Throw_Out_of_Range_if(it == map.end(), "key not exist");
		return values[it->second];
	}

	/// @brief Get the value from a key
	/// @param key The key
	/// @return The correspoding value
	[[nodiscard]] value_type& operator[](const key_type& key)
	{
		const auto it = map.find(key);
		Throw_Out_of_Range_if(it == map.end(), "key not exist");
		return values[it->second];
	}

	/// @brief Get the i-th value
	/// @param id The index
	/// @return The i-th value
	[[nodiscard]] const value_type& operator()(int id) const noexcept
	{
		assert(id >= 0 && id < size());
		return values[id];
	}

	/// @brief Get the i-th value
	/// @param id The index
	/// @return The i-th value
	[[nodiscard]] value_type& operator()(int id) noexcept
	{
		assert(id >= 0 && id < size());
		return values[id];
	}

	/// @brief Get the i-th key
	/// @param id The index
	/// @return The i-th key
	[[nodiscard]] const key_type& find_key(int id) const noexcept
	{
		assert(id >= 0 && id < size());
		return data[id]->first;
	}

	/// @brief Does the map contain a given key
	/// @param key The given key
	/// @return True if the map contains the given key
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

	/// @brief Set the i-th element by a given key and a given value
	/// @tparam K Type of new key
	/// @tparam ...T Type of new value
	/// @param i The index
	/// @param key The key
	/// @param ...value The value
	/// @return True if the index is valid, and the key is not in the set
	template<typename K, typename... T>
	bool set(int i, K&& key, T&&... value)
	{
		if (i < 0 || i >= size() || map.find(key) != map.end())
		{
			return false;
		}
		map.erase(data[i]->first);
		data[i] = &(*map.try_emplace(std::forward<K>(key), i).first);
		values[i] = value_type(std::forward<T>(value)...);
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

	/// @brief Invalid index
	static constexpr int InvalidIndex = -1;

private:
	/// @brief Vector of iterators
	vector_type data;

	/// @brief Vector of values
	value_vector_type values;

	/// @brief Map from key to index of value
	map_type map;
};
} // namespace AMCAX
