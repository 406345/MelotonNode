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
* Description   :
* Creator       : Shubo Yang
* Date          :
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef OBJECT_POOL_H_
#define OBJECT_POOL_H_

#include <vector>
#include <functional>

using std::vector;

template<class TYPE>
class ObjectPool
{
public:

    typedef std::function<bool( TYPE left , TYPE right )> CompareType;
    typedef std::function<bool( TYPE object )> FindType;
    typedef std::function<void( TYPE object )> EachType;
      
    void Push( TYPE instance )
    {
        pool.push_back( instance );
    };

    TYPE Pop ( TYPE instance )
    {
        for ( auto itr = this->pool.begin();
        itr != this->pool.end();
            ++itr )
        {
            if ( *itr == instance )
            {
                this->pool.erase( itr );
                return instance;
            }
        }

        return nullptr;
    };

    void Sort( int front , int end , CompareType callback )
    {
        int i = front , j = end;
        int temp = this->pool[front];//记录第一个数据  

        while ( i < j )
        {
            while ( i < j && callback( this->pool[j] , temp ) )  //与first数据比较，右边下标逐渐左移  
                j--;

            this->pool[i] = this->pool[j];

            while ( i < j && !callback( this->pool[i] , temp ) )  //与first数据比较，左边下标逐渐右移  
                i++;

            this->pool[j] = this->pool[i];
        }

        this->pool[i] = temp;                      //将first数据放置于i=j处  

        if ( front < (i - 1) )
            Sort( front , i - 1 , callback );

        if ( end > (i + 1) )
            Sort( i + 1 , end , callback );
    }

    // Sort the pool if left > right return true if left <= right return false;
    // @callback : use lamda expression to compare two objects
    //             bool( TYPE * left , TYPE * right ) 
    void Sort( CompareType callback )
    {
        if ( callback == nullptr )
            return;

        Sort( 0 , this->pool.size() - 1 , callback );
    }


    // Access all the object one by one
    // @callback : use lamda expression to access the object
    //             bool( TYPE * object )
    TYPE Find( FindType callback )
    {
        if ( callback == nullptr )
            return nullptr;

        for ( auto object : this->pool )
        {
            if ( callback( object ) )
            {
                return object;
            }
        }

        return nullptr;
    }

    // Find a object in pool 
    // return true if find the object
    // @callback : use lamda expression to select the object
    //             void( TYPE * object )
    void Each( EachType callback )
    {
        if ( callback == nullptr )
            return;

        for ( auto object : this->pool )
        {
            callback( object );
        }
    }

protected:

    vector<TYPE> pool;

    ObjectPool ()
    {

    };

    ~ObjectPool()
    {
        pool.clear();
    }

};

#endif // !OBJECT_POOL_H_