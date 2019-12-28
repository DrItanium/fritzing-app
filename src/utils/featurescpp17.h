/*******************************************************************

Part of the Fritzing project - http://fritzing.org
Copyright (c) 2007-2019 Fritzing

Fritzing is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Fritzing is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Fritzing.  If not, see <http://www.gnu.org/licenses/>.

********************************************************************/

#ifndef FEATURES_CPP17_H__ 
#define FEATURES_CPP17_H__ 
#include <type_traits>
#if __cplusplus < 201703L
namespace std {
template<typename From, typename To>
constexpr auto is_convertible_v = is_convertible<From, To>::value;

template<typename Base, typename Derived>
constexpr auto is_base_of_v = is_base_of<Base, Derived>::value;

} // end namespace std
#endif 
template<bool condition>
using ValidWhen = std::enable_if_t<condition, int>;
#endif // end FEATURES_CPP17_H__

