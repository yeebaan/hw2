#include <chrono>
#include <iomanip> // For std::setprecision

#include "SobelFilter.h"
#include "Testbench.h"

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
    tb.initiator.i_skt(sobel_filter.t_skt);

    tb.read_bmp(argv[1]);
    sc_start();
    std::cout << "Simulated time == " << sc_core::sc_time_stamp() << std::endl;
    tb.write_bmp(argv[2]);
  }
  {
    // Get the ending timepoint
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate elapsed time in nanoseconds
    std::chrono::duration<double, std::nano> elapsed = end - start;
    // Output the elapsed time with high precision
    std::cout << "Time taken by sc_main function is : " << std::fixed
              << std::setprecision(9) << elapsed.count() * 1e-9 << " seconds" << std::endl;
  }
  return 0;
}
