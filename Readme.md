## To build on linux:

Run in order-book folder:
```
mkdir build
cd build
cmake ..
make
./ORDER_BOOK 
```

### Benchmarking result on 100 million orders:
```
Average time taken for adding orders: 281 nanoseconds
Average time taken for modifying orders: 163 nanoseconds
Average time taken for deleting orders: 146 nanoseconds
```

### Thoughts on impementation:
`Current time complecity for insert and lookup is logarithmic O(log[size]), and linear O(n) for erase and print. We could use unordered container as well, then lookup and inertion would be O(N) in worst case, but print would be much of a problem, since it must be ordered.`
