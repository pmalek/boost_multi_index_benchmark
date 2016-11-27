# boost_multi_index_benchmark

### Build

```
git clone https://github.com/pmalek/boost_multi_index_benchmark.git && \
  ( cd boost_multi_index_benchmark && git submodule update --init --recursive ) && \
  ( mkdir build && cd build && \
  cmake -DCMAKE_BUILD_TYPE=Release ../boost_multi_index_benchmark && cmake --build . -- -j)
```

### Results

* [Intel® Xeon® Processor E3-1231 v3 (8M Cache, 3.40 GHz)](https://ark.intel.com/products/80910/Intel-Xeon-Processor-E3-1231-v3-8M-Cache-3_40-GHz)

```
Run on (8 X 3798.44 MHz CPU s)
2016-11-27 17:02:44
Benchmark                                      Time           CPU Iterations
----------------------------------------------------------------------------
StdSet1/2                                    169 ns        171 ns    4142172
StdSet1/4                                    199 ns        200 ns    3508843
StdSet1/16                                   429 ns        431 ns    1620949
StdSet1/64                                  1354 ns       1356 ns     518071
StdSet1/256                                 5141 ns       5142 ns     137006
StdSet1/1024                               22832 ns      22845 ns      30763
StdSet1/4k                                103405 ns     103414 ns       6781
StdSet1/16k                               564584 ns     564584 ns       1242
StdSet1/64k                              2476859 ns    2476812 ns        287
StdSet1/128k                             7769676 ns    7769674 ns         92
BoostMultiIndex_ModifyTimeView/2             175 ns        177 ns    3950988
BoostMultiIndex_ModifyTimeView/4             209 ns        211 ns    3305716
BoostMultiIndex_ModifyTimeView/16            448 ns        449 ns    1552197
BoostMultiIndex_ModifyTimeView/64           1458 ns       1459 ns     479963
BoostMultiIndex_ModifyTimeView/256          5355 ns       5355 ns     131501
BoostMultiIndex_ModifyTimeView/1024        25218 ns      25218 ns      27653
BoostMultiIndex_ModifyTimeView/4k         124628 ns     124619 ns       5620
BoostMultiIndex_ModifyTimeView/16k        605412 ns     605387 ns       1146
BoostMultiIndex_ModifyTimeView/64k       2905184 ns    2905080 ns        241
BoostMultiIndex_ModifyTimeView/128k     12857073 ns   12856931 ns         56
BoostMultiIndex_CreationTimeView/2           183 ns        185 ns    3800658
BoostMultiIndex_CreationTimeView/4           214 ns        215 ns    3259133
BoostMultiIndex_CreationTimeView/16          450 ns        452 ns    1552462
BoostMultiIndex_CreationTimeView/64         1598 ns       1599 ns     438810
BoostMultiIndex_CreationTimeView/256        6618 ns       6618 ns     105081
BoostMultiIndex_CreationTimeView/1024      31085 ns      31085 ns      22638
BoostMultiIndex_CreationTimeView/4k       175692 ns     175679 ns       3981
BoostMultiIndex_CreationTimeView/16k      723575 ns     723542 ns        967
BoostMultiIndex_CreationTimeView/64k     3983730 ns    3983749 ns        175
BoostMultiIndex_CreationTimeView/128k   12130616 ns   12130436 ns         55
```

