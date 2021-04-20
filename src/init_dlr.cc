#include <dlr.h>
#include <chrono>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

const int N = 10;

const int c = 1;
const int h = 224;
const int w = 384;

template <class T>
void PrintSample(const std::vector<T>& v, const int n) {
  for (int i=0; i<n; i++)
    std::cout << v[i] << " ";
  std::cout << std::endl;
}

int init_dlr() {
  int device_type = 1;
  const char* model_dir = "./model";
  std::cout << "Loading model... " << std::endl;
  DLRModelHandle model = NULL;
  if (CreateDLRModel(&model, model_dir, device_type, 0) != 0) {
    std::cout << DLRGetLastError() << std::endl;
    throw std::runtime_error("Could not load DLR Model");
  }
  std::cout << "Model was created" << std::endl;
  std::string input_name = "data";
  std::vector<int64_t> in_shape {1,c,h,w};
  std::vector<float> input(c*h*w, 0.14);
  std::vector<int32_t> output1(3, 0);
  std::vector<float> output2(12, 0.0);
  std::vector<int32_t> output3(6, 0);

  std::cout << "Setting input..." << std::endl;
  if (SetDLRInput(&model, input_name.c_str(), in_shape.data(), input.data(), 4) != 0) {
    throw std::runtime_error("Could not set input '" + input_name + "'");
  }
  std::cout << "Running model..." << std::endl;
  if (RunDLRModel(&model) != 0) {
    std::cout << DLRGetLastError() << std::endl;
    throw std::runtime_error("Could not run");
  }
  std::cout << "Getting output..." << std::endl;
  if (GetDLROutput(&model, 1, output1.data()) != 0) {
    throw std::runtime_error("Could not get output1");
  }
  if (GetDLROutput(&model, 2, output2.data()) != 0) {
    throw std::runtime_error("Could not get output2");
  }
  if (GetDLROutput(&model, 3, output3.data()) != 0) {
    throw std::runtime_error("Could not get output3");
  }
  std::cout << "GetOutput - done" << std::endl;

  std::cout << "Input: ";
  PrintSample(input, 10);
  std::cout << "Output1: ";
  PrintSample(output1, 3);
  std::cout << "Output2: ";
  PrintSample(output2, 12);
  std::cout << "Output3: ";
  PrintSample(output3, 6);

  double total_time = 0.0;
  for (int i = -1; i < N; i++) {
    auto t1 = std::chrono::high_resolution_clock::now();
    SetDLRInput(&model, input_name.c_str(), in_shape.data(), input.data(), 4);
    RunDLRModel(&model);
    GetDLROutput(&model, 1, output1.data());
    GetDLROutput(&model, 2, output2.data());
    GetDLROutput(&model, 3, output3.data());
    auto t2 = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
    total_time += dur;
    std::cout << "Run " << i << " - Done, Time: " << dur/1000000.0 << std::endl;
  }
  std::cout << "Avg Time: " << total_time/N << std::endl;
  return 0;
}
