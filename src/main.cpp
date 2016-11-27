#include <chrono>
#include <iostream>
#include <random>
#include <set>

#include "benchmark/benchmark_api.h"

#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>

struct Event {
  using tp = std::chrono::system_clock::time_point;

  Event(tp t1, tp t2) : modify_time(t1), creation_time(t2) {}

  const tp& get_modify_time() const { return modify_time; };
  const tp& get_creation_time() const { return creation_time; };

  tp modify_time;
  tp creation_time;
};

std::ostream& operator<<(std::ostream& os, const Event& e) {
  std::time_t mt = std::chrono::system_clock::to_time_t(e.modify_time);
  std::time_t ct = std::chrono::system_clock::to_time_t(e.creation_time);
  os << std::asctime(std::localtime(&mt)) << ' ' << std::asctime(std::localtime(&ct)) << '\n';
  return os;
}

bool operator<(const Event& e1, const Event& e2) {
  return e1.modify_time < e2.modify_time;
}

namespace tags {
struct modify_time_asc {};
struct creation_time_asc {};
}

using namespace boost::multi_index;

using EventList = boost::multi_index_container<
    Event, indexed_by<ordered_non_unique<tag<tags::modify_time_asc>,
                                         const_mem_fun<Event, const std::chrono::system_clock::time_point&,
                                                       &Event::get_modify_time>,
                                         std::less<Event::tp>>,
                      ordered_non_unique<tag<tags::creation_time_asc>,
                                         const_mem_fun<Event, const std::chrono::system_clock::time_point&,
                                                       &Event::get_creation_time>,
                                         std::less<Event::tp>>>>;

std::random_device rd;
std::uniform_int_distribution<int64_t> dist(1448251000, 1480251000);

static void StdSet1(benchmark::State& state) {
  while(state.KeepRunning()) {
    state.PauseTiming();
    std::multiset<Event> set;
    auto count = state.range(0);
    while(count--) {
      set.emplace(std::chrono::system_clock::from_time_t(dist(rd)),
                  std::chrono::system_clock::from_time_t(dist(rd)));
    }
    state.ResumeTiming();

    for(const auto& e : set) {
      benchmark::DoNotOptimize(e);
    }
  }
}
BENCHMARK(StdSet1)->RangeMultiplier(4)->Range(2, 128 << 10);

static void BoostMultiIndex_ModifyTimeView(benchmark::State& state) {
  while(state.KeepRunning()) {
    state.PauseTiming();
    EventList list;
    auto count = state.range(0);
    while(count--) {
      list.emplace(std::chrono::system_clock::from_time_t(dist(rd)),
                   std::chrono::system_clock::from_time_t(dist(rd)));
    }
    state.ResumeTiming();

    auto&& view_mod = list.get<tags::modify_time_asc>();
    for(const auto& e : view_mod) {
      benchmark::DoNotOptimize(e);
    }
  }
}
BENCHMARK(BoostMultiIndex_ModifyTimeView)->RangeMultiplier(4)->Range(2, 128 << 10);

static void BoostMultiIndex_CreationTimeView(benchmark::State& state) {
  while(state.KeepRunning()) {
    state.PauseTiming();
    EventList list;
    auto count = state.range(0);
    while(count--) {
      list.emplace(std::chrono::system_clock::from_time_t(dist(rd)),
                   std::chrono::system_clock::from_time_t(dist(rd)));
    }
    state.ResumeTiming();

    auto&& view_cr = list.get<tags::creation_time_asc>();
    for(const auto& e : view_cr) {
      benchmark::DoNotOptimize(e);
    }
  }
}
BENCHMARK(BoostMultiIndex_CreationTimeView)->RangeMultiplier(4)->Range(2, 128 << 10);

BENCHMARK_MAIN()
