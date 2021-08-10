#pragma once


CAF_BEGIN_TYPE_ID_BLOCK(server_launcher, first_custom_type_id)

CAF_ADD_ATOM(server_launcher, send_to_client_atom)
CAF_ADD_ATOM(server_launcher, broadcast_atom)
CAF_ADD_ATOM(server_launcher, broadcast_notification_atom)
CAF_ADD_ATOM(server_launcher, send_and_broadcast_atom)

CAF_ADD_ATOM(server_launcher, chat_request_atom)

CAF_ADD_ATOM(server_launcher, login_request_atom)

CAF_END_TYPE_ID_BLOCK(server_launcher)
