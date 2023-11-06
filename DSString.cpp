#include "DSString.h"

/*
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project.
 *
 * Note that c-strings use `\0` as a terminator symbol
 * but your class should store its length in a member variable. Do not use c-string functions
 * from <string.h> or <cstring> other than for conversion from a c-string.
 */

DSString::DSString()
{
    data = new char[1];
    data[0] = '\0';
    len = 0;
}

DSString::DSString(const char *c)
{
    len = strlen(c);
    data = new char[len + 1];
    strcpy(data, c);
}

DSString::DSString(const DSString &c)
{
    len = c.len;
    data = new char[len + 1];
    strcpy(data, c.data);
    data[len] = '\0';
}

DSString::DSString(const char c)
{
    len = 1;
    data = new char[len + 1];
    data[0] = c;
    data[1] = '\0';
}

DSString::~DSString()
{
    delete[] data;
}

DSString &DSString::operator=(const DSString &original)
{
    DSString lhs;
    delete[] lhs.data;
    lhs.len = original.len;
    lhs.data = new char[lhs.len + 1];
    for (size_t i = 0; i < lhs.len; ++i)
    {
        lhs.data[i] = original.data[i];
    }
    lhs.data[lhs.len] = '\0';
    return lhs;

}

DSString &DSString::operator=(const char *s)
{
    len = strlen(s);
    data = new char[strlen(s) + 1];
    strcpy(data, s);
    data[len] = '\0';
    return *this;
}

size_t DSString::length(const char *s)
{
    size_t ret = strlen(s);
    return ret;
}

char &DSString::operator[](size_t num)
{
    return data[num];
}

DSString DSString::operator+(const DSString &original) const
{

    size_t l = len + original.len + 1;
    char *w = new char[100];
    for (size_t i = 0; i < len; ++i)
    {
        w[i] = data[i];
    }
    for (size_t i = 0; i < original.len; ++i)
    {
        w[len + i] = original.data[i];
    }
    w[l] = '\0';
    DSString ret(w);
    delete[] w;
    return ret;
}

DSString DSString::operator+=(const char original)
{
    size_t l = len + 1;
    char *newdat = new char[l + 1];
    for (size_t i = 0; i < l - 1; ++i)
    {
        newdat[i] = data[i];
    }
    newdat[l - 1] = original;
    newdat[l] = '\0';

    delete[] data;
    this->data = newdat;
    this->len = l;

    return *this;
}

DSString DSString::operator+(const char c) const
{

    // std::cout<< "in +operator" << std::endl;
    DSString lhs;
    lhs.len = this->len + 1;
    delete[] lhs.data;
    lhs.data = new char[lhs.len + 1];
    for (size_t i = 0; i < this->len; ++i)
        lhs.data[i] = this->data[i];
    lhs.data[lhs.len] = '\0';
    lhs.data[lhs.len - 1] = c;
    return lhs;
}

bool DSString::operator==(const DSString &original) const
{
    if ((original.data == this->data) && (original.len == this->len))
    {
        return true;
    }
    else
        return false;
}

bool DSString::operator<(const DSString &original) const
{   

    size_t smallLen;
    if(original.len > len)
        smallLen = len;
    else
        smallLen = original.len;

    for (size_t i = 0; i < smallLen; ++i)
    {
        if (((original.data[i]) + 0) < (data[i] + 0))
            return false;
        if (((original.data[i]) + 0) > (data[i] + 0))
            return true;
    }

    return len < original.len;
}

DSString DSString::substring(size_t start, size_t numChars) const
{

//    DSString rhs;
//    rhs.len = numChars;
//    rhs.data = new char[rhs.len + 1];
    char* rhs = new char[numChars];
    for (size_t i = 0; i < numChars; ++i)
    {
        rhs[i] = data[start + i];
    }

    rhs[numChars] = '\0';
    DSString ret(rhs);

    return ret;
}

DSString DSString::toLower(const DSString &original) const
{
    DSString low = original;

    for (size_t i = 0; i < len; ++i)
    {
        if (((low.data[i] + 0) > 64) && ((low.data[i] + 0) < 97))
        {
            low.data[i] += 32;
        }
    }
    return low;
}

char *DSString::c_str() const
{
    return data;
}

std::ostream &operator<<(std::ostream &c, const DSString &original)
{

    if (original.data != nullptr)
    {
        c << original.data;
    }
    return c;
}

void DSString::cleanString()
{

    DSString original = *this;
    DSString cleantweet("");

    // std::cout<< "Original: " << original << std::endl;
    // std::cout<< "Cleantweet:" << cleantweet << "." << std::endl;

    // std::cout << std::endl << "Original string: " << original;
    for (size_t i = 0; i < original.getLength(); ++i)
    {
        char c = original.data[i];
        if ((c >= 'a' && c <= 'z') || c == ' ')
        {
            cleantweet += c;
        }
        else if ((c >= 'A') && (c <= 'Z'))
        {
            cleantweet += (c + 32);
        }
    }

    //std::cout<< "Clean tweet post loop:" << cleantweet << "." << std::endl;

    char * tmp = data;
    data = cleantweet.data;
    len = cleantweet.len;
    cleantweet.data = tmp;

}