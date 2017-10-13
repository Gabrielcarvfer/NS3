/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */

#ifndef NS3_DEPRECATED_H
#define NS3_DEPRECATED_H

/**
 * \file
 * \ingroup core
 * NS_DEPRECATED macro definition.
 */

/**
 * \ingroup core
 * \def NS_DEPRECATED
 * Mark a function as deprecated.
 *
 * Users should expect deprecated features to be removed eventually.
 *
 * When deprecating a feature, please update the documentation
 * with information for users on how to update their code.
 *
 * For example,
 * \snippet src/core/doc/deprecated-example.h doxygen snippet
 */

#if defined(__GNUC__)
/* Test for GCC >= 4.1 */
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100)
#if (GCC_VERSION >= 40100)
#define NS_DEPRECATED  __attribute__ ((deprecated))
#endif
#undef GCC_VERSION


#elif defined(__clang__) || defined(__llvm__)
#define NS_DEPRECATED  __attribute__ ((deprecated))

#elif defined(_MSC_VER)
#define NS_DEPRECATED __declspec(deprecated)

#else
#define NS_DEPRECATED
#endif

#endif /* NS3_DEPRECATED_H */
