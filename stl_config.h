#ifndef __STL_CONFIG_H_
#define __STL_CONFIG_H_


#define __STL_BEGIN_NAMESPACE namespace miniSTL {
#define __STL_END_NAMESPACE }

#define __STL_USE_EXCEPTIONS

#ifdef __STL_USE_EXCEPTIONS

#define __STL_TRY try
#define __STL_CATCH_CALL catch(...)
#define __STL_THROW(x) throw x
#define __STL_RETHROW throw
#define __STL_NOTHROW throw()
#define __STL_UNWIND(action) catch(...) { action; throw; }


#else 

#define __STL_TRY
#define __STL_CATCH_CALL if (false)
#define __STL_THROW(x)
#define __STL_RETHROW
#define __STL_NOTHROW
#define __STL_UNWIND(action)



#endif








#endif