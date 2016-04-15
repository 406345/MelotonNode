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
    //auto token  = TokenPool::Instance()->CheckToken( message->token() );

    //if ( token == nullptr )
    //{
    //    Logger::Error( "duplicate token(%) not found node:%" ,
    //                   message->token() ,
    //                   session->ip_address() );
    //    return -1;
    //}

    auto block = BlockHub::Instance()->FindBlock( message->index() );

    //if ( block == nullptr )
    //{
    //    Logger::Error( "duplicate block(%) not found node:%" ,
    //                   message->index()  ,
    //                   session->ip_address() );
    //    return -1;
    //}

    
    auto buf = BlockHub::Instance()->ReadBlock( block->Index ,
                                                message->offset() ,
                                                BLOCK_TRANSFER_SIZE );
    auto read_size = buf->Size(); 
    bool is_last   = false;

    if ( (message->offset() + read_size) == BLOCK_SIZE )
    {
        is_last = true;
    }

    if ( read_size < BLOCK_TRANSFER_SIZE )
    {
        is_last = true;
    }

    /*Logger::Log( "duplicate send block % offset % size % to %" ,
                 block->Index ,
                 message->offset() ,
                 buf->Size() ,
                 peer->ip_address() );*/

    uptr<MessageDuplicateData> reply = make_uptr( MessageDuplicateData );
    reply->set_data         ( buf->Data() , read_size );
    reply->set_sessionid    ( message->sessionid() );
    reply->set_checksum     ( 0 );
    reply->set_index        ( message->index() );
    reply->set_offset       ( message->offset() );
    reply->set_size         ( read_size );
    reply->set_token        ( "" );
    reply->set_islast       ( is_last );
    peer->SendMessage       ( move_ptr( reply ) );

    Logger::Log( "duplicate request block % offset % size % is_last % from %" ,
                 message->index() ,
                 message->offset() ,
                 read_size , 
                 is_last ,
                 peer->ip_address() );

    return 0;
}
