## To build on linux:

Run in order-book folder:
```
mkdir build
cd build
cmake ..
make
./ORDER_BOOK 
```

### benchmarking result on 100 million orders:
```
Average time taken for adding orders: 281 nanoseconds
Average time taken for modifying orders: 163 nanoseconds
Average time taken for deleting orders: 146 nanoseconds
```
