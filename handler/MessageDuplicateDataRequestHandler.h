/***********************************************************************************
This file is part of Project for Meloton
For the latest info, see  https://github.com/Yhgenomics/MelotonClient.git
Copyright 2016 Yhgenomics
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***********************************************************************************/

/***********************************************************************************
* Description   : MessageDuplicateDataRequest handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-04-08
* Modifed       : 2016-04-08      | Shubo Yang      | Create
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessageDuplicateDataRequest.pb.h>
#include <BlockHub.h>
#include <TokenPool.h>
#include <MessageDuplicateData.pb.h>
#include <MelotonSession.h>

static int MessageDuplicateDataRequestHandler( MRT::Session * session , uptr<MessageDuplicateDataRequest> message )
{
    auto peer   = scast<MelotonSession*>( session );
    auto token  = TokenPool::Instance()->CheckToken( message->token() );

    if ( token == nullptr )
    {
        return -1;
    }

    auto block = BlockHub::Instance()->FindBlock( token->Index() );

    if ( block == nullptr )
    {
        return -1;
    }

    auto buf = BlockHub::Instance()->ReadBlock( block->Index ,
                                                message->offset() ,
                                                BLOCK_TRANSFER_SIZE );

    uptr<MessageDuplicateData> reply = make_uptr( MessageDuplicateData );
    reply->set_data         ( buf->Data() , buf->Size() );
    reply->set_sessionid    ( message->sessionid() );
    reply->set_checksum     ( 0 );
    reply->set_index        ( message->index() );
    reply->set_offset       ( message->offset() );
    reply->set_size         ( buf->Size() );
    reply->set_token        ( message->token() );
    reply->set_islast       ( buf->Size() < BLOCK_TRANSFER_SIZE ? true : false );
    peer->SendMessage       ( move_ptr( reply ) );
                                    
    return 0;
}
