#pragma once
#include <appbase/application.hpp>

#include <sophiatx/plugins/chain/chain_plugin.hpp>
#include <sophiatx/plugins/json_rpc/json_rpc_plugin.hpp>

#define SOPHIATX_MPM_PLUGIN_NAME "custom_currencies"

namespace sophiatx { namespace plugins { namespace custom_currencies {

namespace detail { class custom_currencies_plugin_impl; }

using namespace appbase;

namespace detail
{
class custom_currencies_api_impl;
class custom_currencies_plugin_impl;
}



/**
 *  This plugin is designed to track a range of operations by account so that one node
 *  doesn't need to hold the full operation history in memory.
 */
class custom_currencies_plugin : public plugin< custom_currencies_plugin >
{
   friend class detail::custom_currencies_api_impl;
   friend class detail::custom_currencies_plugin_impl;
   public:
      custom_currencies_plugin();
      ~custom_currencies_plugin(){};

      APPBASE_PLUGIN_REQUIRES(
            (sophiatx::plugins::chain::chain_plugin)
            (sophiatx::plugins::json_rpc::json_rpc_plugin)
      )

      static const std::string& name() { static std::string name = SOPHIATX_MPM_PLUGIN_NAME; return name; }

      static void set_program_options(
         options_description& cli,
         options_description& cfg );
      virtual void plugin_initialize( const variables_map& options ) override;
      virtual void plugin_startup() override;
      virtual void plugin_shutdown() override;

      uint64_t app_id;
      std::shared_ptr< class custom_currencies_api > api;
   private:
      std::shared_ptr< detail::custom_currencies_plugin_impl > _my;
      std::map< sophiatx::protocol::public_key_type, fc::ecc::private_key > _private_keys;
      std::set< sophiatx::protocol::account_name_type >                     _accounts;
};

} } } //sophiatx::plugins::custom_currencies

