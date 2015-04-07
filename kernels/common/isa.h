// ======================================================================== //
// Copyright 2009-2015 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#define DECLARE_SYMBOL(type,name)                  \
  namespace isa   { extern type name; }            \
  namespace sse41 { extern type name; }                                 \
  namespace sse42 { extern type name; }                                 \
  namespace avx   { extern type name; }                                 \
  namespace avx2  { extern type name; }                                 \
  void name##_error() { std::cerr << "Error: " << TOSTRING(name) << " not supported by your CPU" << std::endl; } \
  type name((type)name##_error);

#define DECLARE_FUNCTION_SYMBOL(name)                  \
  namespace isa   { name; }            \
  namespace sse41 { name; }                                 \
  namespace avx   { name; }                                 \
  namespace avx2  { name; }                                

#define SELECT_SYMBOL_DEFAULT(features,intersector) \
  intersector = isa::intersector;

#define SELECT_SYMBOL_DEFAULT2(features,intersector,intersector2) \
  intersector = isa::intersector2;

#if defined(__SSE__)
#if !defined(__TARGET_SIMD4__)
#define __TARGET_SIMD4__
#endif
#endif

#if defined(__TARGET_SSE41__)
#define SELECT_SYMBOL_SSE41(features,intersector) \
  if ((features & SSE41) == SSE41) intersector = sse41::intersector;
#else
#define SELECT_SYMBOL_SSE41(features,intersector)
#endif

#if defined(__TARGET_SSE42__)
#define SELECT_SYMBOL_SSE42(features,intersector) \
  if ((features & SSE42) == SSE42) intersector = sse42::intersector;
#else
#define SELECT_SYMBOL_SSE42(features,intersector)
#endif

#if defined(__TARGET_AVX__)
#if !defined(__TARGET_SIMD8__)
#define __TARGET_SIMD8__
#endif
#define SELECT_SYMBOL_AVX(features,intersector) \
  if ((features & AVX) == AVX) intersector = avx::intersector;
#else
#define SELECT_SYMBOL_AVX(features,intersector)
#endif

#if defined(__TARGET_AVX2__)
#if !defined(__TARGET_SIMD8__)
#define __TARGET_SIMD8__
#endif
#define SELECT_SYMBOL_AVX2(features,intersector) \
  if ((features & AVX2) == AVX2) intersector = avx2::intersector;
#else
#define SELECT_SYMBOL_AVX2(features,intersector)
#endif

#if defined(__MIC__)
#if !defined(__TARGET_SIMD4__)
#define __TARGET_SIMD16__
#endif
#define SELECT_SYMBOL_KNC(features,intersector) \
  intersector = knc::intersector;
#else
#define SELECT_SYMBOL_KNC(features,intersector)
#endif

#define SELECT_SYMBOL_DEFAULT_SSE41(features,intersector) \
  SELECT_SYMBOL_DEFAULT(features,intersector);                                 \
  SELECT_SYMBOL_SSE41(features,intersector);                                  

#define SELECT_SYMBOL_DEFAULT_AVX(features,intersector) \
  SELECT_SYMBOL_DEFAULT(features,intersector);                     \
  SELECT_SYMBOL_AVX(features,intersector);                        

#define SELECT_SYMBOL_AVX_AVX2(features,intersector) \
  SELECT_SYMBOL_AVX(features,intersector);                         \
  SELECT_SYMBOL_AVX2(features,intersector);

#define SELECT_SYMBOL_DEFAULT_AVX_AVX2(features,intersector) \
  SELECT_SYMBOL_DEFAULT(features,intersector);                     \
  SELECT_SYMBOL_AVX(features,intersector);                         \
  SELECT_SYMBOL_AVX2(features,intersector);                       

#define SELECT_SYMBOL_SSE42_AVX_AVX2(features,intersector) \
  SELECT_SYMBOL_SSE42(features,intersector);                       \
  SELECT_SYMBOL_AVX(features,intersector);                         \
  SELECT_SYMBOL_AVX2(features,intersector);                       

#define SELECT_SYMBOL_DEFAULT_SSE41_AVX_AVX2(features,intersector) \
  SELECT_SYMBOL_DEFAULT(features,intersector);                     \
  SELECT_SYMBOL_SSE41(features,intersector);                       \
  SELECT_SYMBOL_AVX(features,intersector);                         \
  SELECT_SYMBOL_AVX2(features,intersector);                       

#define SELECT_SYMBOL_SSE42_AVX(features,intersector) \
  SELECT_SYMBOL_SSE42(features,intersector);                       \
  SELECT_SYMBOL_AVX(features,intersector);                        

#define SELECT_SYMBOL_DEFAULT_SSE41_AVX(features,intersector) \
  SELECT_SYMBOL_DEFAULT(features,intersector);                     \
  SELECT_SYMBOL_SSE41(features,intersector);                       \
  SELECT_SYMBOL_AVX(features,intersector);                        

