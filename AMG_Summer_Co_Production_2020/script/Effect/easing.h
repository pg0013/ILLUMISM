#pragma once
/**
 * @file  easing.h
 * @brief イージング
 *
 * @date 2020-06-28
 * @version 1.0
 *
 * Copyright (C) Amusement Media Academy All rights Resved.
 */
#include <string>
#include <unordered_map>
#include <functional>

namespace utility
{
	using Param = std::function<double(double, double, double, double)>;
	using EasingMap = std::unordered_map<std::string, Param>;

	class Easing
	{
	public:
		static Param GetFunction(std::string type)
		{
			return _type.at(type);
		}
	private:
		static const EasingMap _type;

	};
}