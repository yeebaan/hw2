#include "Initiator.h"
Initiator::Initiator(sc_module_name n) : sc_module(n), i_skt("i_skt")
{
  m_qk.set_global_quantum(sc_time(3, SC_NS));
  m_qk.reset();
}
int Initiator::read_from_socket(uint64_t addr,
                                uint8_t *mask,
                                uint8_t *rdata,
                                uint64_t dataLen)
{
  trans.set_read();
  trans.set_address(addr);
  trans.set_byte_enable_length(dataLen);
  trans.set_byte_enable_ptr(mask);
  trans.set_data_length(dataLen);
  trans.set_data_ptr(rdata);
  do_trans(trans);
  return trans.is_response_ok();
}
int Initiator::write_to_socket(uint64_t addr,
                               uint8_t *mask,
                               uint8_t *wdata,
                               uint64_t dataLen)
{
  trans.set_write();
  trans.set_address(addr);
  trans.set_byte_enable_length(dataLen);
  trans.set_byte_enable_ptr(mask);
  trans.set_data_length(dataLen);
  trans.set_data_ptr(wdata);
  do_trans(trans);
  return trans.is_response_ok();
}
void Initiator::do_trans(tlm::tlm_generic_payload &trans)
{
  sc_core::sc_time delay = sc_core::sc_time(0, SC_NS);
  i_skt->b_transport(trans, delay);
  if (true)
  {
    wait(delay);
  }
  else
  {
    m_qk.inc(delay);
    if (m_qk.need_sync())
    {
      m_qk.sync();
    }
  }
}
