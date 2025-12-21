#include "metric_impl/code_lines_count.hpp"

#include <gtest/gtest.h>

namespace analyzer::metric::metric_impl {

constexpr static size_t FUNCS_SIZE = 1;
constexpr static std::string_view METRIC_NAME = "Code lines count";

static analyzer::file::File get_file(std::string_view filename) {
    constexpr static std::string_view FILE_DIR = "src/metric_impl/tests/files";
    return {std::format("{}/{}", FILE_DIR, filename)};
}

static auto get_funcs_metric(std::string_view filename) {
    auto file = get_file(filename);
    auto funcs = analyzer::function::FunctionExtractor{}.Get(file);
    auto metric_result = CodeLinesCountMetric{}.Calculate(funcs[0]);
    return std::make_pair(funcs, metric_result);
}

TEST(CodeLinesCountCheck, Comments) {
    auto [funcs, metric_result] = get_funcs_metric("comments.py");

    EXPECT_EQ(funcs.size(), FUNCS_SIZE);
    EXPECT_EQ(metric_result.metric_name, METRIC_NAME);
    EXPECT_EQ(metric_result.value, 3);
}

TEST(CodeLinesCountCheck, Exceptions) {
    auto [funcs, metric_result] = get_funcs_metric("exceptions.py");

    EXPECT_EQ(funcs.size(), FUNCS_SIZE);
    EXPECT_EQ(metric_result.metric_name, METRIC_NAME);
    EXPECT_EQ(metric_result.value, 7);
}

TEST(CodeLinesCountCheck, If) {
    auto [funcs, metric_result] = get_funcs_metric("if.py");

    EXPECT_EQ(funcs.size(), FUNCS_SIZE);
    EXPECT_EQ(metric_result.metric_name, METRIC_NAME);
    EXPECT_EQ(metric_result.value, 3);
}

TEST(CodeLinesCountCheck, Loops) {
    auto [funcs, metric_result] = get_funcs_metric("loops.py");

    EXPECT_EQ(funcs.size(), FUNCS_SIZE);
    EXPECT_EQ(metric_result.metric_name, METRIC_NAME);
    EXPECT_EQ(metric_result.value, 6);
}

TEST(CodeLinesCountCheck, ManyLines) {
    auto [funcs, metric_result] = get_funcs_metric("many_lines.py");

    EXPECT_EQ(funcs.size(), FUNCS_SIZE);
    EXPECT_EQ(metric_result.metric_name, METRIC_NAME);
    EXPECT_EQ(metric_result.value, 11);
}

TEST(CodeLinesCountCheck, ManyParameters) {
    auto [funcs, metric_result] = get_funcs_metric("many_parameters.py");

    EXPECT_EQ(funcs.size(), FUNCS_SIZE);
    EXPECT_EQ(metric_result.metric_name, METRIC_NAME);
    EXPECT_EQ(metric_result.value, 1);
}

TEST(CodeLinesCountCheck, MatchCase) {
    auto [funcs, metric_result] = get_funcs_metric("match_case.py");

    EXPECT_EQ(funcs.size(), FUNCS_SIZE);
    EXPECT_EQ(metric_result.metric_name, METRIC_NAME);
    EXPECT_EQ(metric_result.value, 7);
}

TEST(CodeLinesCountCheck, NestedIf) {
    auto [funcs, metric_result] = get_funcs_metric("nested_if.py");

    EXPECT_EQ(funcs.size(), FUNCS_SIZE);
    EXPECT_EQ(metric_result.metric_name, METRIC_NAME);
    EXPECT_EQ(metric_result.value, 8);
}

TEST(CodeLinesCountCheck, Simple) {
    auto [funcs, metric_result] = get_funcs_metric("simple.py");

    EXPECT_EQ(funcs.size(), FUNCS_SIZE);
    EXPECT_EQ(metric_result.metric_name, METRIC_NAME);
    EXPECT_EQ(metric_result.value, 5);
}

TEST(CodeLinesCountCheck, Ternary) {
    auto [funcs, metric_result] = get_funcs_metric("ternary.py");

    EXPECT_EQ(funcs.size(), FUNCS_SIZE);
    EXPECT_EQ(metric_result.metric_name, METRIC_NAME);
    EXPECT_EQ(metric_result.value, 1);
}

}  // namespace analyzer::metric::metric_impl
