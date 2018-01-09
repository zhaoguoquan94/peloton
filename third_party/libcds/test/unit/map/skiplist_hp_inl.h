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


TEST_F( CDSTEST_FIXTURE_NAME, compare )
{
    typedef cc::SkipListMap< gc_type, key_type, value_type,
        typename cc::skip_list::make_traits<
            cds::opt::compare< cmp >
        >::type
    > map_type;

    map_type m;
    test( m );
}

TEST_F( CDSTEST_FIXTURE_NAME, less )
{
    typedef cc::SkipListMap< gc_type, key_type, value_type,
        typename cc::skip_list::make_traits<
            cds::opt::less< base_class::less >
        >::type
    > map_type;

    map_type m;
    test( m );
}

TEST_F( CDSTEST_FIXTURE_NAME, cmpmix )
{
    typedef cc::SkipListMap< gc_type, key_type, value_type,
        typename cc::skip_list::make_traits<
            cds::opt::less< base_class::less >
            ,cds::opt::compare< cmp >
        >::type
    > map_type;

    map_type m;
    test( m );
}

TEST_F( CDSTEST_FIXTURE_NAME, item_counting )
{
    struct map_traits: public cc::skip_list::traits
    {
        typedef cmp compare;
        typedef base_class::less less;
        typedef cds::atomicity::item_counter item_counter;
    };
    typedef cc::SkipListMap< gc_type, key_type, value_type, map_traits > map_type;

    map_type m;
    test( m );
}

TEST_F( CDSTEST_FIXTURE_NAME, backoff )
{
    struct map_traits: public cc::skip_list::traits
    {
        typedef cmp compare;
        typedef base_class::less less;
        typedef cds::atomicity::item_counter item_counter;
        typedef cds::backoff::yield back_off;
    };
    typedef cc::SkipListMap< gc_type, key_type, value_type, map_traits > map_type;

    map_type m;
    test( m );
}

TEST_F( CDSTEST_FIXTURE_NAME, stat )
{
    struct map_traits: public cc::skip_list::traits
    {
        typedef cmp compare;
        typedef base_class::less less;
        typedef cds::atomicity::item_counter item_counter;
        typedef cds::backoff::yield back_off;
        typedef cc::skip_list::stat<> stat;
    };
    typedef cc::SkipListMap< gc_type, key_type, value_type, map_traits > map_type;

    map_type m;
    test( m );
}

TEST_F( CDSTEST_FIXTURE_NAME, xorshift32 )
{
    struct map_traits: public cc::skip_list::traits
    {
        typedef base_class::less less;
        typedef cc::skip_list::xorshift32 random_level_generator;
    };
    typedef cc::SkipListMap< gc_type, key_type, value_type, map_traits > map_type;

    map_type m;
    test( m );
}

TEST_F( CDSTEST_FIXTURE_NAME, xorshift24 )
{
    struct map_traits: public cc::skip_list::traits
    {
        typedef base_class::less less;
        typedef cc::skip_list::stat<> stat;
        typedef cc::skip_list::xorshift24 random_level_generator;
    };
    typedef cc::SkipListMap< gc_type, key_type, value_type, map_traits > map_type;

    map_type m;
    test( m );
}

TEST_F( CDSTEST_FIXTURE_NAME, xorshift16 )
{
    struct map_traits: public cc::skip_list::traits
    {
        typedef cmp compare;
        typedef cc::skip_list::xorshift16 random_level_generator;
    };
    typedef cc::SkipListMap< gc_type, key_type, value_type, map_traits > map_type;

    map_type m;
    test( m );
}

TEST_F( CDSTEST_FIXTURE_NAME, turbo32 )
{
    struct map_traits: public cc::skip_list::traits
    {
        typedef cmp compare;
        typedef cc::skip_list::turbo32 random_level_generator;
    };
    typedef cc::SkipListMap< gc_type, key_type, value_type, map_traits > map_type;

    map_type m;
    test( m );
}

TEST_F( CDSTEST_FIXTURE_NAME, turbo24 )
{
    struct map_traits: public cc::skip_list::traits
    {
        typedef cmp compare;
        typedef cc::skip_list::turbo24 random_level_generator;
    };
    typedef cc::SkipListMap< gc_type, key_type, value_type, map_traits > map_type;

    map_type m;
    test( m );
}

TEST_F( CDSTEST_FIXTURE_NAME, turbo16 )
{
    struct map_traits: public cc::skip_list::traits
    {
        typedef cmp compare;
        typedef cc::skip_list::turbo16 random_level_generator;
    };
    typedef cc::SkipListMap< gc_type, key_type, value_type, map_traits > map_type;

    map_type m;
    test( m );
}
