#include <BlockHub.h>
#include <Path.h>

void BlockHub::LoadIndex()
{
    int index = 0;
    this->index_file_.open( "index.dat" , ios::out | ios::in | ios::binary );

    if ( !this->index_file_.is_open() )
    {
        this->index_file_.open( "index.dat" , ios::binary | ios::out | ios::binary );
        this->index_file_.close();
        this->index_file_.open( "index.dat" , ios::out | ios::in | ios::binary );
        this->index_file_.seekg( 0 , this->data_file_.beg );
    }

    this->data_file_.open ( "block.dat" , ios::out | ios::in | ios::binary );

    if ( !this->data_file_.is_open() )
    {
        this->data_file_.open( "block.dat" , ios::out | ios::binary );
        this->data_file_.close();
        this->data_file_.open( "block.dat" , ios::out | ios::in | ios::binary );
        this->data_file_.seekg( 0 , this->data_file_.beg );
    }

    do 
    {
        auto bi = make_sptr( BlockIndex );
        index_file_.read( ( char* ) bi.get() , sizeof( BlockIndex ) );
        this->index_list_[index] = bi;

        if ( index_file_.gcount() == 0 )
            break;

        if( bi->Used == false )
        {
            this->empty_list_[this->block_empty_count_] = bi;
            ++this->block_empty_count_;
        }

        index++;
    }
    while ( true );

    this->index_file_.seekg( 0 , this->index_file_.beg );
    this->block_count_ = index; 
}

sptr<BlockIndex> BlockHub::FindBlock( size_t index )
{
    if ( index >= BLOCK_INDEX_ARRAY_SIZE )
        return nullptr;

    return this->index_list_[index];
}

sptr<BlockIndex> BlockHub::CreateBlock( int partId , size_t fileOffset , string path )
{
    sptr<BlockIndex> idx = nullptr;

    if ( this->block_empty_count_ > 0 )
    {
        idx = this->empty_list_[this->block_empty_count_ - 1];
        --this->block_empty_count_;
    }
    else
    {
        idx = make_sptr( BlockIndex ); 
        idx->Index = this->block_count_;
        this->index_list_[this->block_count_] = idx;
        ++this->block_count_;
    }
     
    idx->Used       = true;
    idx->FileOffset = fileOffset;
    idx->Location   = idx->Index * BLOCK_SIZE;
    idx->PartId     = partId;
    
    memcpy( idx->Path , path.c_str() , path.size() );
    SaveBlockIndex( idx );

    return idx;
}

bool BlockHub::RemoveBlock( size_t index )
{
    this->empty_list_[this->block_empty_count_]         = this->index_list_[index];
    this->empty_list_[this->block_empty_count_]->Used   = false;
    this->index_list_[index] = nullptr;
    ++this->block_empty_count_;

    return false;
}

size_t BlockHub::WriteBlock( int blockid , 
                             size_t offset , 
                             const char* data , 
                             size_t len )
{
    auto    block        =  this->index_list_[blockid];
    size_t  write_size   =  (offset + len) > BLOCK_SIZE ? 
                            (BLOCK_SIZE - offset + 1 ) : len;
    
    if ( block == nullptr )
        return 0;

    data_file_.seekg( block->Location + offset , data_file_.beg );
    data_file_.write( data , write_size );

    return write_size;
}

uptr<Buffer> BlockHub::ReadBlock( int blockid , 
                                  size_t offset ,
                                  size_t len )
{
    auto         block        = this->index_list_[blockid];
    size_t       read_size    = (offset + len) > BLOCK_SIZE ? 
                                (BLOCK_SIZE - offset + 1 ) : len;

    if ( block == nullptr )
        return nullptr;

    uptr<Buffer> result       = make_uptr( Buffer , read_size );

    data_file_.seekg( block->Location + offset , data_file_.beg );
    data_file_.read ( result->Data() , read_size );

    return move_ptr( result );
}

BlockHub::BlockHub()
{

}

BlockHub::~BlockHub()
{

}

void BlockHub::SaveBlockIndex( sptr<BlockIndex> block )
{
    auto block_instance = block.get();
    size_t pos          = block->Index * sizeof( BlockIndex );
    
    this->index_file_.seekg( pos , this->index_file_.beg );
    this->index_file_.write( ( char* ) block_instance , sizeof( BlockIndex ) );

    auto exp    = this->index_file_.exceptions();
    auto count  = this->index_file_.gcount();
}
