#ifndef DSSTRING_H
#define DSSTRING_H
#include <iostream>

class DSString{

private:
    char *data; // a pointer to a character array containing the string with a `\0` terminator
    size_t len; // the length of the string (without the terminator)
    // Note: we keep the terminator only so we can return a c-string version in function c_str().
public:
    DSString();
    DSString(const char *c);
    // constructor that converts a cstring
    // you can also provide  DSString(const string &); for std::string

    // Rule of three is needed if dynamic memory allocation is used
    DSString(const DSString &);            // copy constructor
    DSString(const char c);
    ~DSString();
    DSString &operator=(const DSString &);
    DSString &operator=(const char*); // assignment operator
    // you can also implement the move versions for the big 5 (C+11)
    size_t length(const char*); // returns the length of the string
    char &operator[](size_t); // returns a reference to the character at the given index
    /**
     * Overloaded operator+ which appends the string in the argument to this string
     */
    DSString operator+(const DSString &) const;

    DSString operator+(const char) const;
    DSString operator+=(const char original) ;

    /**
     * Standard relational operators to compare and order your strings.
     * Feel free to add additional.
     **/
    bool operator==(const DSString &) const;
    bool operator<(const DSString &) const;
    bool operator>(const DSString &) const;
    // bool operator!=(const DSString &) const;
    /**
     * The substring method returns a new string object that contains a
     * sequence of characters from this string object.
     *
     * param start - the index of where to start
     * param numChars - the number (count) of characters to copy into
     *    the substring
     * @return a DSString object containing the requested substring
     **/
    DSString substring(size_t start, size_t numChars) const;
    /**
     * @brief Returns a new string object with all characters in lowercase
     *
     * @return DSString
     */
    DSString toLower(const DSString &) const; // look at the ASCII table for this!
    /**
     * the c_str function returns a pointer a null-terminated c-string holding the
     * contents of this object. Since data already has a `\0`
     * at the end of the string in DSString so you can just return a pointer to data.
     **/
    char *c_str() const;
    // a conversion to std::string would also be nice: string string() const;
    /**
     * Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument. Remember:
     * This operator needs to be implemented outside of the class as
     * a friend because it operates on the stream and not the DSString object.
     **/
   friend std::ostream &operator<<(std::ostream &, const DSString &);
    // You are free to add more functionality to the class.  For example,
    // you may want to add a find(...) function that will search for a
    // substring within a string or a function that breaks a string into words.
    // You will need a split or tokenize function.

    size_t getLength(){ return len; };

    void resize();
    void resize(size_t);

    //void cleanString(const DSString &tweet);
    void cleanString();


};

#endif
