#ifndef INITIATOR_H_
#define INITIATOR_H_
#include <systemc>
using namespace sc_core;
#include "tlm"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/tlm_quantumkeeper.h"
class Initiator : public sc_module
{
public:
  tlm_utils::simple_initiator_socket<Initiator> i_skt;
  SC_HAS_PROCESS(Initiator);
  Initiator(sc_module_name n);
  int read_from_socket(uint64_t addr,
                       uint8_t *mask,
                       uint8_t *rdata,
                       uint64_t dataLen);
  int write_to_socket(uint64_t addr,
                      uint8_t *mask,
                      uint8_t *rdata,
                      uint64_t dataLen);
  void do_trans(tlm::tlm_generic_payload &trans);
  tlm::tlm_generic_payload trans;
  tlm_utils::tlm_quantumkeeper m_qk;
};
#endif
