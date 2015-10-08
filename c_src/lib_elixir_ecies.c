#include "erl_nif.h"

#include <openssl/err.h>
#include <openssl/ssl.h>

#include <stdio.h>
#include <strings.h>
#include <unistd.h>

static ERL_NIF_TERM encrypt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
	ErlNifBinary key;
	ErlNifBinary data;
	ErlNifBinary result;

    if (argc != 2) {
        return enif_make_badarg(env);
    }

    if(!enif_inspect_binary(env, argv[0], &key)){
        return enif_make_badarg(env);
    }

    if(!enif_inspect_binary(env, argv[1], &data)){
        return enif_make_badarg(env);
    }

    return enif_make_string(env, "Hello world!", ERL_NIF_LATIN1);
}

static ERL_NIF_TERM decrypt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    ErlNifBinary key;
    ErlNifBinary data;
    ErlNifBinary result;

    if (argc != 2) {
        return enif_make_badarg(env);
    }

    if(!enif_inspect_binary(env, argv[0], &key)){
        return enif_make_badarg(env);
    }

    if(!enif_inspect_binary(env, argv[1], &data)){
        return enif_make_badarg(env);
    }
    return enif_make_string(env, "Hello world!", ERL_NIF_LATIN1);
}
static ErlNifFunc nif_funcs[] =
{
  {"encrypt", 2, encrypt_nif},
  {"decrypt", 2, decrypt_nif}
};

ERL_NIF_INIT(Elixir.ExEcies, nif_funcs,NULL,NULL,NULL,NULL)