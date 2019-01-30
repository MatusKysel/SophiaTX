#include <appbase/application.hpp>

#include <sophiatx/plugins/block_api/block_api.hpp>
#include <sophiatx/plugins/block_api/block_api_plugin.hpp>

#include <sophiatx/protocol/get_config.hpp>

namespace sophiatx { namespace plugins { namespace block_api {

class block_api_impl
{
   public:
      block_api_impl(block_api_plugin& plugin);
      ~block_api_impl();

      DECLARE_API_IMPL(
         (get_block_header)
         (get_block)
      )

   std::shared_ptr<chain::database_interface> _db;
};

//////////////////////////////////////////////////////////////////////
//                                                                  //
// Constructors                                                     //
//                                                                  //
//////////////////////////////////////////////////////////////////////

block_api::block_api(block_api_plugin& plugin)
   : my( new block_api_impl(plugin) )
{
   JSON_RPC_REGISTER_API( SOPHIATX_BLOCK_API_PLUGIN_NAME, plugin.app() );
}

block_api::~block_api() {}

block_api_impl::block_api_impl(block_api_plugin& plugin)
   : _db( plugin.app()->get_plugin< sophiatx::plugins::chain::chain_plugin >().db() ) {}

block_api_impl::~block_api_impl() {}


//////////////////////////////////////////////////////////////////////
//                                                                  //
// Blocks and transactions                                          //
//                                                                  //
//////////////////////////////////////////////////////////////////////
DEFINE_API_IMPL( block_api_impl, get_block_header )
{
   get_block_header_return result;
   auto block = _db->fetch_block_by_number( args.block_num );

   if( block )
      result.header = *block;

   return result;
}

DEFINE_API_IMPL( block_api_impl, get_block )
{
   get_block_return result;
   auto block = _db->fetch_block_by_number( args.block_num );

   if( block )
      result.block = *block;

   return result;
}

DEFINE_READ_APIS( block_api,
   (get_block_header)
   (get_block)
)

} } } // sophiatx::plugins::block_api
