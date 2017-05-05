#if defined(LOGIC_ENUM_CONST) || defined(LOGIC_ENUM_NOCONST)
#if !defined(LOGIC_ENUM_CONST) || !defined(LOGIC_ENUM_NOCONST)

#if defined(LOGIC_ENUM_CONST)
	#define LOGIC_ENUM_IFACE IConstEnumerator
	#define LOGIC_ENUM_NAME ConstEnumerator
	#define LOGIC_ENUM_REFTYPE const T &
	#define LOGIC_ENUM_PTRTYPE const T *
	#define LOGIC_ENUM_CONSTMODIFIER const
#elif defined(LOGIC_ENUM_NOCONST)
	#define LOGIC_ENUM_IFACE IEnumerator
	#define LOGIC_ENUM_NAME Enumerator
	#define LOGIC_ENUM_REFTYPE T &
	#define LOGIC_ENUM_PTRTYPE T *
	#define LOGIC_ENUM_CONSTMODIFIER
#else
	#error "Must define either LOGIC_ENUM_CONST or LOGIC_ENUM_NOCONST"
#endif // LOGIC_ENUM_NOCONST

#include <logic/global>

#include <iterator>
#include <stdexcept>
#include <typeinfo>
#include <cstddef>

namespace logic
{
	template<typename T>
	class LOGIC_API LOGIC_ENUM_IFACE
	{
	protected:
		LOGIC_ENUM_IFACE &operator=(LOGIC_ENUM_IFACE &) { return *this; };

	public:
		virtual ~LOGIC_ENUM_IFACE() = 0;

		virtual void next() = 0;

		virtual LOGIC_ENUM_REFTYPE get() const = 0;
		virtual bool valid() const = 0;
		virtual LOGIC_ENUM_IFACE<T> *clone() const = 0;

		virtual bool operator==(const LOGIC_ENUM_IFACE<T> &other) const = 0;

	public:
		class LOGIC_API Iterator
			: public std::iterator< std::forward_iterator_tag,
									T,
									std::ptrdiff_t,
									LOGIC_ENUM_REFTYPE,
									LOGIC_ENUM_PTRTYPE>
		{
		public:
			Iterator()
			{
				enumerator_ = nullptr;
			}

			Iterator(LOGIC_ENUM_IFACE<T> *enumerator)
			{
				enumerator_ = enumerator;
			}

			Iterator(const Iterator &other)
				: enumerator_(other.enumerator_->clone())
			{ }

			~Iterator()
			{
				if(enumerator_) delete enumerator_;
			}

			Iterator &operator=(const Iterator &other)
			{
				if(enumerator_) delete enumerator_;
				enumerator_ = other.enumerator_->clone();
			}

			bool operator==(const Iterator &other) const
			{
				return (enumerator_ == nullptr 
					&& other.enumerator_ == nullptr)
					|| (enumerator_ != nullptr 
					&& other.enumerator_ != nullptr
					&& *enumerator_ == *other.enumerator_);
			}

			bool operator!=(const Iterator &other) const
			{
				return !(*this == other);
			}

			LOGIC_ENUM_REFTYPE operator*()
			{
				if(!enumerator_)
					throw std::logic_error("Not in dereferenceable state!");
				return enumerator_->get();
			}

			LOGIC_ENUM_PTRTYPE operator->()
			{
				if(!enumerator_)
					throw std::logic_error("Not in dereferenceable state!");
				return &enumerator_->get();
			}

			Iterator &operator++()
			{
				if(enumerator_) enumerator_->next();
				return *this;
			}

			Iterator operator++(int)
			{
				Iterator beforeInc(*this);
				++(*this);
				return beforeInc;
			}

		private:
			LOGIC_ENUM_IFACE<T> *enumerator_;

		}; // class Iterator;

	}; // class LOGIC_ENUM_IFACE

	template<typename T, typename Iter>
	class LOGIC_API LOGIC_ENUM_NAME : public LOGIC_ENUM_IFACE<T>
	{
	public:
		LOGIC_ENUM_NAME() { ended_ = true; }

		LOGIC_ENUM_NAME(Iter end) : current_(end), end_(end), ended_(true) { }

		LOGIC_ENUM_NAME(Iter begin, Iter end)
			: current_(begin), end_(end), ended_(begin == end)
		{ }

		virtual ~LOGIC_ENUM_NAME() { }

		LOGIC_ENUM_NAME &operator=(const LOGIC_ENUM_NAME &other)
		{
			current_ = other.current_;
			end_ = other.end_;
			ended_ = other.ended_;
		}
		
		virtual void next()
		{
			++current_;
			ended_ |= current_ == end_;
		}

		virtual LOGIC_ENUM_REFTYPE get() const
		{
			retref<underlying_type> rr;
			return rr(current_);
		}

		virtual bool valid() const
		{
			return !ended_;
		}

		virtual LOGIC_ENUM_IFACE<T> *clone() const
		{
			return new LOGIC_ENUM_NAME<T, Iter>(*this);
		}

		virtual bool operator==(const LOGIC_ENUM_IFACE<T> &other) const
		{
			if(typeid(other) != typeid(*this)) return false;

			const LOGIC_ENUM_NAME<T, Iter> &tmpother =
				static_cast<const LOGIC_ENUM_NAME<T, Iter> &>(other);
			return *this == tmpother;
		}

		virtual bool operator==(const LOGIC_ENUM_NAME<T, Iter> &other) const
		{
			return current_ == other.current_ && end_ == other.end_;
		}

	private:
		typedef typename std::iterator_traits<Iter>::value_type underlying_type;

		Iter current_;
		Iter end_;
		bool ended_;

		template<typename U>
		struct retref
		{
			LOGIC_ENUM_CONSTMODIFIER U &operator()(Iter i) { return *i; }
		};

		template<typename U>
		struct retref<U *>
		{
			LOGIC_ENUM_CONSTMODIFIER U &operator()(Iter i) { return **i; }
		};

	}; // class LOGIC_ENUM_NAME
	
	template<typename T>
	inline LOGIC_ENUM_IFACE<T>::~LOGIC_ENUM_IFACE() { }

} // namespace logic

#undef LOGIC_ENUM_IFACE
#undef LOGIC_ENUM_NAME
#undef LOGIC_ENUM_REFTYPE
#undef LOGIC_ENUM_PTRTYPE
#undef LOGIC_ENUM_CONSTMODIFIER

#endif // !defined(LOGIC_ENUM_CONST) || !defined(LOGIC_ENUM_NOCONST)
#endif // defined(LOGIC_ENUM_CONST) || defined(LOGIC_ENUM_NOCONST)
