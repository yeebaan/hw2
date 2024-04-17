#include "SobelFilter.h"

SobelFilter::SobelFilter(sc_module_name n)
    : sc_module(n), t_skt("t_skt"), base_offset(0)
{
  SC_THREAD(do_filter);

  t_skt.register_b_transport(this, &SobelFilter::blocking_transport);
}

void SobelFilter::do_filter()
{
  std::array<std::array<uint8_t, 5>, 5> gray = {0};
  while (true)
  {
    {
      gray[4][0] = gray[3][0];
      gray[4][1] = gray[3][1];
      gray[4][2] = gray[3][2];
      gray[4][3] = gray[3][3];
      gray[4][4] = gray[3][4];
      gray[3][0] = gray[2][0];
      gray[3][1] = gray[2][1];
      gray[3][2] = gray[2][2];
      gray[3][3] = gray[2][3];
      gray[3][4] = gray[2][4];
      gray[2][0] = gray[1][0];
      gray[2][1] = gray[1][1];
      gray[2][2] = gray[1][2];
      gray[2][3] = gray[1][3];
      gray[2][4] = gray[1][4];
      gray[1][0] = gray[0][0];
      gray[1][1] = gray[0][1];
      gray[1][2] = gray[0][2];
      gray[1][3] = gray[0][3];
      gray[1][4] = gray[0][4];
      gray[0][0] = (input[0][0].read() + input[0][1].read() + input[0][2].read()) / 3;
      gray[0][1] = (input[1][0].read() + input[1][1].read() + input[1][2].read()) / 3;
      gray[0][2] = (input[2][0].read() + input[2][1].read() + input[2][2].read()) / 3;
      gray[0][3] = (input[3][0].read() + input[3][1].read() + input[3][2].read()) / 3;
      gray[0][4] = (input[4][0].read() + input[4][1].read() + input[4][2].read()) / 3;
    }
    output.write((
                     gray[0][0] * 1 +
                     gray[0][1] * 4 +
                     gray[0][2] * 7 +
                     gray[0][3] * 4 +
                     gray[0][4] * 1 +
                     gray[1][0] * 4 +
                     gray[1][1] * 16 +
                     gray[1][2] * 26 +
                     gray[1][3] * 16 +
                     gray[1][4] * 4 +
                     gray[2][0] * 7 +
                     gray[2][1] * 16 +
                     gray[2][2] * 26 +
                     gray[2][3] * 16 +
                     gray[2][4] * 4 +
                     gray[3][0] * 4 +
                     gray[3][1] * 16 +
                     gray[3][2] * 26 +
                     gray[3][3] * 16 +
                     gray[3][4] * 4 +
                     gray[4][0] * 1 +
                     gray[4][1] * 4 +
                     gray[4][2] * 7 +
                     gray[4][3] * 4 +
                     gray[4][4] * 1) /
                 273);
  }
}

void SobelFilter::blocking_transport(tlm::tlm_generic_payload &payload,
                                     sc_core::sc_time &delay)
{
  delay += sc_time(1, SC_NS);

  switch (payload.get_command())
  {

  case tlm::TLM_READ_COMMAND:
  {
    switch (payload.get_address() - base_offset)
    {

    case SOBEL_FILTER_RESULT_ADDR:
    {
      payload.get_data_ptr()[0] = output.read();
      break;
    }

    case SOBEL_FILTER_CHECK_ADDR:
    {
      payload.get_data_ptr()[0] = output.num_available() > 0;
      break;
    }

    default:
    {
      std::cerr << "Error! SobelFilter::blocking_transport: address 0x"
                << std::hex << payload.get_address()
                << std::dec << " is not valid" << std::endl;
      break;
    }
    }
    break;
  }

  case tlm::TLM_WRITE_COMMAND:
  {
    switch (payload.get_address() - base_offset)
    {

    case SOBEL_FILTER_R_ADDR:
    {
      input[0][0].write(payload.get_data_ptr()[0x0]);
      input[0][1].write(payload.get_data_ptr()[0x1]);
      input[0][2].write(payload.get_data_ptr()[0x2]);
      input[1][0].write(payload.get_data_ptr()[0x3]);
      input[1][1].write(payload.get_data_ptr()[0x4]);
      input[1][2].write(payload.get_data_ptr()[0x5]);
      input[2][0].write(payload.get_data_ptr()[0x6]);
      input[2][1].write(payload.get_data_ptr()[0x7]);
      input[2][2].write(payload.get_data_ptr()[0x8]);
      input[3][0].write(payload.get_data_ptr()[0x9]);
      input[3][1].write(payload.get_data_ptr()[0xa]);
      input[3][2].write(payload.get_data_ptr()[0xb]);
      input[4][0].write(payload.get_data_ptr()[0xc]);
      input[4][1].write(payload.get_data_ptr()[0xd]);
      input[4][2].write(payload.get_data_ptr()[0xe]);
      break;
    }

    default:
    {
      std::cerr << "Error! SobelFilter::blocking_transport: address 0x"
                << std::hex << payload.get_address()
                << std::dec << " is not valid" << std::endl;
      break;
    }
    }
    break;
  }

  case tlm::TLM_IGNORE_COMMAND:
  {
    payload.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return;
  }

  default:
  {
    payload.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return;
  }
  }

  payload.set_response_status(tlm::TLM_OK_RESPONSE); // Always OK
}
