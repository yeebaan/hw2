# HW2

```shell
git clone https://github.com/yeebaan/hw2.git
cd hw2
cd hw2a
# cd hw2b
# cd hw2c
mkdir build
cd build
cmake ..
# make
# make run
make check
```

## (40 pt) Gaussian Blur Filter with TLM interface

- Please implement and wrap the filter module (the data buffer version) with TLM interface.
- Please insert delays with wait() in the target module.
- Please reuse codes in lab3 to write a testbench as a initiator to test the TLM module.

## (30 pt) Gaussian Blur Filter with quantum keeper

- Please setup a quantum keeper to reduce the wait() in the implementation.
- Does the quantum keeper version improves the simulation run time?

## (30 pt) Gaussian Blur Filter with TLM interconnect

- Please connect the quantum keeper modules through a TLM bus.
- Please also insert counters in the transaction functions of TLM bus to count the number of read/write to the target module.
