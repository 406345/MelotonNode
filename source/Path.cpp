/***********************************************************************************
This file is part of Project for Meloton
For the latest info, see  https://github.com/Yhgenomics/MelotonMaster.git

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
* Description   :
* Creator       : Shubo Yang
* Date          :
* Modifed       : When      | Who       | What
***********************************************************************************/

#include <Path.h>
#include <MRT.h>

Path::Path( string path )
{
    this->original_path_ = path;
    this->ParsePath     ();
    this->ParseFilename ();
}

Path::Path( string path , string filename )
{
    this->original_path_        = path;
    this->original_filename_    = filename;
    this->filename_             = filename;
    this->ParsePath     ();
    this->ParseFilename ();
}

Path::Path( Path & path )
{
    this->filename_                     = path.filename_;
    this->filename_extention_           = path.filename_extention_;
    this->filename_without_extention_   = path.filename_without_extention_;
    this->original_filename_            = path.original_filename_;
    this->original_path_                = path.original_path_;

    this->path_list_ = vector<string>( path.path_list_ );
}

Path::Path( Path && path )
{
    this->filename_                     = path.filename_;
    this->filename_extention_           = path.filename_extention_;
    this->filename_without_extention_   = path.filename_without_extention_;
    this->original_filename_            = path.original_filename_;
    this->original_path_                = path.original_path_;

    this->path_list_ = vector<string>( path.path_list_ );
}

Path Path::operator=( Path & path )
{
    this->filename_                     = path.filename_;
    this->filename_extention_           = path.filename_extention_;
    this->filename_without_extention_   = path.filename_without_extention_;
    this->original_filename_            = path.original_filename_;
    this->original_path_                = path.original_path_;

    this->path_list_ = vector<string>( path.path_list_ );
    
    return *this;
}

Path Path::operator=( Path && path )
{
    this->filename_                     = path.filename_;
    this->filename_extention_           = path.filename_extention_;
    this->filename_without_extention_   = path.filename_without_extention_;
    this->original_filename_            = path.original_filename_;
    this->original_path_                = path.original_path_;

    this->path_list_ = vector<string>( path.path_list_ );
    
    return *this;
}

void Path::ParsePath()
{
    int index = 0;
    int last_spliter_pos = 0;

    /*if ( this->original_path_[0] != '/' )
    {
        this->original_path_ = "/" + this->original_path_;
    }
    else
    {
        this->path_list_.push_back( "/" );
    }*/

    for ( int pos = 0; pos < this->original_path_.size(); pos++ )
    {
        if ( this->original_path_[pos] == '/' )
        {
            if ( last_spliter_pos > this->original_path_.size() )
            {
                return;
            }

            if ( ( pos - last_spliter_pos ) >= this->original_path_.size() )
            {
                return;
            }

            auto fname =  this->original_path_.substr(
                last_spliter_pos ,
                pos - last_spliter_pos );

            this->path_list_.push_back( fname );
            last_spliter_pos = pos + 1;
        }
    }

    if ( last_spliter_pos >= this->original_path_.size() )
    {
        return;
    }

    if ( this->filename_.empty() )
    {
        this->filename_ =  this->original_path_.substr(
            last_spliter_pos ,
            this->original_path_.size() - last_spliter_pos );
    }
}

void Path::ParseFilename()
{
    for ( int i = scast<int>(this->filename_.size()) - 1; i > 0; i-- )
    {
        if ( this->filename_[i] == '.' )
        {
            this->filename_without_extention_ = this->filename_.substr( 0 , i );

            if ( ( this->filename_.size() - ( i + 1 ) ) > 0 )
                this->filename_extention_ = this->filename_.substr( i + 1 , this->filename_.size() - ( i + 1 ) );
            break;
        }
    }

    if ( this->filename_without_extention_.empty() )
    {
        this->filename_without_extention_ = this->filename_;
    }
}
