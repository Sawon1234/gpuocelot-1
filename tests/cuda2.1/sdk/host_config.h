/*
 * Copyright 1993-2009 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO USER:   
 *
 * This source code is subject to NVIDIA ownership rights under U.S. and 
 * international Copyright laws.  Users and possessors of this source code 
 * are hereby granted a nonexclusive, royalty-free license to use this code 
 * in individual and commercial software.
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE 
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR 
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH 
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF 
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL, 
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS 
 * OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE 
 * OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE 
 * OR PERFORMANCE OF THIS SOURCE CODE.  
 *
 * U.S. Government End Users.   This source code is a "commercial item" as 
 * that term is defined at  48 C.F.R. 2.101 (OCT 1995), consisting  of 
 * "commercial computer  software"  and "commercial computer software 
 * documentation" as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995) 
 * and is provided to the U.S. Government only as a commercial end item.  
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through 
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the 
 * source code with only those rights set forth herein. 
 *
 * Any use of this source code in individual and commercial software must 
 * include, in the user documentation and internal comments to the code,
 * the above Disclaimer and U.S. Government End Users Notice.
 */

#if !defined(__HOST_CONFIG_H__)
#define __HOST_CONFIG_H__

/*******************************************************************************
*                                                                              *
*                                                                              *
*                                                                              *
*******************************************************************************/

#if defined(__CUDACC__)

#if defined(__APPLE__)

#define _CRTIMP
#define __THROW

#if defined(__MULTI_CORE__)

#error multicore not supported for MacOs

#endif /* __MULTI_CORE__ */

#elif defined(__GNUC__)

#define _CRTIMP

#if defined(__MULTI_CORE__) && __GNUC__ > 3

#error multicore not supported for gcc 4.x

#endif /* __MULTI_CORE__ & __GNUC__ > 3 */

#include <features.h>       /* for __THROW */
#include <bits/c++config.h> /* for _GLIBCXX_ATOMIC_BUILTINS */

#if _GLIBCXX_ATOMIC_BUILTINS == 1

#undef _GLIBCXX_ATOMIC_BUILTINS /* for missing __sync_fetch_and_add */

#endif /* _GLIBCXX_ATOMIC_BUILTINS == 1 */

#elif defined(_WIN32)

#if defined(__MULTI_CORE__) && _MSC_VER != 1400

#error multicore support available only for VC8

#endif /* __MULTI_CORE__ & _MSC_VER != 1400 */

#if _MSC_VER >= 1500

#undef _USE_DECLSPECS_FOR_SAL
#define _USE_DECLSPECS_FOR_SAL \
        1

#endif /* _MSC_VER >= 1500 */

#if _MSC_VER >= 1400

#if !defined(_CRT_NONSTDC_NO_WARNINGS)

#define _CRT_NONSTDC_NO_WARNINGS /* to suppress warnings */

#endif /* _CRT_NONSTDC_NO_WARNINGS */

#if !defined(_CRT_SECURE_NO_WARNINGS)

#define _CRT_SECURE_NO_WARNINGS /* to suppress warnings */

#endif /* _CRT_SECURE_NO_WARNINGS */

#endif /* _MSC_VER >= 1400 */

#if !defined(NOMINMAX)

#define NOMINMAX /* min and max are part of cuda runtime */

#endif /* !NOMINMAX */

#include <crtdefs.h> /* for _CRTIMP */

#define __THROW

#endif /* __APPLE__ */

#endif /* __CUDACC__ */

#endif /* !__HOST_CONFIG_H__ */
