// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. 
//  Copyright Eric Niebler 2013.
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef RANGE_V3_ADAPTOR_CONST_HPP
#define RANGE_V3_ADAPTOR_CONST_HPP

#include <utility>
#include <range/v3/range_fwd.hpp>
#include <range/v3/begin_end.hpp>
#include <range/v3/utility/bindable.hpp>

namespace ranges
{
    inline namespace v3
    {
        template<typename Rng>
        struct const_range
        {
        private:
            Rng rng_;
        public:
            using const_iterator = decltype(ranges::cbegin(std::declval<Rng const &>()));
            using iterator = const_iterator;

            explicit const_range(Rng && rng)
              : rng_(rng)
            {}
            iterator begin() const
            {
                return ranges::cbegin(rng_);
            }
            iterator end() const
            {
                return ranges::cend(rng_);
            }
            bool operator!() const
            {
                return begin() == end();
            }
            explicit operator bool() const
            {
                return begin() != end();
            }
        };

        struct conster
        {
            // E.g.: rng | const_
            template<typename Rng>
            friend const_range<Rng> operator|(Rng && rng, conster const &)
            {
                return const_range<Rng>{std::forward<Rng>()};
            }
            // E.g.: const_(rng)
            template<typename Rng>
            const_range<Rng> operator()(Rng && rng) const
            {
                return const_range<Rng>{std::forward<Rng>()};
            }
        };
        
        constexpr bindable<conster> const_ {};
    }
}

#endif
