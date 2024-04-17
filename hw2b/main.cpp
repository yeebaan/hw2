#include <chrono>
#include <iomanip>
#include "SobelFilter.h"
#include "Testbench.h"
#include "SimpleBus.h"
int sc_main(int argc, char **argv)
{
  // Get the starting timepoint
  auto start = std::chrono::high_resolution_clock::now();
  if ((argc < 3) || (argc > 4))
  {
    std::cout << "No arguments for the executable : " << argv[0] << endl;
    std::cout << "Usage : >" << argv[0] << " in_image_file_name out_image_file_name"
              << endl;
    return 0;
  }
  {
    Testbench tb("tb");
    SobelFilter sobel_filter("sobel_filter");
    SimpleBus<1, 1> bus("bus");
    if (simple_bus_enable)
    {
      tb.initiator.i_skt(bus.t_skt[0]);
      bus.i_skt[0](sobel_filter.t_skt);
      bus.setDecode(0, SOBEL_MM_BASE, SOBEL_MM_BASE + SOBEL_MM_SIZE - 1);
      bus.set_clock_period(sc_time(1, SC_NS));
    }
    else
    {
      tb.initiator.i_skt(sobel_filter.t_skt);
      bus.i_skt[0](bus.t_skt[0]);
    }
    {
      tb.read_bmp(argv[1]);
      sc_start();
      std::cout << "Simulated time == " << sc_core::sc_time_stamp() << std::endl;
      tb.write_bmp(argv[2]);
    }
    if (simple_bus_enable)
    {
      std::cout << "Number of read  is " << bus.count_read << std::endl;
      std::cout << "Number of write is " << bus.count_write << std::endl;
    }
  }
  {
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> elapsed = end - start;
    std::cout << "Time taken by sc_main function is : " << std::fixed
              << std::setprecision(9) << elapsed.count() * 1e-9 << " seconds" << std::endl;
  }
  return 0;
}
