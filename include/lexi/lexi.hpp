//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexi public header.
 */

#pragma once

#include "bool.hpp"
#include "char.hpp"
#include "int.hpp"
#include "enum.hpp"
#include "float.hpp"
#include "null.hpp"
#include "detail/string.hpp"
#include "detail/type.hpp"


namespace lexi
{
// OBJECTS
// -------


/** \brief Type detection for formatting overloads.
 */
struct Format
{
    template <typename T>
    enable_if_t<is_null_pointer_v<T>, FormatNull>
    operator()(const T t)
    {
        return FormatNull(t);
    }

    template <typename T>
    enable_if_t<is_bool_v<T>, FormatBool>
    operator()(const T t)
    {
        return FormatBool(t);
    }

    template <typename T>
    enable_if_t<is_char_v<T>, FormatChar>
    operator()(const T t)
    {
        return FormatChar(t);
    }

    template <typename T>
    enable_if_t<is_integer_v<T>, FormatInt>
    operator()(const T t)
    {
        return FormatInt(t);
    }

    template <typename T>
    enable_if_t<is_float_v<T>, FormatFloat>
    operator()(const T t)
    {
        return FormatFloat(t);
    }

    template <typename T>
    enable_if_t<is_enum_v<T>, FormatEnum>
    operator()(const T t)
    {
        return FormatEnum(t);
    }

    template <typename T>
    enable_if_t<is_fpos_v<T>, FormatInt>
    operator()(const T t)
    {
        return FormatInt(std::streamoff(t));
    }
};


/** \brief Type detection for extraction overloads.
 */
template <typename T>
struct Extract
{
    template <typename U = T>
    enable_if_t<is_null_pointer_v<U>, T>
    operator()(const std::string &string)
    {
        return ExtractNull(string).null();
    }

    template <typename U = T>
    enable_if_t<is_bool_v<U>, T>
    operator()(const std::string &string)
    {
        return T(ExtractBool(string));
    }

    template <typename U = T>
    enable_if_t<is_char_v<U>, T>
    operator()(const std::string &string)
    {
        return T(ExtractChar(string));
    }

    template <typename U = T>
    enable_if_t<is_integer_v<U>, T>
    operator()(const std::string &string)
    {
        return T(ExtractInt(string));
    }


    template <typename U = T>
    enable_if_t<is_float_v<U>, T>
    operator()(const std::string &string)
    {
        return T(ExtractFloat(string));
    }

    template <typename U = T>
    enable_if_t<is_enum_v<U>, T>
    operator()(const std::string &string)
    {
        return T(ExtractEnum(string));
    }

    template <typename U = T>
    enable_if_t<is_fpos_v<U>, T>
    operator()(const std::string &string)
    {
        return T(std::streamoff(ExtractInt(string)));
    }
};


// FUNCTIONS
// ---------


/** \brief Extract value from string.
 */
template <typename T>
T lexi(const std::string &string, enable_if_t<!is_string_v<T>, T>* = nullptr)
{
    return Extract<T>()(string);
}


/** \brief Extract value from string literal.
 */
template <typename T>
T lexi(const char *string, enable_if_t<!is_string_v<T>, T>* = nullptr)
{
    return Extract<T>()(string);
}


/** \brief Format value to string.
 */
template <typename T>
std::string lexi(const T &t, enable_if_t<!is_string_v<T>, T>* = nullptr)
{
    return Format()(t).string();
}


/** \brief Overload for existing string types.
 */
template <typename T>
std::string lexi(const T &string, enable_if_t<is_string_v<T>, T>* = nullptr)
{
    return string;
}


/** \brief Format value to string.
 */
template <typename T>
std::string string(const T &t, enable_if_t<!is_string_v<T>, T>* = nullptr)
{
    return Format()(t).string();
}



/** \brief Overload for existing string types.
 */
template <typename T>
std::string string(const T &string, enable_if_t<is_string_v<T>, T>* = nullptr)
{
    return string;
}


/** \brief Format escaped value to string.
 */
template <typename T>
std::string escape(const T &t, enable_if_t<!is_string_v<T>, T>* = nullptr)
{
    return Format()(t).escape();
}


/** \brief Escape existing string.
 */
template <typename T>
std::string escape(const T &string, enable_if_t<is_string_v<T>, T>* = nullptr)
{
    return detail::escape(string);
}


/** \brief Format value to JSON-literal.
 */
template <typename T>
std::string jsonify(const T &t, enable_if_t<!is_string_v<T>, T>* = nullptr)
{
    return Format()(t).jsonify();
}


/** \brief Format string to JSON-literal.
 */
template <typename T>
std::string jsonify(const T &string, enable_if_t<is_string_v<T>, T>* = nullptr)
{
    return "\"" + detail::jsonify(string) + "\"";
}

}   /* lexi */
