/** Implementation of NSRegularExpression for GNUStep

   Copyright (C) 2010 Free Software Foundation, Inc.

   This file was part of the GNUstep Base Library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02111 USA.

   $Date: 2010-09-18 16:09:58 +0100 (Sat, 18 Sep 2010) $ $Revision: 31371 $
   */

#ifndef _GSBLOCKS_H

/* Define the has_feature pseudo-macro for GCC. */
#ifndef __has_feature 
#define __has_feature(x) 0
#endif

#if __has_feature(blocks)
/**
 * Defines a block type.  Will work whether or not the compiler natively
 * supports blocks.
 */
#define DEFINE_BLOCK_TYPE(name, retTy, argTys, ...) \
typedef retTy(^name)(argTys, ## __VA_ARGS__)
/**
 * Calls a block.  Works irrespective of whether the compiler supports blocks.
 */
#define CALL_BLOCK(block, args, ...) \
	block(args, ## __VA_ARGS__)
/* Fall-back versions for when the compiler doesn't have native blocks support.
 */
#else

#if (GCC_VERSION >= 3000)

#define DEFINE_BLOCK_TYPE(name, retTy, argTys, ...) \
	typedef struct {\
		void *isa;\
		int flags;\
		int reserved;\
		retTy (*invoke)(void*, argTys, ## __VA_ARGS__);\
	} *name
#define CALL_BLOCK(block, args, ...) \
	block->invoke(block, args, ## __VA_ARGS__)

#else /* GCC_VERSION >= 3000 */

#define DEFINE_BLOCK_TYPE(name, retTy, argTys, args...) \
	typedef struct {\
		void *isa;\
		int flags;\
		int reserved;\
		retTy (*invoke)(void*, argTys, args);\
	} *name
#define CALL_BLOCK(block, args...) \
	block->invoke(block, args)


#endif /* GCC_VERSION >= 3000 */

#endif

#define _GSBLOCKS_H
#endif