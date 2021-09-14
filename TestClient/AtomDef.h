#pragma once


CAF_BEGIN_TYPE_ID_BLOCK(test_client, first_custom_type_id)

CAF_ADD_ATOM(test_client, send_to_server_atom)

CAF_ADD_ATOM(test_client, chat_request_atom)
CAF_ADD_ATOM(test_client, chat_response_atom)
CAF_ADD_ATOM(test_client, chat_notification_atom)

CAF_ADD_ATOM(test_client, login_request_atom)
CAF_ADD_ATOM(test_client, login_response_atom)

CAF_ADD_ATOM(test_client, character_create_request_atom)
CAF_ADD_ATOM(test_client, character_create_response_atom)
CAF_ADD_ATOM(test_client, character_delete_request_atom)
CAF_ADD_ATOM(test_client, character_delete_response_atom)
CAF_ADD_ATOM(test_client, character_select_request_atom)
CAF_ADD_ATOM(test_client, character_select_response_atom)

CAF_ADD_ATOM(test_client, ingame_enter_request_atom)
CAF_ADD_ATOM(test_client, ingame_enter_response_atom)

CAF_ADD_ATOM(test_client, position_move_request_atom)
CAF_ADD_ATOM(test_client, position_move_response_atom)


CAF_ADD_TYPE_ID(test_client, (wzbgame::model::Position))

CAF_END_TYPE_ID_BLOCK(test_client)
