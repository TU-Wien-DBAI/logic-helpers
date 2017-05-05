#ifndef LOGIC_LOGIC_ID_H_
#define LOGIC_LOGIC_ID_H_

#include <logic/global>

#include <stdint>
#include <vector>

namespace logic
{
	typedef std::uint_least32_t id_t;
	typedef std::vector<id_t> id_vector;

	struct Id
	{
	private:
		Id();
	};

} // namespace logic

#endif // LOGIC_LOGIC_ID_H_
