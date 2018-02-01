#include <gtest/gtest.h>
#include "log.h"
#include "log_output.h"

TEST(Log, output_type)
{
    LogOutput_Initialize("test");
    LogFatal("fatal");
    LogErr("err");
    LogWarn("warn");
    LogInfo("info");
    LogDbg("debug");
    LogTrace("trace");
    LogUndo();
    LogTag();
}

TEST(Log, output_detail)
{
    LogInfo("%s, %d, %f", "hello", 123456, 12.345);
    LogInfo("%d, %f, %s", 123456, 12.345, "world");
}