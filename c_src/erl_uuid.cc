#define BOOST_NO_EXCEPTIONS 1
#define BOOST_EXCEPTION_DISABLE 1

#include "erl_nif.h"

#include <boost/uuid/random_generator.hpp>

// Prototypes
static ERL_NIF_TERM erl_uuid_v4(ErlNifEnv* env, int argc,
                                const ERL_NIF_TERM argv[]);

static ErlNifFunc nif_funcs[] =
{
  {"v4", 0, erl_uuid_v4}
};

static ERL_NIF_TERM erl_uuid_v4(ErlNifEnv* env, int,
                                const ERL_NIF_TERM [])
{
  boost::uuids::basic_random_generator<boost::random::mt19937> gen;
  boost::uuids::uuid uuid = gen();

  ERL_NIF_TERM value_bin;
  unsigned char* value = enif_make_new_binary(env, 16, &value_bin);
  memcpy(value, &uuid, 16);

  return value_bin;
}

static int on_load(ErlNifEnv*, void**, ERL_NIF_TERM)
{
  return 0;
}

ERL_NIF_INIT(erl_uuid, nif_funcs, &on_load, NULL, NULL, NULL);

namespace
boost
    {
#ifdef BOOST_NO_EXCEPTIONS
    void throw_exception( std::exception const &) {}; // user defined
#else
    template <class E>
    void throw_exception( E const & e );
#endif
    }
