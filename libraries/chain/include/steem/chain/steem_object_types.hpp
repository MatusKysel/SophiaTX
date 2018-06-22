#pragma once
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>

#include <chainbase/chainbase.hpp>

#include <steem/protocol/types.hpp>
#include <steem/protocol/authority.hpp>


namespace steem { namespace chain {

namespace bip = chainbase::bip;
using namespace boost::multi_index;

using boost::multi_index_container;

using chainbase::object;
using chainbase::oid;
using chainbase::allocator;

using steem::protocol::block_id_type;
using steem::protocol::transaction_id_type;
using steem::protocol::chain_id_type;
using steem::protocol::account_name_type;
using steem::protocol::share_type;

typedef bip::basic_string< char, std::char_traits< char >, allocator< char > > shared_string;
inline std::string to_string( const shared_string& str ) { return std::string( str.begin(), str.end() ); }
inline void from_string( shared_string& out, const string& in ){ out.assign( in.begin(), in.end() ); }

struct by_id;

enum object_type
{
   dynamic_global_property_object_type,
   account_object_type,
   account_authority_object_type,
   witness_object_type,
   transaction_object_type,
   block_summary_object_type,
   witness_schedule_object_type,
   witness_vote_object_type,
   feed_history_object_type,
   operation_object_type,
   account_history_object_type,
   hardfork_property_object_type,
   owner_authority_history_object_type,
   account_recovery_request_object_type,
   change_recovery_account_request_object_type,
   escrow_object_type,
   reward_fund_object_type,
   economic_model_object_type,
   custom_content_object_type,
   application_object_type,
   account_fee_sponsor_object_type,
   application_buying_object_type,
#ifdef STEEM_ENABLE_SMT
   // SMT objects
   smt_token_object_type,
   account_regular_balance_object_type,
   account_rewards_balance_object_type
#endif
};

class dynamic_global_property_object;
class account_object;
class account_authority_object;
class witness_object;
class transaction_object;
class block_summary_object;
class witness_schedule_object;
class witness_vote_object;
class feed_history_object;
class operation_object;
class account_history_object;
class hardfork_property_object;
class owner_authority_history_object;
class account_recovery_request_object;
class change_recovery_account_request_object;
class escrow_object;
class reward_fund_object;
class economic_model_object;
class custom_content_object;
class application_object;
class account_fee_sponsor_object;
class application_buying_object;

#ifdef STEEM_ENABLE_SMT
class smt_token_object;
template < enum object_type ObjectType > class account_balance_object;
typedef account_balance_object< account_regular_balance_object_type > account_regular_balance_object;
typedef account_balance_object< account_rewards_balance_object_type > account_rewards_balance_object;
#endif

typedef oid< dynamic_global_property_object         > dynamic_global_property_id_type;
typedef oid< account_object                         > account_id_type;
typedef oid< account_authority_object               > account_authority_id_type;
typedef oid< witness_object                         > witness_id_type;
typedef oid< transaction_object                     > transaction_object_id_type;
typedef oid< block_summary_object                   > block_summary_id_type;
typedef oid< witness_schedule_object                > witness_schedule_id_type;
typedef oid< witness_vote_object                    > witness_vote_id_type;
typedef oid< feed_history_object                    > feed_history_id_type;
typedef oid< operation_object                       > operation_id_type;
typedef oid< account_history_object                 > account_history_id_type;
typedef oid< hardfork_property_object               > hardfork_property_id_type;
typedef oid< owner_authority_history_object         > owner_authority_history_id_type;
typedef oid< account_recovery_request_object        > account_recovery_request_id_type;
typedef oid< change_recovery_account_request_object > change_recovery_account_request_id_type;
typedef oid< escrow_object                          > escrow_id_type;
typedef oid< reward_fund_object                     > reward_fund_id_type;
typedef oid< economic_model_object                  > economic_model_id_type;
typedef oid< custom_content_object                  > custom_content_id_type;
typedef oid< application_object                     > application_id_type;
typedef oid< account_fee_sponsor_object             > account_fee_sponsor_id_type;
typedef oid< application_buying_object              > application_buying_id_type;

#ifdef STEEM_ENABLE_SMT
typedef oid< smt_token_object                       > smt_token_id_type;
typedef oid< account_regular_balance_object         > account_regular_balance_id_type;
typedef oid< account_rewards_balance_object         > account_rewards_balance_id_type;
#endif

enum bandwidth_type
{
   post,    ///< Rate limiting posting reward eligibility over time
   forum,   ///< Rate limiting for all forum related actins
   market   ///< Rate limiting for all other actions
};

} } //steem::chain

namespace fc
{
   class variant;
   inline void to_variant( const steem::chain::shared_string& s, variant& var )
   {
      var = fc::string( steem::chain::to_string( s ) );
   }

   inline void from_variant( const variant& var, steem::chain::shared_string& s )
   {
      auto str = var.as_string();
      s.assign( str.begin(), str.end() );
   }

   template<typename T>
   void to_variant( const chainbase::oid<T>& var,  variant& vo )
   {
      vo = var._id;
   }
   template<typename T>
   void from_variant( const variant& vo, chainbase::oid<T>& var )
   {
      var._id = vo.as_int64();
   }

   namespace raw {
      template<typename Stream, typename T>
      inline void pack( Stream& s, const chainbase::oid<T>& id )
      {
         s.write( (const char*)&id._id, sizeof(id._id) );
      }
      template<typename Stream, typename T>
      inline void unpack( Stream& s, chainbase::oid<T>& id )
      {
         s.read( (char*)&id._id, sizeof(id._id));
      }
   }
}

FC_REFLECT_ENUM( steem::chain::object_type,
                 (dynamic_global_property_object_type)
                 (account_object_type)
                 (account_authority_object_type)
                 (witness_object_type)
                 (transaction_object_type)
                 (block_summary_object_type)
                 (witness_schedule_object_type)
                 (witness_vote_object_type)
                 (feed_history_object_type)
                 (operation_object_type)
                 (account_history_object_type)
                 (hardfork_property_object_type)
                 (owner_authority_history_object_type)
                 (account_recovery_request_object_type)
                 (change_recovery_account_request_object_type)
                 (escrow_object_type)
                 (reward_fund_object_type)
                 (economic_model_object_type)
                 (custom_content_object_type)
                 (application_object_type)
                 (account_fee_sponsor_object_type)
                 (application_buying_object_type)
               )

FC_REFLECT_TYPENAME( steem::chain::shared_string )

FC_REFLECT_ENUM( steem::chain::bandwidth_type, (post)(forum)(market) )
