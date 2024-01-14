//
// Created by j50036120 on 2023/9/20.
//

#ifndef LEETCODE_CPP_COMMON_H
#define LEETCODE_CPP_COMMON_H

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifdef SPDLOG
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#endif

#ifdef GTEST
#include <gtest/gtest.h>
#endif

#ifdef DOCTEST
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#endif

#include "algorithm/Sorter.h"
#include "algorithm/Utils.h"
#include "list/BLNode.h"
#include "list/ListNode.h"
#include "log/Logger.h"
#include "tree/TreeNode.h"

#endif  // LEETCODE_CPP_COMMON_H
