#include "erl_nif.h"

#include "ecies.h"

#include <openssl/err.h>
#include <openssl/ssl.h>

#include <stdio.h>
#include <strings.h>
#include <unistd.h>

static ERL_NIF_TERM init_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    (void)argc;
    (void)argv;
    SSL_library_init();
    SSL_load_error_strings();
    ecies_group_init();
    return enif_make_atom(env, "ok");
}
static ERL_NIF_TERM encrypt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
	ErlNifBinary key;
	ErlNifBinary data;
	ErlNifBinary result;
	secure_t *out_secure = NULL;
	uint64_t length;
    if (argc != 2) {
        return enif_make_badarg(env);
    }

    if(!enif_inspect_binary(env, argv[0], &key)){
        return enif_make_badarg(env);
    }
    key.data[key.size] = '\0';

    if(!enif_inspect_binary(env, argv[1], &data)){
        return enif_make_badarg(env);
    }
    data.data[data.size] = '\0';

	if (!(out_secure = ecies_encrypt((const char*)key.data, data.data, data.size))) {
		return enif_make_badarg(env);
	}

    length = secure_total_length(out_secure);

	if (!enif_alloc_binary(length, &result)){
		secure_free(out_secure);
		return enif_make_badarg(env);
	}

    strncpy((char*)result.data, (const char*)out_secure, length);
    secure_free(out_secure);
    return enif_make_binary(env, &result);
}

static ERL_NIF_TERM decrypt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    ErlNifBinary key;
    ErlNifBinary data;
    ErlNifBinary result;
    size_t length;
    unsigned char *output;

    if (argc != 2) {
        return enif_make_badarg(env);
    }

    if(!enif_inspect_binary(env, argv[0], &key)){
        return enif_make_badarg(env);
    }
    key.data[key.size] = '\0';



    if(!enif_inspect_binary(env, argv[1], &data)){
        return enif_make_badarg(env);
    }
  data.data[data.size] = '\0';


    if(!(output = ecies_decrypt((const char*)key.data, (secure_t*)data.data, &length))) {
    	return enif_make_badarg(env);
    }

    if (!enif_alloc_binary(length, &result)){
		free(output);
		return enif_make_badarg(env);
	}

    strncpy((char*)result.data, (char*)output, length);
    free(output);

    return enif_make_binary(env, &result);
}
static ErlNifFunc nif_funcs[] =
{
  {"init_nif", 0, init_nif, 0},
  {"encrypt_nif", 2, encrypt_nif, 0},
  {"decrypt_nif", 2, decrypt_nif, 0}
};

ERL_NIF_INIT(Elixir.ExEcies, nif_funcs,NULL,NULL,NULL,NULL)
