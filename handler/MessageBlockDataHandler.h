/***********************************************************************************
This file is part of Project for Meloton
For the latest info, see  https://github.com/Yhgenomics/MelotonNode.git
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
* Description   : MessageBlockData handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-03-22
* Modifed       : 2016-03-22      | Shubo Yang      | Create
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessageBlockData.pb.h>
#include <MessageBlockAccept.pb.h>
#include <TokenPool.h>
#include <BlockHub.h>
#include <ClientSession.h>
#include <MasterSession.h>
#include <MessageSyncBlock.pb.h>
#include <MessageBlockMeta.pb.h>
#include <MessageError.pb.h>
#include <ErrorCode.h>
#include <MessageNewBlock.pb.h>

static int MessageBlockDataHandler( MRT::Session * session , uptr<MessageBlockData> message )
{ 
    auto client = scast<ClientSession*>( session );
    auto token  = TokenPool::Instance()->CheckToken( message->token() );

    if ( token == nullptr )
    {
        // Invailed access, disconnect it
        auto error = make_uptr( MessageError );
        error->set_code( ERROR_BAD_TOKEN );
        error->set_message( "bad token" );
        client->SendMessage( move_ptr( error ) );

        return -1;
    }

    auto block = BlockHub::Instance()->FindBlock( token->Index() );
     
    // Check if the block exists
    if ( block == nullptr )
    {
        auto error = make_uptr( MessageError );
        error->set_code( ERROR_BLOCK_NOT_EXIST );
        error->set_message( "block is not exist" );
        client->SendMessage( move_ptr( error ) );
        return -1;
    } 

    size_t size   = message->size();
    size_t offset = message->offset();

    size = size > BLOCK_SIZE ? BLOCK_SIZE : size;
    size = ( offset + size ) > BLOCK_SIZE ? ( BLOCK_SIZE - offset ) : size;

    if ( size == 0 )
    {
        auto error = make_uptr( MessageError );
        error->set_code( ERROR_SIZE_NOT_AVAILABLE );
        error->set_message( "block size is not available" );
        client->SendMessage( move_ptr( error ) );
        return -1;
    }

    block->Size += BlockHub::Instance()->WriteBlock( block->Index ,
                                                     offset ,
                                                     message->data().c_str() ,
                                                     size );
    BlockHub::Instance()->SaveBlockIndex( block );
    //BlockHub::Instance()->SyncBlock( block );

    

    if ( message->islast() )
    {
        Logger::Log( "Accept Block path:% part:% size:% from %" , 
                     block->Path , 
                     block->Size ,
                     block->PartId ,
                     client->ip_address()
                     );

        auto sync = make_uptr   ( MessageBlockMeta );
        sync->set_fileoffset    ( block->FileOffset );
        sync->set_index         ( block->Index );
        sync->set_partid        ( block->PartId );
        sync->set_path          ( block->Path );
        sync->set_size          ( block->Size );
        sync->set_status        ( 0 );
        MasterSession::Instance ()->SendMessage( move_ptr( sync ) );

        // Duplicate Block
        auto new_block = make_uptr( MessageNewBlock );
        new_block->set_fileoffset ( block->FileOffset );
        new_block->set_index      ( block->Index );
        new_block->set_partid     ( block->PartId );
        new_block->set_path       ( block->Path );
        new_block->set_size       ( block->Size );
        new_block->set_status     ( 0 );
        new_block->set_token      ( TokenPool::Instance()->CreateToken( 0 , 
                                    block->Index ,
                                    TOKEN_EXPIRE_TIME ) );

        MasterSession::Instance()->SendMessage( move_ptr( new_block ) );
        return -1;
    }

    uptr<MessageBlockAccept> reply = make_uptr( MessageBlockAccept );
    reply->set_size         ( size );
    reply->set_token        ( token->TokenStr() );
    reply->set_checksum     ( 0 );
    reply->set_nextoffset   ( offset + size );
    reply->set_nextsize     ( BLOCK_TRANSFER_SIZE );
    client->SendMessage     ( move_ptr( reply ) );


    return 0;
}
