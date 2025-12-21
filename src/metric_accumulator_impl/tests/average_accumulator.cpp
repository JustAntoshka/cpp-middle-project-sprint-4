#include "metric_accumulator_impl/average_accumulator.hpp"

#include <gtest/gtest.h>

#include <cmath>

namespace analyzer::metric_accumulator::metric_accumulator_impl::test {

TEST(AverageAccumulatorCheckThrow, Empty) {
    AverageAccumulator acc;
    EXPECT_THROW(acc.Get(), std::runtime_error);
}

TEST(AverageAccumulatorCheckThrow, NonFinalized) {
    AverageAccumulator acc;
    metric::MetricResult mr;
    acc.Accumulate(mr);
    EXPECT_THROW(acc.Get(), std::runtime_error);
}

TEST(AverageAccumulatorCheckThrow, NonAccumulatedFinalize) {
    AverageAccumulator acc;
    EXPECT_THROW(acc.Finalize(), std::runtime_error);
}

TEST(AverageAccumulatorCheckThrow, Reset) {
    AverageAccumulator acc;
    acc.Reset();
    EXPECT_THROW(acc.Get(), std::runtime_error);
}

TEST(AverageAccumulatorCheckThrow, AccumulateReset) {
    AverageAccumulator acc;
    metric::MetricResult mr;
    acc.Accumulate(mr);
    acc.Reset();
    EXPECT_THROW(acc.Get(), std::runtime_error);
}

TEST(AverageAccumulatorCheckThrow, AccumulateFinalizeReset) {
    AverageAccumulator acc;
    metric::MetricResult mr;
    acc.Accumulate(mr);
    acc.Finalize();
    acc.Reset();
    EXPECT_THROW(acc.Get(), std::runtime_error);
}

TEST(AverageAccumulatorCheckFinalize, AccumulateOneResult) {
    AverageAccumulator acc;
    metric::MetricResult mr;
    acc.Accumulate(mr);
    acc.Finalize();
    EXPECT_DOUBLE_EQ(acc.Get(), mr.value);
}

TEST(AverageAccumulatorCheckFinalize, AccumulateTwoResults) {
    AverageAccumulator acc;
    metric::MetricResult mr1{"Metric", 1};
    metric::MetricResult mr2{"Metric", 2};
    acc.Accumulate(mr1);
    acc.Accumulate(mr2);
    acc.Finalize();
    EXPECT_DOUBLE_EQ(acc.Get(), static_cast<double>(mr1.value + mr2.value) / 2);
}

TEST(AverageAccumulatorCheckReset, AccumulateOneResult) {
    AverageAccumulator acc;
    metric::MetricResult mr1;
    metric::MetricResult mr2;
    acc.Accumulate(mr1);
    acc.Reset();
    acc.Accumulate(mr2);
    acc.Finalize();
    EXPECT_DOUBLE_EQ(acc.Get(), mr2.value);
}

TEST(AverageAccumulatorCheckReset, AccumulateTwoResults) {
    AverageAccumulator acc;
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
    EXPECT_DOUBLE_EQ(acc.Get(), static_cast<double>(mr3.value + mr4.value) / 2);
}

}  // namespace analyzer::metric_accumulator::metric_accumulator_impl::test
