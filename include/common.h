//
// Created by j50036120 on 2023/9/20.
//

#ifndef LEETCODE_CPP_COMMON_H
#define LEETCODE_CPP_COMMON_H

#include <iostream>
#include <sstream>
#include <memory>
#include <exception>

#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cstring>


#ifdef SPDLOG
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#endif

#ifdef GTEST
#include <gtest/gtest.h>
#endif

#ifdef DOCTEST
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#endif

#include "list/LNode.h"
#include"list/ListNode.h"
#include "tree/TreeNode.h"
#include "algorithm/Sorter.h"
#include "algorithm/Utils.h"
#include "log/Logger.h"

#endif //LEETCODE_CPP_COMMON_H
