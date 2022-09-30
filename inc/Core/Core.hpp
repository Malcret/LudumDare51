#pragma once

#include <Core/Logger.hpp>
#include <string>

#define ASSERT(x) if (!x) { LOG_ERROR("{0}:{1}: Assertion failed !", __FILE__, __LINE__); abort(); }
#define ASSERT_MSG(x, msg) if (!x) { LOG_ERROR("{0}:{1}: Assertion failed: {2}", __FILE__, __LINE__, msg); abort(); }
#define ASSERT_QUIET(x) if (!x) { abort(); }