#pragma once
#include <sophiatx/chain/account_object.hpp>
#include <sophiatx/chain/block_summary_object.hpp>
#include <sophiatx/chain/global_property_object.hpp>
#include <sophiatx/chain/history_object.hpp>
#include <sophiatx/chain/sophiatx_objects.hpp>
#include <sophiatx/chain/transaction_object.hpp>
#include <sophiatx/chain/witness_objects.hpp>
#include <sophiatx/chain/database/database_interface.hpp>

namespace sophiatx { namespace plugins { namespace block_api {

using namespace sophiatx::chain;

struct api_signed_block_object : public signed_block
{
   api_signed_block_object( const signed_block& block ) : signed_block( block )
   {
      block_id = id();
      signing_key = signee();
      transaction_ids.reserve( transactions.size() );
      for( const signed_transaction& tx : transactions )
         transaction_ids.push_back( tx.id() );
   }
   api_signed_block_object() {}

   block_id_type                 block_id;
   public_key_type               signing_key;
   vector< transaction_id_type > transaction_ids;
};

} } } // sophiatx::plugins::database_api

FC_REFLECT_DERIVED( sophiatx::plugins::block_api::api_signed_block_object, (sophiatx::protocol::signed_block),
                     (block_id)
                     (signing_key)
                     (transaction_ids)
                  )
