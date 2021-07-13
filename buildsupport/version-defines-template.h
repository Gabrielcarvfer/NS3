/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2018 Lawrence Livermore National Laboratory
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
 * Authors: Mathew Bielejeski <bielejeski1@llnl.gov>
 */

#ifndef NS3_VERSION_DEFINES_H_
#define NS3_VERSION_DEFINES_H_

/**
  * \file
  * \ingroup buildversion
  * Defines the macro values for printing the build version.
  * These will be populated by the build system.
  */

/**
  * \ingroup buildversion
  * @{
  */

/**
 * The first tag found which matches the pattern ns-3*.
 *
 * The expected format of the ns-3 version tag is: ns-3.<minor>[.patch][-release_candidate]
 *
 * The tag is found by starting at the tip of the current branch and walking
 * back towards the root.
 *
 * Type: string literal
 */
#cmakedefine NS3_VERSION_TAG "@NS3_VERSION_TAG@"

/**
 * The tag closest to the tip of the current branch
 *
 * The tag is found by starting at the tip of the current branch and
 * walking back towards the root.
 *
 * This value will be the same as #NS3_VERSION_TAG when #NS3_VERSION_TAG is
 * the closest tag.
 *
 * Type: string literal
 */
#cmakedefine NS3_VERSION_CLOSEST_TAG "@NS3_VERSION_CLOSEST_TAG@"

/**
 * The major version extracted from #NS3_VERSION_TAG
 *
 * For a tag with the format ns-<digit>.<digit>[.digit], the major
 * version is the number after ns- and before the first period.
 *
 * Type: integer
 */
#cmakedefine NS3_VERSION_MAJOR @NS3_VERSION_MAJOR@

/**
 * The minor version extracted from #NS3_VERSION_TAG
 *
 * For a tag with the format ns-<digit>.<digit>[.digit], the minor
 * version is the number after the first period.
 *
 * Type: integer
 */
#cmakedefine NS3_VERSION_MINOR @NS3_VERSION_MINOR@

/**
 * The patch number extracted from #NS3_VERSION_TAG
 *
 * For a tag with the format ns-<digit>.<digit>[.digit], the patch
 * is the number after the last period.
 *
 * The patch value is optional and may not be present in the tag.
 * In cases where the patch value is not present, the field will be set to 0
 *
 * Type: integer
 */
#cmakedefine NS3_VERSION_PATCH @NS3_VERSION_PATCH@

/**
 * The portion of the #NS3_VERSION_TAG indicating the version
 * of the release candidate (if applicable).
 *
 * In order for this field to contain a value, the #NS3_VERSION_TAG
 * must have the format ns-<digit>.<digit>[.digit][-RC<digit>].
 * The contents of the release candidate will be the RC<digit>
 * portion of the tag.
 *
 * Type: string literal
 */
#cmakedefine NS3_VERSION_RELEASE_CANDIDATE "@NS3_VERSION_RELEASE_CANDIDATE@"

/**
 * The number of repository commits between #NS3_VERSION_CLOSEST_TAG
 * and the branch HEAD.
 *
 * Type: integer
 */
#cmakedefine NS3_VERSION_TAG_DISTANCE @NS3_VERSION_TAG_DISTANCE@

/**
 * Hash value which uniquely identifies the commit of the
 * branch HEAD.
 * The first character of the commit hash is 'g' to indicate this hash is
 * a git hash
 *
 * Type: string literal
 */
#cmakedefine NS3_VERSION_COMMIT_HASH "@NS3_VERSION_COMMIT_HASH@"

/**
 * Flag indicating whether the repository working tree had uncommitted
 * changes when the library was built.
 *
 * The flag will be 1 if there were uncommitted changes, 0 otherwise.
 *
 * Type: integer
 */
#cmakedefine01 NS3_VERSION_DIRTY_FLAG

/**
 * Indicates the build profile that was specified by the --build-profile option
 * of "waf configure"
 *
 * Type: string literal
 */
#cmakedefine NS3_VERSION_BUILD_PROFILE "@NS3_VERSION_BUILD_PROFILE@"

/** @} */

#endif
