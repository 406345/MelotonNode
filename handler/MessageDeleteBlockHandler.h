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
* Description   : MessageDeleteBlock handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-04-13
* Modifed       : 2016-04-13      | Shubo Yang      | Create
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessageDeleteBlock.pb.h>
#include <MasterSession.h>
#include <BlockHub.h>
#include <MessageDeleteBlockACK.pb.h>

static int MessageDeleteBlockHandler( MRT::Session * session , uptr<MessageDeleteBlock> message )
{
    MasterSession* master = scast<MasterSession*>( session );

    if ( master != MasterSession::Instance() )
    {
        return -1;
    }

    auto index    = message->index();
    auto clientid = message->clientid();
    auto block    = BlockHub::Instance()->FindBlock( index );

    uptr<MessageDeleteBlockACK> msg = make_uptr( MessageDeleteBlockACK );
    msg->set_index      ( index );
    msg->set_clientid   ( clientid );
    msg->set_path       ( "" );
    
    if ( block == nullptr )
    {
        msg->set_code       ( 1 );
        msg->set_message    ( "block does not exist" );
    }
    
    msg->set_path( block->Path );

    if ( BlockHub::Instance()->RemoveBlock( index ) )
    {
        msg->set_code       ( 0 );
        msg->set_message    ( "" );
    }
    else
    {
        msg->set_code       ( 1 );
        msg->set_message    ( "index is out of range" );
    }
    
    master->SendMessage( move_ptr( msg ) );

    return 0;
}
