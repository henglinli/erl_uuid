#include "erl_nif.h"

static ErlNifResourceType* erl_uuid_RESOURCE = NULL;

typedef struct
{
} erl_uuid_handle;

// Prototypes
static ERL_NIF_TERM erl_uuid_new(ErlNifEnv* env, int argc,
                                   const ERL_NIF_TERM argv[]);
static ERL_NIF_TERM erl_uuid_myfunction(ErlNifEnv* env, int argc,
                                          const ERL_NIF_TERM argv[]);

static ErlNifFunc nif_funcs[] =
{
    {"new", 0, erl_uuid_new},
    {"myfunction", 1, erl_uuid_myfunction}
};

static ERL_NIF_TERM erl_uuid_new(ErlNifEnv* env, int argc,
                                   const ERL_NIF_TERM argv[])
{
    erl_uuid_handle* handle = enif_alloc_resource(erl_uuid_RESOURCE,
                                                    sizeof(erl_uuid_handle));
    ERL_NIF_TERM result = enif_make_resource(env, handle);
    enif_release_resource(handle);
    return enif_make_tuple2(env, enif_make_atom(env, "ok"), result);
}


static ERL_NIF_TERM erl_uuid_myfunction(ErlNifEnv* env, int argc,
                                          const ERL_NIF_TERM argv[])
{
    return enif_make_atom(env, "ok");
}

static void erl_uuid_resource_cleanup(ErlNifEnv* env, void* arg)
{
    /* Delete any dynamically allocated memory stored in erl_uuid_handle */
    /* erl_uuid_handle* handle = (erl_uuid_handle*)arg; */
}

static int on_load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info)
{
    ErlNifResourceFlags flags = ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER;
    ErlNifResourceType* rt = enif_open_resource_type(env, NULL,
                                                     "erl_uuid_resource",
                                                     &erl_uuid_resource_cleanup,
                                                     flags, NULL);
    if (rt == NULL)
        return -1;

    erl_uuid_RESOURCE = rt;

    return 0;
}

ERL_NIF_INIT(erl_uuid, nif_funcs, &on_load, NULL, NULL, NULL);