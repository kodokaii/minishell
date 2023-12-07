all: norm chforbid test

norm:
	@norminette *.c *.h | grep -v OK; [ $$? = 0 ] && exit 1 || :

ALLOWED_FUNCTIONS = \
					malloc free

chforbid:
	@chforbid/chforbid -a "$(ALLOWED_FUNCTIONS)" *.c

test:
	@tests/run_tests.sh

.PHONY: all norm chforbid test
