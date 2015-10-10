CFLAGS += -I@ERLANG_ROOT_DIR@/erts-@ERLANG_ERTS_VER@/include

LDFLAGS+= -lssl -lcrypto

all: priv/lib_elixir_ecies@LIBEXT@

priv/lib_elixir_ecies@LIBEXT@:
	mkdir -p priv
	$(CC) $(CFLAGS) -o $@ c_src/secure.c c_src/keys.c c_src/ecies.c c_src/lib_elixir_ecies.c -shared $(LDFLAGS)

clean:
	$(RM) -r priv/* COPYING INSTALL Makefile Makefile.in aclocal.m4
	$(RM) -r autom4te.cache/ compile config.guess config.h config.h.in config.log
	$(RM) -r config.status config.sub configure install-sh missing stamp-h1
