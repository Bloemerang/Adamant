#ifndef DebugDefs_H__
#define DebugDefs_H__
/**
 * @file
 * @brief Contains various definitions used for debugging within Flexigin.
 * @author   Steven Bloemer
 * @date     12/9/2010
 * @lastedit 12/16/2010
 */
#include <functional>
#include <cassert>

#ifdef DEBUG
#define FLEXI_DEBUG
#endif

namespace flexi {
namespace util {

/// The type of the application-defined assertion callback
typedef std::function<void(const char *const, unsigned, const char *const)>
    AssertionCallback;

/**
 * @brief Ensures that @a expr is true before returning to the caller.
 * 
 * Returns immediately if @a expr is true, otherwise calls the application-
 * defined assert function (if set) and then calls @c assert(false) from the
 * standard C header @c assert.h.
 * 
 * Inasmuch as a failed assertion ultimately crashes the program, it is strongly
 * recommended that flexiAssert be used only to detect programmer errors, and
 * not to detect runtime errors. The former will generally be tested for and
 * eliminated before deployment, while the latter are out of the programmer's
 * control and must be handled in a way that allows the program to respond
 * gracefully.
 * 
 * It may be argued that many programmer errors cannot be entirely eliminated
 * before deployment, and thus calling this function amounts to leaving a bomb
 * in the code. This argument is absolutely correct, and underlines the
 * importance of not using flexiAssert() if the error it would be detecting must
 * be responded to gracefully at runtime.
 * 
 * @param expr The expression to ensure the truth-ness of.
 * @param file A C-string giving the file in which this function was called.
 * @param line The line number at which this function was called.
 * @param message An optional character string forwarded to application-defined
 *  assertion functions. The intention is that @a message explains the error
 *  that occurred if the assertion failed.
 */
inline void _flexi_assert(const bool expr,
                          const char *const file, const unsigned line,
                          const char *const message = 0);

#ifdef FLEXI_DEBUG

/// Calls _flexi_assert with the file and line number.
#define flexiAssert(expr) //(flexi::util::_flexi_assert(expr, __FILE__, __LINE__))
/// Calls _flexi_assert with the file and line number and specified failure message
#define flexiAssertM(expr, message) //(flexi::util::_flexi_assert(expr, __FILE__, __LINE__, message))

#else

#define flexiAssert(expr)
#define flexiAssertM(expr, message)

#endif

/**
 * @brief Sets the function called when flexiAssert() is called with a false
 *  @a expr value.
 *  
 *  The function need not abort the program, since flexiAssert() does so
 *  automatically if the assertion function returns. The function must not call
 *  flexiAssert(), otherwise an infinite recursion will occur.
 *  
 *  The assertion callback must take a constant character constant pointer, a
 *  constant unsigned integer, and a constant character constant pointer in
 *  order. The first character pointer receives the file name in which the
 *  assertion occurred. The unsigned integer receives the line number in which
 *  the assertion occurred. The second and last character pointer receives a
 *  message explaining the error, or null if no message was provided.
 */
void setAssertFunction(const AssertionCallback& callback);

} // namespace util
} // namespace flexi

#endif // DebugDefs_H__