/*
    This file is a part of libcds - Concurrent Data Structures library

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2017

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CDSTEST_FIXTURE_H
#define CDSTEST_FIXTURE_H

#include <cds_test/ext_gtest.h>
#include <algorithm>
#include <random>

namespace cds_test {

    class fixture : public ::testing::Test
    {
    public:
        template <typename RandomIt>
        static void shuffle( RandomIt first, RandomIt last )
        {
            //std::shuffle( first, last, std::mt19937( std::random_device()() ) );
            std::shuffle( first, last, random_gen_ );
        }

        static unsigned int rand( unsigned int nMax )
        {
            /*
            std::random_device rd;
            std::mt19937 gen(rd());
            */
            std::uniform_int_distribution<unsigned> dis(0, nMax - 1);
            return dis( random_gen_ );
        }

    private:
        static std::random_device random_dev_;
        static std::mt19937 random_gen_;
    };

} // namespace cds_test

#endif // CDSTEST_FIXTURE_H
