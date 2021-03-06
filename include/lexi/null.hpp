//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for null types.
 */

#pragma once

#include "detail/fmt.hpp"


namespace lexi
{
// OBJECTS
// -------


/** \brief Generic null formatter.
 */
class FormatNull
{
protected:
    char buffer_[5];

public:
    FormatNull();
    FormatNull(const std::nullptr_t nullp);

    // DATA
    size_t size() const;
    size_t length() const;
    const char * data() const;
    const char * c_str() const;

    std::string string() const;
    std::string escape() const;
    std::string jsonify() const;

    // CONVERSIONS
    explicit operator std::string() const;
};


/** \brief Generic null extractor.
 */
struct ExtractNull
{
    ExtractNull(const std::string &string);

    std::nullptr_t null() const;

    // CONVERSIONS
    explicit operator std::nullptr_t() const;
};

}   /* lexi */
