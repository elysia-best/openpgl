// Copyright 2009-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include "alloc.h"
#include "intrinsics.h"


////////////////////////////////////////////////////////////////////////////////
/// All Platforms
////////////////////////////////////////////////////////////////////////////////
  
namespace embree
{
  void* alignedMalloc(size_t size, size_t align) 
  {
    if (size == 0)
      return nullptr;
    
    assert((align & (align-1)) == 0);
#ifndef __loongarch__
    void* ptr = _mm_malloc(size,align);
#else
    void* ptr = aligned_alloc (align, size);
#endif

    if (size != 0 && ptr == nullptr)
      throw std::bad_alloc();
    
    return ptr;
  }
  
  void alignedFree(void* ptr)
  {
    if (ptr)
#ifndef __loongarch__
       _mm_free(ptr);
#else
        free(ptr);
#endif
  }
}

