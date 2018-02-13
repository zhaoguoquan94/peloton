//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// lock_free_lock_free_array.cpp
//
// Identification: src/container/lock_free_lock_free_array.cpp
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <memory>

#include "container/lock_free_array.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/internal_types.h"

namespace peloton {

namespace index{
class Index;
}

namespace storage{
class TileGroup;
class Database;
class IndirectionArray;
}

LOCK_FREE_ARRAY_TEMPLATE_ARGUMENTS
LOCK_FREE_ARRAY_TYPE::LockFreeArray(){
  // Initialize hazard pointer GC.
  cds::gc::hp::GarbageCollector::Construct(10, 100, 10);
  LOG_DEBUG("Initialized lock free array");
}

LOCK_FREE_ARRAY_TEMPLATE_ARGUMENTS
LOCK_FREE_ARRAY_TYPE::~LockFreeArray(){
  // Destruct hazard pointer GC
  //cds::gc::hp::GarbageCollector::Destruct(false);
  LOG_DEBUG("Destructing lock free array");
}

LOCK_FREE_ARRAY_TEMPLATE_ARGUMENTS
bool LOCK_FREE_ARRAY_TYPE::Update(const std::size_t &offset, ValueType value){
  cds::threading::Manager::attachThread();
  // Insert into offset (key) with value.
  LOG_DEBUG("Update at %lu", offset);
  return lock_free_list.upsert(offset, value, false).first;
}

LOCK_FREE_ARRAY_TEMPLATE_ARGUMENTS
bool LOCK_FREE_ARRAY_TYPE::Append(ValueType value){
  cds::threading::Manager::attachThread();
  LOG_DEBUG("Appended at %lu", lock_free_array_offset.load());
  return lock_free_list.insert(lock_free_array_offset++, value);
}

// invalid_value: not used.
LOCK_FREE_ARRAY_TEMPLATE_ARGUMENTS
bool LOCK_FREE_ARRAY_TYPE::Erase(const std::size_t &offset){
  cds::threading::Manager::attachThread();
  LOG_DEBUG("Erase at %lu", offset);
  return lock_free_list.erase(offset);
}

LOCK_FREE_ARRAY_TEMPLATE_ARGUMENTS
ValueType LOCK_FREE_ARRAY_TYPE::Find(const std::size_t &offset, const ValueType& invalid_value) const{
  LOG_DEBUG("Find at %lu", offset);
  cds::threading::Manager::attachThread();
  auto it = lock_free_list.find(offset);
  if (it == lock_free_list.end()) {
    return invalid_value;
  }
  return it->second;
}

LOCK_FREE_ARRAY_TEMPLATE_ARGUMENTS
ValueType LOCK_FREE_ARRAY_TYPE::FindValid(const std::size_t &offset,
                                          const ValueType& invalid_value) const {
  cds::threading::Manager::attachThread();
  LOG_DEBUG("Find Valid at %lu", offset);
  std::size_t off = 0;
  auto it = lock_free_list.begin();
  while (it != lock_free_list.end()) {
    if (off == offset) {
      return it->second;
    }
    ++it;
  }
  return invalid_value;
}

LOCK_FREE_ARRAY_TEMPLATE_ARGUMENTS
size_t LOCK_FREE_ARRAY_TYPE::GetSize() const{
  cds::threading::Manager::attachThread();
  auto size = lock_free_list.size();
  LOG_DEBUG("Size: %lu", size);
  return size;
}

LOCK_FREE_ARRAY_TEMPLATE_ARGUMENTS
bool LOCK_FREE_ARRAY_TYPE::IsEmpty() const{
  cds::threading::Manager::attachThread();
  auto isEmpty = lock_free_list.empty();
  LOG_DEBUG("IsEmpty: %d", isEmpty);
  return isEmpty;
}

LOCK_FREE_ARRAY_TEMPLATE_ARGUMENTS
void LOCK_FREE_ARRAY_TYPE::Clear() {
  cds::threading::Manager::attachThread();
  lock_free_list.clear();
}

LOCK_FREE_ARRAY_TEMPLATE_ARGUMENTS
bool LOCK_FREE_ARRAY_TYPE::Contains(const ValueType& value) {
  cds::threading::Manager::attachThread();
  bool exists = false;
  auto it = lock_free_list.begin();
  while(it != lock_free_list.end()) {
    if (it->second == value) {
      exists = true;
    }
    ++it;
  }
  return exists;
}

// Explicit template instantiation
template class LockFreeArray<std::shared_ptr<oid_t>>;

template class LockFreeArray<std::shared_ptr<index::Index>>;

template class LockFreeArray<std::shared_ptr<storage::TileGroup>>;

template class LockFreeArray<std::shared_ptr<storage::Database>>;

template class LockFreeArray<std::shared_ptr<storage::IndirectionArray>>;

template class LockFreeArray<oid_t>;

}  // namespace peloton
