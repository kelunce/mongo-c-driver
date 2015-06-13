/*
 * Copyright 2015 MongoDB, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <bson.h>

#include "mongoc.h"

#include "mongoc-rpc-private.h"

struct _mock_server_t;  /* forward declaration */

typedef struct _request_t
{
   mongoc_rpc_t request_rpc;
   mongoc_opcode_t opcode;  /* copied from rpc for convenience */
   struct _mock_server_t *server;
   mongoc_stream_t *client;
   uint16_t client_port;
   bool is_command;
   char *command_name;
   char *as_str;
   mongoc_array_t docs;
} request_t;


request_t *request_new (const mongoc_rpc_t *request_rpc,
                        struct _mock_server_t *server,
                        mongoc_stream_t *client,
                        uint16_t client_port);

bool request_matches_query (const request_t *request,
                            const char *ns,
                            mongoc_query_flags_t flags,
                            uint32_t skip,
                            uint32_t n_return,
                            const char *query_json,
                            const char *fields_json,
                            bool is_command);

bool request_matches_kill_cursors (const request_t *request,
                                   int64_t cursor_id);

uint16_t request_get_server_port (request_t *request);

void request_destroy (request_t *request);

#endif //REQUEST_H