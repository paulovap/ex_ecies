ERLANG_PATH = $(shell erl -eval 'io:format("~s", [lists:concat([code:root_dir(), "/erts-", erlang:system_info(version), "/include"])])' -s init stop -noshell)
CFLAGS = -g -O3 -ansi -pedantic -Wall -Wextra -I$(ERLANG_PATH) -I/usr/include
LDFLAGS += -L/usr/lib/x86_64-linux-gnu/ -lssl -lcrypto
ifneq ($(OS),Windows_NT)
	CFLAGS += -fPIC

	ifeq ($(shell uname),Darwin)
		LDFLAGS += -dynamiclib -undefined dynamic_lookup
	endif
endif

priv/lib_elixir_ecies.so: clean
	$(CC) $(CFLAGS) -o $@ c_src/secure.c c_src/keys.c c_src/ecies.c c_src/lib_elixir_ecies.c -shared $(LDFLAGS)

clean:
	$(RM) -r priv/*