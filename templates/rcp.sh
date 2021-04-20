#!/usr/bin/env bash
#
# USAGE
#
#     ./rcp.sh <destination>
#
# DESCRIPTION
#
#     Copies a directory from source to destination using rsync's
#     include/exclude features.
#
# NOTE
#
#     A trailing slash on the source path copies the contents of the source
#     directory rather than the directory itself.
#
# INCLUDE/EXCLUDE MATCHING
#
#     Patterns starting with '/' are anchored to a particular spot in the
#     directory tree hierarchy.
#
#     Patterns ending with '/' only match directories.
#
# EXAMPLES
#
#     --filter='- *.o' excludes all matching names
#
#     --filter='- /foo' excludes the matching name in the transfer-root directory
#
#     --filter='- foo/' excludes all matching directories
#
#     --filter'+ foo/ + foo/bar.c - *' includes only foo/ and and foo/bar.c
#

# Template 1: Transfer root directory
rsync -av \
    --exclude="/${ROOT}/.git" \
    --exclude="/${ROOT}/resources" \
    ../abc $1

# Template 2: Transfer root directory contents
rsync -av \
    --exclude="/.git" \
    --exclude="/resources" \
    ../abc/ $1
