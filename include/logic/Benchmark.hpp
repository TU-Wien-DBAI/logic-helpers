#ifndef LOGIC_LOGIC_BENCHMARK_H_
#define LOGIC_LOGIC_BENCHMARK_H_

#include <logic/global>

#include <iostream>
#include <string>

namespace logic
{
	class LOGIC_API Benchmark
	{
	public:
		static void registerTimestamp(const std::string &name);
		static void printBenchmarks(std::ostream &out, bool csv);

	private:
		Benchmark();
	};

} // namespace logic

#endif // LOGIC_LOGIC_BENCHMARK_H_
