#ifndef SOBEL_FILTER_H_
#define SOBEL_FILTER_H_
#include <systemc>
#include "tlm"
#include "tlm_utils/simple_target_socket.h"
#include "filter_def.h"
using namespace sc_core;
class SobelFilter : public sc_core::sc_module
{
public:
  tlm_utils::simple_target_socket<SobelFilter> t_skt;
  std::array<std::array<sc_core::sc_fifo<uint8_t>, 5>, 5> input;
  sc_core::sc_fifo<uint8_t> output;
  SC_HAS_PROCESS(SobelFilter);
  SobelFilter(sc_module_name n);
  ~SobelFilter() = default;
  void do_filter();
  unsigned int base_offset;
  void blocking_transport(tlm::tlm_generic_payload &payload,
                          sc_core::sc_time &delay);
};
#endif
