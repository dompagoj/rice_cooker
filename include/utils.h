#pragma once

#ifdef IF_RELEASE
#define IF_RELEASE(x) x
#else
#define IF_RELEASE(x)
#endif

#ifdef IF_DEBUG
#define IF_DEBUG(x) x
#else
#define IF_DEBUG(x)
#endif
