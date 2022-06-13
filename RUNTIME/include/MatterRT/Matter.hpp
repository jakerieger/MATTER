#ifdef MATTER_RT_DLL
#define MATTER_RT_API __declspec(dllexport)
#else
#define MATTER_RT_API __declspec(dllimport)
#endif

namespace Matter {
    namespace Core {}
}