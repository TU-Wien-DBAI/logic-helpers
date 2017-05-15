#ifndef LOGIC_LOGIC_ID_H_
#define LOGIC_LOGIC_ID_H_

#include <logic/global>

#include <cstdint>
#include <vector>

namespace logic
{
	typedef std::uint_least32_t id_t;
	typedef std::vector<id_t> id_vector;

	typedef std::int_least32_t num_t;
	typedef std::vector<num_t> num_vector;

	struct Id
	{
	private:
		Id();
	};

} // namespace logic

#endif // LOGIC_LOGIC_ID_H_
