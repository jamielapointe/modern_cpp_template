#include <benchmark/benchmark.h>

#include "modern_cpp_template/fibonacci.h"

using modern_cpp_template::algorithms::fibonacci;
using modern_cpp_template::algorithms::fibonacci_fast1;
using modern_cpp_template::algorithms::fibonacci_fast2;

static void BM_fibonacci(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(_);
    auto result = fibonacci(state.range(0));
    benchmark::DoNotOptimize(result);
    benchmark::ClobberMemory();
  }
  state.SetComplexityN(state.range(0));
}
static constexpr int64_t kMinRange0{2};
static constexpr int64_t kMaxRange0{92};
// clang-format off
BENCHMARK(BM_fibonacci)->Range(kMinRange0, kMaxRange0)->Complexity(benchmark::oN)->MeasureProcessCPUTime()->UseRealTime();  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory,clang-diagnostic-global-constructors)
// clang-format on

static void BM_fibonacci_fast1(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(_);
    auto result = fibonacci_fast1(state.range(0));
    benchmark::DoNotOptimize(result);
    benchmark::ClobberMemory();
  }
  state.SetComplexityN(state.range(0));
}
static constexpr int64_t kMinRange1{2};
static constexpr int64_t kMaxRange1{63};
// clang-format off
BENCHMARK(BM_fibonacci_fast1)->Range(kMinRange1, kMaxRange1)->Complexity(benchmark::oN)->MeasureProcessCPUTime()->UseRealTime();  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory,clang-diagnostic-global-constructors)
// clang-format on

static void BM_fibonacci_fast2(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(_);
    auto result = fibonacci_fast2(state.range(0));
    benchmark::DoNotOptimize(result);
    benchmark::ClobberMemory();
  }
  state.SetComplexityN(state.range(0));
}
static constexpr int64_t kMinRange2{2};
static constexpr int64_t kMaxRange2{92};
// clang-format off
BENCHMARK(BM_fibonacci_fast2)->Range(kMinRange2, kMaxRange2)->Complexity(benchmark::oN)->MeasureProcessCPUTime()->UseRealTime();  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory,clang-diagnostic-global-constructors)
// clang-format on
