#!/bin/sh

cwd="$(dirname "$0")"

CC=cc
CFLAGS='-Wall -Werror -Wall -g'
LIBTEST=-I"$cwd"
LIBFT=-I"$cwd"/../libft

marker='Oh nuuuu!!! Leaks! OwO'

for file in "$cwd"/test_*.c; do
	name="${file##*/}"
	name="${file%%.c}"
	$CC $CFLAGS \
		"$LIBTEST" "$LIBFT" \
		"$cwd"/libtest.c "$cwd"/../libft/libft.a \
		"$file"	-o "$name"
	trap 'rm -f "$name"' EXIT
	logfile=$(mktemp)
	trap 'rm -f "$logfile"' EXIT
	# we need to use markers instead
	# of --error-exitcode since valgrind
	# does not exit with the specific exitcode
	# if the children have errors
	valgrind \
		--log-file="$logfile" \
		--trace-children=yes --show-leak-kinds=all \
		--error-markers="$marker" --leak-check=full ./"$name"
	if [ $? != 0 ] || grep -q "$marker" "$logfile"; then
		cat "$logfile" | \
			grep -v "$marker" | \
			sed 's/=\?==[0-9]\+\(== \)\?//g' | \
			grep -v 'rerun with: -s' | \
			tail +9 >&2
		echo "$name" failed :/ >&2
	fi
	rm "$name"
done
