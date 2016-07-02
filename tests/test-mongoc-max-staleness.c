#include <mongoc.h>

#include "mongoc-client-private.h"

#include "TestSuite.h"

#undef MONGOC_LOG_DOMAIN
#define MONGOC_LOG_DOMAIN "client-test-max-staleness"


/* from max-staleness-tests.rst */
static void
test_mongoc_client_max_staleness (void)
{
   mongoc_client_t *client;
   int32_t max_staleness_ms;

   /* no maxStalenessMS with primary mode */
   ASSERT (!mongoc_client_new ("mongodb://a/?maxStalenessMS=120000"));
   ASSERT (!mongoc_client_new (
              "mongodb://a/?readPreference=primary&maxStalenessMS=120000"));

   client = mongoc_client_new (
      "mongodb://host/?readPreference=secondary&maxStalenessMS=120000");
   max_staleness_ms = mongoc_uri_get_option_as_int32 (
      mongoc_client_get_uri (client), "maxstalenessms", 0);
   ASSERT_CMPINT32 (120000, ==, max_staleness_ms);
   mongoc_client_destroy (client);

   client = mongoc_client_new (
      "mongodb://a/?readPreference=secondary&maxStalenessMS=1");
   max_staleness_ms = mongoc_uri_get_option_as_int32 (
      mongoc_client_get_uri (client), "maxstalenessms", 0);
   ASSERT_CMPINT32 (1, ==, max_staleness_ms);
   mongoc_client_destroy (client);
}


void
test_client_max_staleness_install (TestSuite *suite)
{
   TestSuite_Add (suite, "/Client/max_staleness",
                  test_mongoc_client_max_staleness);
}
