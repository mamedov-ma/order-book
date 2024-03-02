## To build on linux:

Run in order-book folder:
```
mkdir build
cd build
cmake ..
make
./ORDER_BOOK 
```

### Benchmarking result on 100 million orders, 11th Gen Intel® Core™ i5-1135G7 @ 2.40GHz × 8:
```
Average time taken for adding orders: 315 nanoseconds
Average time taken for modifying orders: 176 nanoseconds
Average time taken for deleting orders: 146 nanoseconds
```

### Thoughts on impementation:
`Current time complecity for insert, lookup and delete operations is logarithmic O(log[size]), and linear O(n) for print (where n stands for top n objects to print, not the number of element in a container). We could use unordered container as well, then insertion, lookup and delete would be O(1) on average, but print would be much of a problem, since it must be sorted every time. So, in order to chose proper algorithm, we have to analyse how often we are going to perform each of these operations. Also, important thing to mention, is that we could use something like std::pmr::monotonic_buffer_resource, or some "in-house" allocator, wich will allow us avoid heap allocations to the certain degree, and therefore increase performance of rmw operations on our OrderBook object`
