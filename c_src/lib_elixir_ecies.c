#include "erl_nif.h"

#include "ecies.h"

#include <openssl/err.h>
#include <openssl/ssl.h>

#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>

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
	ErlNifBinary keyBin;
	ErlNifBinary data;
	ErlNifBinary result;
    secure_t *out_secure = NULL;
	char *keyChar = NULL;
    uint64_t length;
    size_t i;

    if (argc != 2) {
        return enif_make_badarg(env);
    }

    if(!enif_inspect_binary(env, argv[0], &keyBin)){
        return enif_make_badarg(env);
    }

    if(!enif_inspect_binary(env, argv[1], &data)){
        return enif_make_badarg(env);
    }


    if (!(keyChar = (char*) malloc(sizeof(char)*(keyBin.size + 1)))) {
        return enif_make_badarg(env);
    }

    strncpy(keyChar, keyBin.data, keyBin.size);
    keyChar[keyBin.size] = '\0';

	if (!(out_secure = ecies_encrypt(keyChar, data.data, data.size))) {
        free(keyChar);
		return enif_make_badarg(env);
	}

    length = secure_total_length(out_secure);
    
    if (!enif_alloc_binary(length, &result)){
		secure_free(out_secure);
        free(keyChar);
		return enif_make_badarg(env);
	}

    for (i=0; i < length; i++)
        result.data[i] = out_secure[i];

    secure_free(out_secure);
    free(keyChar);
    return enif_make_binary(env, &result);
}

static ERL_NIF_TERM decrypt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    ErlNifBinary key;
    ErlNifBinary data;
    ErlNifBinary result;
    size_t length;
    char *keyChar = NULL;
    unsigned char *output;
    size_t i;

    if (argc != 2) {
        return enif_make_badarg(env);
    }

    if (!enif_inspect_binary(env, argv[0], &key)){
        return enif_make_badarg(env);
    }

    if (!enif_inspect_binary(env, argv[1], &data)){
        return enif_make_badarg(env);
    }

    if (!(keyChar = (char*) malloc(sizeof(char)*(key.size + 1)))) {
        return enif_make_badarg(env);
    }

    strncpy(keyChar, key.data, key.size);
    keyChar[key.size] = '\0';
    
    if (!(output = ecies_decrypt(keyChar, (secure_t*)data.data, &length))) {
        free(keyChar);
    	return enif_make_badarg(env);
    }

    if (!enif_alloc_binary(length, &result)){
        free(keyChar);
		free(output);
		return enif_make_badarg(env);
	}

    for (i=0; i < length; i++)
        result.data[i] = output[i];

    strncpy((char*)result.data, (char*)output, length);
    free(output);
    free(keyChar);
    return enif_make_binary(env, &result);
}
static ErlNifFunc nif_funcs[] =
{
  {"init_nif", 0, init_nif, 0},
  {"encrypt_nif", 2, encrypt_nif, 0},
  {"decrypt_nif", 2, decrypt_nif, 0}
};

ERL_NIF_INIT(Elixir.ExEcies, nif_funcs,NULL,NULL,NULL,NULL)
