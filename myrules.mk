ifneq ($(CORRECTION),1)
all: norm chforbid
endif

FILES = \
	builtins/*.c \
	parsing/*.c \
	parsing/*.h \
	*.h *.c

ALLOWED_FUNCTIONS = \
					readline rl_clear_history rl_on_new_line \
					rl_replace_line rl_redisplay add_history \
					printf malloc free write access open read \
					close fork wait waitpid wait3 wait4 signal \
					sigaction sigemptyset sigaddset kill exit \
					getcwd chdir stat lstat fstat unlink execve \
					dup dup2 pipe opendir readdir closedir \
					strerror perror isatty ttyname ttyslot ioctl \
					getenv tcsetattr tcgetattr tgetent tgetflag \
					tgetnum tgetstr tgoto tputs

norm:
	@norminette $(FILES) *.h | grep -v OK; [ $$? = 0 ] && exit 1 || :

chforbid:
	@chforbid/chforbid -a "$(ALLOWED_FUNCTIONS)" $(FILES)

test: all
	@tests/run_tests.sh

setup:
	pip install tree_sitter
	git submodule update --init --recursive

.PHONY: all norm chforbid test setup
