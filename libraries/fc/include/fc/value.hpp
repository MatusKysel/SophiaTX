#pragma once

#include <fc/string.hpp>
#include <fc/vector.hpp>
#include <fc/aligned.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace fc {
    template<BOOST_PP_ENUM_PARAMS(9, typename A)> struct tuple;

    /**
     *  @brief a dynamic container that can hold
     *  integers, reals, strings, booleans, arrays, and
     *  or null.   
     *
     *  This type serves as an intermediate representation between
     *  C++ type and serialized type (JSON,XML,etc).  
     *
     *  As much as possible value attempts to preserve 'type' information, but
     *  type information is not always provided equally by all serialization formats.
     *
     *  value is move aware, so move it when you can to avoid expensive copies
     */
    class value {
      public:
        struct key_val;
        struct object {
          typedef fc::vector<key_val>::const_iterator const_iterator;
          //fc::string           type;
          fc::vector<key_val>  fields;
        };
        struct array {
          array( size_t s = 0 ):fields(s){}
          //fc::string           type;
          fc::vector<value>    fields;
        };

        struct const_visitor {
          virtual void operator()( const int8_t& v      ){};
          virtual void operator()( const int16_t& v     ){};
          virtual void operator()( const int32_t& v     ){};
          virtual void operator()( const int64_t& v     ){};
          virtual void operator()( const uint8_t& v     ){};
          virtual void operator()( const uint16_t& v    ){};
          virtual void operator()( const uint32_t& v    ){};
          virtual void operator()( const uint64_t& v    ){};
          virtual void operator()( const float& v       ){};
          virtual void operator()( const double& v      ){};
          virtual void operator()( const bool& v        ){};
          virtual void operator()( const fc::string& v  ){};
          virtual void operator()( const object&  ){};
          virtual void operator()( const array&  ){};
          virtual void operator()( ){};
        };

        value();
        value( value&& m );
        value( const value& m );

        value( char* c );
        value( int8_t );
        value( int16_t );
        value( int32_t );
        value( int64_t );
        value( uint8_t );
        value( uint16_t );
        value( uint32_t );
        value( uint64_t );
        value( double );
        value( float );
        value( bool );
        value( fc::string&& );
        value( fc::string& );
        value( const fc::string& );

        value( object&& o );
        value( const object& o );
        value( object& o );

        value( array&& a );
        value( array& a );
        value( const array& a );

        ~value();

        value& operator=( value&& v );
        value& operator=( const value& v );
        value& operator=( value& v );


        /**
         *  Include fc/value_cast.hpp for implementation
         */
        template<typename T>
        explicit value( T&& v );

        template<typename T>
        value& operator=( T&& v ) {
          value tmp(fc::forward<T>(v) );
          fc_swap(*this,tmp);
          return *this;
        }

        /** used to iterate over object fields, use array index + size to iterate over array */
        object::const_iterator find( const char* key )const;
        object::const_iterator begin()const;
        object::const_iterator end()const;

        /** avoid creating temporary string just for comparisons! **/
        value&       operator[]( const char* key );
        const value& operator[]( const char* key )const;
        value&       operator[]( const fc::string& key );
        const value& operator[]( const fc::string& key )const;

        /** array & object interface **/
        void         clear();
        size_t       size()const;

        /** array interface **/
        void         resize( size_t s );
        void         reserve( size_t s );
        void         push_back( value&& v );
        value&       operator[]( int32_t idx );
        const value& operator[]( int32_t idx )const;

        /** gets the stored type **/
        const char*  type()const;
        bool         is_null()const;

        void         visit( const_visitor&& v )const;

        /*  sets the subkey key with v and return *this */
        value&       set( const char* key,       fc::value v );
        value&       set( const fc::string& key, fc::value v );

        template<typename S, typename T>
        value&       set( S&& key, T&& v ) { return set( fc::forward<S>(key), fc::value( fc::forward<T>(v) ) ); }

      private:
        /** throws exceptions on errors 
         *
         *  Defined in fc/value_cast.hpp because it depends upon
         *  reflection
         */
        template<typename T>
        friend T value_cast( const value& v );

        aligned<24> holder;
    };
    bool operator == ( const value& v, std::nullptr_t );
    bool operator != ( const value& v, std::nullptr_t );

    struct value::key_val {
       key_val(){};
       
       key_val( fc::string k, value v = value())
       :key(fc::move(k)),val(fc::move(v)){}
       
       key_val( key_val&& m )
       :key(fc::move(m.key)),val(fc::move(m.val)){}
       
       key_val( const key_val& m )
       :key(m.key),val(m.val){}
       
       key_val& operator=( key_val&& k ) {
         key = fc::move(k.key);
         val = fc::move(k.val);
         return *this;
       }
       key_val& operator=( const key_val& k ) {
         key = k.key;
         val = k.val;
         return *this;
       }
       
       fc::string key;
       value      val;
    };

} // namespace fc

