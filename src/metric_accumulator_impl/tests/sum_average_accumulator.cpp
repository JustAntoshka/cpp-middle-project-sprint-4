#include "metric_accumulator_impl/sum_average_accumulator.hpp"

#include <gtest/gtest.h>

#include <cmath>

namespace analyzer::metric_accumulator::metric_accumulator_impl::test {

TEST(SumAverageAccumulatorCheckThrow, Empty) {
    SumAverageAccumulator acc;
    EXPECT_THROW(acc.Get(), std::runtime_error);
}

TEST(SumAverageAccumulatorCheckThrow, NonFinalized) {
    SumAverageAccumulator acc;
    metric::MetricResult mr;
    acc.Accumulate(mr);
    EXPECT_THROW(acc.Get(), std::runtime_error);
}

TEST(SumAverageAccumulatorCheckThrow, Reset) {
    SumAverageAccumulator acc;
    acc.Reset();
    EXPECT_THROW(acc.Get(), std::runtime_error);
}

TEST(SumAverageAccumulatorCheckThrow, AccumulateReset) {
    SumAverageAccumulator acc;
    metric::MetricResult mr;
    acc.Accumulate(mr);
    acc.Reset();
    EXPECT_THROW(acc.Get(), std::runtime_error);
}

TEST(SumAverageAccumulatorCheckThrow, AccumulateFinalizeReset) {
    SumAverageAccumulator acc;
    metric::MetricResult mr;
    acc.Accumulate(mr);
    acc.Finalize();
    acc.Reset();
    EXPECT_THROW(acc.Get(), std::runtime_error);
}

TEST(SumAverageAccumulatorCheckFinalize, AccumulateOneResult) {
    SumAverageAccumulator acc;
    metric::MetricResult mr;
    acc.Accumulate(mr);
    acc.Finalize();
    auto [sum, average] = acc.Get();
    EXPECT_EQ(sum, mr.value);
    EXPECT_DOUBLE_EQ(average, mr.value);
}

TEST(SumAverageAccumulatorCheckFinalize, AccumulateTwoResults) {
    SumAverageAccumulator acc;
    metric::MetricResult mr1{"Metric", 1};
    metric::MetricResult mr2{"Metric", 2};
    acc.Accumulate(mr1);
    acc.Accumulate(mr2);
    acc.Finalize();
    auto [sum, average] = acc.Get();
    EXPECT_EQ(sum, mr1.value + mr2.value);
    EXPECT_DOUBLE_EQ(average, static_cast<double>(mr1.value + mr2.value) / 2);
}

TEST(SumAverageAccumulatorCheckReset, AccumulateOneResult) {
    SumAverageAccumulator acc;
    metric::MetricResult mr1;
    metric::MetricResult mr2;
    acc.Accumulate(mr1);
    acc.Reset();
    acc.Accumulate(mr2);
    acc.Finalize();
    auto [sum, average] = acc.Get();
    EXPECT_EQ(sum, mr2.value);
    EXPECT_DOUBLE_EQ(average, mr2.value);
}

TEST(SumAverageAccumulatorCheckReset, AccumulateTwoResults) {
    SumAverageAccumulator acc;
    metric::MetricResult mr1{"Metric", 1};
    metric::MetricResult mr2{"Metric", 2};
    metric::MetricResult mr3{"Metric", 3};
    metric::MetricResult mr4{"Metric", 4};
    acc.Accumulate(mr1);
    acc.Accumulate(mr2);
    acc.Reset();
    acc.Accumulate(mr3);
    acc.Accumulate(mr4);
    acc.Finalize();
    auto [sum, average] = acc.Get();
    EXPECT_EQ(sum, mr3.value + mr4.value);
    EXPECT_DOUBLE_EQ(average, static_cast<double>(mr3.value + mr4.value) / 2);
}

}  // namespace analyzer::metric_accumulator::metric_accumulator_impl::test
