#ifndef TESTBENCH_H_
#define TESTBENCH_H_

#include <string>
using namespace std;

#include <systemc>
using namespace sc_core;

#include "Initiator.h"
#include "filter_def.h"

class Testbench : public sc_module
{
public:
  Initiator initiator;

  SC_HAS_PROCESS(Testbench);

  Testbench(sc_module_name n);
  ~Testbench() = default;

  int read_bmp(string infile_name);
  int write_bmp(string outfile_name);

  unsigned int input_rgb_raw_data_offset;
  const unsigned int output_rgb_raw_data_offset;
  int width;
  int height;
  unsigned char bits_per_pixel;
  unsigned short bytes_per_pixel;
  unsigned char *source_bitmap;
  unsigned char *target_bitmap;

  void do_sobel();
};
#endif
