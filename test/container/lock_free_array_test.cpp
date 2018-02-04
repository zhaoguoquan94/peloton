//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// lock_free_array_test.cpp
//
// Identification: test/container/lock_free_array_test.cpp
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//


#include "container/lock_free_array.h"

#include "common/harness.h"
#include "libcds/cds/init.h"
#include "libcds/cds/gc/hp.h"
#include "libcds/cds/container/iterable_list_hp.h"

namespace peloton {
namespace test {

//===--------------------------------------------------------------------===//
// LockFreeArray Test
//===--------------------------------------------------------------------===//

class LockFreeArrayTests : public PelotonTest {};

/*TEST_F(LockFreeArrayTests, BasicLibCdsTest) {
  cds::Initialize();
  {
    typedef cds::container::IterableList<cds::gc::HP, int> list_type;
    cds::gc::hp::GarbageCollector::Construct(list_type::c_nHazardPtrCount + 3, 1, 16);

    cds::container::IterableList<cds::gc::HP, int,
      typename cds::container::iterable_list::make_traits<
        cds::opt::item_counter<cds::atomicity::item_counter>
      >::type
    > list;

    cds::threading::Manager::attachThread();


    EXPECT_TRUE(list.insert(1));
    EXPECT_TRUE(list.insert(2));

    EXPECT_EQ(list.size(), 2);
  }
  cds::Terminate();
}

TEST_F(LockFreeArrayTests, BasicSharedPointerLibCdsTest) {
  cds::Initialize();
  {
    typedef cds::container::IterableList<cds::gc::HP, std::shared_ptr<oid_t>> list_type;
    cds::gc::hp::GarbageCollector::Construct(list_type::c_nHazardPtrCount + 3, 1, 16);

    cds::container::IterableList<cds::gc::HP, std::shared_ptr<oid_t>,
      typename cds::container::iterable_list::make_traits<
        cds::opt::item_counter<cds::atomicity::item_counter>
      >::type
    > list;
    cds::threading::Manager::attachThread();

    size_t const element_count = 3;
    for (size_t element = 0; element < element_count; ++element) {
      std::shared_ptr<oid_t> entry(new oid_t);
      auto status = list.insert(entry);
      EXPECT_TRUE(status);
    }
    EXPECT_EQ(list.size(), element_count);
  }
  cds::Terminate();
}*/

// Test basic functionality
TEST_F(LockFreeArrayTests, BasicTest) {

  typedef uint32_t  value_type;

  {
    LockFreeArray<value_type> array;

    cds::threading::Manager::attachThread();

    size_t const element_count = 3;
    for (size_t element = 0; element < element_count; ++element ) {
      auto status = array.Append(element);
      EXPECT_TRUE(status);
    }

    auto array_size = array.GetSize();
    EXPECT_EQ(array_size, element_count);
  }
}

// Test shared pointers
TEST_F(LockFreeArrayTests, SharedPointerTest) {

  typedef std::shared_ptr<oid_t> value_type;

  {
    LockFreeArray<value_type> array;


    std::thread t0([&] {
      cds::threading::Manager::attachThread();
      size_t const element_count = 10000;
      for (size_t element = 0; element < element_count; ++element ) {
        std::shared_ptr<oid_t> entry(new oid_t);
        auto status = array.Append(entry);
        EXPECT_TRUE(status);
      }

      auto array_size = array.GetSize();
      EXPECT_EQ(array_size, element_count);
      cds::threading::Manager::detachThread();
    });


      cds::threading::Manager::attachThread();
      size_t const element_count = 10000;
      for (size_t element = 0; element < element_count; ++element ) {
        std::shared_ptr<oid_t> entry(new oid_t);
        auto status = array.Append(entry);
        EXPECT_TRUE(status);
      }

      auto array_size = array.GetSize();
      EXPECT_EQ(array_size, element_count);


    t0.join();

  }
}

}  // namespace test
}  // namespace peloton
